#### 例子1. 内存泄漏 
```bash
$ g++ MemoryLeak.cc -g -o memory-leak
$ valgrind --tool=memcheck --leak-check=yes --show-reachable=yes memory-leak
```
错误信息：
>
==5772== HEAP SUMMARY:
==5772==     in use at exit: 20 bytes in 2 blocks
==5772==   total heap usage: 5 allocs, 3 frees, 72,900 bytes allocated
==5772== 
==5772== 10 bytes in 1 blocks are definitely lost in loss record 1 of 2
==5772==    at 0x483C583: operator new\[](unsigned long) (in /usr/lib/x86\_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==5772==    by 0x1093DC: test::test() (in /home/phoenix/DevelopmentTools/learn-valgrind/memcheck/memory-leak)
==5772==    by 0x10930F: main (in /home/phoenix/DevelopmentTools/learn-valgrind/memcheck/memory-leak)
==5772== 
==5772== 10 bytes in 1 blocks are definitely lost in loss record 2 of 2
==5772==    at 0x483C583: operator new\[](unsigned long) (in /usr/lib/x86\_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==5772==    by 0x109325: main (in /home/phoenix/DevelopmentTools/learn-valgrind/memcheck/memory-leak)
==5772== 
==5772== LEAK SUMMARY:
==5772==    definitely lost: 20 bytes in 2 blocks
==5772==    indirectly lost: 0 bytes in 0 blocks
==5772==      possibly lost: 0 bytes in 0 blocks
==5772==    still reachable: 0 bytes in 0 blocks
==5772==         suppressed: 0 bytes in 0 blocks
==5772== 
==5772== For lists of detected and suppressed errors, rerun with: -s
==5772== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

#### 例子2. 无效访问
```bash
$ g++ UnauthorizedAccess.cc -g -o unauthorized-access
$ valgrind --tool=memcheck unauthorized-access
```
错误信息：
>...
==5756== Invalid write of size 1
==5756==    at 0x10923C: main (UnauthorizedAccess.cc:7)
==5756==  Address 0x4db2c8a is 0 bytes after a block of size 10 alloc'd
==5756==    at 0x483C583: operator new[\](unsigned long) (in /usr/lib/x86\_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==5756==    by 0x1091FE: main (UnauthorizedAccess.cc:5)
==5756== 
==5756== Invalid read of size 1
==5756==    at 0x10925A: main (UnauthorizedAccess.cc:9)
==5756==  Address 0x4db2c8a is 0 bytes after a block of size 10 free'd
==5756==    at 0x483D74F: operator delete\[](void*) (in /usr/lib/x86\_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==5756==    by 0x109251: main (UnauthorizedAccess.cc:8)
...

#### 例子3. 访问未初始化内存
```bash
$ g++ UninitilizedAccess.cc -g -o uninitialized-access
$ valgrind --tool=memcheck uninitialized-access 
```
错误信息：
>
==5684== Conditional jump or move depends on uninitialised value(s)
==5684==    at 0x4AD3F5D: \_IO\_file\_overflow@@GLIBC_2.2.5 (fileops.c:783)
==5684==    by 0x4AD51A3: \_IO\_default\_xsputn (genops.c:399)
...
==5684==    by 0x1091FF: main (UninitilizedAccess.cc:7)
...
==5800== Syscall param write(buf) points to uninitialised byte(s)
==5800==    at 0x4B511E7: write (write.c:26)
==5800==    by 0x4AD200C: \_IO\_file\_write@@GLIBC\_2.2.5 (fileops.c:1181)
==5800==    by 0x4AD3AD0: new\_do\_write (fileops.c:449)
==5800==    by 0x4AD3AD0: \_IO\_new\_do\_write (fileops.c:426)
==5800==    by 0x4AD3AD0: \_IO\_do\_write@@GLIBC\_2.2.5 (fileops.c:423

#### 例子4. 非法 free
```bash
$ g++ IllegalFree.cc -g -o illegal-free
$ valgrind illegal-free
```
错误信息
> ==5943== Mismatched free() / delete / delete []
==5943==    at 0x483D74F: operator delete[](void*) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==5943==    by 0x10919C: main (IllegalFree.cc:4)
==5943==  Address 0x4db2c80 is 0 bytes inside a block of size 4 alloc'd
==5943==    at 0x483BE63: operator new(unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==5943==    by 0x109185: main (IllegalFree.cc:3)

#### 例子5.内存重叠
```bash
$ g++ MemoryOverlap.cc -g -o memory-overlap 
$ valgrind memory-overlap 
```
错误信息
> 
==6882== Source and destination overlap in strncpy(0x1ffefffe19, 0x1ffefffe05, 21)
==6882==    at 0x483F320: strncpy (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==6882==    by 0x1091DF: main (MemoryOverlap.cc:13)
==6882== 

