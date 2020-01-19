# XObject
## Using C ++ 11 (indefinite parameter template) to implement Qt-like signals-slots mechanism, additional property binding.
### 1.概论

  刚开始写工程的时候，并没有想到实现信号与槽，但是随着开发的进行，不管是早期的属性绑定，还是事件传输都因为c++的语言特性（强类型）对接口进行了限制，虽然可以使用基类来传输对象，但是实际上，已经丢失了派生的数据类型，c++的语言特性决定了，这种丢失几乎是无法动态还原的，只能使用静态（固定的写好的代码来进行类型转换）的，这也是早期Qt实现信号与槽要使用moc的原因，实现静态的代码转化。但是如今已经步入了c++1x时代了，新的c++特性已经非常的厉害了，这里就想着能不能通过c++11来实现signals-slots，最后发现不定参模板，这里便做了一个简单的实现(意思就是非常的粗糙)
  
  另外，本人水平有限，这个工程只是起到了抛砖引玉的作用，只是自己的一个想法，更多细节问题都没有去处理，也希望大家能给我提更多的意见，看能否更好的优化.
  
### 2.建立

  这个工程是一个库，工程使用Qt的qmake编程，可以直接使用qmake编译出动态库;
  
  也可以自己使用源文件和头文件编译出库。
  
### 3.使用
  使用中只要继承其中的Object类型，并且实现其中的SendSignalEvent(...)，需要实现这个函数将Object嵌入到自己实现的事件机制中
  
  这个工程的实现和实际的qt仍然有区别：
  
  1>signal不能connect signal，只能连接到slots(函数指针),slots可以是通用类型的指针
  
  2>由于对槽没有做特殊的处理，它只是普通的函数，所以connect不支持使用字符串来指向信号和槽，只能使用函数指针，另外connect和disconnect必须一一对应，对象销毁前必须disconnect的signal-slot的连接
  
  3>这个工程是非线程安全的，因为工程是针对单线程开发（个人虽然也经常使用多线程，但并不喜欢，多线程带来的大量的资源竞争问题，拉低了效率）,如果需要支持多线程可能需要添加线程安全机制，避免竞争问题.
