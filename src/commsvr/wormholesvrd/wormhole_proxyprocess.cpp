#include "wormhole_predefine.h"
#include "wormhole_proxyprocess.h"
#include "wormhole_application.h"
#include "wormhole_stat_define.h"


//===================================================================================================


Interface_WH_Proxy::Interface_WH_Proxy()
{
}
Interface_WH_Proxy::~Interface_WH_Proxy()
{
}


Interface_WH_Proxy::PROXY_TYPE Interface_WH_Proxy::str_to_proxytype(const char *str_proxy)
{
    if (0 == strcasecmp(str_proxy, "ECHO"))
    {
        return PROXY_TYPE_ECHO;
    }
    else if (0 == strcasecmp(str_proxy, "TRANSMIT"))
    {
        return PROXY_TYPE_TRANSMIT;
    }
    else if (0 == strcasecmp(str_proxy, "BROADCAST"))
    {
        return PROXY_TYPE_BROADCAST;
    }
    else if (0 == strcasecmp(str_proxy, "MODULO_UID"))
    {
        return PROXY_TYPE_MODULO_UID;
    }
    else if (0 == strcasecmp(str_proxy, "MODULO_SENDSVCID"))
    {
        return PROXY_TYPE_MODULO_SENDSVCID;
    }
    else
    {
        return INVALID_PROXY_TYPE;
    }
}

//�����ӿ�����Ĺ���
Interface_WH_Proxy *Interface_WH_Proxy::create_proxy_factory(PROXY_TYPE proxytype)
{
    Interface_WH_Proxy *tmpintface = NULL;
    ZLOG_INFO("Interface_Proxy_Process::CreatePorxyFactory PROXY_TYPE: %d.", proxytype);

    switch (proxytype)
    {
        // ���Է�����
        case PROXY_TYPE_ECHO:
        {
            tmpintface = new Echo_Proxy_Process();
            break;
        }

        // ͸תת���ķ�ʽ
        case PROXY_TYPE_TRANSMIT:
        {
            tmpintface = new Transmit_Proxy();
            break;
        }

        // �����ݽ��п����ַ��㲥
        case PROXY_TYPE_BROADCAST:
        {
            tmpintface = new Broadcast_ProxyProcess();
            break;
        }

        // DBPROXY��ģʽ������UINȡģ�ķ�ʽ�ĵ���������ID
        case PROXY_TYPE_MODULO_UID:
        {
            tmpintface = new Modulo_ProxyProcess(Modulo_ProxyProcess::MODULO_UID);
            break;
        }

        // DBPROXY��ģʽ������APPID��UIN�ķ�ʽ�ĵ���������ID
        case PROXY_TYPE_MODULO_SENDSVCID:
        {
            tmpintface = new Modulo_ProxyProcess(Modulo_ProxyProcess::MODULO_SENDSVC_ID);
            break;
        }

        default:
        {
            // ����
            ZLOG_ERROR("Error Proxy Type define. Please check you code. ");
            return NULL;
        }
        
    }

    return tmpintface;
}





int Interface_WH_Proxy::init_proxy_instance()
{
    // int ret =0;
    // ��ʼ��MMAP�ڴ��PIPE
    zerg_mmap_pipe_ = Soar_MMAP_BusPipe::instance();

    return 0;
}


//��ȡ����
int Interface_WH_Proxy::get_proxy_config(const ZCE_Conf_PropertyTree *conf_tree)
{
    ZCE_UNUSED_ARG(conf_tree);
    return 0;
}

//===================================================================================================

Echo_Proxy_Process::Echo_Proxy_Process()
{

}
Echo_Proxy_Process::~Echo_Proxy_Process()
{

}

int Echo_Proxy_Process::get_proxy_config(const ZCE_Conf_PropertyTree *conf_tree)
{
    //
    int ret = Interface_WH_Proxy::get_proxy_config(conf_tree);
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}


int Echo_Proxy_Process::process_proxy(Zerg_App_Frame *proc_frame)
{

    ZCE_LOGMSG_DBG(RS_DEBUG, "Receive a echo frame to process,"
               "send svr:[%u|%u], "
               "recv svr:[%u|%u], "
               "frame_uin:%u, "
               "frame_cmd:%u, "
               "frame_len:%u. ",
               proc_frame->send_service_.services_type_,
               proc_frame->send_service_.services_id_,
               proc_frame->recv_service_.services_type_,
               proc_frame->recv_service_.services_id_,
               proc_frame->frame_uid_,
               proc_frame->frame_command_,
               proc_frame->frame_length_);

    int ret = 0;
    // �ڲ�����������
    bool bsnderr;

    if (proc_frame->is_internal_process(bsnderr) == true)
    {
        ZLOG_DEBUG("Receive a internal command, frame_uin:%u, frame_command:%u. ",
                   proc_frame->frame_uid_, proc_frame->frame_command_);
        return 0;
    }

    // �������֡
    proc_frame->exchange_rcvsnd_svcid();

    ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);

    //
    if (ret != 0)
    {
        return SOAR_RET::ERR_PROXY_SEND_PIPE_IS_FULL;
    }

    ZCE_LOGMSG_DBG(RS_DEBUG, "Echo to [%u|%u], frame_uin:%u, frame_command:%u, frame_len:%u. ",
                proc_frame->recv_service_.services_type_,
                proc_frame->recv_service_.services_id_,
                proc_frame->frame_uid_,
                proc_frame->frame_command_,
                proc_frame->frame_length_);
    return 0;
}






//===================================================================================================
//ֱ�ӽ���ת����������������֡�����κδ���

Transmit_Proxy::Transmit_Proxy()
{
}

Transmit_Proxy::~Transmit_Proxy()
{
}

int Transmit_Proxy::get_proxy_config(const ZCE_Conf_PropertyTree *conf_tree)
{
    //
    int ret = Interface_WH_Proxy::get_proxy_config(conf_tree);
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}

int Transmit_Proxy::process_proxy(Zerg_App_Frame *proc_frame)
{
    ZCE_LOGMSG_DBG(RS_DEBUG, "Receive a transmit frame to process,"
        "send svr:[%u|%u], "
        "recv svr:[%u|%u], "
        "frame_uin:%u, "
        "frame_cmd:%u, "
        "frame_len:%u. ",
        proc_frame->send_service_.services_type_,
        proc_frame->send_service_.services_id_,
        proc_frame->recv_service_.services_type_,
        proc_frame->recv_service_.services_id_,
        proc_frame->frame_uid_,
        proc_frame->frame_command_,
        proc_frame->frame_length_);

    int ret = 0;

    // �ڲ�����������,����
    bool bsnderr;

    if (proc_frame->is_internal_process(bsnderr) == true)
    {
        ZLOG_DEBUG("Receive a internal command, frame_uin:%u, frame_command:%u. ",
            proc_frame->frame_uid_, proc_frame->frame_command_);
        return 0;
    }

    ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);

    //
    if (ret != 0)
    {
        return SOAR_RET::ERR_PROXY_SEND_PIPE_IS_FULL;
    }

    ZCE_LOGMSG_DBG(RS_DEBUG,"Transmit to [%u|%u], frame_uin:%u, frame_command:%u, frame_len:%u, trans_id[%u]. ",
        proc_frame->recv_service_.services_type_,
        proc_frame->recv_service_.services_id_,
        proc_frame->frame_uid_,
        proc_frame->frame_command_,
        proc_frame->frame_length_,
        proc_frame->transaction_id_);

    return 0;
}


//===================================================================================================

//�����ݸ���ת�����������õķ�����
Broadcast_ProxyProcess::Broadcast_ProxyProcess() :
    Interface_WH_Proxy(),
    broadcast_svctype_(0),
    broadcast_svcnum_(0)
{
    memset(broadcast_svcid_, 0, sizeof(broadcast_svcid_));
}

Broadcast_ProxyProcess::~Broadcast_ProxyProcess()
{
}

int Broadcast_ProxyProcess::get_proxy_config(const ZCE_Conf_PropertyTree *conf_tree)
{
    //
    int ret = Interface_WH_Proxy::get_proxy_config(conf_tree);

    if (ret != 0)
    {
        return ret;
    }


    ret = conf_tree->path_get_leaf("BROADCAST_CFG", "BROADCAST_SVCTYPE",
        broadcast_svctype_);
    if (0 != ret || broadcast_svctype_ == SERVICES_ID::INVALID_SERVICES_TYPE)
    {
        SOAR_CFG_READ_FAIL(RS_ERROR);
        return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
    }

    ret = conf_tree->path_get_leaf("BROADCAST_CFG", "BROADCAST_NUM",
        broadcast_svcnum_);
    ZLOG_DEBUG("Broadcast service num: %u.", broadcast_svcnum_);
    if (0 != ret || broadcast_svcnum_ == 0 || broadcast_svcnum_ > MAX_NUM_COPY_SVC)
    {
        SOAR_CFG_READ_FAIL(RS_ERROR);
        return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
    }

    

    
    //ע���Ǵ�1��ʼ
    for (size_t i = 0; i < broadcast_svcnum_; ++i)
    {
        ret = conf_tree->pathseq_get_leaf("BROADCAST_CFG", "BROADCAST_SVCID_", i+1, broadcast_svcid_[i]);
        ZLOG_DEBUG("Broadcast service id: %hu.%u.", broadcast_svctype_, broadcast_svcid_[i]);
        if (0 != ret)
        {
            SOAR_CFG_READ_FAIL(RS_ERROR);
            return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
        }
    }
    

    // ����Ƿ����ظ���ID
    std::list <uint32_t> check_list;
    for (size_t i = 0; i < broadcast_svcnum_; ++i)
    {
        check_list.push_back(broadcast_svcid_[i]);
    }

    // ������Ч�ʵĵط�
    check_list.sort();
    check_list.unique();
    if (check_list.size() != broadcast_svcnum_)
    {
        ZLOG_ERROR("Cfg file have repeat svc id,Please check.");
        SOAR_CFG_READ_FAIL(RS_ERROR);
        return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
    }

    return 0;
}

//
int Broadcast_ProxyProcess::process_proxy(Zerg_App_Frame *proc_frame)
{
    int ret = 0;

    // �����ͷ������
    proc_frame->dumpoutput_framehead("[FROM RECV FRAME]", RS_DEBUG);

    // �ڲ�����������,����
    bool bsnderr;

    if (proc_frame->is_internal_process(bsnderr) == true)
    {
        ZLOG_DEBUG("Receive a internal command, frame_uin:%u, frame_command:%u. ",
            proc_frame->frame_uid_, proc_frame->frame_command_);
        return 0;
    }

    // ���������Ƿ�ã��Ҳ�֪����
    if (proc_frame->recv_service_.services_type_ != broadcast_svctype_)
    {
        ZLOG_ERROR("Can't Porcess services_type_%u. ", proc_frame->recv_service_.services_type_);
        return SOAR_RET::ERR_PROXY_RCVSVC_TYPE_ERROR;
    }

    // ��������N��֡��ת������ͬ�ķ�����
    for (size_t i = 0; i < broadcast_svcnum_; ++i)
    {
        // �޸�Ϊ�µ�ID
        proc_frame->recv_service_.services_id_ = broadcast_svcid_[i];
        ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);

        //
        if (ret != 0)
        {
            return ret;
        }

        ZCE_LOGMSG_DBG(RS_DEBUG, "Copy to [%u|%u], frame_uin:%u, frame_command:%u, frame_len:%u, trans_id[%u]. ",
            proc_frame->recv_service_.services_type_,
            proc_frame->recv_service_.services_id_,
            proc_frame->frame_uid_,
            proc_frame->frame_command_,
            proc_frame->frame_length_,
            proc_frame->transaction_id_);
    }

    return 0;
}


//===================================================================================================

Modulo_ProxyProcess::Modulo_ProxyProcess(MODULO_TYPE modulo_type) :
    Interface_WH_Proxy(),
    modulo_type_(modulo_type)
{
    memset(modulo_svcid_, 0, sizeof(modulo_svcid_));
}

Modulo_ProxyProcess::~Modulo_ProxyProcess()
{
}

int Modulo_ProxyProcess::get_proxy_config(const ZCE_Conf_PropertyTree *conf_tree)
{
    //
    int ret = Interface_WH_Proxy::get_proxy_config(conf_tree);

    if (ret != 0)
    {
        return ret;
    }


    ret = conf_tree->path_get_leaf("MODULO_CFG", "MODULO_SVCTYPE",
        modulo_svctype_);
    if (0 != ret || modulo_svctype_ == SERVICES_ID::INVALID_SERVICES_TYPE)
    {
        SOAR_CFG_READ_FAIL(RS_ERROR);
        return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
    }

    ret = conf_tree->path_get_leaf("MODULO_CFG", "MODULO_NUM",
        modulo_svcnum_);
    ZLOG_DEBUG("Modulo service num: %u.", modulo_svcnum_);
    if (0 != ret || modulo_svcnum_ == 0 || modulo_svcnum_ > MAX_NUM_MODULO_SVC)
    {
        SOAR_CFG_READ_FAIL(RS_ERROR);
        return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
    }

    //ע���Ǵ�1��ʼ
    for (size_t i = 0; i < modulo_svcnum_; ++i)
    {
        ret = conf_tree->pathseq_get_leaf("MODULO_CFG", "MODULO_SVCID_", i + 1, modulo_svcid_[i]);
        ZLOG_DEBUG("Broadcast service id: %hu.%u.", modulo_svctype_, modulo_svcid_[i]);
        if (0 != ret)
        {
            SOAR_CFG_READ_FAIL(RS_ERROR);
            return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
        }
    }


    // ����Ƿ����ظ���ID
    std::list <uint32_t> check_list;
    for (size_t i = 0; i < modulo_svcnum_; ++i)
    {
        check_list.push_back(modulo_svcid_[i]);
    }

    // ������Ч�ʵĵط�
    check_list.sort();
    check_list.unique();
    if (check_list.size() != modulo_svcnum_)
    {
        ZLOG_ERROR("Cfg file have repeat svc id,Please check.");
        SOAR_CFG_READ_FAIL(RS_ERROR);
        return SOAR_RET::ERROR_GET_CFGFILE_CONFIG_FAIL;
    }

    return 0;
}

//
int Modulo_ProxyProcess::process_proxy(Zerg_App_Frame *proc_frame)
{
    int ret = 0;

    // �����ͷ������
    proc_frame->dumpoutput_framehead("[FROM RECV FRAME]", RS_DEBUG);

    // �ڲ�����������,����
    bool bsnderr;

    if (proc_frame->is_internal_process(bsnderr) == true)
    {
        ZLOG_DEBUG("Receive a internal command, frame_uin:%u, frame_command:%u. ",
            proc_frame->frame_uid_, proc_frame->frame_command_);
        return 0;
    }

    // ���������Ƿ�ã��Ҳ�֪����
    if (proc_frame->recv_service_.services_type_ != modulo_svctype_)
    {
        ZLOG_ERROR("Can't Porcess services_type_%u. ", proc_frame->recv_service_.services_type_);
        return SOAR_RET::ERR_PROXY_RCVSVC_TYPE_ERROR;
    }

    uint32_t mod_number = 0;
    if ( MODULO_UID == modulo_type_)
    {
        mod_number = proc_frame->frame_uid_;
    }
    else if (MODULO_SENDSVC_ID == modulo_type_)
    {
        mod_number = proc_frame->send_service_.services_id_;
    }
    else
    {
        ZCE_ASSERT(true);
    }

    proc_frame->recv_service_.services_id_ = modulo_svcid_[mod_number%modulo_svcnum_];
    ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);

    //
    if (ret != 0)
    {
        return ret;
    }

    ZCE_LOGMSG_DBG(RS_DEBUG, "Copy to [%u|%u], frame_uin:%u, frame_command:%u, frame_len:%u, trans_id[%u]. ",
        proc_frame->recv_service_.services_type_,
        proc_frame->recv_service_.services_id_,
        proc_frame->frame_uid_,
        proc_frame->frame_command_,
        proc_frame->frame_length_,
        proc_frame->transaction_id_);

    return 0;
}



//const DBModalMGRouteItem *DBModalMGProxyInfo::find_route(unsigned int uin)
//{
//    if (route_cfg_.size() == 0)
//    {
//        // û������·��,��һ���Ǹ�����
//        ZLOG_ERROR("[%s] no route configed", __ZCE_FUNC__);
//        return NULL;
//    }
//
//    DBModalMGRouteItem tmp;
//    // ȡuin�ĵ�16λ��Ϊhashֵ,Ӧ�ù������
//    tmp.hash_ = (uin & 0xFFFF);
//
//    std::vector<DBModalMGRouteItem>::iterator iter
//        = std::upper_bound(route_cfg_.begin(), route_cfg_.end(), tmp);
//
//    // ���ָ��·�ɱ���ĩβ,��ôʵ����Ӧ������·�ɱ��ĵ�һ��
//    if (iter == route_cfg_.end())
//    {
//        iter = route_cfg_.begin();
//    }
//
//    return &(*iter);
//}


////===================================================================================================
//
////����DBȡģ����Proxyת��������DBServer�ͽ��ڷ����� 
//DBModalProxyProcess::DBModalProxyProcess():
//    Interface_WH_Proxy()
//{
//}
//
//DBModalProxyProcess::~DBModalProxyProcess()
//{
//    std::map<unsigned short, DBModalProxyInfo*>::iterator iter = dbmodal_proxy_map_.begin();
//
//    for (; iter != dbmodal_proxy_map_.end(); iter++)
//    {
//        // �ͷŷ�����ڴ�
//        delete iter->second;
//        iter->second = NULL;
//    }
//}
//
//
//int DBModalProxyProcess::get_proxy_config(const ZCE_Conf_PropertyTree *conf_tree)
//{
//
//    int ret = 0;
//
//    //�õ����˵�����
//    ret = Interface_WH_Proxy::get_proxy_config(conf_tree);
//    if (ret != 0)
//    {
//        return ret;
//    }
//
//
//
//    for (unsigned int i = 0; i < cfg->dbmodal_info_.route_num_; i++)
//    {
//        DBModalProxyInfo *dbmodal_proxy_info = new DBModalProxyInfo();
//        conf_proxysvr::RouteInfo *route_info = &(cfg->dbmodal_info_.route_info_[i]);
//
//        dbmodal_proxy_info->distribute_module_ = route_info->distribute_module_;
//        dbmodal_proxy_info->distribute_offset_ = route_info->distribute_offset_;
//        dbmodal_proxy_info->router_svr_type_ = route_info->svr_type_;
//
//        ZLOG_INFO("[DBModalProxy] route_svr_type:%u, distribute_offset:%u, distribute_module:%u",
//            dbmodal_proxy_info->router_svr_type_,
//            dbmodal_proxy_info->distribute_offset_,
//            dbmodal_proxy_info->distribute_module_);
//
//        dbmodal_proxy_info->normal_router_cfg_.resize(dbmodal_proxy_info->distribute_module_);
//        dbmodal_proxy_info->clone_router_cfg_.resize(dbmodal_proxy_info->distribute_module_);
//
//        for (unsigned int k = 0; k < dbmodal_proxy_info->distribute_module_; k++)
//        {
//            dbmodal_proxy_info->normal_router_cfg_[k] = route_info->svr_id_[k].nomal_service_id_;
//
//            if (route_info->svr_id_[k].clone_service_id_)
//            {
//                dbmodal_proxy_info->clone_router_cfg_[k] = route_info->svr_id_[k].clone_service_id_;
//            }
//            else
//            {
//                dbmodal_proxy_info->clone_router_cfg_[k] = SERVICES_ID::INVALID_SERVICES_ID;
//            }
//
//            ZLOG_INFO("[DBModalProxy] normal service:%u|%u, clone service:%u|%u, passby service:%u|%u",
//                dbmodal_proxy_info->router_svr_type_, dbmodal_proxy_info->normal_router_cfg_[k],
//                dbmodal_proxy_info->router_svr_type_, dbmodal_proxy_info->clone_router_cfg_[k]);
//        }
//
//        dbmodal_proxy_map_.insert(std::make_pair<unsigned short, DBModalProxyInfo*>
//            (dbmodal_proxy_info->router_svr_type_, dbmodal_proxy_info));
//    }
//
//    return 0;
//}
//
////Ҫ������֡
//int DBModalProxyProcess::process_proxy(Zerg_App_Frame *proc_frame)
//{
//    ZLOG_DEBUG("Receive a dbmode frame to process,"
//               "send svr:[%u|%u], "
//               "recv svr:[%u|%u], "
//               "frame_uin:%u, "
//               "frame_cmd:%u, "
//               "frame_len:%u. ",
//               proc_frame->send_service_.services_type_,
//               proc_frame->send_service_.services_id_,
//               proc_frame->recv_service_.services_type_,
//               proc_frame->recv_service_.services_id_,
//               proc_frame->frame_uid_,
//               proc_frame->frame_command_,
//               proc_frame->frame_length_);
//
//    int ret = 0;
//    // �ڲ�����������,����
//    bool bsnderr;
//
//    if (proc_frame->is_internal_process(bsnderr) == true)
//    {
//        ZLOG_INFO("Receive a internal command, frame_uin:%u, frame_command:%u. ",
//                  proc_frame->frame_uid_, proc_frame->frame_command_);
//        return 0;
//    }
//
//    std::map<unsigned short, DBModalProxyInfo*>::iterator iter =
//        dbmodal_proxy_map_.find(proc_frame->recv_service_.services_type_);
//
//    if (iter != dbmodal_proxy_map_.end())
//    {
//        // Ҫת��������������, ��ȡ��Ӧ·����Ϣ
//        DBModalProxyInfo *dbmodal_proxy_info = iter->second;
//
//        //------------------------------------------------------------------
//        unsigned int uin = proc_frame->frame_uid_;
//
//        // ���˵�uinΪ0������
//        if (uin == 0 )
//        {
//
//            proc_frame->dumpoutput_framehead("[FROM RECV FRAME]", RS_ERROR);
//
//            Soar_Stat_Monitor::instance()->increase_once(WORMHOLE_TRANS_PKG_ERROR);
//
//            return SOAR_RET::ERROR_APPFRAME_ERROR;
//        }
//
//        // �ؼ����봦
//        unsigned int mod =
//            (uin >> dbmodal_proxy_info->distribute_offset_) % dbmodal_proxy_info->distribute_module_;
//
//        // ------------------------------------------------------------------
//        proc_frame->recv_service_.services_type_ = dbmodal_proxy_info->router_svr_type_;
//        proc_frame->recv_service_.services_id_ =  dbmodal_proxy_info->normal_router_cfg_[mod];
//
//        // ��־����ΪDEBUG�����
//        ZLOG_DEBUG("Send to main services [%u|%u], frame_uin:%u, "
//            "frame_command:%u, frame_len:%u, trans_id[%u]. ",
//                   proc_frame->recv_service_.services_type_,
//                   proc_frame->recv_service_.services_id_,
//                   proc_frame->frame_uid_,
//                   proc_frame->frame_command_,
//                   proc_frame->frame_length_,
//                   proc_frame->transaction_id_);
//
//        // ֻ������һ��֡
//        int ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);
//
//        //
//        if (ret != 0)
//        {
//            return SOAR_RET::ERR_PROXY_SEND_PIPE_IS_FULL;
//        }
//
//        // ����б���·��,������ת����һ�����ݵĴ���
//        if (dbmodal_proxy_info->clone_router_cfg_[mod] != SERVICES_ID::INVALID_SERVICES_ID )
//        {
//
//            proc_frame->recv_service_.services_id_ = dbmodal_proxy_info->clone_router_cfg_[mod];
//            ZLOG_INFO("Send to backup services [%u|%u], frame_uin:%u,"
//                " frame_command:%u, frame_len:%u, back trans_id[%u]. ",
//                      proc_frame->recv_service_.services_type_,
//                      proc_frame->recv_service_.services_id_,
//                      proc_frame->frame_uid_,
//                      proc_frame->frame_command_,
//                      proc_frame->frame_length_,
//                      proc_frame->backfill_trans_id_);
//
//            ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);
//
//            if (ret != 0)
//            {
//                return SOAR_RET::ERR_PROXY_SEND_PIPE_IS_FULL;
//            }
//        }
//
//    }
//    // ����һ��·�ɷ�������飬ֱ��͸��
//    else
//    {
//        //
//        // ��һ����־���������
//        ZLOG_INFO("Send back [%u|%u], frame_uin:%u, frame_command:%u, frame_len:%u. ",
//                  proc_frame->recv_service_.services_type_,
//                  proc_frame->recv_service_.services_id_,
//                  proc_frame->frame_uid_,
//                  proc_frame->frame_command_,
//                  proc_frame->frame_length_);
//
//        ret = zerg_mmap_pipe_->push_back_sendpipe(proc_frame);
//
//        //
//        if (ret != 0)
//        {
//            return SOAR_RET::ERR_PROXY_SEND_PIPE_IS_FULL;
//        }
//    }
//
//    return 0;
//}
