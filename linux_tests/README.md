
## 进程

```asm

fork 子进程会复制父进程的内存空间，但是对于打开的文件则是共享的（包括读写位置）
vfork 子进程与父进程共享内存空间（数据段、代码段），好处是可以快速的创建子进程，问题是共享的代码和数据有竞争问题
而且因为函数栈也是共享的，很可能一个函数栈被释放了，另外一个才去执行，就要就报错了

如果在子进程中调用exec系列函数，会将子进程的用户空间资源（正文，数据，堆栈，）完全由新程序替代
system以新进程方式运行一个程序，然后结束。system函数用来创建新进程，并在此进程中运行新程序，直到新进程结束后，才继续运行父进程。进程结束后
会返回退出状态。如wait一样

孤儿进程：父进程先结束了，子进程交给了init进程，由init进程负责回收子进程的内核PCB
僵尸进程：子进程结束了，但它的父进程还没有回收子进程的内核PCB，此时进程是僵尸进程

```

## 文件操作


```asm

FILE *fp;//这个是流，可用fprintf()进行操作，还可以设置缓冲区
fflush刷新流的用户空间的缓冲区

POSIX的文件操作是更加底层的系统调用，以文件描述符为操作对象
sync 只是将修改过的块的缓存排入写入队列，然后就返回
fsync和fdatasync会等待修改过的块写到磁盘，fdatasync只更新数据，不更新文件属性

mmap、munmap、msync 提供了高效的文件访问方式


```

## 内存分析

```asm

pmap -x pid
查看内存使用情况
/proc/${pid}/maps 会获得同样的信息


```

## UTF-8支持

```

#include

#include

int main()

{
FILE* fp = fopen("test.txt", "wt+,ccs=UTF-8");

wchar_t* s = _T("hello, 你好！");

fwrite(s, sizeof(wchar_t), wcslen(s), fp);

fclose(fp);

return 0;

}

第二种情况，先将字符串编码转换为UTF-8格式的，然后再写入。

#include

#include

#include

int main()

{
FILE* fp = fopen("test.txt", "wb+");

// 写入UTF-8的BOM文件头

char header[3] = {(char)0xEF, (char)0xBB, (char)0xBF};

fwrite(header, sizeof(char), 3, fp);

char* s = "hello, 你好！";

wchar_t wc[256];

// 将ANSI编码的多字节字符串转换成宽字符字符串

int n = MultiByteToWideChar(CP_ACP, 0, s, strlen(s), wc, 256);

if ( n > 0 )

{
wc[n] = 0;

char mb[1024];

// 将宽字符字符串转换成UTF-8编码的多字节字符串

n = WideCharToMultiByte(CP_UTF8, 0, wc, wcslen(wc), mb, 1024, NULL, NULL);

if ( n > 0 )

{
mb[n] = 0;

fwrite(mb, sizeof(char), strlen(mb), fp);

}

}

fclose(fp);

return 0;

}

```



## X11

sudo apt-get install libpng-dev libjpeg-dev libxml2-dev libfreetype6-dev libx11-dev


## GTK相关的包

/usr/lib/x86_64-linux-gnu/pkgconfig/gdk-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gdk-broadway-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gdk-wayland-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gdk-x11-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-broadway-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-unix-print-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-wayland-3.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/gtk+-x11-3.0.pc

/usr/lib/x86_64-linux-gnu/pkgconfig/webkit2gtk-4.0.pc
/usr/lib/x86_64-linux-gnu/pkgconfig/webkit2gtk-web-extension-4.0.pc