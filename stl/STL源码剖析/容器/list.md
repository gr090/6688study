# list

## list概述

**环形双向链表**

**特点：**

- 底层是使用链表实现的，支持双向顺序访问
- 在list中任何位置进行**插入和删除的速度都很快**
- **不支持随机访问**，为了访问一个元素，必须遍历整个容器
- 与其他容器相比，**额外内存开销大**

**设计目的：**令容器在任何位置进行插入和删除都很快

**何时使用：**

- 容器需要不断地在中间插入或删除元素
- 无论删除还是增加，list的迭代器、引用、指针都不会失效

## list使用

* **头文件：**#include <list>

* **using声明：**using std::list;

* **初始化**

  list<T> v1; ==>v1是一个空的list

  list<T> v2(v1); ===>v2是v1的副本，拷贝构造

  list<T> v2=v1; ===>同上

  list<T> v1(n,val); ===>初始化n个value

  list<T> v1(iter1,iter2); ===>用迭代器iter1与iter2所指的区间内元素进行初始化

  list<T> v1(n); ===>初始化n个元素，每个元素使用默认值（int为0，string为空...）

  list<T> v1{a,b,c...}; ===>用元素a,b,c进行初始化

  list<T> v1={a,b,c...}; ===>同上

* **相关操作**

  运算符

  ```c++
  L1==L2;//判断L1和L2是否相等
  L1!=L2;//判断L1和L2是否相等
  >、>=、<、<= //以字典顺序进行比较
  ```

  取值：不能通过索引取值，只能遍历容器

* **相关函数**

  list不支持capacity()和reserve()、at()

  ```c++
  L.empty();//判断是否为空，返回布尔值
  L.size();//返回容器中的元素个数
  L.max_size();//返回容器的容量
  L.reverse();//将元素逆序
  
  L.front();//得到头元素
  L.back();//得到尾元素
  
  L1.swap(L2);//将L1和L2进行交换。容器的成员函数版本
  swap(L1,L2);//同上。系统函数版本
   
  L.assign(iter1,iter2);//将容器元素更换为一个迭代器的区间元素
  L.assign(n,t);//将容器元素变为n个t元素
  
  L.insert(iter,t);//在迭代器iter处插入t。返回所插位置处的迭代器
  L.insert(L.end(),10,t);//在容器L的末尾插入10个元素，每个元素都是t。返回新添加元素的第一个元素的迭代器
  L.insert(L.end(),{"a","b"...});//将后面花括号的每个元素插入容器v的尾部。返回新添加元素的第一个元素的迭代器
  L.insert(L.begin(),L2.end()-2,L2.end());//将容器L2的最后两个元素插入容器L的头部。返回新添加元素的第一个元素的迭代器
  注意：上面这个用法，后面两个参数不能为自身容器的范围（L.insert(L.begin(),L.end()-2,L.end());是错误的）
   
  //利用insert的返回值，下面代码为一直在lst容器的头部插入元素(类似于push_front的功能)
  list<string> lst;
  auto iter=lst.begin();
  while(cin>> word)
      iter=lst.insert(iter,word);//insert函数每回执行完，返回容器的首元素位置
  
  L.push_front(t);//头部追加元素t
  L.push_back(t);//尾部追加元素t
  L.pop_back();//删除尾元素
   
  L.earse(iter);//删除迭代器iter所指位置处的元素。返回删除位置处后一个元素迭代器
  L.erase(iter1,iter2);//删除迭代器iter1与iter2区间内的元素。返回删除最后一个元素的后一个元素迭代器
   
  L.clear();//清空容器，重新初始化容器
  
  L.resize(n);//将容器v的元素变为n个。若n<原始元素个数，删除多于元素。若n>原始元素个数，则用默认初始值初始化容器
  L.resize(n,t);//将容器元素变为n个t。与容器原始个数无关
   
  list<int> L(5,666);
  L.resize(3);//L内有3个元素，都是666
  L.resize(8);;//L内有8个元素，前5个个是666，后3个都是0(默认)
  L.resize(10,666);//L内有10个元素，都是666
  
  //下面的两个函数，是在在内存中创建一个对象，然后添加进相应的位置
  L.empalce(iter,args);//在容器L的位置添加创建一个args对象
  L.emplace_back(args);//在容器L的尾部添加创建一个args对象
  L.emplace_front(args);//在容器L的头部添加创建一个args对象
   
  例如
  class A{
      string name;int age;
  public:
      A(string name, int age);
  };
  int main()
  {
      list<A> L;
      L.emplace_back("C语言", 18);//在尾部创建一个元素
      L.emplace(v.begin(),"C++",18);//在容器L的头部添加一个元素
  }
  
  li.remove_if(t);//调用earse删除第一个值为t元素
  li.remove_if(条件);//删除参数参数为真的条件元素
   
  li.sort();//排序，默认升序
  li.sort(条件);//排序，参数条件取决于降序还是升序
   
  li.unique();//调用earse如果有单/多个相邻且相同的元素，则删除重复的元素
  li.unique(条件);//如果有多个相邻且满足参数条件的元素，则删除重复元素
   
  //m也是list类型
  t.merge(m);//要求t与m都是相同的排序规则(此版本为<)，将m内元素全部插入t内且仍使用此排序规则，m内元素清空
  t.merge(m,条件);//将t与m以参数条件的方式合并，其余规则同上
  ```

* **容器的迭代器、引用、指针**

  无论删除还是增加，list的迭代器、引用、指针都不会失效

## list的节点(__list_node)

- list的每个节点是一个结构体。以下是list的节点（node）结构：

