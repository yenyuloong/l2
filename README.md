### 一种简单的、弱类型的、解释型的脚本编程语言，及其脚本解释器的设计与实现
#### 暂且叫 L2 编程语言吧 (恕本人水平有限，纯 C 的代码过于冗杂，PS: 目前本人已弃坑)
---

### 解释器用途
* 可作为课题设计或课程设计
* 开发者可自行扩展解释器功能，比如作为嵌入式编程语言使用
* 同样可以作为玩具把玩（逃

### 从源代码开始构建
  可使用 CMake 和 MinGW/GCC 按照 ```CMakeList.txt``` 中所述构建可执行文件，代码模块结构简单，本人不再赘述

---

### L2 编程语言
- [L2 编程语言简要说明](#l2-编程语言简要说明)
  - [类 C 的语法](#类-c-的语法)
  - [语法关键字（14 个）](#语法关键字14-个)
  - [仅支持单行的注释](#仅支持单行的注释)
  - [基本类型](#基本类型)
  - [var 关键字](#变量定义和赋值var-关键字)
  - [proc 关键字](#函数过程的定义和使用proc-关键字)
  - [运算符与优先级](#运算符与优先级)
  - [作用域](#作用域)
  - [eval 关键字](#任意复杂的表达式的评估eval-关键字)
  - [程序分支](#程序分支if-elif-else)
  - [循环和迭代](#循环和迭代forwhile-和-do-while)

- [L2 编程语言的一些技巧](#l2-编程语言的一些技巧)
  - [过程 lambda 化](#过程-lambda-化)
  - [高阶过程（回调过程）](#高阶过程回调过程)
  
  
---

### 未完成的 features
* 尚未实现**字符串**（string）支持
* 尚未实现**原生数组**（native array）支持
* 尚未实现基本的**对象系统**（objective system）
* 尚未实现对程序中对**标准输入**（standard input）的支持

---

## L2 编程语言简要说明

### 类 C 的语法
L2 编程语言与 C、C++、Java、JS 等编程语言的语法类似

### 语法关键字（14 个）
true, false, var, if, else, elif, while, do, for, break, continue, return, proc, eval

### 仅支持单行的注释
* 由 ``` // ``` 开始到行尾结束的一段内容将自动被解释器忽略

### 基本类型
* 实数型（64 位有符号浮点数）
* 整数型（64 位有符号整数）
* 布尔型
* 过程型（或者叫函数型、lambda 型）
> lambda 型之上可进行的操作有可实现性，但是本人已弃坑，只保留了极为有限的 lambda 语法
（其实也算不上，目前变量无法直接赋值为过程，但是可以通过参数传递过程型变量）

### 变量定义和赋值（var 关键字）
* 示例 L2 代码
```JavaScript
var a = 0;        // 定义变量 a 并且初始化为整数 0
var b;            // 定义变量 b, 但是暂不初始化
b = 4;            // 将变量 b 赋值为整数 4
var pi = 3.14;    // 定义变量 pi，并且初始化为实数 3.14 
var b = true;     // 定义变量 b，并且初始化为布尔值 true
```
> 若不定义变量或者不初始化变量，该变量均无法在表达式中正常使用；若试图使用，解释器将会报告错误

> 变量赋值时，变量的类型可能会发生变化，这与赋给它的新值的类型相关（变量类型的可变性）

### 函数（过程）的定义和使用（proc 关键字）
* 定义不带参的过程
```JavaScript
proc pi() {
  return 3.14159;
}
```
* 定义带参的过程
```JavaScript
proc area(r) {
  return r * r * pi();
}
```
* 嵌套定义的过程（综合前两个过程）
```JavaScript
proc area(r) {
  proc pi() {
    return 3.14159;
  }
  return r * r * pi();
}
```
* 调用过程
```JavaScript
var d = 10;             // 直径
var s = area(d / 2);    // 变量 s 将得到 5 * 5 * 3.14159 的初始值（这个我就不算了）
```
> 过程调用时，形参和实参名字可以不同，但是参数数量必须保持一致

> 函数可以嵌套定义

> 与一些类 C 的编程语言类似，``` return ```关键字用于结束过程调用，
并返回一个有效的值（如果调用者需要这个值进行运算的话，返回值是必须的，否则可以不返回值）

### 运算符与优先级
| 优先级 | 运算作用 | 顺序 & 结合性 | 运算符 |
|:---:|:---|:---|:---:|
| 1 | 逻辑非 | 从左到右，右结合 | ! |
| 1 | 按位取反 | 从左到右，右结合 | ~ |
| 1 | 负号 | 从左到右，左结合 | - |
| 2 | 乘 | 从左到右，左结合 | * |
| 2 | 除 | 从左到右，左结合 | / |
| 2 | 取余 | 从左到右，左结合 | % |
| 3 | 加 | 从左到右，左结合 | + |
| 3 | 减 | 从左到右，左结合 | - |
| 4 | 左移 | 从左到右，左结合 | << |
| 4 | 右移 | 从左到右，左结合 | >> |
| 4 | 无符号右移 | 从左到右，左结合 | >>> |
| 5 | 大于等于 | 从左到右，左结合 | >= |
| 5 | 大于 | 从左到右，左结合 | > |
| 5 | 小于等于 | 从左到右，左结合 | <= |
| 5 | 小于 | 从左到右，左结合 | < |
| 6 | 不等于 | 从左到右，左结合 | != |
| 6 | 等于 | 从左到右，左结合 | == |
| 7 | 按位与 | 从左到右，左结合 | & |
| 8 | 按位异或 | 从左到右，左结合 | ^ |
| 9 | 按位或 | 从左到右，左结合 | \| |
| 10 | 逻辑与 | 从左到右，左结合 | && |
| 11 | 逻辑或 | 从左到右，左结合 | \|\| |
| 12 | 条件 | 特殊 | ? : |
| 13 | 赋值 | 从左到右，右结合 | = |
| 13 | 除赋值 | 从左到右，右结合 | /= |
| 13 | 乘赋值 | 从左到右，右结合 | \*= |
| 13 | 取余赋值 | 从左到右，右结合 | %= |
| 13 | 加赋值 | 从左到右，右结合 | += |
| 13 | 减赋值 | 从左到右，右结合 | -= |
| 13 | 左移赋值 | 从左到右，右结合 | <<= |
| 13 | 右移赋值 | 从左到右，右结合 | >>= |
| 13 | 无符号右移赋值 | 从左到右，右结合 | >>>= |
| 13 | 按位与赋值 | 从左到右，右结合 | &= |
| 13 | 按位异或赋值 | 从左到右，右结合 | ^= |
| 13 | 按位或赋值 | 从左到右，右结合 | \|= |
| 14 | 逗号 | 从左到右，左结合 | , |

> 不支持 ++、-- 这种在类 C 编程语言中常见的单目运算符

### 作用域
无论是过程的定义还是变量的定义，它们在以下两个位置都可以正常使用
* 定义的下文
* 定义的下文的所有的子作用域（包含嵌套）

### 任意复杂的表达式的评估（eval 关键字）
* 示例 L2 代码
```JavaScript
eval 5 + 3;       // 将输出 8
var pi = 3.14;
var r = 2;
eval r * r * pi;  // 将输出 12.56
eval pi();        // 当然，评估某个已定义的函数的返回值也是可行的
```
> eval 关键字的右侧可以是任意复杂的表达式

### 程序分支（if-elif-else）
* 示例 L2 代码
```JavaScript
var a = 3;
var b = 3;
if (a == b) {
  // 处理等于的情形 ...
} elif ( a < b ) {
  // 处理小于的情形 ...
} else {
  // 处理大于的情形 ...
}
```
> if 和 elif 的表达式的计算结果必须是布尔型的，最终的表达式结果
必须由 ``` == <= >= != ! && || ``` 等这些运算符或者布尔型变量复合作用而成

> if...elif...else 结构的每一个子块都必须使用花括号括起，L2 中不允许出现单条语句或者空语句，子块必须以语句块的形式出现

### 循环和迭代（for、while 和 do-while）
* for 循环示例
```JavaScript
for (var i = 0; i < 10; i += 1) {   // 该循环体将被执行 10 次
  // 这里做一些操作
}
```
* while 循环示例
```JavaScript
var i = 0;
while (i < 5) {
  // 这里做一些操作
  i += 1;   // 递增循环变量，该循环体将被执行 5 次
}
```
* do...while 循环示例
```JavaScript
var i = 0;
do {
  // 这里做一些操作
  i += 1;   // 递增循环变量，该循环体将被执行 5 次
} while (i < 5);
```

> 这里 ```break``` 、 ```continue``` 这些循环体独有的语句与类 C 编程语言类似，不再多说

> if...elif...else 结构的每一个子块都必须使用花括号括起，L2 中不允许出现单条语句或者空语句，子块必须以语句块的形式出现
---

## L2 编程语言的一些技巧

### 过程 lambda 化
在 L2 编程语言中，可以将一个过程赋值给一个变量，或用于初始化某个变量
* L2 代码示例
```JavaScript
// 定义过程 pi
proc pi() {
  return 3.14159;
}

// 过程 lambda 化，p 被初始化成过程
var p = pi;
// 调用过程
p();
```

### 高阶过程（回调过程）
在 L2 编程语言中，可以将一个过程作为另一个过程的参数（当然也可以是自身）
* L2 代码示例
```JavaScript
// 定义过程 area
proc area(r, callproc) {
  return r * r * callproc();  // 调用者必须提供一个过程，用于产生某个精度的 pi 值
}

// 定义一个生成保留 2 位小数的 pi2 过程
proc pi2() { return 3.14; }

// 定义一个生成保留 5 位小数的 pi5 过程
proc pi5() { return 3.14159; }

// 使用保留了 2 位小数的 pi 值来计算半径为 2 的圆面积，并输出
eval area(2, pi2);

// 使用保留了 5 位小数的 pi 值来计算半径为 2 的圆面积，并输出
eval area(2, pi5);

```
