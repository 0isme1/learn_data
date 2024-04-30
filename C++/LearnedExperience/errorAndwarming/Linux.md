## 执行可执行文件出错

> 错误信息：
> error while loading shared libraries: libAnimal.so: cannot open shared object file: No such file or directory
>
> 原因：
> 
>处理结果：
> 需要将相应的dll文件夹配置到环境变量中，如果环境变量没有问题，则可能是创建动态库时，使用了相对路径