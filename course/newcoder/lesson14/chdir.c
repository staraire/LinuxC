/*

    #include <unistd.h>

    int chdir(const char *path);
        作用：修改进程的工作目录
            比如再/home/newcoder 启动了一个可执行程序a.out,进程的工作目录 /home/newcoder
        参数
            path:需要修改的工作目录

    #include <unistd.h>

    char *getcwd(char *buf, size_t size);
        作用：获取当前工作目录
        参数
            - buf: 存储的路径，指向的是一个数组(传出参数)
            - size: 数组的大小
        返回值
            返回的指向一块内存，这个数据就是第一个参数


*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    // 获取当前的工作目录
    char buf[128];
    getcwd(buf,sizeof(buf));
    printf("当前的工作目录是: %s\n",buf);

    //修改工作目录
    int ret = chdir("/home/star-air/Desktop/workspace/LinuxC/course/newcoder/lesson13");
    if(ret==-1)
    {
        perror("chdir");
        return -1;
    }

    // 创建一个新的文件
    int fd = open("chdir.txt",O_RDWR|O_CREAT,0777);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    //关闭
    close(fd);
    // 获取当前的工作目录
    
    getcwd(buf,sizeof(buf));
    printf("当前的工作目录是: %s\n",buf);

    return 0;
}

