# using声明

1. `std::cin` 中的 `::` 是作用域操作符，即从左侧名字的作用域中寻找右侧的名字
2. 为了省事，使用 `using` 声明，如 `using std::cin`，之后就可以直接用 `cin` 了。
3. 头文件不该包含using声明，因为头文件的内容会拷贝到引用的文件里，可能会造成冲突。

# string

1. **标准库**类型，表示**可变长**的字符序列，需要引用头文件`#include <string>`

## 初始化

```
 string s1;  // 未显式初始化，默认为空串
 string s2 = s1; // 将s1的内容拷贝到s2
 string s2(s1);  // 将s1的内容拷贝到s2
 string s3 = "hello";    // s3是字符串字面值的副本
 string s4("hello"); // 直接初始化
 string s5(10, 'c'); // s5="cccccccccc"
 
 string s6 = string(10, 'c');    // 拷贝初始化，不过没有上面的直接
```

直接初始化：直接把字符串初始化

拷贝初始化：把等式右侧的内容(除了最后的空字符)都拷贝到左侧

注意：

```
string s2 = s1` 执行的是拷贝操作，`s2` 的修改不对 `s1` 产生影响，等同于 `string s2 = s1.substr()
```

## 操作

### 基本操作

可以调用函数、重载运算符，比如重新定义`+`：字符串＋数字 or 数字＋字符串得到的是它们的拼接，要注意顺序的问题哦

```
 getline(cin, s);
 s.empty();
 s.size();   s.length();
 s1 == s2;
 s1 > s2;    // 字典序判断
 string s = s1 + to_string(1);   // 字符串＋数字
```

如何判断两个字符串是否相等：`s1 == s2` 即可，而java需要调用`Objects.equals(a, b)`

设计标准库类型时，力求和内置类型一样具有易用性，因此字符串可以赋值和相加（感觉是用了操作符重载？）

```
 string a, b(10, 'c');
 b = a;  // a, b此时都为空串
 
 string a = "a", b = "b";
 a = a + b;
```

注意：**字面值和字符串相加**

第一眼看时，别把字面值看成字符值了，像”hello”, ‘c’叫字面值。C++中的字面值和字符串是**不同的类型**

需要确保加号两侧**至少有一个是string对象**

```
 string a = b + "hello"; // correct
 string a = "hello" + b; // correct
 
 string a = "hello" + "world";   // wrong 字面值不能直接相加
 string a = b + "hello" + "world";   // correct ((b + "hello") + "world")
 string a = "hello" + "world" + b;   // wrong
```

### 读取

1. 分为cin和getline，cin忽略掉空白符，getline默认遇到换行结束(换行符也被读取，但是不存进string对象中)，因此在调用cin后想使用getline时，记得先用 *cin >> ws* 把多余的空白符读掉
2. 读取不定数量的string

```
 while (cin >> str) {
     cout << str << endl;
 }
 
 while (getline(cin, str)) {
     cout << str << endl;
     // endl: 换行并刷新显示缓冲区
 }
```

### string::size_type

1. `str.size()` 返回的是 `string::size_type`，无符号类型的值
2. 如果混用了负数和无符号数，负数会被转成一个很大的正数
3. *auto* 和 *decltype*

auto: 编译器推断变量的类型 `auto a = str.size()`，推断出a是`string::size_type`类型

decltype: 给一个表达式，指定变量的类型 `decltype(str.size()) a`，a类型是`string::size_type`

## 处理string的字符

### cctype头文件

C++的标准库兼容了C的标准库，C的标准库名称为 *name.h*，C++则改为 *cname*，在前面加了个c，表示这是一个C的标准库头文件。

实际上内容一样，不过 *cname* 更符合C++的命名规范，以及 *cname* 中定义的名字属于命名空间std，而 *name.h* 则不属于std

cctype的函数

```
 toupper(c); // 若c是小写字母，就返回大写字母; 如果不是小写字母，原样返回
 tolower(c);
 isupper(c);
 islower(c);
 isdigit(c);
 isalpha(c);
 isalnum(c); // c是数字或字母为true
 isspace(c); // c是空白符为true
```

### 范围for语句——记得想起来用

for (declaration: expression)

\ \ \ \ statement

#### 输出

```
 for (auto c: str) {
     // 这里的auto实际上就是char
     if (!isspace(c))
         cout << c;
 }
```

#### 改变字符：引用

```
 string str("hello world");
 for (auto &c: str) {
     // 变量c就被绑定到了str序列的元素上
     c = toupper(c);
 }
 cout << str << endl;
```

#### 下标引用

使用 *[]* ，*str[i]* 代表下标为i的字符，**下标从0开始**

下标接受的参数为 *string::size_type* 类型，返回值为该字符的引用。如果传入一个有符号的值，会自动转成无符号的值。

下标要有意义，*0 <= index < str.size()*，C++并不检查下标是否合法，若超过表示范围，是未定义的行为。

```
 if (!str.empty()) {
     cout << str[0];
 }
 for (decltype(str.size()) i = 0; i < str.size() && !isspace(str[i]); i++) {
     str[i] = toupper(str[i]);
 }
 // 将第一个词改成大写
```

#### 下标的实例

将十进制数字转为十六进制

```
 const string hex = "0123456789ABCDEF";  // 不改变的字符串可以设为const常量
 string res;
 string::size_type num;
 while (cin >> num) {
     if (num < hex.size())
         // Nice, 检验了数字是否小于16
         res += hex[num];
 }
```

# Vector

## 前言

vector是一个类模板，使用vector时，应当告诉编译器将类**实例化**成什么类型

> vector\<int>

vector的元素应当是对象，但是引用不是对象，所以不存在包含引用的vector

## 初始化

### 基本方法

```
vector<T> v1;    // 空，默认初始化
vector<T> v2(v1);    // v2包含v1所有元素，且长度也被改变成v1的长度
vector<T> v2 = v1;    // 等价于v2(v1)
/* 因此不用担心v1是否会被改变 */

vector<T> v3(n, val);    // n个值为val的元素
vector<T> v4(n);    // n个元素执行值初始化，int类型就被初始化为0
vector<T> v5{a, b, c};
vector<T> v6 = {a, b, c};
```

拷贝初始化时，两个vector**类型必须相同**

### 圆括号和花括号

圆括号：构造vector对象，第一个值代表元素数量

花括号：列表初始化，第一个值是vector的初始值

特例：确认无法执行列表初始化时，编译器会尝试用圆括号的方式来初始化

```
vector<string> v1={10, "hello"};
// v1有10个"hello"
```

## 添加元素

```
vector<string> text;
string word;
while (cin >> word) {
    text.push_back(word);
}
```

vector在运行时能高效地添加元素，当元素有所不同的时候，更有效的方法是定义一个空vector，然后添加元素

- 范围for语句中不应改变**遍历序列**的大小

这涉及到范围for语句的实现：迭代器

## 基本操作

vector可以进行比较！

```
v.empty();
v.size();
v[n];    // 返回第n个位置元素的引用
v1 = {a, b, c};    // 用列表元素拷贝替换v1的元素
v1 == v2;    // v1和v2元素数量相同，且对应元素相同
v1 != v2;
```

小补充：拷贝会覆盖掉原来vector的元素，不止是对应元素被替换，原有多余的元素被删除

```
v1 = {1, 2, 3};
v2 = {4, 5};
v1 = v2;    // v1 元素为 4, 5,
```

### 范围for语句——和auto &联动

优雅的遍历或改变vector

```
vector v1{1, 2, 3};
for (auto i: v) {
    cout << i << endl;
}
for (auto &i: v) {
    i *= i;
}
```

### vector\<T>::size_type

- `v.size()` 的返回值，`unsigned int` 或 `unsigned long long` 的 `typedef`
- vector对象的下标类型也是`vector<T>::size_type`

```
// 分数统计
vector<unsigned> scores(11, 0);
unsigned grade;
while (cin >> grade) {
    if (grade <= 100) {
        // 老是想不起来只处理有效成绩
        ++scores[grade / 10];
    }
}
```

分数统计的关键点在于只关心grade属于的层次，而不是grade本身的值，所以别把grade push进去了。

## 迭代器（重点）

### begin和end

begin：返回指向第一个元素的迭代器

end：返回指向尾元素的下一位置的迭代器，被称作**尾后迭代器**

> 若容器为空，begin和end返回同一个迭代器，都是尾后迭代器

迭代器的类型有 `vector<int>::iterator`, `vector<int>::const_iterator`，也可以直接用 `auto`

### 迭代器运算符

```
*iter        // 所指元素的引用
iter-mem    // 等价于(*iter).mem
++iter        // 指向下一个元素
--iter
iter1 == iter2    // 都指向同一个元素或都是尾后迭代器，true
```

注意：

- 解引用一个非法迭代器或尾后迭代器都是**未被定义的行为**
- end返回的迭代器不能进行递增或解引用的操作

#### 实例：首字母大写

```
string s = "hello world";
auto beg = s.begin();
if (s.begin() != s.end()) {    
    /* 首先检查s是否为空 */

    *beg = toupper(*beg);
}
```

#### 实例：第一个单词大写

```
string s("some string");
for (auto it = s.begin(); it != s.end() && !isspace(*it); it++) {
    *it = toupper(*it);
}
```

所有标准库容器的迭代器都定义了 `==` `!=`，大多数没有定义 `<`，所以for循环的终止条件通常写做 `!=`

### 迭代器类型

如果对象是常量，则begin和end返回const_iterator，如果对象不是常量，begin和end返回iterator

```
const vector<int> cv;
auto it = cv.begin();    // it类型vector<int>::const_iterator
```

#### cbegin和cend

C++11中引入的两个新函数，返回const_iterator

```
auto it = v.cbegin();    // vector<int>::const_iterator
```

#### vector\<string> 实例

假设用一个名为text的字符串向量存放数据，元素或是一句话或是空字符串。要输出text第一段的内容，遇到空字符串的元素为止

```
for (auto it = text.cbegin(); it != text.cend() && !it->empty(); it++) {
    cout << *it;
}
```

### 迭代器失效

string那一节提到，范围for循环的实现原理是先保存end，如果向容器中添加元素，可能重新分配空间，或者end直接失效。

**用了迭代器的循环体，都不要向容器中添加元素**

### 迭代器运算

```
iter + n;        // 向前移动n位
iter - n;
iter1 - iter2;    // 两个迭代器之间的距离
> < ==            // 迭代器位置的比较
```

迭代器相减结果为 `difference_type`，有符号整数

#### 二分查找

```
auto low = v.begin();
auto high = v.end();
auto mid = low + (high - low) / 2;
while (mid != high && mid != search) {
    if (*mid < search) {
        low = mid + 1;
    } else {
        high = mid;
    }
    mid = low + (high - low) / 2;
}
if (mid == high) {
    cout << "not find";
} else {
    cout << "find";
}
```

`high` 指的是搜索序列的下一个位置，因此 `high = mid`，而不是 `high = mid - 1`。

如果开始 `high = v.end() - 1`，则 `high = mid - 1`