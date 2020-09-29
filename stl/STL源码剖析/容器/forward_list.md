# forward_list

## forward_list概述

**单向链表**

**特点**：

- **①总的来说：****单向链表**。只支持单向顺序访问。在链表任何位置进行插入和删除操作速度都很快。
- **②设计目的：**令容器在任何位置进行插入和删除都很快
- **③**不支持随机访问，为了访问一个元素，必须遍历整个容器
- **④**与其他容器相比，额外内存开销大
- **⑤**C++11新标准新增的类型，设计的目的是：达到与最好的手写的单向链表数据结构相当的性能

**何时使用：**

- 容器需要不断地在中间插入或删除元素

它其实就是对C语言风格的单链表的封装，仅提供有限的接口，相对于std::list(双向链表，并且定义很多接口)来说它节省了内存，同时又有比list更好的运行时性能；相对于自己实现的C风格的单链表(hand-written c-style linked list)而言，`forward_list`也有与其不相上下的效率表现。

> “`forward_list`设计的目标是, 使用`forward_list`不会比使用自己手写的C风格单链表有更多的时间和空间的开销, 任何有悖于这个目标的接口和特性都会被标准拒之门外”

## forward_list使用

* **头文件**：\#include <forward_list>

* **using声明**：using std::forward_list;

* **初始化**

  forward_list<T> v1; ==>v1是一个空的forward_list

  forward_list<T> v2(v1); ===>v2是v1的副本，拷贝构造

  forward_list<T> v2=v1; ===>同上

  forward_list<T> v1(n,val); ===>初始化n个value

  forward_list<T> v1(iter1,iter2); ===>用迭代器iter1与iter2所指的区间内元素进行初始化

  forward_list<T> v1(n); ===>初始化n个元素，每个元素使用默认值（int为0，string为空...）

  forward_list<T> v1{a,b,c...}; ===>用元素a,b,c进行初始化

  forward_list<T> v1={a,b,c...}; ===>同上

* **相关操作**

  运算符

  ```c++
  fL1==fL2;//判断fL1和fL2是否相等
  fL1!=fL2;//判断fL1和fL2是否相等
  >、>=、<、<= //以字典顺序进行比较
  ```

  取值：不能通过索引取值，只能遍历容器

* **相关函数**

  不支持size();、at();、back();、earse();、capacity();、reserve();、push_back();、pop_back()

  因为forward_after是一个链表，对某个元素进行操作，会使用到它的前一个元素，所以它会有单独的插入相关的函数和emplace()相关的函数

  ```c++
  fL.empty();//判断是否为空，返回布尔值
  fL.max_size();//返回容器的容量
  fL.reverse();//将元素逆序
  
  fL.front();//得到头元素
  fL.back();//得到尾元素
  
  fL1.swap(fL2);//将fL1和fL2进行交换。容器的成员函数版本
  swap(fL1,fL2);//同上。系统函数版本
   
  fL.assign(iter1,iter2);//将容器元素更换为一个迭代器的区间元素
  fL.assign(n,t);//将容器元素变为n个t元素
  
  fL.push_front(t);//头部追加元素t
  fL.pop_front();//删除首元素
   
  fL.clear();//清空容器，重新初始化容器
  
  fL.resize(n);//将容器fL的元素变为n个。若n<原始元素个数，删除多于元素。若n>原始元素个数，则用默认初始值初始化容器
  fL.resize(n,t);//将容器元素变为n个t。与容器原始个数无关
   
  forward_list<int> fL(5,666);
  fL.resize(3);//fL内有3个元素，都是666
  fL.resize(8);;//fL内有8个元素，前5个个是666，后3个都是0(默认)
  fL.resize(10,666);//fL内有10个元素，都是666
  
  fL.insert_after(iter,t);//在迭代器iter后插入一个元素t
  fL.insert_after(iter,n,t)//在迭代器iter后插入n个t元素
  fL.insert_after(iter,it1,it2);//在迭代器iter后插入迭代器it1到it2区间内的元素(it1，it2不能为lst的迭代器区间)
  fL.insert_after(iter,il);//在迭代器iter后插入il，il为一个花括号列表
  //以上函数都返回插入新元素的最后一个元素迭代器。若iter为尾后迭代器，则函数出错
  
  fL.emplace_after(iter,args);//在迭代器iter之后插入一个使用args创建的元素。返回这个新元素的迭代器
  
  fL.earse_after(iter);//删除迭代器iter之后的元素。返回被删除元素的下一个迭代器位置
  fL.earse_after(iter1,iter2);//删除iter1之后到iter2区间内的元素，返回被删除的最后一个元素的下一个迭代器位置
  
  //m也是forward_list类型
  fL.merge(m);//要求t与m都是相同的排序规则(此版本为<)，将m内元素全部插入t内且仍使用此排序规则，m内元素清空
  fL.merge(m,条件);//将t与m以参数条件的方式合并，其余规则同上
  
  fL.remove_if(t);//调用earse删除第一个值为t元素
  fL.remove_if(条件);//删除参数参数为真的条件元素
   
  fL.sort();//排序，默认升序
  fL.sort(条件);//排序，参数条件取决于降序还是升序
   
  fL.unique();//调用earse如果有单/多个相邻且相同的元素，则删除重复的元素
  fL.unique(条件);//如果有多个相邻且满足参数条件的元素，则删除重复元素
  
  //t2也是forward_list类型，iter可以是首元素的前一个位置
  fL.splice_after(iter,t2);//将t2容器元素添加到迭代器iter之后的位置，并且清空t2
   
  fL.splice_after(iter,t2,iter2);//将t2容器内迭代器iter2之后的元素添加到fL容器的迭代器itrer处，并且移除iter2处元素
   
  fL.splice_after(iter,t2,iter1，iter2);//将t2容器内迭代器iter1与iter2区间内的元素添加到fL容器的iter处，并且删除迭代器iter1与iter2区间内的元素
  ```

* **容器的迭代器、引用、指针**

  无论删除还是增加，forward_list的迭代器、引用、指针都不会失效