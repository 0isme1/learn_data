### 创建进程

1. **exec系列**(调用可执行程序)

     > **是什么：**
     >
     > - `exec`系列函数（如`execlp`, `execv`等）用于将当前进程的代码段替换为新程序的代码段。简而言之，它们会在当前进程中执行一个新程序。
     > - 一旦`exec`调用成功，当前进程的地址空间、代码段、数据段等都会被新程序所替换，执行新程序的代码，并不会创建新的进程。
     >
     > **用法**：
     >
     > - 通常与`fork()`一起使用：先使用`fork()`创建一个子进程，然后在子进程中使用`exec()`执行新程序。
     > - 这样，父进程可以继续执行原有的程序，而子进程则执行一个完全不同的程序。
     > - 
     >
     > 该函数会创建一个进程，来取代调用者的进程
     >
     > l 进程执行的参数，以可变参数的形式给出，这些参数以NULL结尾
     >
     > p exec会将当前的path作为参考环境变量
     >
     > e  进程函数，需要用户设置环境变量
     >
     > v 进程函数，会用一个参数数组，来传递argv

     1. **`int execl(const char* path,const char* arg,...)`**

          ```c++
          execl("bin/ls","ls","-l",NULL);
          //它会执行ls -l 命令
          ```

     2. **`int execlp(const char *file, const char *arg, ...);`**

          ```c++
          execlp("ls","ls","-l",NULL);
          //会执行ls -l命令
          ```

     3. `int execle(const char *path,const char* arg,...,char*const envp[])`

          

2. **fork**

     > **是**：`fork()`用于创建一个新进程。新进程是调用进程的副本，称为子进程。
     >
     > 子进程拥有与父进程相同的代码、数据、堆和栈，但它们是独立的，子进程继承了父进程的大部分环境。
     >
     > `fork()`返回两次：一次在父进程中，返回子进程的PID（进程ID）；一次在子进程中，返回0。如果`fork`失败，它将在父进程中返回`-1`。

     > **用**：通常用于需要并行执行的任务，例如在服务器中处理多个客户端请求时，每个请求可以使用一个子进程来处理。
     >
     > 在`fork()`之后，父子进程可以选择继续执行相同的代码或使用`exec`来运行不同的程序。

### 结束进程

1. **`void abort(void)`**

     > 终止当前进程，并生成一个core dump文件便于分析

     ```c++
     #include <stdio.h>
     #include <stdlib.h>
     
     int main() {
         printf("Program is running...\n");
     
         // 发现致命错误，立即终止程序
         printf("A critical error occurred. Terminating the program.\n");
         abort();
     
         // 这行代码永远不会被执行
         printf("This line will never be printed.\n");
     
         return 0;
     }
     
     ```

2. **`void assert(int expression)`**

     > 当express表达式为假时，终止程序，并给出相关信息。常常用于开发测试时，发布时可以通过定义BDEBUG宏来移除该函数。

     ```c++
     #include <stdio.h>
     #include <stdlib.h>
     #include <assert.h>
     
     int main() {
         int x = -1;
     
         // 使用assert来检查x的值是否为非负
         assert(x >= 0);  // 如果x < 0，这里会触发断言失败，并输出调试信息
     
         // 紧急情况下使用abort来强制终止程序
         if (x < 0) {
             printf("Critical error: x is negative. Aborting.\n");
             abort();  // 立即终止程序，不输出额外信息
         }
     
         printf("This line will not be executed if x < 0.\n");
     
         return 0;
     }
     
     ```

3. **`void exit(int status)`**

     > 正常结束程序
     >
     > 调用通过 `atexit()` 注册的所有清理函数，按逆序执行。
     >
     > 刷新并关闭所有打开的标准 I/O 流（例如 `stdout`, `stderr`），确保所有缓冲区的数据被写入文件或终端。
     >
     > 调用操作系统提供的 `_exit()` 函数，最终终止进程，并返回 `status` 给操作系统。

4. **`void _exit(int status)`**

     > 设置程序正常结束前调用的函数
     >
     > 
     >
     > `_exit()` 是系统调用，直接终止进程，通常用于子进程中。
     >
     > 调用 `_exit()` 时，它会立即终止进程，而不会执行任何清理操作：
     >
     > 1. 不会调用通过 `atexit()` 注册的函数。
     > 2. 不会刷新或关闭标准 I/O 流。
     > 3. 直接向操作系统返回 `status`，终止进程。

5. **`int atexit(void(*fun)(void))`**

     > 注册/登记一个程序正常结束前调用的函数
     >
     > `atexit()` 是一个标准 C 库函数，用于注册一个函数，当程序通过调用 `exit()` 正常终止时，这个函数会被自动调用。
     >
     > 通过 `atexit()` 注册的函数按注册的逆序执行（即后注册的函数先执行）。
     >
     > `atexit()` 只接受一个不带参数且无返回值的函数指针。
     >
     > 该函数在 ANSI C 标准中被定义，几乎在所有平台上都可用。(考虑兼容性，且不需要传递信息，优先使用)

6. `int on_exit(void(*funtion)(int,void*),void* arg)`

     > `on_exit()` 是一种非标准函数（POSIX 特性，在某些 Unix 系统上可用），用于注册一个函数，这个函数将在程序通过 `exit()` 正常终止时调用。
     >
     > 与 `atexit()` 不同，`on_exit()` 注册的函数可以接受两个参数：
     >
     > 1. `int status`：`exit()` 调用时传递的退出状态。
     > 2. `void *arg`：可以传递给 `on_exit()` 注册函数的一个指针参数，允许传递上下文数据。



### 保存恢复环境

> c语言的一种异常处理机制

1. `int setjmp(jmp_buf environment)`

     > 保存当前堆栈环境
     >
     > `setjmp` 是一个 C 标准库函数，用于保存当前的程序执行环境（包括程序计数器、栈指针等），以便以后通过 `longjmp` 恢复这个环境，继续执行。
     >
     > `setjmp` 的常见使用场景是异常处理和非局部跳转。

2. `int sigsetjmp(sigjmp_buf env,int savemask)`

     > 保存当前堆栈环境
     >
     > `sigsetjmp` 是 POSIX 标准的一部分，类似于 `setjmp`，但它提供了额外的功能，允许在保存执行环境时选择性地保存当前的信号屏蔽集（signal mask）。
     >
     > 与之对应的恢复函数是 `siglongjmp`。

3. `void longjmp(jmp_buf env,int value)`

4. `void siglongjmp(sigjmp_buf env,int val)`

### 进程(组)识别码及优先级

1. **`pid_t getpid(void)`**

     > 获得当前进程识别码

2. **`pid_t getppid(void)`**

     > 获得父进程识别码

3. **`pid_t getpgrp(void)`**

     > 获取当前进程组识别码

4. **`pid_t getpgid(pid_t pid)`**

     > 取得进程所属进程组识别码 

5. **`int setpgid(pid_t pid,pid_t pgid)`**

     > 设置进程组识别码，将pid设为pgid

6. **`int serpgrp(void)`**

     > 设置进程组识别码，将所属组id设为所属进程id

7. **`int getpriority(int witch,int who)`**

     > 取得程序进程执行优先权

8. **`int serpriority(int which,int who,int prio)`**

     > 设置程序执行优先权

9. **`int nice(int inc)`**

     > 改变程序优先级，修改当前进程优先级，inc为偏移量

### 等待进程

1. **`int wait(int* status)`**

     > 等待子进程中断或结束
     >
     > **功能**: `wait()` 用于使调用的父进程挂起（暂停执行），直到它的任一子进程终止。当子进程终止时，`wait()` 会返回子进程的进程ID，并在提供的参数中存储子进程的终止状态。
     >
     > **限制**: `wait()` 只能处理任意一个终止的子进程。如果有多个子进程，它会等待第一个终止的子进程，但不能指定等待某个特定的子进程。

     ```c++
     #include <sys/types.h>
     #include <sys/wait.h>
     #include <unistd.h>
     #include <stdio.h>
     
     int main() {
         pid_t pid = fork();
         if (pid == 0) {
             // 子进程代码
             sleep(2);
             return 0;
         } else {
             // 父进程代码
             int status;
             pid_t terminated_pid = wait(&status);
             if (terminated_pid > 0) {
                 printf("子进程 %d 终止。\n", terminated_pid);
             }
         }
         return 0;
     }
     
     ```

     

2. **`pid_t waitpid(pid_t pid,int* status,int options)`** 

     > **功能**: `waitpid()` 是 `wait()` 的一个更灵活的版本。它允许父进程：
     >
     > - 等待特定的子进程（通过指定进程ID）。
     > - 选择是否阻塞父进程（通过传递不同的选项，例如 `WNOHANG`）。
     > - 还可以通过不同的选项设置以处理不同的子进程终止情况（例如 `WUNTRACED`，`WCONTINUED`）。
     >
     > **参数**:
     >
     > - `pid`
     >
     >      : 可以是子进程的ID，也可以是以下特殊值：
     >
     >      - `-1`: 等待任何子进程，这相当于`wait()`的行为。
     >      - `> 0`: 等待特定进程ID的子进程。
     >      - `0`: 等待同一进程组中的任一子进程。
     >      - `< -1`: 等待绝对值为`pid`的进程组ID中的任一子进程。
     >
     > - `options`: 用于修改等待行为的选项，如 `WNOHANG`（非阻塞）或 `WUNTRACED`（等待未决的子进程）。

     ```c++
     #include <sys/types.h>
     #include <sys/wait.h>
     #include <unistd.h>
     #include <stdio.h>
     
     int main() {
         pid_t pid = fork();
         if (pid == 0) {
             // 子进程代码
             sleep(2);
             return 0;
         } else {
             // 父进程代码
             int status;
             pid_t terminated_pid = waitpid(pid, &status, 0);
             if (terminated_pid > 0) {
                 printf("子进程 %d 终止。\n", terminated_pid);
             }
         }
         return 0;
     }
     
     /*
     灵活性: waitpid() 比 wait() 更灵活，可以指定等待的子进程，甚至可以设置非阻塞模式。
     使用场景: 如果你只需要等待任意一个子进程结束，wait() 可能已经足够。如果你需要等待特定子进程或使用非阻塞模式，waitpid() 是更好的选择。
     非阻塞选项: waitpid() 可以通过 WNOHANG 选项实现非阻塞操作，而 wait() 始终是阻塞的。
     */
     ```

     