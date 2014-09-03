
#ifndef ZERG_COMMUNICATION_MANAGER_H_
#define ZERG_COMMUNICATION_MANAGER_H_

#include "zerg_configure.h"
#include "zerg_stat_define.h"

//��С���䣺�����ǰ�ǹ�ɣ����߽�����ëǮ
//��������¼һ�£�Ϊʲôÿ���˿�Ҫ����һ��SVC ID��������⣬
//�Ҹ�������ͻῼ��һ�ߡ�����ÿ�ζ��ῼ�ǵ�UDP��͸���������,̫TMD��������ˡ�
//����̫���Ľ������ʵ�ܼ�
//���һ��SVCID��Ӧ����˿ڣ��㲻���ֱ�ʶ������ô����������֪�����ӵ�SVCID�������Ǹ��˿���

class TCP_Accept_Handler;
class UDP_Svc_Handler;
class Zerg_MMAP_BusPipe;
class ZBuffer_Storage;

/****************************************************************************************************
class  Zerg_Comm_Manager
****************************************************************************************************/
class Zerg_Comm_Manager
{

    //
    typedef std::vector<TCP_Accept_Handler *> TCPACCEPT_HANDLER_LIST;
    //
    typedef std::vector<UDP_Svc_Handler *> UDPSVC_HANDLER_LIST;

protected:

    //���캯������������
    Zerg_Comm_Manager();
    ~Zerg_Comm_Manager();

public:

    //��ʼ��,�������ļ���ȡ����
    int get_config(const Zerg_Server_Config *config);

    //��ʼ��Socket, backlogĬ��ֵ��open��ʹ�õ�Ĭ��ֵ����һ��
    int init_socketpeer(ZERG_SERVICES_INFO &init_svcid);

    //���˿��Ƿ�ȫ,��ȫ�˿ڱ��벻ʹ�ñ���(FALSE)
    int check_safeport(ZCE_Sockaddr_In     &inetadd);

    //ȡ�÷������ݽ��з���
    int popall_sendpipe_write(size_t want_, size_t &proc_frame_num);

    //
    void pushback_recvpipe(Zerg_App_Frame *recv_frame);

    //��鷢��Ƶ��
    void check_freamcount(unsigned int now);

    int send_single_buf(Zerg_Buffer * tmpbuf);

public:

    //����ʵ������
    static Zerg_Comm_Manager *instance();
    //��������ʵ��
    static void clean_instance();

protected:

    //һ����෢��2048֡
    static const unsigned int MAX_ONCE_SEND_FRAME = 4096;




protected:
    //����ʵ��
    static Zerg_Comm_Manager  *instance_;


protected:

    //ACCEPET��HANDLER����
    TCPACCEPT_HANDLER_LIST    zerg_acceptor_;
    //UPD��HANDLER����
    UDPSVC_HANDLER_LIST       zerg_updsvc_;


    //���ڴ��������,���Է��͵Ĵ���,ֻ���˱�֤һ��������˲��
    unsigned int              error_try_num_;

    //��������������Ϊ�˼ӿ��ٶȣ����ñ�����
    size_t                    monitor_size_;
    //��ص�����
    unsigned int              monitor_cmd_[ZERG_CONFIG::MAX_NUMBER_OF_MONITOR_FRAME];

    //�ڴ�ܵ����ʵ�����󣬱���������Ϊ�˼���
    Zerg_MMAP_BusPipe        *zerg_mmap_pipe_;
    //���ͺͽ��ջ����BUFF��ʵ�����󣬱���������Ϊ�˼���
    ZBuffer_Storage          *zbuffer_storage_;
    //ͳ�ƣ�ʹ�õ������ָ�룬����������Ϊ�˼���
    Comm_Stat_Monitor          *server_status_;


    //�������澯ֵ
    static const unsigned int SEND_FRAME_ALERT_VALUE = 40000;
    //������ʼʱ��
    unsigned int              count_start_time_;
    //Э������ͼ�����
    unsigned int              send_frame_count_;


};



#endif //_ZERG_COMMUNICATION_MANAGER_H_
