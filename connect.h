#ifndef CONNECT_H
#define CONNECT_H


#include <string>
class Object;
class MethodInfo;

class Connect{
public:
    enum ConnectMode{
       Auto,
       Direct,
        Queued,
   };

    Connect(bool rc = false);

    Connect(const std::string& signal, Object*reciver, MethodInfo* method,void*pointer, ConnectMode mode = Auto);
   Connect(const Connect& conn);
    ~Connect();
    virtual  bool operator ==(const Connect& conn);
   virtual Connect& operator = (bool rc);
   virtual Connect& operator = (const Connect& conn);
    virtual bool operator<(const Connect&conn)const;
   //virtual bool operator>(const Connect&conn)const;
   virtual operator bool();
    const std::string& signal()const;
    const Object* Reciver()const;
    const MethodInfo* Method()const;
    const ConnectMode& ConnectedMode()const;
   // void SetPurePointer(void*  pointer);
    void* PurePointer();
private:

   std::string m_signal;
   Object* m_reciver;
   MethodInfo* m_slotmethod;
   ConnectMode  m_connectMode;
   void *      m_pure_pointer;

};

#endif // CONNECT_H
