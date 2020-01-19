#include "connect.h"

Connect::Connect(bool rc):m_signal(""),m_reciver(nullptr),m_slotmethod(nullptr),m_pure_pointer(nullptr)
{

}

Connect::Connect(const std::string &signal, Object *reciver, MethodInfo *method,void*pointer,ConnectMode mode ):
    m_signal(signal),m_reciver(reciver),m_slotmethod(method),m_connectMode(mode),m_pure_pointer(pointer)
{

}

Connect::Connect(const Connect &conn):
    m_signal(conn.m_signal),m_reciver(conn.m_reciver),m_slotmethod(conn.m_slotmethod),m_connectMode(conn.m_connectMode),m_pure_pointer(conn.m_pure_pointer)
{

}

Connect::~Connect()
{

}

bool Connect::operator ==(const Connect &conn)
{
    if(m_signal == conn.m_signal && m_reciver == conn.m_reciver&& m_pure_pointer == conn.m_pure_pointer)
        return true;
    else
        return false;
}

Connect &Connect::operator =(bool rc)
{
    if(!rc){
        m_signal = "";
        m_reciver = nullptr;
        m_slotmethod = nullptr;
        m_pure_pointer = nullptr;
    }
    return *this;
}

Connect &Connect::operator =(const Connect &conn)
{
    m_signal=conn.m_signal;
    m_reciver=conn.m_reciver;
    m_slotmethod=conn.m_slotmethod;
     m_connectMode=conn.m_connectMode;
    m_pure_pointer=conn.m_pure_pointer;
    return *this;
}

bool Connect::operator<(const Connect &conn)const
{
    if(m_signal < conn.m_signal)
        return true;
    else
        return false;
}



const std::string &Connect::signal() const
{
    return m_signal;
}

const Object *Connect::Reciver()const
{
    return m_reciver;
}

const MethodInfo *Connect::Method() const
{
    return m_slotmethod;
}

const Connect::ConnectMode &Connect::ConnectedMode() const
{
    return m_connectMode;
}

//void Connect::SetPurePointer(void *pointer)
//{

//}

void *Connect::PurePointer()
{
    return m_pure_pointer;
}

Connect::operator bool()
{

    if(m_signal.empty() || !m_slotmethod||!m_pure_pointer)
        return false;
    else
        return true;

}
