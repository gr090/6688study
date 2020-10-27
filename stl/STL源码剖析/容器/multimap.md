# multimap

## multimap概述

- multimap的特性以及用法和map完全相同，**唯一的差别在于它允许键值重复，**因此它的插入操作采用的是底层RB-tree的insert_equal()而非insert_unique()

## multimap使用

- 与map相同：由“键值（key）与值（value）”两部分组成，这两者形成映射关系
- 头文件：#include <map>

### 特点

- key可以重复（如果有相同的key，则相邻存储），默认也为升序排序
- 其它特点与map相同
- multimap不提供下标操作（下标运算符和at函数），因为key可以重复

### 升序、降序操作

- 与map相同，key默认是升序操作，我们也可以将key设置为显式地升序或者设置为降序排序
- 下面两个标准库函数（less、greater）都在头文件#include <xfunctional>中
- 演示升序操作

```c++
multimap<string, int, std::less<string>> word_count;//升序
//multimap<string, int> word_count;//升序
 
word_count.insert({ "a",1 });
word_count.insert({ "c",1 });
word_count.insert({ "b",1 });
 
for (const auto &w : word_count) {
    cout << w.first << "  occurs  " << w.second <<
        ((w.second>1) ? "  times" : "  time") << endl;
}
```

- 演示降序操作

```c++
multimap<string, int,std::greater<string>> word_count;//降序
	
word_count.insert({ "a",1 });
word_count.insert({ "c",1 });
word_count.insert({ "b",1 });
 
for (const auto &w : word_count) {
    cout << w.first << "  occurs  " << w.second <<
        ((w.second>1) ? "  times" : "  time") << endl;
}
```

### 初始化

- 如果没有给出初始化值，就默认为空容器

### 迭代器与遍历

与map相似，见map的介绍

### 添加元素

与map相似，见map的介绍

### 删除元素

与map相似，见map的介绍

### 其他操作

与map相似，见map的介绍

## multimap源码

```c++
template <class _Key, class _Tp, class _Compare, class _Alloc>
class multimap {
  // requirements:

  __STL_CLASS_REQUIRES(_Tp, _Assignable);
  __STL_CLASS_BINARY_FUNCTION_CHECK(_Compare, bool, _Key, _Key);

public:

// typedefs:

  typedef _Key                  key_type;
  typedef _Tp                   data_type;
  typedef _Tp                   mapped_type;
  typedef pair<const _Key, _Tp> value_type;
  typedef _Compare              key_compare;

  class value_compare : public binary_function<value_type, value_type, bool> {
  friend class multimap<_Key,_Tp,_Compare,_Alloc>;
  protected:
    _Compare comp;
    value_compare(_Compare __c) : comp(__c) {}
  public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return comp(__x.first, __y.first);
    }
  };

private:
  typedef _Rb_tree<key_type, value_type, 
                  _Select1st<value_type>, key_compare, _Alloc> _Rep_type;
  _Rep_type _M_t;  // red-black tree representing multimap
public:
  typedef typename _Rep_type::pointer pointer;
  typedef typename _Rep_type::const_pointer const_pointer;
  typedef typename _Rep_type::reference reference;
  typedef typename _Rep_type::const_reference const_reference;
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator; 
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::allocator_type allocator_type;

// allocation/deallocation

  multimap() : _M_t(_Compare(), allocator_type()) { }
  explicit multimap(const _Compare& __comp,
                    const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { }

#ifdef __STL_MEMBER_TEMPLATES  
  template <class _InputIterator>
  multimap(_InputIterator __first, _InputIterator __last)
    : _M_t(_Compare(), allocator_type())
    { _M_t.insert_equal(__first, __last); }

  template <class _InputIterator>
  multimap(_InputIterator __first, _InputIterator __last,
           const _Compare& __comp,
           const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_equal(__first, __last); }
#else
  multimap(const value_type* __first, const value_type* __last)
    : _M_t(_Compare(), allocator_type())
    { _M_t.insert_equal(__first, __last); }
  multimap(const value_type* __first, const value_type* __last,
           const _Compare& __comp,
           const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_equal(__first, __last); }

  multimap(const_iterator __first, const_iterator __last)
    : _M_t(_Compare(), allocator_type())
    { _M_t.insert_equal(__first, __last); }
  multimap(const_iterator __first, const_iterator __last,
           const _Compare& __comp,
           const allocator_type& __a = allocator_type())
    : _M_t(__comp, __a) { _M_t.insert_equal(__first, __last); }
#endif /* __STL_MEMBER_TEMPLATES */

  multimap(const multimap<_Key,_Tp,_Compare,_Alloc>& __x) : _M_t(__x._M_t) { }
  multimap<_Key,_Tp,_Compare,_Alloc>&
  operator=(const multimap<_Key,_Tp,_Compare,_Alloc>& __x) {
    _M_t = __x._M_t;
    return *this; 
  }

  // accessors:

  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return value_compare(_M_t.key_comp()); }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  iterator begin() { return _M_t.begin(); }
  const_iterator begin() const { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() { return _M_t.rbegin(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  reverse_iterator rend() { return _M_t.rend(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  void swap(multimap<_Key,_Tp,_Compare,_Alloc>& __x) { _M_t.swap(__x._M_t); }

  // insert/erase

  iterator insert(const value_type& __x) { return _M_t.insert_equal(__x); }
  iterator insert(iterator __position, const value_type& __x) {
    return _M_t.insert_equal(__position, __x);
  }
#ifdef __STL_MEMBER_TEMPLATES  
  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    _M_t.insert_equal(__first, __last);
  }
#else
  void insert(const value_type* __first, const value_type* __last) {
    _M_t.insert_equal(__first, __last);
  }
  void insert(const_iterator __first, const_iterator __last) {
    _M_t.insert_equal(__first, __last);
  }
#endif /* __STL_MEMBER_TEMPLATES */
  void erase(iterator __position) { _M_t.erase(__position); }
  size_type erase(const key_type& __x) { return _M_t.erase(__x); }
  void erase(iterator __first, iterator __last)
    { _M_t.erase(__first, __last); }
  void clear() { _M_t.clear(); }

  // multimap operations:

  iterator find(const key_type& __x) { return _M_t.find(__x); }
  const_iterator find(const key_type& __x) const { return _M_t.find(__x); }
  size_type count(const key_type& __x) const { return _M_t.count(__x); }
  iterator lower_bound(const key_type& __x) {return _M_t.lower_bound(__x); }
  const_iterator lower_bound(const key_type& __x) const {
    return _M_t.lower_bound(__x); 
  }
  iterator upper_bound(const key_type& __x) {return _M_t.upper_bound(__x); }
  const_iterator upper_bound(const key_type& __x) const {
    return _M_t.upper_bound(__x); 
  }
   pair<iterator,iterator> equal_range(const key_type& __x) {
    return _M_t.equal_range(__x);
  }
  pair<const_iterator,const_iterator> equal_range(const key_type& __x) const {
    return _M_t.equal_range(__x);
  }

#ifdef __STL_TEMPLATE_FRIENDS 
  template <class _K1, class _T1, class _C1, class _A1>
  friend bool operator== (const multimap<_K1, _T1, _C1, _A1>&,
                          const multimap<_K1, _T1, _C1, _A1>&);
  template <class _K1, class _T1, class _C1, class _A1>
  friend bool operator< (const multimap<_K1, _T1, _C1, _A1>&,
                         const multimap<_K1, _T1, _C1, _A1>&);
#else /* __STL_TEMPLATE_FRIENDS */
  friend bool __STD_QUALIFIER
  operator== __STL_NULL_TMPL_ARGS (const multimap&, const multimap&);
  friend bool __STD_QUALIFIER
  operator< __STL_NULL_TMPL_ARGS (const multimap&, const multimap&);
#endif /* __STL_TEMPLATE_FRIENDS */
};
```



