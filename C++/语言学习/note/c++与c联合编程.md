### 1static与inline

> static 是函数，变量和类的修饰符之一，表示为静态
> 在c中，可以修饰**局部变量**，**全局变量**和**函数**，在c++中还可以修饰**类**
>
> 其常用于控制变量的**存储方式**，和**作用范围**

#### 修饰局部变量和函数

> 1.不改变作用域，但生命周期延长
> 2.其存储位置在静态区，而非栈区，程序结束后才释放
> 3.默认初始化为0，仅可被初始化一次；
> 4.和全局变量相比，static可以控制变量的可见范围

```c++
void test(){
    static int t = 1;
    t++;
    std::cout<<t<<std::endl;
}

void main(){
    test();   //2
    test();		//3
    test();		//4
}
```

#### 修饰全局变量和函数

> 1.全局变量作用范围非常广，既可以在源文件中使用，也可以通过extern关键字在其他文件中使用，	
> 2.static修饰全局变量，会改变全局变量和函数的链接属性，使其只能在内部链接，缩小作用域。可以避免命名冲突。

```c++
//test.cpp
int a = 10;
void prints(){
    std::cout<<"static test"<<std::endl;
}

//main.cpp
extern int a;             //外部链接/声明 
extern void prints();        //在test.cpp 中，给a和prints加上static修饰后，程序将无法通过编译。

int main(){
    std::cout<<a<<std::endl;
    prints();
    
    return 0;
}
```

#### 修饰类

> static可以修饰类的成员变量和成员函数，其中成员变量一定要在类外初始化

1.静态成员为所有类对象所共享，不属于某个具体的实例

```c++
class A{
    private:
    	static int a;
    	int b;
    	char c;
};

int main(void){
    std::cout<<sizeof(A)<<std::endl;  //输出8，并未将a算入其中
}
```

2.静态成员变量必须在类外初始化，初始化时不添加static关键字

```c++
class A
{
private:
	static int _n;
	static int _k;
};
int A::_n = 0;
int A::_k = 0;
```

3.静态成员函数没有隐藏的this指针，不能访问任何非静态成员

```c++
class A
{
public:
	static void Func()
	{
		cout << ret << endl;  // err错误，访问了非静态成员，因为无this指针
		cout << _k << endl; //正确
	}
private:
	//声明
	int ret = 0;
	static int _k;
};
//定义
int A::_k = 0;
```

4.访问静态成员变量的特殊方式

> 静态成员为共有时
> 1.对象.静态成员
> 2.类名::静态成员
> 3.匿名对象.静态成员
> 如果为私有，则通过访问静态成员函数来访问变量

### 2定义与声明

> 对于编译器而言，在预处理完成后，会有一个.i文件，编译器会编译该文件，如果遇到该行代码
>
> `int a = add(1,2);` 如果之前从未有过add出现，那么编译器并不知道这个步骤是否合理，会立即停止编译，并给出错误。可以将定义放在前面，或者将声明放在前面，声明在编译时并不会分配内存。

### 3头文件和源文件

> 在学习函数后，会发现，在之前没有定义或者声明的函数，编译器会报错，那么为什么有些函数，我们并没有主动写，却也可以通过编译呢？在学习时，往往引用头文件后，就可以正常编译哪些我们未定义的函数。

> 可以猜测，头文件中，可能有着它们的声明或定义，事实也是如此，当程序复杂起来后，将常用函数，或者变量或者类，都在一个头文件中声明，是一种不错的选择。它们的定义实现也已封装号在磁盘中，在链接时，会正确的和源目标文件链接。

```c++
//在自定义头文件时，需要配置相关属性，以便于程序可以正常查找自定义头文件，一些ide会默认好这些配置（将头文件放在正确的位置时）

//test.h

void testHead();
void testPrint();

//test.cpp
void testHead(){
    std::cout<<"hello main"<<std::endl;
}

void testPrint(){
    std::cout<<"hello print"std::endl;
}

//main.cpp
#include"test.h"
int main(void){
    testHead();
    testPrint();
}
```

> 注意，`#include` 在预处理阶段会按照逻辑，将该条命令处理为一段代码，如果在头文件中嵌套循环应勇头文件，可能会出现无限引用的情况，可以使用两个方法
>
> 1.  `#progma once`
>
> 2.  `#ifndef 变量名称`
>        `#define 变量名称`
>
>      代码区
>      `#endif`

#### c和c++源文件混用问题

> 编译时，会将各个文件编译成.obj文件，如果.c 文件和.cpp文件重名，则会生成两个相同的.obj文件。

### 4extern

>  由于c++支持函数重载，c风格和c++风格对于函数是否相同的判断并不相同，c++风格一般无法调用c风格的函数，而extern可以处理这种情况，但是c无法使用c++风格函数
>
> extern作用
>
> 1. 声明
> 2. 表明函数为c风格  `extern "c" {int test();}`
> 3. `extern "c" { #include<>}`
>
> c风格中 extern”c” 不成立，需要特殊从处理

```C++
#ifdef __cplusplus
extern "c"
#endif
int add();

//该文件可以同时被c++和c引用
```

### 5自定义sdk

> sdk往往是一个封装好的工具包，里面包含封装好的库函数等
>
> 生成库后，可以库文件和头文件放在一个文件夹
> 通过vs配置后即像iostream等头文件一样引用，
>
> lib需要额外配置链接器或者使用   `#pragma comment(lib,"库名称")`
>
> 注意release，debug需要对应

### 5函数调用约定

> 函数调用约定是调用者和被调用者之间的一种协议，其规定了，如何传递参数，如何恢复栈平衡
>
> 1. __cdecl  : 参数入栈顺序，从右往左  ，堆栈平衡：谁调用谁平衡
> 2. __stdcall : 参数入栈顺序，从右往左   ，堆栈平衡：被调用者平衡
> 3. __fastcall :  优先通过寄存器来存参数（两个ECX/EDX），从右到左（push）   ，由被调用者恢复
> 4. __thiscall:  用于c++中类的访问，参数从右到左，需要将实例化对象指针赋值给寄存器，由被调用者恢复
> 5. naked call  :不常用，一般用于驱动开发

> **类的自定义函数调用约定**： 在函数定义前加入约定