/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h> 函数的声明在这里面


    int open(const char *pathname, int flags, mode_t mode);
        参数:
            - path name:要穿简单文件的路径
            - flags：对文件的额操作权限和其它的设置
                - 必选项：O_RDONLY, O_WRONLY, or O_RDWR 这三个是互斥的
                - 可选项：O_CREAT 文件不存在，创建新文件
            - mode：八进制的数，用户创建新文件的操作权限，比如0775
                最终的权限： (mode & ~umask) umask默认002
                0777 & (~002) = 0777 & 0775 = 0775
                umask的作用就是抹去某些权限

    #include <unistd.h>

    int close(int fd);


*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

    // 创建新的文件
    int fd = open("create.txt",O_RDWR|O_CREAT,0777);

    if(fd == -1)
    {
        perror("open");
    }
    //关闭
    close(fd);
    return 0;
}