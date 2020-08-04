# 常用数据结构的TypeScript实现

## TypeScript基础类型

* number: 数字类型。 双精度 64 位浮点值。它可以用来表示整数和分数。

* string: 字符串类型。一个字符系列，使用单引号（**'**）或双引号（**"**）来表示字符串类型。反引号（**`**）来定义多行文本和内嵌表达式。

* boolean: 布尔类型。表示逻辑值：true 和 false。

* void: 用于标识方法返回值的类型，表示该方法没有返回值。

* any: 任意类型。任意值是 TypeScript 针对编程时类型不明确的变量使用的一种数据类型，它常用于以下三种情况：

     * 变量的值会动态改变时，比如来自用户的输入，任意值类型可以让这些变量跳过编译阶段的类型检查。

       ```typescript
       let x: any = 1;    // 数字类型
       x = 'I am who I am';    // 字符串类型
       x = false;    // 布尔类型
       ```

     * 改写现有代码时，任意值允许在编译时可选择地包含或移除类型检查。

       ```typescript
       let x: any = 4;
       x.ifItExists();    // 正确，ifItExists方法在运行时可能存在，但这里并不会检查
       x.toFixed();    // 正确
       ```

     * 定义存储各种类型数据的数组时。

       ```typescript
       let arrayList: any[] = [1, false, 'fine'];
       arrayList[1] = 100;
       ```

* null:  null是一个只有一个值的特殊类型。表示一个空对象引用。用 typeof 检测 null 返回是 object。

* undefined: undefined 是一个没有设置值的变量。typeof 一个没有值的变量会返回 undefined。

  Null 和 Undefined 是其他任何类型（包括 void）的子类型，可以赋值给其它类型，如数字类型，此时，赋值后的类型会变成 null 或 undefined。而在TypeScript中启用严格的空校验（--strictNullChecks）特性，就可以使得null 和 undefined 只能被赋值给 void 或本身对应的类型。

* never: never 是其它类型（包括 null 和 undefined）的子类型，代表从不会出现的值。这意味着声明为 never 类型的变量只能被 never 类型所赋值，在函数中它通常表现为抛出异常或无法执行到终止点（例如无限循环）。

## Array数组

两种方法声明变量为数组：

```typescript
// 在元素类型后面加上[]
let arr: number[] = [1, 2];

// 或者使用数组泛型
let arr: Array<number> = [1, 2];
```

常用的数组方法：

1. concat()

   连接两个或更多的数组，并返回结果。

   ```typescript
   var alpha = ["a", "b", "c"]; 
   var numeric = [1, 2, 3];
   var alphaNumeric = alpha.concat(numeric); 
   console.log("alphaNumeric : " + alphaNumeric );    // a,b,c,1,2,3   
   ```

2. every()

   检测数值元素的每个元素是否都符合条件。

   ```typescript
   function isBigEnough(element, index, array) { 
       return (element >= 10); 
   } 
   var passed = [12, 5, 8, 130, 44].every(isBigEnough); 
   console.log("Test Value : " + passed ); // false
   ```

3. filter()

   检测数组元素，并返回符合条件所有元素的数组。

   ```typescript
   function isBigEnough(element, index, array) { 
       return (element >= 10); 
   } 
   var passed = [12, 5, 8, 130, 44].filter(isBigEnough); 
   console.log("Test Value : " + passed ); // 12,130,44
   ```

4. forEach()

   数组每个元素都执行一次回调函数。

   ```typescript
   let num = [7, 8, 9];
   num.forEach(function (value) {
       console.log(value);
   }); 
   ```

5. indexOf()

   搜索数组中的元素，并返回它所在的位置。如果搜索不到，返回值 -1，代表没有此项。

   ```typescript
   var index = [12, 5, 8, 130, 44].indexOf(8); 
   console.log("index is : " + index );  // 2
   ```

6. join()

   把数组的所有元素放入一个字符串。

   ```typescript
   var arr = new Array("First","Second","Third"); 
             
   var str = arr.join(); 
   console.log("str : " + str );  // First,Second,Third 
             
   var str = arr.join(", "); 
   console.log("str : " + str );  // First, Second, Third
             
   var str = arr.join(" + "); 
   console.log("str : " + str );  // First + Second + Third
   ```

7. lastIndexOf()

   返回一个指定的元素值最后出现的位置，指定位置从后向前搜索。

   ```typescript
   var index = [12, 5, 8, 130, 44].lastIndexOf(8); 
   console.log("index is : " + index );  // 2
   ```

8. map()

   通过指定函数处理数组的每个元素，并返回处理后的数组。

   ```typescript
   var numbers = [1, 4, 9]; 
   var roots = numbers.map(Math.sqrt); 
   console.log("roots is : " + roots );  // 1,2,3
   ```

9. pop()

   删除数组的最后一个元素并返回删除的元素。

   ```typescript
   var numbers = [1, 4, 9]; 
   var element = numbers.pop(); 
   console.log("element is : " + element );  // 9
   var element = numbers.pop(); 
   console.log("element is : " + element );  // 4
   ```

10. push()

    向数组的末尾添加一个或更多元素，并返回新的长度。

    ```typescript
    var numbers = new Array(1, 4, 9); 
    var length = numbers.push(10); 
    console.log("new numbers is : " + numbers );  // 1,4,9,10 
    length = numbers.push(20); 
    console.log("new numbers is : " + numbers );  // 1,4,9,10,20
    ```

11. reduce()

    将数组元素计算为一个值（从左到右）。

    ```typescript
    var total = [0, 1, 2, 3].reduce(function(a, b){ return a + b; }); 
    console.log("total is : " + total );  // 6
    ```

12. reduceRight()

    将数组元素计算为一个值（从右到左）。

    ```typescript
    var total = [0, 1, 2, 3].reduceRight(function(a, b){ return a + b; }); 
    console.log("total is : " + total );  // 6
    ```

13. reverse()

    反转数组的元素顺序。

    ```typescript
    var arr = [0, 1, 2, 3].reverse(); 
    console.log("Reversed array is : " + arr );  // 3,2,1,0
    ```

14. shift()

    删除并返回数组的第一个元素。

    ```typescript
    var arr = [10, 1, 2, 3].shift(); 
    console.log("Shifted value is : " + arr );  // 10
    ```

15. slice()

    选取数组的的一部分，并返回一个新数组。

    ```typescript
    var arr = ["orange", "mango", "banana", "sugar", "tea"]; 
    console.log("arr.slice( 1, 2) : " + arr.slice( 1, 2) );  // mango
    console.log("arr.slice( 1, 3) : " + arr.slice( 1, 3) );  // mango,banana
    ```

16. some()

    检测数组元素中是否有元素符合指定条件。

    ```typescript
    function isBigEnough(element, index, array) { 
       return (element >= 10); 
              
    } 
    var retval = [2, 5, 8, 1, 4].some(isBigEnough);
    console.log("Returned value is : " + retval );  // false  
    var retval = [12, 5, 8, 1, 4].some(isBigEnough); 
    console.log("Returned value is : " + retval );  // true
    ```

17. sort()

    对数组的元素进行排序。

    ```typescript
    var arr = new Array("orange", "mango", "banana", "sugar"); 
    var sorted = arr.sort(); 
    console.log("Returned string is : " + sorted );  // banana,mango,orange,sugar
    ```

18. splice()

    从数组中添加或删除元素。

    ```typescript
    var arr = ["orange", "mango", "banana", "sugar", "tea"];  
    var removed = arr.splice(2, 0, "water");  
    console.log("After adding 1: " + arr );    // orange,mango,water,banana,sugar,tea 
    console.log("removed is: " + removed); 
              
    removed = arr.splice(3, 1);  
    console.log("After removing 1: " + arr );  // orange,mango,water,sugar,tea 
    console.log("removed is: " + removed);  // banana
    ```

19. toString()

    把数组转换为字符串，并返回结果。

    ```typescript
    var arr = new Array("orange", "mango", "banana", "sugar");         
    var str = arr.toString(); 
    console.log("Returned string is : " + str );  // orange,mango,banana,sugar
    ```

20. unshift()

    向数组的开头添加一个或更多元素，并返回新的长度。

    ```typescript
    var arr = new Array("orange", "mango", "banana", "sugar"); 
    var length = arr.unshift("water"); 
    console.log("Returned array is : " + arr );  // water,orange,mango,banana,sugar 
    console.log("Length of the array is : " + length ); // 5
    ```

## LinkNode链表

