## Allocator

标准库allocator类帮助我们将内存分配和对象构造分离开来。它分配的内存是原始的、未构造的。

* allocator<T> a;  定义了一个名为a的allocator对象，它可以为类型为T的对象分配内存
* a.allocate(n);  分配一段原始的、未构造的内存，保存n个类型为T的对象
* a.deallocate(p, n) ; 释放从T*指针p中地址开始的内存，这块内存保存了n个类型为T的对象；p必须是一个先前由allocate返回的指针，且n必须是p创建时所要求的大小。在调用deallocate之前，用户必须对每个在这块内存中创建的对象调用destroy
* a.construct(p, args);  p必须是一个类型为T*的指针，指向一块原始内存；args被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象
* a.destroy(p);  p为T*类型的指针，此算法对p指向的对象执行析构函数
* a.address(x);  返回某个对象的地址，等同于&x
* a.max_size(); 返回可成功配置的最大量
* allocator::value_type
* allocator::pointer
* allocator::const_pointer
* allocator::reference
* allocator::const_reference
* allocator::size_type
* allocator::difference_type

### 使用方法：

- 第一步：使用allocator<>模板定义一个特定类型的allocator类对象
- 第二步：使用**allocate()函数**分配一块指定大小的内存，该内存中的对象都是未构造的
- 第三步：使用**construct()函数**对指定位置的元素就行初始化
- 第四步：如果某个位置的元素不想使用就调用**destroy()函数**来销毁它们（但是空间还没有释放）。如果该位置需要重新使用就调用allocate()函数来初始化。如果不再使用进行下一步
- 第五步（依情况而选）：元素销毁之后，可以调用**deallocate()函数**来释放内存

### allocate函数

allocator模板定义出来的类对象并没有分配内存空间，只是定义了一个对象。此后需要调用allocate()函数来指定分配的元素个数。allocate()函数分配的元素都是未初始化的，因此不能够直接使用。后面会介绍使用construct()函数来初始化。

返回值：返回allocator类对象的首元素地址。

```c++
allocator<string> alloc;  //可以分配string的allocator对象，此时还不占用内存空间
auto const p = alloc.allocate(10); //分配n个未初始化的string
```

### construct函数

allocate()函数分配的内存元素都是未初始化的，因此不能够直接使用，需要调用该函数来对指定位置的元素进行初始化。

参数1为一个地址，参数2以及之后的参数是可变的（用来对参数1指定的位置进行初始化的元素

```c++
allocator<string> alloc;
auto const p = alloc.allocate(10); 
auto q=p; //q指向最后构造的元素之后的位置
 
//在q位置进行构造，然后指针再向后偏移一个元素的大小
alloc.construct(q++);       //*q为空字符串
alloc.construct(q++,10,'c');//*q为10个c的字符串（cccccccccc）
alloc.construct(q++,"hi");  //*q为hi
```

**还未构造对象就直接使用是错误的：**

```c++
cout<< *p <<endl;  //正确，使用stirng的输出运算符
cout<< *q <<endl;  //错误，q最后++指向一块未构造的内存
```

### destroy函数

当我们使用完对象之后，如果不再需要该对象，就可以调用该函数来销毁指定的元素。

参数为一个指定位置元素的地址

```c++
//在循环开始处，q指向最后一个构造的元素的下一个位置，我们将其传入destroy函数中，然后循环递减逐渐释放内存 
while(q!=p)
    alloc.destroy(--q);  //销毁指定位置的元素
```

### deallocate函数

如果destroy函数销毁指定位置的元素之后，该位置不再使用，就可以调用该函数来释放该位置的内存空间

参数1是要销毁的内存起始地址，参数2是要销毁的个数。参数1的指针不能为空

```c++
//上面我们调用了destroy函数销毁了所有的元素，接下来我们调用deallocate函数将所有的元素内存释放
alloc.deallocate(p,10);
```

### 拷贝和填充未初始化内存的算法

标准库为allocator类定义了两个伴随算法。可以在未初始化内存中创建对象。头文件#include<memory>

这些函数在给定目的位置创建元素，而不是由系统分配内存给它们。

* uninitialized_copy(b, e, b2);  从迭代器b和e指出的输入范围中拷贝元素到迭代器b2指定的未构造的原始内存中。b2指向的内存必须足够大，能容纳输入序列中元素的拷贝。uninitialized_copy函数返回递增后的目的位置迭代器。

* uninitialized_copy_n(b, n, b2); 从迭代器b指向的元素开始，拷贝n个元素到b2开始的内存中。

* uninitialized_fill(b, e, t);  在迭代器b和e指定的原始内存范围中创建对象，对象的值均为t的拷贝。

* uninitialized_fill_n(b, n, t); 从迭代器b指向的内存地址开始创建n个对象。b必须指向足够大的未构造的原始内存，能够容纳给定数量的对象。

```c++
  // 我们现在有一个int型的vector。然后我们创建一个2倍vector对象的动态内存，然后在动态内存的前半部分拷贝vector的对象。后半部分用指定的值填充
  vector<int> vi = { 1,2,3,4,5 };      //分配一个vector数组
  allocator<int> alloc;
  auto p=alloc.allocate(vi.size() * 2);//分配一个2倍vector大小的动态内存
   
  auto q = uninitialized_copy(vi.begin(), vi.end(), p); //动态内存前半部分拷贝vector的内存，uninitialized_copy函数返回递增后的目的位置迭代器（alloc中间位置的地址）
  uninitialized_fill_n(q,vi.size(),666);  //动态内存后半部分，全部使用666数组初始化
  ```

  

