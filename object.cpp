#include "object.h"
#include <assert.h>




Object::Object()
{
}

Object::~Object()
{

}

bool Object::RegisterProperty(IProperty *pProperty)
{
    assert(pProperty);
    if(!pProperty)
        return false;
    m_propertys[pProperty->Name()] = pProperty;
    return true;
}

void Object::UnregisterProperty(IProperty *pProperty)
{
    assert(pProperty);
    if(!pProperty)
        return ;
    m_propertys.erase(pProperty->Name());
}

void Object::Unbind(const Connect &conn)
{
    disconnect(conn);
}

void Object::disconnect(const Connect &conn)
{
    auto it =  m_connects.find(conn);
    if(it != m_connects.end()){
        m_connects.erase(it);
    }
}

void Object::disconnect(Object *sender, const Connect &conn)
{
    sender->disconnect(conn);
}

void Object::disconnect(Object *reciver)
{
    for(auto it = m_connects.begin(); it != m_connects.end(); ){
        if(it->Reciver() == reciver){
            it=m_connects.erase(it);
        }else{
            it++;
        }
    }
}

void Object::disconnect(Object *sender, Object *reciver)
{
    sender->disconnect(reciver);
}

bool Object::SendSignalEvent(const Method<void(void)> &method, const Object* reciver)
{
    if(!reciver)
        return false;

    return true;
}

void Object::InvokeMethod(Object *sender, const Method<void ()> &method)
{
    SetSlotSender(sender);
    method();
    SetSlotSender(nullptr);
}

void Object::SetSlotSender(Object *sender)
{
    m_slot_sender = sender;

}

Object *Object::Sender()
{
    return m_slot_sender;
}
