# MakeFile

## 静态库制作与链接

> ```c++
> //静态库制作
> 
> g++ -c fileName -o lib+targetName.a
>     
> //静态库的使用
>     //链接使用  fileName 不需要后缀
>     g++ -c fileName -L filePosition -l filename -o targetName
>     g++ -o targetName fileName -L filePosition -l filename
>  
> ```

## 动态库制作与链接

> ```c++
> //make Dynamic Link Library   / make dll
> 		g++ fileName -fPIC -shared -o lib+targetName.so
> //use dll
>         g++ fileName -L filePosition -l fileName -o targetName
> 
> ```
>
> 注意：运行动态库链接的执行文件，需要提前配置相应环境变量
>
> ```c++
> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:filePosition
> ```

## make_file文件编写

> make_file文件编写
>
> ```makefile
> #目标文件
> all:libAnimal.a libAnimal.so
> 
> #用于生成目标文件
> libAnimal.a:Animal.h Animal.cpp
> 		g++ -c Animal.cpp -o libAnimal.a
> 
> libAnimal.so:Animal.h Animal.cpp
> 		g++ -fPIC -shared Animal.cpp -o libAnimal.so
> 
> #清理时清理的文件
> clean: 
> 		rm -f libAnimal.a libAnimal.so
> ```
>
> 当相关文件被修改时，就会编译它所关联的目标文件
> 原理是，目标文件的修改时间保持最后，当关联文件被修改，修改时间晚于源目标文件，则修改

# CMake

## CMakeLists.txt文档编写

> CMake文档在构建大型项目时，往往在每个文件中都进行添加CMakeLists.txt文档，某些如include除外

> ```cmake
> cmake_minimum_required(VERSION 3.0.0)  	#指定最低版本号 
> project(CALC) 						  #指定项目名称   
> 
> SET(VAR VALUE ) 					  #定义变量
> set(CMAKE_CXX_STANDARD 11)			   #指定使用的C++标准
> set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin) #指定可执行程序输出的路径
> set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)   #指定制作库的输出路径
> 
> aux_source_directory(< dir > < variable >)     #查找某个目录中的源文件，并添加到集合中
> file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)    #搜索文件，并添加到集合中
> 
> include_directories(headpath)               #指定头文件路径
> link_directories(<lib path>)			   #链接时，指定库所在路径
> link_libraries(<static lib> [<static lib>...])  #链接静态库
> 
> #指定编码方式
> add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8")
> add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8")
> 
> add_library(库名称 STATIC 源文件1 [源文件2] ...)     #制作静态库
> add_library(库名称 SHARED 源文件1 [源文件2] ...)     #制作动态库
> add_executable(targetName main.cpp [other.cpp]) 		#生成可执行程序
> 
> target_link_libraries( <target>  <item> [item]) 		#链接动态库，也可以用来链接静态库
> 
> message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)   #日志
> ```

## 变量操作

> ```cmake
> #追加
> set(变量名1 ${变量名1} ${变量名2} ...)    #使用set拼接
> list(APPEND <list> [<element> ...])     #使用list拼接
> 
> #移除
> list(REMOVE_ITEM <list> <value> [<value> ...])
> list(REMOVE_ITEM SRC_1 ${PROJECT_SOURCE_DIR}/main.cpp)  #注意要是绝对路径，否则移除失败
> ```
>
> 更多操作见 [CMake ](https://subingwen.cn/cmake/CMake-primer/)

## 宏变量

> ```cmake
> #自定义宏
> add_definitions(-DDEBUG)
> 
> #预定义宏
> CMAKE_CXX_STANDARD        #编译标准
> PROJECT_SOURCE_DIR		  #使用cmake命令后紧跟的目录，一般是工程的根目录
> PROJECT_BINARY_DIR		  #执行cmake命令的目录
> CMAKE_CURRENT_SOURCE_DIR   #当前处理的CMakeLists.txt所在的路径
> CMAKE_CURRENT_BINARY_DIR   #target 编译目录
> EXECUTABLE_OUTPUT_PATH	   #重新定义目标二进制可执行文件的存放位置
> LIBRARY_OUTPUT_PATH		   #重新定义目标链接库文件的存放位置
> PROJECT_NAME			  #返回通过PROJECT指令定义的项目名称
> CMAKE_BINARY_DIR	       #项目实际构建路径，假设在build目录进行的构建，那么得到的就是这个目录的路径
> 
> ```

## 不同系统中使用CMake

### Linux

> 在Linux系统中，可以
>
> - 手动构建，手动编写

### Windows

> 在Windows系统中，可以
>
> - 借助IDE快速构建，如VS
