#include <stdio.h>

int main()
{
    int a = 10;
// gcc test.c -DDEBUG 在编译时加入这个宏才会编译下面这句
// gcc test.c -o test -Wall
// -Wall 生成所有警告信息 -w 不生成警告
#ifdef DEBUG
    printf("我是一个程序猿, 我不会爬树...\n");
#endif
    for(int i=0; i<3; ++i)
    {
        printf("hello, GCC!!!\n");
    }

    int b, c, d, f;
    b = 10;
    c = b;
    d = c;
    f = d;

    /*
        int b,c,d,f;
        b = 10;
        c = 10;
        d = 10;
        f = 10;
    */


    return 0;
}
