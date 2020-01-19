#ifndef METHOD_H
#define METHOD_H

#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include "methodinfo.h"
#include "indexseq.h"
#include "membermethod.h"
////////////////////////////////////
/// \brief The Method class  这是一个闭包方法，提供对所有泛函数类型的封装，这是一个变参类模板
///作者:肖志昂
///
///
template<typename ...Args> class Method;

template<typename Res, typename ...Args>
class Method<Res(Args...)>:public MethodInfo
{
public:
Method() = default;
Method(std::function<Res(Args...)>& func, std::string methodName=""):m_method_name(methodName), m_call(func)
{

}
Method(std::function<Res(Args...)>&& func, std::string methodName=""):m_method_name(methodName), m_call(func)
{

}

Method(const Method<Res(Args...)>& method):m_call(method.m_call),m_method_name(method.m_method_name)
{

}
Method(const Method<Res(Args...)>&& method):m_call(method.m_call),m_method_name(method.m_method_name)
{

}

 Method<Res(Args...)>& operator =(const Method<Res(Args...)>& method){
        m_call=method.m_call;
         m_method_name=method.m_method_name;
         return *this;
 }

template<typename T>
Method(T* obj, Res(T::*pfunc)(Args...), std::string name =""):m_method_name(name)
{
    using _type =typename MakeIndexes<sizeof...(Args)+1>::type;
    bindMemberMethod(obj, pfunc, _type());
}

template<typename T>
Method(T* obj, const MemberMethod<Res(T::*)(Args...)>& pfunc , std::string name =""):m_method_name(name)
{
    using _type =typename MakeIndexes<sizeof...(Args)+1>::type;
    bindMemberMethod(obj, pfunc.MethodPointer() , _type());
}

Method(Res(*pfunc)(Args...), std::string name=""):m_call(pfunc),m_method_name(name)
{

}

virtual ~Method()override{

}


operator bool(){
    return m_call.operator bool();
}
template<typename ...Paras>
auto  BindParams(Paras... args)const->decltype (std::bind(std::function<Res(Args...)>(), args...))
{
    auto f = std::bind(m_call, args...);

    return f;
}
//     decltype (std::bind(std::function<Res(Args...)>(), Paras()...)) BindParams(Paras... args){
//        auto f = std::bind(m_call, args...);
//        return f;
//    }

Res operator()(Args... args)const{
    return m_call(args...);
}

const std::string ReturnType()const override{
    return typeid(Res).name();
}

virtual  const std::string Name()const override{
    return  m_method_name;
}

virtual  const std::string Signature()const override{
    std::stringstream str;
    str<<ReturnType()<<" "<<Name()<<"(";
    auto  vec= ParamsNames();
    for(int i = 0 ; i < vec.size(); i++){
        str<<vec[i]<<" ";
    }

    str<<")";
    return str.str();
}


virtual const std::vector<std::string> ParamsNames() const override{
    std::vector<std::string>  vec{ typeid (Args).name()...};
    return vec;
}

protected:
template<int... indexs, typename T>
void bindMemberMethod(T* obj, Res(T::*pfunc)(Args...), IndexSeq<0,indexs...> ){
    m_call = std::bind(pfunc, obj, std::_Placeholder<indexs>()...);

}


private:
std::function<Res(Args...)> m_call;
std::string   m_method_name;

};

#endif // METHOD_H
