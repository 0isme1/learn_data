## QT编译过程

> 1.生成工程文件`qmake -project ` 
> 	此时会生成.pro文件，编辑该文件，在末尾添加`QT += widgets gui`
>
> 2.使用`qmake` 生成makefile文件
>
> 3.linux 使用make 进行编译； win使用mingw32-make 进行编译 
>      在release中生成可执行文件
>
> 

