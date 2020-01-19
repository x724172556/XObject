#ifndef SLOTMETHOD_H
#define SLOTMETHOD_H
#include "method.h"
#include "methodinfo.h"
#include "Object_global.h"
#include "indexseq.h"
template < typename... Args>  class SlotMethodWrap;
template <typename Res, typename... Args>
class SlotMethodWrap<Res(Args...)>
{
 public:
        typedef typename MakeIndexes<sizeof...(Args)+1>::type  Placeholder_size_type;
        template< int... I>
        static Method<DefaultSlotRType (Args...)> ToMethod(Method<Res(Args...)> method, IndexSeq<0,I...> ){
            return Method<DefaultSlotRType(Args...)>(std::bind(&CallMethod, method, std::_Placeholder<I>()...));
        }
        protected:
        static void CallMethod(Method<Res(Args...)> method, Args... args){
            method(args...);
        }




};

#endif // SLOTMETHOD_H
