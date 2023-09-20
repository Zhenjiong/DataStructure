# Data Structures, Algorithms, and Application in C++, Second Edition

<br>

## TODO List

智能指针

左值和右值

虚函数

正则表达式

windows编译 动态链接和静态链接

extern "C"

__cplusplus





## The First Volume: Review of C++

### 函数与参数

函数执行前，把实参复制给形参，复制的过程由形参类型的复制构造函数(copy constructor)来完成

函数运行结束，形参类型的析构函数(destructor)负责释放形参。

```c++
template<class T>
T abc(T a, T b, T c)
{
    a = a - 1;
    T p = a + b + c;
    return p;
}
```

### 引用与指针

#### 引用(reference, or lvalue reference左值引用)

引用即别名，引用并非对象(没有引用的引用，没有指向引用的指针)，只是一个已经存在的对象的另一个名字

引用必须初始化，初始化完成后将和它的初始值一直绑定在一起

##### 引用的定义

```C++
int &r = i, bb = i3;   //可以这样定义，共用int
int &ref = 10;      //错误：引用的初始值必须是一个对象
```

一般引用的类型要和绑定对象的类型严格匹配(是对象，不是某个数值或表达式计算结果)，例外情况有两种：关于const的引用和类的继承

#### 指针(pointer)

从右向左阅读比较合适

```C++
int i = 42;
int *p;         //定义int指针p
int *&r = p;    //定义引用r，装int型指针，初始化为p
int &*r2 = p;    //错误:没有指向引用的指针，因为引用不是对象，没法指
r = nullptr;     //引用r指向空指针
r = &i;        //引用r指向地址i
```

#### Const限定符

Const对象创建后不能再改变，必须初始化

```c++
const int i = get_size()    //正确：运行时初始化
const int j = 42;           //正确：编译时初始化
```

默认情况下const对象仅在文件内有效，加入extern该常量可以被其他文件访问：

```C++
//file.cc 定义并初始化了一个常量，该常量能被其他文件访问
extern const int bufSize = fcn();
//file.h 头文件
extern const int bufSize;      //进行声明，与file.cc中的bufSize是同一个
```

##### 对常量的引用(reference to const) 指向常量的指针(pointer to const)

构造出来是为了指向常量对象而使用的：

```C++
const int ci = 1024;
int &rr = ci;    //错误：无法用非常量引用指向一个常量对象
```

“自以为是”指向了常量，无法通过它改变所指对象的值，但所指对象并不必须是常量对象

```C++
double dval = 3.14;
const int &ri = dval;     //正确；去掉const将错误
//这个过程中ri绑定的是一个临时量对象
const int temp = dval;  //由dval生成临时的整型常量temp
const int &ri = temp;   //让ri绑定这个临时量
```

在定义函数的时候，如果该引用或指针并不准备改变所指对象的值，应当尽量使用对常量的引用或对常量的指针。这一方面避免了误导：函数可以修改它实参的值；另一方面可以扩大函数可以接受的实参类型，允许把const对象、字面值或者需要类型转换的对象传递给形参。

```C++
void reset(int *p){ /* */ }
void reset(int &p){ /* */ }
int i = 0;
const int ci = i;
int j = ci;   //正确：当拷贝ci时，忽略它的顶层const
reset(&i);   //调用形参类型时int*的reset函数
reset(&ci);   //错误：不能用指向const int的指针初始化int*
reset(i);    //调用参数类型是int&的reset函数
reset(ci);    //错误：不能把普通引用绑定到const int ci上
reset(42);    //错误：不能把普通引用绑定到字面值上
```

##### 常量指针(const pointer)

指针本身作为对象，可以被定为常量。不变的是指针本身而非指向的那个值

```C++
int i = 42;
int *const p = &i;
*p = 78;      //正确，可以通过常量指针改变普通的int对象
```

顶层const(top-level const) 本身是常量，例如常量指针

底层const(low-level const) 所指对象是一个常量，例如指向常量的指针：底层const要求拷贝时，拷入和拷出要有相同的底层const资格（或者两者数据类型能转换，像非常量就可以转换成常量）；顶层const在拷贝时没有这样的要求。

在函数的参数传递的过程中，用实参初始化形参时会忽略掉顶层const：

```C++
void fcn(const int i)  { /* fcn能够读取i,但不能向i写值 */}
void fcn(int i)  { /* */ }  //错误：重复定义了fcn(int)
```

##### const 成员函数(const member function)

一般情况下，一个class T的this指针的类型是T *const，即指向类类型的常量指针，指向非常量，默认情况下不能把this绑定到一个常量对象上(即不能有this = const balbab;)。于是不能在一个常量对象上调用普通的函数成员。出于此便有了常量成员函数，在该函数的声明末尾加上关键词const

```C++
bool empty() const;
```

谨记：常量对象，以及常量对象的引用或指针都只能调用常量成员函数。

#### 智能指针

四种智能指针，其中auto_ptr是c++98标准的，在c++11中被弃用

##### shared_ptr

##### unique_ptr

##### weak_ptr



#### 动态存储空间分配(new and delete)

创建一个二维数组，动态存储分配

```C++
template <class T>
void make2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{
    x = new T *[numberOfRows];
    for(int i = 0; i < numberOfRows; i++)
        x[i] = new T [numberOfColumns];
}
//还可以创建一个二维数组，第i行的列数是rowSize[i]
template <class T>
void make2dArray(T ** &x, int numberOfRows, const int *rowSize)
{
    x = new T *[numberOfRows];
    for(int i = 0; i < numberOfRows; i++)
        x[i] = new T [rowSize[i]];
}
```

同时有释放二维数组空间的函数

```C++
template <class T>
void delete2dArray(T **&x, int numberOfRows)
{
    for(int i = 0; i < numberOfRows; i++)
        delete [] x[i];
    delete []x;
    x = nullptr;    //防止用户继续访问已经被释放的空间
}
```

异常处理可以在main函数中用try{/* */}实现，用catch{/* */}捕获异常

```C++
try{make2dArray(x, 3, 4);}
catch(std::bad_alloc)
{
        std::cerr<<"Could not creat x"<<std::endl;
        exit(1);
}
```

#### static限定符

#### 内存

<div align=center>
<img src="../media/memory structure.jpg"  />
</div>

从下往上数，最底下是代码区(.text)，然后是已经初始化的静态内存(.data)，然后是未初始化的全局和静态变量(.bss)默认为0.然后是向上生长的堆区，然后是向下生长的栈区。

静态内存与栈内存，由编译器自动创建和销毁

堆内存，程序员动态分配

代码区，存放程序的机器码，函数体的二进制代码。共享、只读。

静态内存：
-- 局部static(静态)对象
    程序执行到第一次执行定义语句时初始化，直到程序终止才被销毁。
-- 类static数据成员
    只属于类，不和任何对象绑在一起；
    在类的外部定义静态成员时，不能重复static关键字

-- 定义在任何函数之外的变量

-- 字面值常量(literal)，如字符串常量"Hello World!"等

栈内存：定义在函数内的非static对象

堆内存：





<br>

### 类和面对对象

#### 构造函数

#### 抽象类 基类(base class) 派生类(derived class)

带有纯虚函数的是抽象类，无法构建实体：

```c++
virtual bool empty() const = 0;
```

纯虚函数意味着它的派生类必须继承这个函数接口，并且给出对应的函数实现。(当然，你可以在抽象类里给出这个纯虚函数的函数实现，如果想要调用这个代码，必须在调用的时候明确指出你调用的是抽象基类的纯虚函数，如ps->Shape::draw(); 这样)

可以声明普通的虚函数，可以给派生类去继承函数接口和缺省实现，派生类也可以定义自己的函数实现。

而对于non-virtual函数，派生类会继承函数接口，并强制性继承这样的实现，不能再重新定义他。

**对于基类，一定要定义一个virtual析构函数！！！**

**多态性质的基类应该设计一个virtual析构。一个class带有任何virtual函数的时候就应该定义一个virtual析构**

### 正则表达式



## The Annotated STL Sources(stl源码剖析)


### Row-major and Column-major

在C++中，默认的二维数组的存储方式是行主序。

因此，索引 R[m][n] 代表第m行第n列

而OpenGL和GLM中采用列主序，因此索引时相反， R[m][n]代表第n行第m列

### 位运算

与   &     都是1才是1

或   |     有一个1就是1，都是0才是0

异或 ^     相同为0，相异为1

取反 ~     0变1，1变0

左移 <<    左移，高位丢弃，低位补0

右移 >>    各二进位全部右移若干位，对无符号数，高位补0，有符号数，各编译器处理方法不一样，有的补符号位（算术右移），有的补0（逻辑右移）

## Container

### 顺序容器

forward_list 和 array是c++11新增类型

支持快速随机访问：array, vector, deque, string

适合在中间插入元素：list, forward_list

既要随机访问又要中间插入元素，就要平衡上述四种容器了

连续内存空间：array, vector, string

### 性能分析
