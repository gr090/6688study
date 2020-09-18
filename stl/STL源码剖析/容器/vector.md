# vector

## vector概述

**vector是**可变大小数组

vector与array非常相似，两者的唯一差别在于空间的运用的灵活性。array是静态空间，一旦配置了就不能改变；vector是动态空间，随着元素的加入，它的内部机制会自行扩产空间以容纳新元素。vector的实现技术，关键在于其对大小的控制以及重新配置时的数据移动效率。

**特点：**

- 支持快速随机访问。在尾部之外的位置插入或删除元素可能很慢
- 元素保存在**连续的内存空间**中，因此通过下标取值非常快
- 在容器中间位置添加或删除元素**非常耗时**
- 一旦vector内存不足，重新申请内存之后，和原vector相关的指针，引用，迭代器都失效。内存重分配耗时很长

通常，使用vector是最好的选择，如果没有什么特殊要求，最好使用vector

与其他容器的比较：

| 名称         | 特性                                                         |
| ------------ | ------------------------------------------------------------ |
| vector       | **可变大小数组**。支持快速随机访问。在尾部之外的位置插入或删除元素可能很慢 |
| deque        | **双端队列**。支持快速随机访问。在头尾插入/删除速度很快      |
| list         | **双向链表**。只支持双向顺序访问。在list中任何位置进行插入和删除的速度都很快 |
| forward_list | **单向链表**。只支持单向顺序访问。在链表任何位置进行插入和删除操作速度都很快 |
| array        | **固定大小数组**。支持快速随机访问。不能添加或删除元素       |
| string       | **与vector相似的容器**，但专门用于保存字符。随机访问快。在尾部插入或删除速度快 |

## vector使用

* **头文件：**#include <vector>

* **using声明：**using std::vector;

* **初始化**

  vector<T> v1; ==>v1是一个空的vector

  vector<T> v2(v1); ===>v2是v1的副本，拷贝构造

  vector<T> v2=v1; ===>同上

  vector<T> v1(n,val); ===>初始化n个value

  vector<T> v1(iter1,iter2); ===>用迭代器iter1与iter2所指的区间内元素进行初始化

  vector<T> v1(n); ===>初始化n个元素，每个元素使用默认值（int为0，string为空...）

  vector<T> v1{a,b,c...}; ===>用元素a,b,c进行初始化

  vector<T> v1={a,b,c...}; ===>同上

* **相关操作**

  运算符

  ```c++
  v1==v2;//判断v1和v2是否相等
  v1!=v2;//判断v1和v2是否相等
  >、>=、<、<= //以字典顺序进行比较
  ```

  取值 索引取值：v[0]，v[1]，v[2]...

* **相关函数**

```c++
v.empty();//判断是否为空，返回布尔值
v.size();//返回容器中的元素个数
v.max_size();//返回容器的容量

v.front();//得到头元素
v.back();//得到尾元素
v.at(int i);//得到下标i处的元素，若下标越界，会抛出异常

v1.swap(v2);//将v1和v2进行交换。容器的成员函数版本
swap(v1,v2);//同上。系统函数版本
 
assign(iter1,iter2);//将容器元素更换为一个迭代器的区间元素
assign(n,t);//将容器元素变为n个t元素

v.insert(iter,t);//在迭代器iter处插入t。返回所插位置处的迭代器
v.insert(v.end(),10,t);//在容器v的末尾插入10个元素，每个元素都是t。返回新添加元素的第一个元素的迭代器
v.insert(v.end(),{"a","b"...});//将后面花括号的每个元素插入容器v的尾部。返回新添加元素的第一个元素的迭代器
v.insert(v.begin(),v2.end()-2,v2.end());//将容器v2的最后两个元素插入容器v的头部。返回新添加元素的第一个元素的迭代器
注意：上面这个用法，后面两个参数不能为自身容器的范围（v.insert(v.begin(),v.end()-2,v.end());是错误的）
 
 
//利用insert的返回值，下面代码为一直在lst容器的头部插入元素(类似于push_front的功能)
vector<string> v;
auto iter=lst.begin();
while(cin>> word)
    iter=v.insert(iter,word);//insert函数每回执行完，返回容器的首元素位置

//vector不支持pop_front
 
v.push_back(t);//尾部追加元素t
v.pop_back();//删除尾元素
 
v.earse(iter);//删除迭代器iter所指位置处的元素。返回删除位置处后一个元素迭代器
v.erase(iter1,iter2);//删除迭代器iter1与iter2区间内的元素。返回删除最后一个元素的后一个元素迭代器
 
v.clear();//清空容器，重新初始化容器

v.resize(n);//将容器v的元素变为n个。若n<原始元素个数，删除多于元素。若n>原始元素个数，则用默认初始值初始化容器
v.resize(n,t);//将容器元素变为n个t。与容器原始个数无关
 
vector<int> v(5,666);
v.resize(3);//v内有3个元素，都是666
v.resize(8);;//v内有8个元素，前5个个是666，后3个都是0(默认)
v.resize(10,666);//v内有10个元素，都是666

//vector不支持emplace_front();
//下面的两个函数，是在内存中创建一个对象，然后添加进相应的位置
v.empalce(iter,args);//在容器v的位置添加创建一个args对象
v.emplace_back(args);//在容器v的尾部添加创建一个args对象
 
例如
class A{
    string name;int age;
public:
    A(string name, int age);
};
int main()
{
    vector<A> v;
    v.emplace_back("C语言", 18);//在尾部创建一个元素
    v.emplace(v.begin(),"C++",18);//在容器v的头部添加一个元素
}

v.capacity();//返回当前容器的容量(总共能存多少个)
v.reserve(n);//为容器v重新分配n个内存空间（如果n<=当前容器大小，则什么都不做）
```

* **容器操作使迭代器、引用、指针失效**

向容器中添加或者删除元素可能会使容器的迭代器、引用、指针失效。失效的迭代器、引用、指针不再表示任何元素，使用起来非常危险。如果vector**没有内存重分配**。插入位置之前的元素的迭代器、引用、指针有效，插入位置之后的迭代器、引用、指针都失效。如果**内存重分配**，则所有的迭代器、引用、指针都失效。删除元素之前的迭代器、引用、指针有效，之后的失效

## vector的迭代器

vector维护的是一个**连续线性空间**，所以不论其元素类别是什么，普通指针都可以作为vector的迭代器而满足所有必要条件

vector迭代器支持有操作有（普通指针也具备）：operator*、operator->、operator++、operator--、operator+、operator-、operator+=、operator-=

vector支持随机存取，而普通指针正有着这样的能力，所以，**vector提供的是随机访问迭代器**（Random Access iterators）

vector的迭代器定义如下：

```c++
  typedef _Tp value_type;
  typedef value_type* iterator;
```

```c++
vector<int>::iterator ivite;   //等同于int* ivite;
vector<Shape>::iterator svite; //等同于Shape* svite;
```

## vector的数据结构

vector的数据结构非常简单：**一个线性连续空间**。它以两个迭代器start和finish分别指向配置得来的连续空间中目前已被使用的范围，并以迭代器end_of_storage指向整块连续空间（含备用空间）的尾端。

```c++
template <class _Tp, class _Alloc> 
class _Vector_base {
...
  protected:
  _Tp* _M_start; // 表示目前使用空间的头
  _Tp* _M_finish; // //表示目前使用空间的尾
  _Tp* _M_end_of_storage; //表示目前可用空间的尾
...
};
```

