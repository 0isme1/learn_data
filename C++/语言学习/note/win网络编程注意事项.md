### 链接

> 当我们引用某些库函数时，虽然引用了头文件，但是并没有他的实现，也就是没有链接到其实现.程序实现往往封装成库，分两种有静态库.a，.lib，动态库.so，.dll。
>
> 在window下使用预处理指令`pragma comment([类型],"库文件名称以及后缀")`
> 如`#pragma comment(lib,"ws2_32.lib)`
>
> 程序从代码到运行会经历以下步骤
>
> 1.预处理   处理预编译指令
> 2.编译		进行语法分析，代码优化等，生成汇编代码
> 3.汇编		使用汇编器将汇编代码转化为机器指令，生成可重定位的目标文件
> 4.链接		将目标文件及依赖的库连接到一起，生成最终的可执行文件

### 初始化网络库

> 在win平台使用网络编程时，需要初始化网络库，具体操作如下

```c++
	WORD wVersionRequested;
	WSADATA wsaData;

	int err;

	wVersionRequested = MAKEWORD(2, 2);   //获得一个值
	
	err = WSAStartup(wVersionRequested, &wsaData);  //用该

//网络容错
	if (err != 0)
	{
		printf("WSAStartup errorNum = %d\n", GetLastError());
		return err;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("LOBYTE errorNum = %d\n", GetLastError());
		WSACleanup();
		return -1;
	}
```



