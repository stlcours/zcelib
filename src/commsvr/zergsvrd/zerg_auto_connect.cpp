
#include "zerg_predefine.h"
#include "zerg_auto_connect.h"
#include "zerg_application.h"
#include "zerg_tcp_ctrl_handler.h"
#include "zerg_configure.h"


/****************************************************************************************************
class Zerg_Auto_Connector
****************************************************************************************************/
Zerg_Auto_Connector::Zerg_Auto_Connector()
{
}
//
Zerg_Auto_Connector::~Zerg_Auto_Connector()
{
}

//ȡ��������Ϣ
int Zerg_Auto_Connector::get_config(const Zerg_Server_Config *config)
{
    int ret = 0;

    zerg_svr_cfg_ = config;

    size_of_autoconnect_ = config->zerg_cfg_data_.auto_connect_num_;
    //��Ԥ�������
    autocnt_svcinfo_set_.rehash(size_of_autoconnect_ + 16);

    //ѭ���������е�����
    SERVICES_INFO svc_route;
    for (size_t i = 0; i < size_of_autoconnect_; ++i)
    {

        svc_route.svc_id_ = config->zerg_cfg_data_.auto_connect_svrs_[i];

        //�ҵ���ص�IP����
        ret = config->get_svcinfo_by_svcid(svc_route.svc_id_,
                                           svc_route);

        //�����ѯ����
        if (ret != 0)
        {
            ZCE_LOGMSG(RS_ERROR, "[zergsvr] Can't find Auto connect services ID %u.%u .Please check config file. ",
                       svc_route.svc_id_.services_type_,
                       svc_route.svc_id_.services_id_);
            return SOAR_RET::ERR_ZERG_CONNECT_NO_FIND_SVCINFO;
        }

        auto ins_iter = autocnt_svcinfo_set_.insert(svc_route);
        if (ins_iter.second == false)
        {
            ZCE_LOGMSG(RS_ERROR, "[zergsvr] Can't insert auto connect services ID %u.%u "
                       "into set .Please check config file. ",
                       svc_route.svc_id_.services_type_,
                       svc_route.svc_id_.services_id_);
            return SOAR_RET::ERR_ZERG_CONNECT_REPEAT_SVCID;
        }


        //���ڸ�����C/C++�ķ��ؾ�ָ̬������⣬���Ҫ���������ַ������ֻ���ȴ�ӡ�������ط�
        const size_t TMP_ADDR_LEN = 32;
        char mainroute_addr[TMP_ADDR_LEN + 1];

        ZCE_LOGMSG(RS_INFO, "[zergsvr] Add one auto connect data, main route services id[%u|%u] ip[%s|%u].",
                   svc_route.svc_id_.services_type_,
                   svc_route.svc_id_.services_id_,
                   svc_route.ip_address_.get_host_addr(mainroute_addr, TMP_ADDR_LEN),
                   svc_route.ip_address_.get_port_number()
                  );

        auto map_iter = type_to_idary_map_.find(svc_route.svc_id_.services_type_);
        if (type_to_idary_map_.end() == map_iter)
        {
            std::vector<uint32_t> id_ary;
            auto insert_iter = type_to_idary_map_.insert(
                                   std::make_pair(svc_route.svc_id_.services_type_, id_ary));
            //�����ϳ��ǿռ䲻�㣬������ʧ��
            ZCE_ASSERT(false == insert_iter.second);

            map_iter = insert_iter.first;
            map_iter->second.reserve(size_of_autoconnect_ + 16);
        }
        std::vector<uint32_t> *ptr_ary = &(map_iter->second);
        ptr_ary->push_back(svc_route.svc_id_.services_id_);
    }

    ZCE_LOGMSG(RS_INFO, "[zergsvr] Get number [%lu] auto connect config success.",
               size_of_autoconnect_);

    return 0;
}


//�������еķ�����,����Ѿ������ӣ�������,
void Zerg_Auto_Connector::reconnect_allserver(size_t &szvalid, size_t &szsucc, size_t &szfail)
{
    int ret = 0;
    szvalid = szsucc = szfail = 0;
    //ѭ�������е�SERVER����һ��,����д�ĺ��ƿ�

    auto iter_end = autocnt_svcinfo_set_.end();
    auto iter_tmp = autocnt_svcinfo_set_.begin();
    for (; iter_tmp != iter_end; ++iter_tmp)
    {
        TCP_Svc_Handler *svchandle = NULL;
        //����Ѿ�����Ӧ�������ˣ�����
        ret = TCP_Svc_Handler::find_services_peer(iter_tmp->svc_id_, svchandle);

        if (0 != ret)
        {
            //��������,
            ret = connect_server_bysvcid(iter_tmp->svc_id_, iter_tmp->ip_address_);

            if (ret == 0)
            {
                ++szsucc;
            }
            else
            {
                ++szfail;
            }
        }
        else
        {
            ++szvalid;

            //����Ǽ���״̬�Ž�������������
            if (svchandle->get_peer_status() == TCP_Svc_Handler::PEER_STATUS_ACTIVE)
            {
                svchandle->send_zergheatbeat_reg();
            }
        }
    }

    ZCE_LOGMSG(RS_INFO, "[zergsvr] Auto NONBLOCK connect server,vaild number:%d ,success Number :%d,fail number:%d .",
               szvalid,
               szsucc,
               szfail);
    return;
}


//����SVC ID,����Ƿ����������ӵķ���.,
int Zerg_Auto_Connector::reconnect_server(const SERVICES_ID &reconnect_svcid)
{

    //�����SET�����Ҳ���
    SERVICES_INFO svc_info;
    svc_info.svc_id_ = reconnect_svcid;
    auto iter = autocnt_svcinfo_set_.find(svc_info);

    //������������¼,���������SVCID��������Ҫ�������ӵķ�����
    if (iter == autocnt_svcinfo_set_.end())
    {
        return SOAR_RET::ERR_ZERG_ISNOT_CONNECT_SERVICES;
    }

    return connect_server_bysvcid(reconnect_svcid, iter->ip_address_);
}


//����SVRINFO+IP,����Ƿ����������ӵķ���.����������
int Zerg_Auto_Connector::connect_server_bysvcid(const SERVICES_ID &svrinfo, const ZCE_Sockaddr_In     &inetaddr)
{
    ZCE_LOGMSG(RS_DEBUG, "[zergsvr] Try NONBLOCK connect services[%u|%u] IP|Port :[%s|%u] .",
               svrinfo.services_type_,
               svrinfo.services_id_,
               inetaddr.get_host_addr(),
               inetaddr.get_port_number()
              );

    ZCE_Socket_Stream sockstream;
    sockstream.open();

    const socklen_t opval = ZERG_SND_RCV_BUF_OPVAL;
    socklen_t opvallen = sizeof(socklen_t);
    //����һ��SND,RCV BUFFER,
    sockstream.setsockopt(SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const void *>(&opval), opvallen);
    sockstream.setsockopt(SOL_SOCKET, SO_SNDBUF, reinterpret_cast<const void *>(&opval), opvallen);

    //tcpscoket.sock_enable (O_NONBLOCK);

    //��ס,�����ʱ���־ʹSOCKET�첽����,��3������true��ʾ�Ƿ�����
    int ret = zerg_connector_.connect(sockstream, &inetaddr, true);

    //��Ȼʧ��!?
    if (ret < 0)
    {
        //����UNIX������ V1��˵���� EINPROGRESS,��ACE�Ľ���˵�� EWOULDBLOCK,
        if (ZCE_LIB::last_error() != EWOULDBLOCK && ZCE_LIB::last_error() != EINPROGRESS)
        {
            sockstream.close();
            return SOAR_RET::ERR_ZERG_FAIL_SOCKET_OP_ERROR;
        }


        //HANDLER_MODE_CONNECTģʽ���۲���ʧ��
        TCP_Svc_Handler *p_handler = TCP_Svc_Handler::alloce_hdl_from_pool(
                                         TCP_Svc_Handler::HANDLER_MODE_CONNECT);
        ZCE_ASSERT(p_handler);
        //��self_svc_info��ȥ��������������.
        p_handler->init_tcpsvr_handler(zerg_svr_cfg_->self_svc_id_,
                                       svrinfo,
                                       sockstream,
                                       inetaddr);

        //����������ʱ��close���
        sockstream.release_noclose();
    }
    //tmpret == 0 �Ǿ�������ȥ��¥,������ UNIX������ ˵Ӧ�����б�������ʱ���ܵ�.(�ҵĲ��Ի��Ƿ��ش���)
    //��ACE��˵�����������ش���,����ʱ�������������,ʵ�ڲ�����ֻ�и�������д��ɬ������ʫ��
    else
    {
        ZCE_LOGMSG(RS_ERROR, "[zergsvr] My God! NonBlock Socket Connect Success , ACE is a cheat.");
    }

    return 0;
}

//����services_type��ѯ��Ӧ�����������������б����� MS��������
int Zerg_Auto_Connector::find_conf_ms_svcid_ary(uint16_t services_type,
                                                std::vector<uint32_t> *& ms_svcid_ary)
{
    auto map_iter = type_to_idary_map_.find(services_type);
    if (type_to_idary_map_.end() == map_iter)
    {
        return -1;
    }
    ms_svcid_ary = &(map_iter->second);
    return 0;
}

//������SVC ID�Ƿ����������ӵķ�����
bool Zerg_Auto_Connector::is_auto_connect_svcid(const SERVICES_ID &svc_id)
{
    //�����SET�����Ҳ���
    SERVICES_INFO svc_info;
    svc_info.svc_id_ = svc_id;
    if (autocnt_svcinfo_set_.find(svc_info) == autocnt_svcinfo_set_.end())
    {
        return false;
    }
    return true;
}
