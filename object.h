#ifndef OBJECT_H
#define OBJECT_H

#include "Object_global.h"
#include "membermethod.h"
#include "method.h"
#include <map>
#include <list>
#include "connect.h"
#include <set>
#include "slotmethodwrap.h"
#include <algorithm>
#include "property.h"
class OBJECT_EXPORT Object
{
public:



    Object();
    virtual ~Object();
    _SIGNAL(OnChanged(Object *))


    bool RegisterProperty(IProperty* pProperty);
    void UnregisterProperty(IProperty* pProperty);

    template<typename T>
    void Property(std::string property, T& value)const{
        auto it =m_propertys.find(property);
         if(it != m_propertys.end() ){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<T>*>(pIProperty);
             if(pProperty){
                value = (*pProperty)();
             }else{
                // rc = false;
             }
         }

    }

    template<typename T>
    void SetProperty(std::string property, const T& value){
        auto it =m_propertys.find(property);
         if(it != m_propertys.end() ){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<T>*>(pIProperty);
             if(pProperty){
                *pProperty = value;
             }else{
                // rc = false;
             }
         }

    }

    template<typename Res2, typename Type2,typename Args2>
    const Connect Bind(const std::string& property, Object * reciver, Res2(Type2::*method)(Args2) ){
        Connect rc = Connect("",nullptr,nullptr,nullptr) ;
        auto it =m_propertys.find(property);
        auto p = static_cast<Type2*>(reciver);
        if(it != m_propertys.end() && p){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<Args2>*>(pIProperty);
             if(pProperty){
               rc= connect(pProperty->Signal()(Args2()),reciver, Method<Res2(Args2)>(p,method),(void*)method);
             }else{
                // rc = false;
             }
        }

        else{
           // rc = false;
        }
        return rc;
    }

    template<typename Res2, typename Type2,typename Args2>
    const Connect Binded(const std::string& property, Object * reciver, Res2(Type2::*method)(Args2) ){
        Connect rc = false ;
        auto it =m_propertys.find(property);
        auto p = static_cast<Type2*>(reciver);
        if(it != m_propertys.end() && p){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<Args2>*>(pIProperty);
             if(pProperty){
                 Method<Res2(Args2)> newMethod(p,method);
               rc= connect(pProperty->Signal()(Args2()),reciver, newMethod,(void*)method);
                if(rc){
                    newMethod((*pProperty)());
                }
             }else{
                 rc = false;
             }
        }

        else{
            //没有这个属性,或者属性的类型和槽函数不匹配
            rc = false;
        }
    }


    template<typename Res2, typename Type2,typename Args2>
    const Connect Bind(const std::string& property,  Res2(*method)(Args2) ){
        Connect rc = Connect("",nullptr,nullptr,nullptr) ;
        auto it =m_propertys.find(property);

        if(it != m_propertys.end() ){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<Args2>*>(pIProperty);
             if(pProperty){
               rc= connect(pProperty->Signal()(Args2()), nullptr, Method<Res2(Args2)>(method),(void*)method);
             }else{
                // rc = false;
             }
        }

        else{
           // rc = false;
        }
        return rc;
    }

    template<typename Res2, typename Type2,typename Args2>
    const Connect Binded(const std::string& property,  Res2(*method)(Args2) ){
        Connect rc = Connect("",nullptr,nullptr,nullptr) ;
        auto it =m_propertys.find(property);

        if(it != m_propertys.end() ){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<Args2>*>(pIProperty);
             if(pProperty){
                 Method<Res2(Args2)> newMethod(method);
               rc= connect(pProperty->Signal()(Args2()), nullptr, newMethod,(void*)method);
                if(rc){
                    newMethod((*pProperty)());
                }
             }else{
                // rc = false;
             }
        }

        else{
           // rc = false;
        }
        return rc;
    }

    template<typename Res2, typename Type2,typename Args2>
    void Unbind(const std::string& property, Object * reciver, Res2(Type2::*method)(Args2) ){

        auto it =m_propertys.find(property);
        auto p = static_cast<Type2*>(reciver);
        if(it != m_propertys.end() && p){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<Args2>*>(pIProperty);
             if(pProperty){
                 Method<Res2(Args2)> newMethod(p,method);
                disconnect(pProperty->Signal()(Args2()),reciver, newMethod,(void*)method);

             }else{

             }
        }

        else{
            //没有这个属性,或者属性的类型和槽函数不匹配

        }
    }

    template<typename Res2,typename Args2>
    void Unbind(const std::string& property,  Res2(*method)(Args2) ){

        auto it =m_propertys.find(property);

        if(it != m_propertys.end()){
             IProperty* pIProperty =  it->second;
             auto pProperty = static_cast<_Property<Args2>*>(pIProperty);
             if(pProperty){
                 Method<Res2(Args2)> newMethod(method);
                disconnect(pProperty->Signal()(Args2()),newMethod,(void*)method);

             }else{

             }
        }

        else{
            //没有这个属性,或者属性的类型和槽函数不匹配

        }
    }

    void Unbind(const Connect& conn);

    template< typename Type, typename... Args>
    bool RegisterSignal(std::string(Type::*memberSignal)(Args...) ){
        // std::pair<std::string, MethodInfo*> insert((this->* memberSignal.MethodPointer())(Args()...),  new MemberMethod<Res(Type::*)(Args...)>(memberSignal));
        //m_signals.insert(insert);
        auto p = static_cast<Type*>(this);
        if(p){
            m_signals[(p->* memberSignal)(Args()...)]=new MemberMethod<std::string(Type::*)(Args...)>(memberSignal);
            return true;
        }
        else
            return false;
    }
    template< typename Type, typename... Args>
    bool UnregisterSignal(std::string(Type::*memberSignal)(Args...) ){
        auto p = static_cast<Type*>(this);
        if(!p)
            return false;
        auto str = (p->* memberSignal)(Args()...);
        auto it = m_signals.find(str);
        if(it != m_signals.end()){
            delete it->second;
            m_signals.erase(str);
        }

        return true;
    }

    template<typename Res, typename Type, typename ...Args>
    bool emitSignal(Res(Type::*signal)(Args...), Args... args){
        auto p = static_cast<Type*>(this);
        if(p)
            return  active((p->*signal)(args...),args...);
        else
            return false;
    }

    template<typename T,typename Res, typename Type, typename... Args>
    const Connect connect(MemberMethod<T> memberSignal, Object * reciver, MemberMethod<Res(Type::*)(Args...)> method, Connect::ConnectMode mode =Connect::Auto){
        auto p = static_cast<Type*>(reciver);
        //assert(p);
        if(p)
            return  connect(memberSignal, reciver, Method<Res(Args...)>(p, method), (void*)(method.MethodPointer()) ,mode);
        else
            return  Connect("",nullptr,nullptr,nullptr);
    }
    template<typename Res, typename Type,typename...Args,typename Res2, typename Type2,typename...Args2>
    static const Connect connect(Object* sender, Res(Type::*memberSignal)(Args...) , Object * reciver, Res2(Type2::*method)(Args2...) , Connect::ConnectMode mode =Connect::Auto){

        return  sender->connect(MemberMethod<Res(Type::*)(Args...) >(memberSignal), reciver, MemberMethod<Res2(Type2::*)(Args2...)>(method),mode);

    }

    template<typename T, typename Res,typename... Args >
    const Connect connect( MemberMethod<T> memberSignal, Res(*method)(Args...) ){

        return connect(memberSignal, nullptr, method, static_cast<void*>(method) ,Connect::Direct);
    }

    template< typename Res, typename Type,typename...Args, typename Res2,typename... Args2>
    static const Connect connect(Object* sender, Res(Type::*memberSignal)(Args...) , Res2(*method)(Args2...) ){

        return sender->connect(MemberMethod<Res(Type::*)(Args...) >(memberSignal), method);

    }


    template<typename T,typename Res, typename Type, typename... Args>
    void disconnect(MemberMethod<T> memberSignal, Object * reciver, MemberMethod<Res(Type::*)(Args...)> method){
        disconnect(memberSignal,  reciver, Method<Res(Args...)>(reciver,method), (void*)method());
    }

    template<typename Res, typename Type,typename...Args,typename Res2, typename Type2,typename...Args2>
    static void disconnect(Object* sender, Res(Type::*memberSignal)(Args...) , Object * reciver, Res2(Type2::*method)(Args2...) ){

        return  sender->disconnect(MemberMethod<Res(Type::*)(Args...) >(memberSignal), reciver, MemberMethod<Res2(Type2::*)(Args2...)>(method));

    }
    template<typename T, typename Res,typename... Args >
    void disconnect( MemberMethod<T> memberSignal, Res(*method)(Args...) ){

         disconnect(memberSignal, nullptr, method, static_cast<void*>(method));
    }

    template< typename Res, typename Type,typename...Args, typename Res2,typename... Args2>
    static void disconnect(Object* sender, Res(Type::*memberSignal)(Args...) , Res2(*method)(Args2...) ){

        return sender->disconnect(MemberMethod<Res(Type::*)(Args...) >(memberSignal), method);

    }


    void disconnect(const Connect&conn);
    static void disconnect(Object* sender, const Connect&conn);

    void disconnect( Object* reciver);
   static   void disconnect(Object*sender, Object* reciver);

   template<typename Res, typename Type,typename...Args>
   void disconnect(MemberMethod<Res(Type::*)(Args...)> memberSignal, Object * reciver){
       auto p = static_cast<Type*>(this);
       if(!p)
           return;
       auto signal = p->memberSignal(Args()...);
       for(auto it = m_connects.begin(); it != m_connects.end();){
           if(it->signal()== signal && it->Reciver() == reciver){
               it = m_connects.erase(it);
           }else{
               it++;
           }
       }
   }

   template<typename Res, typename Type,typename...Args>
   static void disconnect(Object*sender, MemberMethod<Res(Type::*)(Args...)> memberSignal, Object * reciver){
       sender->disconnect(memberSignal, reciver);
   }
protected:
    template<typename Res1,typename Type, typename... Args1 , typename Res, typename... Args>
    const Connect connect( MemberMethod<Res1(Type::*)(Args1...)> memberSignal, Object * reciver, Method<Res(Args...)> method, void * data ,Connect::ConnectMode mode =Connect::Auto){
        auto p = static_cast<Type*>(this);
        if(!p)
            return Connect("",nullptr,nullptr,nullptr);
        auto str = (p->* memberSignal.MethodPointer())(Args()...);
        using _type =typename SlotMethodWrap<Res(Args...)>::Placeholder_size_type;
        Connect conn(str, reciver, new Method<DefaultSlotRType(Args...)>( SlotMethodWrap<Res(Args...)>::ToMethod(method, _type()) ),data,mode);

        auto it =m_connects.find(conn);
        if(it != m_connects.end()){
            delete it->Method() ;
            m_connects.erase(it);
        }

        m_connects.insert(conn);
        return conn;
        //m_connects.insert()


    }

    template< typename Res, typename... Args>
    const Connect connect( std::string Signal, Object * reciver, Method<Res(Args...)> method, void * data ,Connect::ConnectMode mode =Connect::Auto){
        if(m_signals.find(Signal) == m_signals.end())
            return Connect("",nullptr,nullptr, nullptr);
        using _type =typename SlotMethodWrap<Res(Args...)>::Placeholder_size_type;
        Connect conn(Signal, reciver, new Method<DefaultSlotRType(Args...)>( SlotMethodWrap<Res(Args...)>::ToMethod(method, _type()) ),data,mode);

        auto it =m_connects.find(conn);
        if(it != m_connects.end()){
            delete it->Method() ;
            m_connects.erase(it);
        }

        m_connects.insert(conn);
        return conn;
        //m_connects.insert()


    }

    template<typename Res1,typename Type, typename... Args1 , typename Res, typename... Args>
    void disconnect( MemberMethod<Res1(Type::*)(Args1...)> memberSignal, Object * reciver, Method<Res(Args...)> method, void * data  ){
        auto p = static_cast<Type*>(this);
        if(!p)
            return ;
        auto str = (p->* memberSignal.MethodPointer())(Args()...);
         Connect conn(str, reciver, nullptr ,data);
        disconnect(conn);
    }

    template< typename Res, typename... Args>
    void disconnect( std::string Signal, Object * reciver, Method<Res(Args...)> method, void * data ){
         if(m_signals.find(Signal) == m_signals.end())
              return;
         Connect conn(Signal, reciver, nullptr ,data);
        disconnect(conn);
    }

    class FindConnectBySignal{
    public:
        bool operator()(const Connect& a, const Connect& b){
            if(a.signal() == b.signal())
                return true;
            else
                return false;
        }
    };

    template<typename... Args>
    bool active(const std::string&signal, Args... args){
        Connect conn(signal, nullptr,nullptr, nullptr);
        // auto result =  std::equal_range(m_connects.begin(), m_connects.end(), conn,FindConnectBySignal() );
        // auto first = std::lower_bound(m_connects.begin(), m_connects.end(), conn,FindConnectBySignal());
        //  auto last = std::upper_bound(m_connects.begin(), m_connects.end(), conn,FindConnectBySignal());
        for(auto it = m_connects.begin(); it != m_connects.end(); it++){
            if(it->signal() == signal){
                auto p = static_cast<const Method<void(Args...)>*>(it->Method()) ;
                if(p){
                    auto new_bind = (*p).BindParams(args...);
                    // ;
                    Method<void(void)> new_method=std::function<void(void)>(new_bind);
                    switch(it->ConnectedMode()){
                    case Connect::Auto:
                        if(it->Reciver() == this || it->Reciver() == nullptr){
                            new_method();

                        }else{

                         return    SendSignalEvent(new_method,it->Reciver());
                            //..............异步调用
                        }
                        break;
                    case Connect::Direct:
                         new_method();

                        break;

                    case Connect::Queued:
                        return  SendSignalEvent(new_method,it->Reciver());
                        break;

                    }
                }else{
                    //params 不匹配
                }
            }
        }
        return true;
    }

    virtual bool SendSignalEvent(const Method<void(void)>& method, const Object *reciver);
    virtual void InvokeMethod(Object*sender,const Method<void(void)>& method);

    void SetSlotSender(Object* sender);
    Object* Sender();

private:

    std::map<std::string, MethodInfo*,std::greater<std::string> > m_signals;
    std::set<Connect>  m_connects;
    std::map<std::string,IProperty*> m_propertys;

    Object  *      m_slot_sender = nullptr;
};

#endif // OBJECT_H
