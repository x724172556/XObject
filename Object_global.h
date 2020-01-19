#ifndef OBJECT_GLOBAL_H
#define OBJECT_GLOBAL_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(OBJECT_LIBRARY)
#  define OBJECT_EXPORT Q_DECL_EXPORT
#else
#  define OBJECT_EXPORT Q_DECL_IMPORT
#endif



#define _SIGNAL(signal_args) \
std::string signal_args{\
   return __FUNCTION__ ;\
}
//#include "method.h"


#define _PROPERTY_IMP(name,type,Class,parent,reader,writer,signal)  \
              name,Method<type(void)>(parent,&Class::reader),\
               Method<void(const type &)>(parent,&Class::writer),\
              Method<std::string(type)>(parent,&Class::signal),parent



using DefaultSlotRType = void;

#endif // OBJECT_GLOBAL_H
