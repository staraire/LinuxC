/*

    #include <sys/types.h>
    #include <dirent.h>
    // 打开一个目录
    DIR *opendir(const char *name);
        参数
            - name:需要打开的目录的名称
        返回值
            DIR * 类型：理解为目录流
            错误返回NULL


    #include <dirent.h>
    //读取目录中的数据
    struct dirent *readdir(DIR *dirp);
        参数
            - dirp是opendir返回的结果
        返回值
            struct dirnet ：代表读取到文件的信息
            读取到了末尾或者失败了，返回的就是NULL

            struct dirent
            {
            // 此目录进入点的inode
            ino_t d_ino; 
            // 目录文件开头至此目录进入点的位移
            off_t d_off;   
            // d_name 的长度, 不包含NULL字符
            unsigned short int d_reclen; 
            // d_name 所指的文件类型
            unsigned char d_type;   
            // 文件名
            char d_name[256];
            };

            d_type
            DT_BLK  - 块设备
            DT_CHR  - 字符设备
            DT_DIR  - 目录
            DT_LNK  - 软连接
            DT_FIFO - 管道
            DT_REG  - 普通文件
            DT_SOCK - 套接字
            DT_UNKNOWN - 未知


    #include <sys/types.h>
    #include <dirent.h>
    // 关闭目录
    int closedir(DIR *dirp);


*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFileNum(const char * path);

// 读取某个目录下所有的普通文件的个数
int main(int argc,char *argv[]){
    if(argc < 2)
    {
        printf("%s path\n",argv[0]);
        return -1;
    }
    
    int num = getFileNum(argv[1]);
    printf("普通文件的个数:%d\n",num);
    return 0;
}

// 用于获取目录下所有普通文件的个数
int getFileNum(const char * path){
    // 1 打开目录
    DIR * dir = opendir(path);

    // 记录普通文件的个数
    int total = 0;

    if(dir == NULL)
    {
        perror("OPENDIR");
        exit(0);
    }
    struct dirent *ptr;

    while((ptr = readdir(dir)) != NULL)
    {
        // 获取名称
        char *dname = ptr->d_name;



        //忽略掉 . 和 ..
        if(strcmp(dname,".") == 0 || strcmp(dname,"..") == 0){
            continue;
        }
        // 判断是普通文件还是目录
        if(ptr->d_type == DT_DIR)
        {
            //目录，继续读取这个目录
            char newpath[256];
            sprintf(newpath,"%s/%s",path,dname);
            getFileNum(newpath);
        }

        if(ptr->d_type == DT_REG){
            //普通文件
            total++;
        }
    }

    // 关闭目录
    closedir(dir);
    return total;
}