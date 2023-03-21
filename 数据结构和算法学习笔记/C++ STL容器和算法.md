# C++ STL容器和算法

## 顺序容器

标准库定义了三种顺序容器类型：

* vector：支持快速随机访问

* list：支持快速插入删除

* deque：双端队列

还提供了三种顺序容器适配器：

* stack：后进先出(LIFO)栈

* queue：先进先出(FIFO)队列

* priority_queue：有优先级管理的队列

> 适配器是使一事物的行为类似于另一事物的行为的一种机制。容器适配器让一种已存在的容器类型采用另一种不同的抽象类型的工作方式实现。例如，stack适配器可使任何一种顺序容器以栈的方式工作。
>
> 默认的stack和queue都基于deque容器实现，而priority_queue则在vector容器上实现。在创建适配器时，可通过将一个顺序容器指定为适配器的第二个类型实参，可覆盖其关联的基础容器类型。

### 迭代器

迭代器是一种检查容器内元素并遍历元素的数据类型。

标准库为每一种标准容器定义了一种迭代器类型，迭代器类型提供了比下标操作更通用化的方法。

> begin()返回的迭代器指向第一个元素
>
> end()返回的迭代器执行末端元素的下一个，通常称为**超出末端迭代器**，表明它执行一个不存在的元素。

每种容器还定义了一种名为const_iterator的类型，该类型只能用于读取容器内元素，而不能改变其值。

我们对普通iterator类型解引用时，得到对某个元素的非const引用。而如果对const_iterator类型解引用时，则可以得到一个指向const对象的引用。

```c++
for(vector<string>::const_iterator iter = text.begin(); iter != text.end(); ++iter){
    cout<<*iter<<endl;
}
```

### 容器元素的初始化

```c++
C<T> c; // 创建一个名为c的空容器。C是容器类型名，如vector，T是元素类型，如int或string，适用用所有容器
C<T> c(c2) // 创建容器c2的副本c；c和c2必须具有相同的容器类型，并存放相同类型的元素。适用于所有容器
C<T> c(b, e) // 创建c，其元素是迭代器b和e标示的范围内元素的副本，适用于所有容器
C<T> c(n, t) // 用n个值为t的元素创建容器c，其中值t必须是容器类型C的元素类型的值，或者是可转换为该类型的值 只适用于顺序容器
C<T> c(n) // 创建有n个值初始化元素的容器c  只适用于顺序容器
    
vector<int> ivec;
vector<int> ivec2(ivec); // 将一个容器复制给另一个容器时，类型必须匹配：容器类型和元素类型都必须相同

// 初始化为一段元素的副本
// 适用迭代器时，不要钱容器类型相同。容器内的元素类型也可以不相同，只有它们相互兼容，能够将要复制的元素转换为所构建的新容器的元素类型时，即可实现复制
list<string> slist(svec.begin(), svec.end());
vector<string>::iterator mid = svec.begin()+svec.size()/2;
deque<string> front(svec.begin(), mid); // 不包括mid
```

### 顺序容器的操作

* 容器定义的类型别名

| 别名                   | 说明                                             |
| ---------------------- | ------------------------------------------------ |
| size_type              | 无符号整型，足以存储此容器类型的最大可能容器长度 |
| iterator               | 此容器类型的迭代器类型                           |
| const_iterator         | 元素的只读迭代器类型                             |
| reverse_iterator       | 按逆序寻址元素的迭代器                           |
| const_reverse_iterator | 元素的只读逆序迭代器                             |
| difference_type        | 足够存储两个迭代器差值的有符号整型，可为负数     |
| value_type             | 元素类型                                         |
| reference              | 元素的左值类型，是value_type&的同义词            |
| const_reference        | 元素的常量左值类型，等效于const value_type&      |

* 添加元素

  ```c++
  c.push_back(t)  //在容器c的尾部添加值为t的元素
  c.push_front(t)  //在容器c的前端添加值为t的元素    只适用于list和deque容器类型
  c.insert(p, t) //在迭代器p所指向的元素前面插入值为t的新元素
  c.insert(p, n, t) //在迭代器p所指向的元素前面插入n个值为t的新元素
  c.insert(p, b, e) //在迭代器p所指向的元素前面插入由迭代器b和e标记的范围内的元素    
  ```

* 容器大小的操作

  ```c++
  c.size() // 返回容器c的元素个数，返回类型为c::size_type
  c.max_size() // 返回容器c可容纳的最多元素个数
  c.empty()  // 返回标记容器大小是否为0的布尔值
  c.resize(n) // 调整容器c的长度大小，使其能容纳n个元素 如果n<c.size()，则删除多出来的元素，否则添加采用值初始化的新元素
  c.resize(n, t) // 调整容器c的大小，使其能容纳n个元素。所有新添加的元素值都为t
  ```

* 访问元素

  ```c++
  c.back() // 返回容器c的最后一个元素的引用
  c.front() // 返回容器c的第一个元素的引用
  c[n]  // 返回下标为n的元素的引用 只适用于vector和deque容器
  c.at(n) // 返回下标为n的元素的引用 只适用于vector和deque容器  越界会抛出out_of_range异常
  ```

  必须是已存在的元素才能用下标操作符进行索引。通过下标操作进行赋值时，不会添加任何元素。

* 删除元素

  ```c++
  c.earse(p) // 删除迭代器p所指向的元素 返回一个迭代器，指向被删除元素后面的元素
  c.earse(b,e) // 删除迭代器b和e所标记的范围内所有的元素 返回一个迭代器，指向被删除元素段后面的元素
  c.clear() // 删除容器c内的所有元素
  c.pop_back() // 删除容器c内的最后一个元素
  c.pop_front() // 删除容器c内的第一个元素  只适用于list和deque容器
  
  ```

* 赋值与swap

  ```c++
  c1=c2 // 删除容器c1的所有元素，然后将c2的元素复制给c1，c1和c2的类型(包括容器类型和元素类型)必须相同
  c1.swap(c2) // 交换内容：调用完该函数后，c1中存放的是c2原来的元素，c2中存放的则是c1原来的元素。c1和c2的类型必须相同。该函数的执行速度通常要比将c2中的元素复制到c1的操作快
  c.assign(b,e) // 重新设置c的元素：将迭代器b和e标记的范围内所有的元素复制到c中。b和e必须不是指向c中元素的迭代器
  c.assign(n,t) // 将容器重新设置为存储n个值为t的元素
  ```
  
  swap()操作不会删除或插入任何元素，而且保证在常量时间内实现交换。由于容器内没有移动任何元素，因此迭代器不会失效。

### 1. vector

#include <vector>

* 初始化

  如果没有指定元素的初始化式，那么标准库将自行提供一个元素初始值进行值初始化。如果vector保存内置类型(如int类型)，那么标准库将用0值创建元素初始化式。如果vector保存的含有构造函数的类类型(如string)的元素，那么标准库将用该类型的默认构造函数创建元素初始化式。

* 自增长

  每当vector容器不得不分配新的存储空间时，以加倍当前容量的分配策略实现重新分配。

  ```c++
  v.capacity() // 获取在容器需要分配更多的存储空间之前能够存储的元素个数
  v.reserve(n) // 告诉vector容器应该预留多少个元素的存储空间
  ```

  capacity(容量)和size(长度)的区别：size指容器当前拥有的元素个数，而capacity则指容器必须分配新存储空间之前可以存储的元素总数。

### 2. list

### 3. deque



### 4. stack

#include <stack>

栈容器适配器支持的操作

| 函数         | 说明                                  |
| ------------ | ------------------------------------- |
| s.empty()    | 如果栈为空，则返回true，否则返回false |
| s.size()     | 返回栈中元素的个数                    |
| s.pop()      | 删除栈顶元素，但不返回其值            |
| s.top()      | 返回栈顶元素的值，但不删除该元素      |
| s.push(item) | 往栈顶压入新元素                      |



### 5. queue和priority_queue

进入队列的对象被放置在尾部，下一个被取出的元素则取自队列的首部。标准库提供了两种风格的队列：FIFO队列以及优先级队列。

priority_queue允许用户为队列中存储的元素设置优先级。这种队列不是直接将新元素放置在队列尾部，而是放在比它优先级低的元素前面。

> 优先队列是一种容器适配器，采用了堆这样的数据结构，保证了第一个元素总是整个优先队列中最大的(或最小的)元素。
>
> 优先队列默认使用vector作为底层存储数据的容器，在vector上使用了堆算法将vector中的元素构造成堆的结构，所以其实我们就可以把它当作堆，凡是需要用堆的位置，都可以考虑优先队列。

#include <queue>

队列和优先级队列支持的操作

| 函数         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| q.empty()    | 如果队列为空，则返回true，否则返回false                      |
| q.size()     | 返回队列中元素的个数                                         |
| q.pop()      | 删除队首元素，但不返回其值                                   |
| q.front()    | 返回队首元素的值，但不删除该元素。 该操作只适用于队列        |
| q.back()     | 返回队尾元素的值，但不删除该元素。 该操作只适用于队列        |
| q.top()      | 返回具有最高优先级的元素值，但不删除该元素。  该操作只适用于优先级队列 |
| q.push(item) | 对于queue，在队尾压入一个新元素。对于priority_queue，在基于优先级的适当位置插入新元素 |

priority_queue类模板参数

```c++
template <class T, class Container = vector<T>,class Compare = less<typename Container::value_type> >
class priority_queue;
```

class T：T是优先队列中存储的元素的类型。

class Container = vector<T>：Container是优先队列底层使用的存储结构，可以看出来，默认采用vector。
class Compare = less<typename Container::value_type> ：Compare是定义优先队列中元素的比较方式的类。

Compare后面跟着的less<typename Container::value_type>就是默认的比较类，默认是按小于(less)的方式比较，这种比较方式创建出来的就是大堆。所以优先队列默认就是大堆。

> **less**类的内部函数。参数列表中有左右两个参数，左边小于右边的时候返回true，此时优先队列就是大堆。
>
> ```c++
> template <class T> 
>         struct less : binary_function <T,T,bool> {
>           bool operator() (const T& x, const T& y) const {return x<y;}
> };
> ```
>
> **greater**类的内部函数，参数列表中有左右两个参数，左边大于右边的时候返回true，此时优先队列就是小堆。
>
> ```c++
> template <class T> 
>         struct greater : binary_function <T,T,bool> {
>           bool operator() (const T& x, const T& y) const {return x>y;}
> }; 
> ```
>
> 注意：less类和greater类只能比较内置类型的数据的大小，如果用户需要比较自定义类型的数据，就需要自己定义一个比较类，并且重载()。
>
> 同时less类和greater类也具有模板参数，因为他们也是模板，所以我们如果要存储自定义类型的元素，就要将自定义类型作为模板参数传递给less类和greater类。

如果需要创建小堆，就需要将less改为greater。



priority_queue构造函数：

```c++
priority_queue (const Compare& comp = Compare(), const Container& ctnr = Container());
```

构造函数中有两个参数，都具有默认值。这两个参数分别是**Compare**类和**Container**类的对象。

**构造函数默认将vector的对象传入构造函数作为底层结构，将less的对象传入构造函数按小于的方式比较构造大堆。**



#### 示例代码

priority_queue存储自定义类型元素

```c++
//Date是日期类
priority_queue<Date, vector<Date>, less<Date>> q1;

#include "iostream"
#include "queue"
using namespace std;
 
class Date {
private:
	int year;
	int month;
	int day;
public:
	//构造函数
	Date(int _year, int _month, int _day)
		:year(_year)
		, month(_month)
		, day(_day)
	{}
	//重载< 
	//当this指向的对象小于d对象返回true
	bool operator<(const Date& d) const {
		if ((year < d.year) || (year == d.year && month < d.month) ||
			(year == d.year && month == d.month && day < d.day)) {
			return true;
		}
		else {
			return false;
		}
	}
	//重载>
	//当this指向的对象大于d对象返回true
	bool operator>(const Date& d) const {
		if ((year > d.year) || (year == d.year && month > d.month) ||
			(year == d.year && month == d.month && day > d.day)) {
			return true;
		}
		else {
			return false;
		}
	}
};
 
 
int main() {
	Date d1(2021, 12, 12);
	Date d2(2020, 12, 12);
	Date d3(2022, 1, 1);
 
	priority_queue<Date, vector<Date>, less<Date>> q1;
	q1.push(d1);
	q1.push(d2);
	q1.push(d3);
 
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(d1);
	q2.push(d2);
	q2.push(d3);
}
```



## 关联容器

关联容器支持通过键来高效地查找和读取元素。两个基本的关联容器是map和set。map的元素以键-值(key-value)对的形式组织：键用作元素在map中的索引，而值则表示所存储和读取的数据。set则包含一个键值，并有效地支持关于某个键是否存在的查询。

* unordered_map
* map
* set
* multimap：支持同一个键多次出现的map类型
* multiset：支持同一个键多次出现的set类型

一般来说，如果希望有效地存储不同值的集合，那么使用set容器比较合适，而map容器则更适用于需要存储(乃至修改)每个键所关联的值的情况。

### 1. map

### 2. set



