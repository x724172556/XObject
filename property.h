#ifndef PROPERTY_H
#define PROPERTY_H
#include "method.h"
//#include "object.h"

class  Object;

class IProperty{
public:
    IProperty(std::string name="", Object *parent=nullptr);
    virtual ~IProperty()=0;
    virtual Object* Parent() const;
    virtual void SetParent(Object* parent=nullptr);
    virtual std::string Name();
    virtual void SetName(std::string name);
private:
    Object* m_parent=nullptr;
    std::string m_name ;
};


template<typename... Args> class _Property;

template <typename _Value>
class _Property<_Value>:public IProperty
{
public:
    _Property(std::string name="",Object* parent = nullptr):IProperty(name,parent) {}
    virtual ~_Property()override{}
    //template<typename Type>
    _Property(std::string name , Method<_Value(void)>Reader,  Method<void(const _Value& value)> Writer, Method<std::string(_Value)> signal, Object* parent = nullptr ):
     IProperty(name,parent),  m_reader(Reader),m_writer(Writer), m_changedSignal(signal)
    {

    }
    _Property(std::string name,std::function<_Value(void)>Reader,  std::function<void(const _Value& value)> Writer, std::function<std::string(_Value)> signal, Object* parent = nullptr ):
      IProperty(name,parent),  m_reader(Reader),m_writer(Writer), m_changedSignal(signal)
    {

    }

    _Property& operator = (const _Property& property){
        m_writer(property());
    }
    _Property& operator = (const _Value& value){
        m_writer(value);
    }
    _Value operator()(){
        return m_reader();
    }

    Method<std::string(_Value)> Signal()const
    {
        return m_changedSignal;
    }

private:
    Method<_Value(void)>  m_reader;
    Method<void(const _Value& value)> m_writer;


    Method<std::string(_Value)>  m_changedSignal;


};



#endif // PROPERTY_H
