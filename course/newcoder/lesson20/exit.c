/*
    #include <unistd.h>
    void _exit(int status);

    #include <stdlib.h>
    void _Exit(int status);

    status参数：是进程退出时的一个状态信息。父进程回收子进程资源的时候可以获得


*/

#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("hello\n");
    printf("world");
    exit(0);
    _exit(0);
    return 0;
}