/*

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);
        作用：获取文件相关的信息
        参数：
            - pathname: 操作的文件的路径
            - statbuf: 结构体变量，传出参数 用于保存获取的文件信息
        返回值
            - 成功：返回0 
            - 失败：返回-1 设置errno


    int lstat(const char *pathname, struct stat *statbuf);
        参数：
            - pathname: 操作的文件的路径
            - statbuf: 结构体变量，传出参数 用于保存获取的文件信息
        返回值
            - 成功：返回0 
            - 失败：返回-1 设置errno

结构体
struct stat {
    dev_t st_dev; // 文件的设备编号
    ino_t st_ino; // 节点
    mode_t st_mode; // 文件的类型和存取的权限
    nlink_t st_nlink; // 连到该文件的硬连接数目
    uid_t st_uid; // 用户ID
    gid_t  st_gid; // 组ID
    dev_t st_rdev; // 设备文件的设备编号
    off_t st_size;       // 文件字节数(文件大小)
    blksize_t st_blksize;    // 块大小
    blkcnt_t st_blocks;     // 块数
    time_t st_atime;      // 最后一次访问时间
    time_t st_mtime;      // 最后一次修改时间
    time_t st_ctime;      // 最后一次改变时间(指属性)
};



*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>

int main(){
    struct stat statbuf;
    int ret = stat("a.txt",&statbuf);
    if(ret == -1)
    {
        perror("stat");
        return -1;
    }

    printf("size:%ld\n",statbuf.st_size);
    printf("size:%o\n",(statbuf.st_mode & S_IFMT));
    // %o 8进制 %X 16进制
    //printf("filemode:%d\n",statbuf.st_mode & S_IFMT);

    return 0;
}