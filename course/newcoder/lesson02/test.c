#include <stdio.h>

#define PI 3.14

// gcc编译四过程
// 1、预处理
// gcc test.c -E -o test.i 生成预编译文件并输出到test.i
// 2、编译
// gcc test.i -S -o test.s 生成汇编代码并输出到test.s
// 3、汇编
// gcc test.s -c -o test.o 生成二进制代码并输出到test.o
// 4、链接 
// gcc test.o [.c...c] -o test 将多个.o文件链接到一起

// 一步到位
// gcc test.c -o test
// gcc -o test test.c 这样写也可以

int main(void)
{
    //这是测试代码
    int Sum = PI + 10;

    printf("Hello World\n");
    return 0;
}

