#ifndef MEMBERMETHOD_H
#define MEMBERMETHOD_H
#include "methodinfo.h"

template <typename... Args> class MemberMethod;

template<typename Res, typename Type, typename... Args>
class MemberMethod<Res(Type::*)(Args...)>:public MethodInfo
{
     public:
     typedef   Res(Type::*pMemberFuncType)(Args...) ;
        typedef   Res(MemberFuncType)(Args...) ;


     MemberMethod(Res(Type::*pfunc)(Args...), std::string name=""):m_pfunc(pfunc),m_name(name)
     {

     }
     MemberMethod(const MemberMethod& method){
         m_pfunc = method.m_pfunc;
         m_name = method.m_name;
     }
      virtual  const std::string Name()const{
        return m_name;
     }

     virtual  const std::string Signature()const {

      }

     virtual const std::string ReturnType()const{

       }
     virtual  pMemberFuncType MethodPointer()const{
            return  static_cast<pMemberFuncType>(m_pfunc);
       }
     operator pMemberFuncType()const{
          return  static_cast<pMemberFuncType>(m_pfunc);
     }

     virtual const std::vector<std::string> ParamsNames() const{

     }
private:
Res(Type::*m_pfunc)(Args...)  ;
std::string        m_name;

};

#endif // MEMBERMETHOD_H
