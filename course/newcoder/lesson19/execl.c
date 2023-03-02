/*
    #include <unistd.h>

    extern char **environ;

    int execl(const char *path, const char *arg, ... );
        参数:
            - path：需要指定的执行的文件的路径或者名称
                a.out /home/newcoder/a.out 推荐使用绝对路径
                ./a.out hello world
            - arg: 是执行可执行文件所需要的参数
                第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称
                从第二个参数往后，就是程序执行所需要的参数列表
                参数最后需要以NULL结束(哨兵)

            返回值：
                只有当调用失败，才会有返回值，返回-1，并且设置errno
                调用成功，没有返回值(调用成功，将不返回)


*/


#include <unistd.h>
#include <stdio.h>


int main(){

    // 创建一个进程
    pid_t pid = fork();

    if(pid > 0){
        // 父进程
        printf("parent process\n");
        sleep(1);
    }
    else if(pid == 0)
    {
        //子进程
        //execl("hello","hello",NULL);
        execl("/bin/ps","ps","aux",NULL);
        printf("child process\n");   
    }

    for(int i = 0;i < 3;i++){
        printf("i = %d pid : %d\n",i,getpid());
    }
    return 0;
}