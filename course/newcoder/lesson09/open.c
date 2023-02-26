
/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h> 函数的声明在这里面
    // 打开一个已经存在的文件
    int open(const char *pathname, int flags);
        参数:
            - pathname: 要打开的文件路径
            - flags: 对文件的操作权限设置还有其它的设置
                O_RDONLY, O_WRONLY, or O_RDWR
        返回值：返回一个新的文件描述符，如果调用失败，返回-1
    errno: 属于Linux系统函数库，库里面的一个全局变量，记录的是最近的错误号

    #include <stdio.h>
    void perror(const char *s);作用：打印errno对应的错误描述
        s参数:用户描述，比如hello，最终输出的内容是hello:xxx(实际的错误描述)

    int open(const char *pathname, int flags, mode_t mode);

    #include <unistd.h>

    int close(int fd);


*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("a.txt",O_RDONLY);
    if(fd == -1)
    {
        perror("open");
    }
    //关闭
    close(fd);
    return 0;
}