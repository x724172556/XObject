#include "property.h"
#include "object.h"




IProperty::~IProperty()
{

}

IProperty::IProperty(std::string name, Object *parent):m_name(name),m_parent(parent)
{
    if(!m_name.empty()&& m_parent){
        m_parent->RegisterProperty(this);
    }
}

Object *IProperty::Parent() const
{
    return m_parent;
}

void IProperty::SetParent(Object *parent)
{
    if(m_parent){
        m_parent->UnregisterProperty(this);
    }
    m_parent = parent;
    if(m_parent)
        m_parent->RegisterProperty(this);
}

std::string IProperty::Name()
{
    return m_name;
}

void IProperty::SetName(std::string name)
{
    if(m_parent)
        m_parent->UnregisterProperty(this);

    m_name = name;
    if(!m_name.empty()&& m_parent){
        m_parent->RegisterProperty(this);
    }
}

