#ifndef METHODINFO_H
#define METHODINFO_H
#include <string>
#include <vector>

class MethodInfo
{
public:
    //MethodInfo();
   virtual  ~MethodInfo() = 0;
   virtual  const std::string Name()const = 0;

    virtual  const std::string Signature()const = 0;

   virtual const std::string ReturnType()const=0;

  virtual const std::vector<std::string> ParamsNames() const =0;

};

#endif // METHODINFO_H
