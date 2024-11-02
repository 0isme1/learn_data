### 文本文件和二进制文件

> 计算机的一切都是以二进制的形式存储，而不同的规则，使得这些二进制数字有了含义。
>
> 当以文本形式打开某一个文件时，往往是以字符串形式获取，这些数据会按照某个规则解析。当以二进制文件打开时，则是获取其二进制，在获取阶段，往往无法知晓该段数据的含义。

### 输入 `ifstream`

> 打开某个文件，并对其进行操作eeeeeeeeeeeeeeeeeee
>
> 以文本形式打开时，往往以行的方式获取/写入数据
>
> 以二进制的形式打开时，往往以块/数据结构形式来获取/写入数据

```c++
ifstream ifs;

ifs.open(filepath,openMode);
//std::ios:: in,binary
ifs.read();

getline(ifstream&,string);

ifs.close();
```

### 输出 `ofstream`

> 将数据输出到硬盘内
>
> 以文本形式打开时，往往以行的方式获取/写入数据
>
> 以二进制的形式打开时，往往以块/数据结构形式来获取/写入数据

```c++
ofstream ofs;

ofs.open(filepath,openMode);
//std::ios:: out,binary,app,

getline(ifstream&,string);
ofs.write();

ifs.close();
```

### 随机存取

> 每一个流都有一个文件指针（仅有一个），该指针指向当前操作的位置(字节)
>
> 正常读取或输出时，该位置会自动更新，但是我们依旧可以手动控制其值

```c++
//对于ifstream对象，tellg，seekg  
//对于ofstream对象，tellp，seekp
//对于fstream对象，tellp，tellg值相同，seekg和seekp修改同一个值

//seek有两种方式，一种偏移，一种指定值
```



### 文件缓冲区

> 由于，开启磁盘读写一次耗时较长，所以设立读写缓冲区，每个流都有单独的缓冲区，当读入时，操作系统会将一块内容写入缓冲区，输出时，内容会先放在缓冲区，直到缓冲区满才会开启磁盘读写。
>
> 我们只需要关注输出缓冲区就行，可以手动刷新缓冲区，
>
> 1. flush成员函数
> 2. `endl`会换行，然后刷新缓冲区
> 3. 设置流属性，`fout<<unitbuf` , 使用`fout<<nounitbuf`可以恢复

### 流状态

> 流在工作过程中可能出问题，为了让程序员知晓问题出在哪，设置了三种标志位
>
> 1. `eofbit` 读文件是否读完
> 2. `badbit` 无法诊断，如对输入流进行写入，磁盘没有空间
> 3. `failbit` 输入流未能读取到预期的字符
>
> 使用clear可以清除三种状态，`setstate`可以重置流状态