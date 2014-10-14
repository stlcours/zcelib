#include "soar_predefine.h"
#include "soar_ogre_peer_id.h"

/****************************************************************************************************
class  Socket_Peer_Info ��������Ϣ,Ϊ��ͬʱ��ʾIP+�˿ڵ�ģʽ������UNION��ʽ
****************************************************************************************************/

OGRE_PERR_ID::OGRE_PERR_ID(unsigned int peer_ip_address, unsigned short peer_port):
    peer_ip_address_(peer_ip_address),
    peer_port_(peer_port)
{
}

OGRE_PERR_ID::OGRE_PERR_ID(const ZCE_Sockaddr_In &inet_addr):
    peer_ip_address_(inet_addr.get_ip_address()),
    peer_port_(inet_addr.get_port_number())
{
}

OGRE_PERR_ID::~OGRE_PERR_ID()
{
}

//
void OGRE_PERR_ID::set(unsigned int peer_ip_address, unsigned short peer_port )
{
    peer_ip_address_ = peer_ip_address;
    peer_port_ = peer_port;
}

//����ACE��IP��ַ����
void OGRE_PERR_ID::set(const ZCE_Sockaddr_In &inet_addr)
{
    peer_ip_address_ = inet_addr.get_ip_address();
    peer_port_ = inet_addr.get_port_number();
}

//�ȽϺ���,
bool OGRE_PERR_ID::operator ==(const OGRE_PERR_ID &others) const
{
    if (others.peer_ip_address_ == peer_ip_address_ && others.peer_port_ == peer_port_)
    {
        return true;
    }

    return false;
}
//�Ƚϲ�ͬ����,
bool OGRE_PERR_ID::operator !=(const OGRE_PERR_ID &others) const
{
    return !(*this == others);
}
//�и���������,
bool OGRE_PERR_ID::operator <(const OGRE_PERR_ID &others) const
{
    if (peer_ip_address_ + peer_port_ < others.peer_ip_address_ + others.peer_port_ )
    {
        return true;
    }

    return false;
}
