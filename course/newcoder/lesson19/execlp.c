/*
    #include <unistd.h>

    extern char **environ;

    int execlp(const char *file, const char *arg, ... );
        会到环境变量中找指定的可执行的文件，如果找到了就执行，找不到就执行不成功
        参数:
            - path：需要执行的可执行文件的文件名
                a.out /home/newcoder/a.out 推荐使用绝对路径
                ./a.out hello world
            - arg: 是执行可执行文件所需要的参数
                第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称
                从第二个参数往后，就是程序执行所需要的参数列表
                参数最后需要以NULL结束(哨兵)

            返回值：
                只有当调用失败，才会有返回值，返回-1，并且设置errno
                调用成功，没有返回值(调用成功，将不返回)
            
            
            int execv(const char *path, char *const argv[]);
            argv是需要的参数的一个字符串数组
            char * argv[] = {"ps", "aux", NULL};
            execv("/bin/ps", argv);

            int execve(const char *filename, char *const argv[], char *const envp[]);
            char * envp[] = {"/home/nowcoder", "/home/bbb", "/home/aaa"};

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
        //execl("/bin/ps","ps","aux",NULL);
        execlp("hello","ps","aux",NULL);
        printf("child process\n");   
    }

    for(int i = 0;i < 3;i++){
        printf("i = %d pid : %d\n",i,getpid());
    }
    return 0;
}