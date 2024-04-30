## 常用命令

> 注意程序编译时不能用-o进行优化，会改变代码，需要加上-g的参数
>
> ```c++
> //use gdb to begin the debug
> gdb demo.exe
> run //let the program run
> b num  //stop in the line num
> n   //next step
> s    //next step and could jump to other function
> p    //display and revise some var's value
> contiune   //go on until to the other breakpoint
> set  var   //set the value of var
> bt      //view the stack used by function
> quit    //quit gdb
> ```

## 调试core文件

> core文件，保存内存的状态，当程序被强行终止时。
> 不会自动生成，需要修改相应参数
>
> 步骤：
> ```c++
> ulimit -a    //check argements we need and set its.
> gdb demo coreName   //get some infromation
> ```

## 调试正在运行中的程序

> 常用于，程序没反应，不动，然后就挂了
> 此时从头调试很麻烦，
>
> ```C++
> //get the pid of target
> ps -ef |grep name
> //use gdb get the pid's information
> gdb fileName -p pid
> //use some command to get inf
>  bt
> ```
>
> 
>
> 