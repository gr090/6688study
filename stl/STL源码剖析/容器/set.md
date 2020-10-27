# set

## set概述

元素依据其value自动排序，每个元素只能出现一次，不允许重复

> ### set的特性
>
> - set所有元素都会根据元素的键值自动被排序
> - set中的键值就是实值，实值就是键值
> - 默认情况下set不允许两个元素重复

> ### set拥有与list的相同的某些性质
>
> - 当客户端对它进行元素新增（insert）操作或删除（erase）操作时，操作之前的所有迭代器在操作完成之后依然有效（当然，被删除的那个元素的迭代器无效）

> ### 相关算法
>
> - STL提供了一组set/multiset相关算法，包括交集（set_intersection）、联集（set_union）、差集（set_difference）、对称差集（set_symmetric_difference）
> - 详情会在后面的“算法”文章中介绍

> ### set的底层结构
>
> - 由于RB-tree是一种平衡二叉搜索树，自动排序的效果很不错，所以标准的STL set是以RB-tree为底层机制
> - 又由于set所开放的各种操作接口，RB-tree也都提供了，所以几乎所有的set操作行为，都只是转调用RB-tree的操作行为而已

## set使用

- set<value>：没有key与value之分，只有一个key数据，且默认为升序
- 头文件：#include <set>
- key不可以重复，默认为升序排序
- 不提供下标操作（下标运算符和at函数）

### 升序、降序操作

- set的key默认为升序排序，我们也可以将key设置为显式地升序或者设置为降序排序
- 下面两个标准库函数（less、greater）都在头文件#include <xfunctional>中
- **升序操作**

```c++
//set<int> s; //升序
set<int, std::less<int>> s; //升序
s.insert(1);
s.insert(3);
s.insert(2);
 
for (const auto &w : s) {
    cout << w<< endl;
}
// 1 2 3
```

- **降序操作**

```c++
set<int, std::greater<int>> s;
s.insert(1);
s.insert(3);
s.insert(2);
 
for (const auto &w : s) {
    cout << w<< endl;
}
//3 2 1
```

### 迭代器与遍历

- 当解引用一个关联容器迭代器时，我们得到的是容器的value_type的值的引用
- **重点：**与map一样，set也只能够通过迭代器访问set的键值（key），但不能改变

```c++
set<int> iset = { 0,1,2,3,4 };
set<int>::iterator set_it = iset.begin();
while (set_it != iset.end()) {
    *set_it = 666; //错误，不能改变值
    cout << *set_it<< endl; //正确，可以读取值
}
```

### 添加元素

与map相似，见map的介绍

### 删除元素

与map相似，见map的介绍

### 演示案例

```c++
//我们将字符串输入保存到map中，将不想要统计的字符串事先定义在set中。然后统计字符串出现的次数
#include <iostream>
#include <map>
#include <set>
#include <string>
 
using namespace std;
 
int main()
{
    map<string, size_t> word_count;
    set<string> exclude = { "The","a","but","and" };
    string word;
 
    while (cin >> word) {
        //find如果没有查找到，返回set的尾后迭代器
        if(exclude.find(word)==exclude.end())
            ++word_count[word];
    }
 
    for (const auto &w : word_count) {
        cout <<w.first <<"："<<w.second<<((w.second>1)?"times":"time")<< endl;
    }
    return 0;
}
```

## set源码

```c++
//代码摘录于stl_set.h
template <class _Key, class _Compare, class _Alloc>
class set {
  // requirements:

  __STL_CLASS_REQUIRES(_Key, _Assignable);
  __STL_CLASS_BINARY_FUNCTION_CHECK(_Compare, bool, _Key, _Key);

public:
  // typedefs:

  typedef _Key     key_type;
  typedef _Key     value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;
private:
  typedef _Rb_tree<key_type, value_type, 
                  _Identity<value_type>, key_compare, _Alloc> _Rep_type;
  _Rep_type _M_t;  // red-black tree representing set 采用红黑树来表现set
public:
  typedef typename _Rep_type::const_pointer pointer;
  typedef typename _Rep_type::const_pointer const_pointer;
  typedef typename _Rep_type::const_reference reference;
  typedef typename _Rep_type::const_reference const_reference;
  typedef typename _Rep_type::const_iterator iterator;
  //注意上一行，iterator定义为RB-tree的const_iterator，表示
  //set的迭代器无法执行写入操作
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::const_reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::allocator_type allocator_type;

  // allocation/deallocation
  //注意，set一定使用RB-tree的insert_unique()而非insert_equal()
  //multiset才使用RB-tree的insert_equal()
  set() : _M_t(_Compare(), allocator_type()) {}
  explicit set(const _Compare& __comp,
               const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) {}

#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  set(_InputIterator __first, _InputIterator __last)
    : _M_t(_Compare(), allocator_type())
    { _M_t.insert_unique(__first, __last); }

  template <class _InputIterator>
  set(_InputIterator __first, _InputIterator __last, const _Compare& __comp,
      const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_unique(__first, __last); }
#else
  set(const value_type* __first, const value_type* __last) 
    : _M_t(_Compare(), allocator_type()) 
    { _M_t.insert_unique(__first, __last); }

  set(const value_type* __first, 
      const value_type* __last, const _Compare& __comp,
      const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_unique(__first, __last); }

  set(const_iterator __first, const_iterator __last)
    : _M_t(_Compare(), allocator_type()) 
    { _M_t.insert_unique(__first, __last); }

  set(const_iterator __first, const_iterator __last, const _Compare& __comp,
      const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_unique(__first, __last); }
#endif /* __STL_MEMBER_TEMPLATES */

  set(const set<_Key,_Compare,_Alloc>& __x) : _M_t(__x._M_t) {}
  set<_Key,_Compare,_Alloc>& operator=(const set<_Key, _Compare, _Alloc>& __x)
  { 
    _M_t = __x._M_t; 
    return *this;
  }
  
  //以下所有的set操作，RB-tree都已提供，所以set只要传递调用即可
  // accessors:
  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return _M_t.key_comp(); }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  iterator begin() const { return _M_t.begin(); }
  iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() const { return _M_t.rbegin(); } 
  reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  void swap(set<_Key,_Compare,_Alloc>& __x) { _M_t.swap(__x._M_t); }

  // insert/erase
  pair<iterator,bool> insert(const value_type& __x) { 
    pair<typename _Rep_type::iterator, bool> __p = _M_t.insert_unique(__x); 
    return pair<iterator, bool>(__p.first, __p.second);
  }
  iterator insert(iterator __position, const value_type& __x) {
    typedef typename _Rep_type::iterator _Rep_iterator;
    return _M_t.insert_unique((_Rep_iterator&)__position, __x);
  }
#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    _M_t.insert_unique(__first, __last);
  }
#else
  void insert(const_iterator __first, const_iterator __last) {
    _M_t.insert_unique(__first, __last);
  }
  void insert(const value_type* __first, const value_type* __last) {
    _M_t.insert_unique(__first, __last);
  }
#endif /* __STL_MEMBER_TEMPLATES */
  void erase(iterator __position) { 
    typedef typename _Rep_type::iterator _Rep_iterator;
    _M_t.erase((_Rep_iterator&)__position); 
  }
  size_type erase(const key_type& __x) { 
    return _M_t.erase(__x); 
  }
  void erase(iterator __first, iterator __last) { 
    typedef typename _Rep_type::iterator _Rep_iterator;
    _M_t.erase((_Rep_iterator&)__first, (_Rep_iterator&)__last); 
  }
  void clear() { _M_t.clear(); }

  // set operations:

  iterator find(const key_type& __x) const { return _M_t.find(__x); }
  size_type count(const key_type& __x) const {
    return _M_t.find(__x) == _M_t.end() ? 0 : 1;
  }
  iterator lower_bound(const key_type& __x) const {
    return _M_t.lower_bound(__x);
  }
  iterator upper_bound(const key_type& __x) const {
    return _M_t.upper_bound(__x); 
  }
  pair<iterator,iterator> equal_range(const key_type& __x) const {
    return _M_t.equal_range(__x);
  }

#ifdef __STL_TEMPLATE_FRIENDS
  template <class _K1, class _C1, class _A1>
  friend bool operator== (const set<_K1,_C1,_A1>&, const set<_K1,_C1,_A1>&);
  template <class _K1, class _C1, class _A1>
  friend bool operator< (const set<_K1,_C1,_A1>&, const set<_K1,_C1,_A1>&);
#else /* __STL_TEMPLATE_FRIENDS */
  friend bool __STD_QUALIFIER
  operator== __STL_NULL_TMPL_ARGS (const set&, const set&);
  friend bool __STD_QUALIFIER
  operator<  __STL_NULL_TMPL_ARGS (const set&, const set&);
#endif /* __STL_TEMPLATE_FRIENDS */
};
```

## set的使用案例

```c++
#include <iostream>
#include <set>
using namespace std;
 
int main()
{
	int i;
	int ia[5] = { 0,1,2,3,4 };
	set<int> iset(ia,ia+5);
	std::cout << "size=" << iset.size() << std::endl;                  // size=5
	std::cout << "3 count=" << iset.count(3) << std::endl << std::endl;// 3 count=1
 
	iset.insert(3);
	std::cout << "size=" << iset.size() << std::endl;                  // size=5
	std::cout << "3 count" << iset.count(3) << std::endl << std::endl; // 3 count=1
 
	iset.insert(5);
	std::cout << "size=" << iset.size() << std::endl;                  // size=6
	std::cout << "3 count" << iset.count(3) << std::endl << std::endl; // 3 count=1
 
	iset.erase(1);
	std::cout << "size=" << iset.size() << std::endl;                  // size=5
	std::cout << "3 count" << iset.count(3) << std::endl;              // 3 count=1
	std::cout << "1 count" << iset.count(1) << std::endl << std::endl; // 1 count=0
 
	set<int>::iterator ite1 = iset.begin();
	set<int>::iterator ite2 = iset.end();
	for (; ite1 != ite2; ite1++)
		std::cout << *ite1<<" ";
	std::cout << std::endl << std::endl;                          // 0 2 3 4 5
 
	//使用STL算法来搜寻元素(循环搜索的)，但是没有set的内置find函数高效
	ite1 = find(iset.begin(), iset.end(), 3);
	if (ite1 != iset.end())
		std::cout << "3 found" << std::endl;                       // 3 found
	else
		std::cout << "3 not found" << std::endl << std::endl;
 
	//使用set的内置find函数，比STL算法高效
	ite1 = iset.find(1);
	if (ite1 != iset.end())
		std::cout << "1 found" << std::endl;
	else
		std::cout << "1 not found" << std::endl << std::endl;       // 1 not found
 
	//*ite1 = 9;  错误，不能通过set的迭代器来改变元素的值
	return 0;
}
```



