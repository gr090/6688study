# deque

## deque概述

**双端队列**

**特点**：

- 支持快速随机访问（支持索引取值）
- 在头尾插入/删除速度很快
- deque是非常复杂的数据结构，由**多个vector**组成，迭代器使用时会在不同的区间跳转
- 存取元素的时候，deque的内部结构会多出一个间接过程，相比vector操作会慢一些
- 对内存有限制的系统中，deque比vector可以包含更多元素，因为它不止使用一块内存

**设计目的**：

在头尾两端分别做元素的插入和删除操作。相比于vector，vector在头部操作效率太低

**何时使用**：

需要在两端进行插入删除操作

**与vector最大差异：**

- 一在于deque**允许于常数时间内**对起头端进行元素的插入或移除动作
- **二在于deque没有所谓容量（capacity）观念**，因为它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来。 换句话说，像vector那样“因旧空间不足而重新配置一块更大空间，然后复制元素，再释放旧空间”这样的事情在deque 是不会发生的。也因此，deque**没有必要提供所谓的空间保留（reserve）功能**

虽然deque也提供 Ramdon Access Iterator，**但它的迭代器并不是原生指标**，其复杂度和 vector不可以相对比，这当然在在影响了各个运算层面 。 因此 ， **除非必要 ， 我们应尽可能选择使用vector而非deque**。 对deque进行的排序动作，为了最高效率，可将deque先完整复制到一个vector中，将vector排序后（利用STL sort 算法），再复制回deque。

## deque使用

- **头文件：**#include <deque>

- **using声明：**using std::deque;

- **初始化**

  deque<T> v1; ==>v1是一个空的deque

  deque<T> v2(v1); ===>v2是v1的副本，拷贝构造

  deque<T> v2=v1; ===>同上

  deque<T> v1(n,val); ===>初始化n个value

  deque<T> v1(iter1,iter2); ===>用迭代器iter1与iter2所指的区间内元素进行初始化

  deque<T> v1(n); ===>初始化n个元素，每个元素使用默认值（int为0，string为空...）

  deque<T> v1{a,b,c...}; ===>用元素a,b,c进行初始化

  deque<T> v1={a,b,c...}; ===>同上

- **相关操作**

  运算符

  ```c++
  d1==d2;//判断d1和d2是否相等
  d1!=d2;//判断d1和d2是否相等
  >、>=、<、<= //以字典顺序进行比较
  ```

  取值：索引取值d[0]，d[1]，d[2]...

- **相关函数**

  相比于vector：deque不支持capacity()和reserve();。支持push_front();和emplace_front();

  ```c++
  d.empty();//判断是否为空，返回布尔值
  d.size();//返回容器中的元素个数
  d.max_size();//返回容器的容量
  
  d.front();//得到头元素
  d.back();//得到尾元素
  d.at(int i);//得到下标i处的元素，若下标越界，会抛出异常
  
  d1.swap(d2);//将d1和d2进行交换。容器的成员函数版本
  swap(d1,d2);//同上。系统函数版本
   
  d.assign(iter1,iter2);//将容器元素更换为一个迭代器的区间元素
  d.assign(n,t);//将容器元素变为n个t元素
  
  d.insert(iter,t);//在迭代器iter处插入t。返回所插位置处的迭代器
  d.insert(v.end(),10,t);//在容器v的末尾插入10个元素，每个元素都是t。返回新添加元素的第一个元素的迭代器
  d.insert(v.end(),{"a","b"...});//将后面花括号的每个元素插入容器v的尾部。返回新添加元素的第一个元素的迭代器
  d.insert(d.begin(),d2.end()-2,d2.end());//将容器d2的最后两个元素插入容器d的头部。返回新添加元素的第一个元素的迭代器
  注意：上面这个用法，后面两个参数不能为自身容器的范围（d.insert(d.begin(),d.end()-2,d.end());是错误的）
   
  //利用insert的返回值，下面代码为一直在d容器的头部插入元素(类似于push_front的功能)
  deque<string> d;
  auto iter=d.begin();
  while(cin>> word)
      iter=d.insert(iter,word);//insert函数每回执行完，返回容器的首元素位置
  
  d.push_back(t);//尾部追加元素t
  d.push_front(t);//头部追加元素t
  d.pop_back();//删除尾元素
   
  d.earse(iter);//删除迭代器iter所指位置处的元素。返回删除位置处后一个元素迭代器
  d.erase(iter1,iter2);//删除迭代器iter1与iter2区间内的元素。返回删除最后一个元素的后一个元素迭代器
   
  d.clear();//清空容器，重新初始化容器
  
  d.resize(n);//将容器d的元素变为n个。若n<原始元素个数，删除多于元素。若n>原始元素个数，则用默认初始值初始化容器
  d.resize(n,t);//将容器元素变为n个t。与容器原始个数无关
   
  deque<int> d(5,666);
  d.resize(3);//d内有3个元素，都是666
  d.resize(8);;//d内有8个元素，前5个个是666，后3个都是0(默认)
  d.resize(10,666);//d内有10个元素，都是666
  
  //下面的两个函数，是在在内存中创建一个对象，然后添加进相应的位置
  d.empalce(iter,args);//在容器d的位置添加创建一个args对象
  d.emplace_back(args);//在容器d的尾部添加创建一个args对象
  d.emplace_front(args);//在容器d的头部添加创建一个args对象
   
  例如
  class A{
      string name;int age;
  public:
      A(string name, int age);
  };
  int main()
  {
      deque<A> d;
      d.emplace_back("C语言", 18);//在尾部创建一个元素
      d.emplace(v.begin(),"C++",18);//在容器d的头部添加一个元素
  }
   
  ```

- **容器操作使迭代器、引用、指针失效**

  向容器中添加或者删除元素可能会使容器的迭代器、引用、指针失效。失效的迭代器、引用、指针不再表示任何元素，使用起来非常危险

  **添加元素**

  - 如果添加到首尾元素之外的任何位置都会导致迭代器、引用、指针失效
  - 如果在首尾位置添加元素，迭代器会失效，但是引用、指针不会失效

  **删除元素**

  - 如果删除的是首尾之外的元素，那么指向被删除元素外的其它元素的迭代器、引用、指针都会失效
  - 如果删除的是首元素，迭代器、引用、指针不受影响
  - 如果删除的是尾元素，尾后迭代器失效，但其它迭代器、指针、引用都不受影响 

## deque的中控器与缓冲区

- **deque是由一段一段的定量连续空间构成**
  - 一旦有必要在deque 的前端或尾端增加新空间，便配置一段定量连续空间，串接在整个 deque的头端或尾端。
  - deque的最大任务，便是在这些分段的定量连续空间上，维护其整体连续的假象，并提供随机存取的接口。避开了“重新配置、复制、释放”的轮回，代价则是复杂的迭代器架构。
- 受到分段连续线性空间的字面影响，我们可能以为deque的实现复杂度和vector相比虽不中亦不远矣，其实不然。主要因为，既要分段连续线性空间，就必须有中央控制，而为了维护整体连续的假象，数据结构的设计及迭代器前进后退等动作都颇为繁琐。deque的实现代码量远比vector或 list都多得多。

> - deque采用一块所谓的map（注意，不是STL的map容器）做为主控
> - 这里**所谓map是一小块连续空间，其中每个元素（此处称为一个节点，node）都是指针**， 指向另一段（较大的）连续线性空间，称为缓冲区
> - 缓冲区才是deque 的储存空间主体。SGI STL允许我们指定缓冲区大小，**默认值0表示将使用512 bytes缓冲区**
>
> ```c++
> template <class _Tp, class _Alloc>
> class _Deque_base {
> public:
>   typedef _Deque_iterator<_Tp,_Tp&,_Tp*>             iterator;
>   ...
> protected:
>   _Tp** _M_map; //指向 map，map是块连续空间，其内的每个元素都是一个指针（称为节点），指向一块缓冲区
>   size_t _M_map_size; //map内可容纳多少指针
>   iterator _M_start;
>   iterator _M_finish;    
>   ...
> };
> 
> template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
> class deque : protected _Deque_base<_Tp, _Alloc> {
> public:                         // Basic types
>   typedef _Tp value_type;
>   typedef value_type* pointer;
>   ...
> protected:                      // Internal typedefs
>   typedef pointer* _Map_pointer;      
>   ...
> };
> ```

* map其实是一个T**，也就是说它是一个指针，所指之物又是一个指针，指向型别为T的一块空间，如下图所示

![deque结构设计中map和node-buffer的关系](./../img/deque结构设计中map和node-buffer的关系.png)

## deque的迭代器

- deque是分段连续空间。**维护其“整体连续”假象的任务**，着落在迭代器的operator++ 和 operator-- 两个运算符身上
- **让我们思考一下，deque迭代器应该具备什么结构：**
  - 首先，它必须能够指出分段连续空间（亦即缓冲区）在哪里
  - 其次它必须能够判断自己是否已经处于其所在缓冲区的边缘，如果是，一旦前进或后退时就必须跳跃至下一个或上一个缓冲区
  - 为了能够正确跳跃，deque必须随时掌握管控中心（map）

> ### cur、first、last、node、buffer_size()函数
>
> - cur：当前迭代器所指的元素
> - first：迭代器当前所指的缓冲区区间的头
> - last：迭代器当前所指的缓冲区区间的尾
> - node：指向deque管控器中的一个指针。用来指示当前迭代器所指的缓冲区归管控器中的哪一个指针所管理
> - buffer_size()函数：绝对缓冲区大小的函数，调用__deque_buf_size()全局函数（见下面介绍）
>
> ```c++
> template <class _Tp, class _Ref, class _Ptr>
> struct _Deque_iterator {
>   typedef _Deque_iterator<_Tp, _Tp&, _Tp*>             iterator;
>   typedef _Deque_iterator<_Tp, const _Tp&, const _Tp*> const_iterator;
>   static size_t _S_buffer_size() { return __deque_buf_size(sizeof(_Tp)); }
> 
>   // 未继承 std::iterator，所以必须自行撰写五个必要的迭代器相应型别
>   typedef random_access_iterator_tag iterator_category;
>   typedef _Tp value_type;
>   typedef _Ptr pointer;
>   typedef _Ref reference;
>   typedef size_t size_type;
>   typedef ptrdiff_t difference_type;
>   typedef _Tp** _Map_pointer;
> 
>   typedef _Deque_iterator _Self;
> 
>   //保持与容器的联结
>   _Tp* _M_cur; // 此迭代器所指之缓冲区中的现行（current）元素
>   _Tp* _M_first; // 此迭代器所指之缓冲区的头
>   _Tp* _M_last; // 此迭代器所指之缓冲区的尾（含备用空间）
>   _Map_pointer _M_node; // 指向管控中心
> ```
>
> ![deque的中控器、缓冲区、迭代器的相互关系](./../img/deque的中控器、缓冲区、迭代器的相互关系.png)
>
> ### deque_buf_size()全局函数
>
> - 迭代器中用来决定缓冲区大小的函数buffer_size()，直接调用__deque_buf_size()， 这是个全局函数，定义如下：
>   - 如果size（元素大小，sizeof(value_type)）小于512，传回512/size
>   - 如果size不小于 512，返回1
>
> ```c++
> inline size_t __deque_buf_size(size_t __size) {
>   return __size < 512 ? size_t(512 / __size) : size_t(1);
> }
> ```
>
> ### 演示说明
>
> - 假设我们声明一个deque<int,alloc,8>，那么这个deque的缓冲区大小为8（是指缓冲区可以存放8个int类型的元素），缓冲区的字节数为4*8=32bytes
> - 再假设经过某些操作之后，deque拥有20个元素， 那么其**begin() 和 end()所传回的两个迭代器应该如下图所示**。这两个迭代器事实上一直保持在deque内，名为start 和 finish，稍后在deque数据结构中便可看到
> - **20个元素需要20/8=3个缓冲区，所以map之内运用了三个节点**
>   - 迭代器start内的cur指标当然指向缓冲区的第一个元素
>   - 迭代器finish内的cur指标当然指向缓冲区的最后元素（的下一位置）
>   - 注意，**最后一个缓冲区尚有备用空间**。 如果有新元素要插入于尾端，可直接拿此备用空间来使用
>
> ![deque迭代器演示说明](./../img/deque迭代器演示说明.png)