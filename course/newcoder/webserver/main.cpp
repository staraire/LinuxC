// c标准库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>   
#include <assert.h>
// 网络相关
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// 系统编程相关
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <signal.h>
// 自定义头文件
#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"

#define MAX_FD 65535
#define MAX_EVENT_NUMBER 10000


// 添加信号捕捉
void addsig(int sig,void (*handler)(int)){
    struct sigaction sa;
    memset(&sa,'\0',sizeof(sa));
    sa.sa_handler = handler; // 回调函数
    sigfillset(&sa.sa_mask); // 注册信号阻塞集
    // sigaction(sig,&sa,NULL); // 注册信号
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

// 添加文件描述符到epoll中
extern void addfd(int epollfd,int fd,bool one_shot);

// 从epoll中删除文件描述符
extern void removefd(int epollfd,int fd);

//修改文件描述符
extern void modfd(int epollfd,int fd,int ev);

int main(int argc,char *argv[]){
    if(argc <= 1){
        // basenaame函数的作用是把路径信息删掉
        // https://blog.csdn.net/Draven_Liu/article/details/38235585
        printf("按照如下格式运行 %s port_number\n",basename(argv[0]));
    }

    // 获取端口号
    int port = atoi(argv[1]);

    // 对SIGPIE信号做处理
    addsig(SIGPIPE,SIG_IGN); //忽略SIGPIPE信号

    // 创建线程池，初始化线程池
    threadpool<http_conn> *pool = NULL;
    try{
        pool = new threadpool<http_conn>;
    }catch(...){ // 异常信号
        exit(-1);
    }

    // 创建一个数组用于保存所有的客户端信息
    http_conn * users = new http_conn[MAX_FD];

    // 创建套接字
    int listenfd = socket(PF_INET,SOCK_STREAM,0);

    // 绑定
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // 设置端口复用
    int reuse = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    bind(listenfd,(struct sockaddr*)&address,sizeof(address));

    // 监听
    int ret = 0;
    ret = listen(listenfd,5);

    // 创建epoll对象，事件数组，添加
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);

    // 将监听的文件描述符添加到epoll种
    addfd(epollfd,listenfd,false);
    http_conn::m_epollfd = epollfd;

    while(true){
        int num = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1); //等待有socket连接
        if((num<0)&&(errno != EINTR)){
            printf("epoll failure\n");
            break;
        }

        // 循环遍历事件数组
        for(int i=0;i<num;i++){
            int sockfd = events[i].data.fd; //
            if(sockfd == listenfd){
                // 有客户端连接进来
                struct sockaddr_in client_address;
                socklen_t client_addrlen = sizeof(client_address);
                int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addrlen);
                if ( connfd < 0 ) {
                    printf( "errno is: %d\n", errno );
                    continue;
                } 

                // 判断连接数有没有满
                if(http_conn::m_user_count >= MAX_FD){
                    // 目前连接数满
                    // 给客户端编写一个信息：服务器内部正忙
                    close(connfd);
                    continue;
                }

                //将新的客户的数据初始化，放到数组中
                users[connfd].init(connfd,client_address);

            }else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
                //对方异常断开或者错误等事件
                users[sockfd].close_conn();
            }else if(events[i].events & EPOLLIN) {
                if(users[sockfd].read()){
                    // 一次性把所有数据读完
                    //printf("read\n");
                    pool->append(users + sockfd);

                }
                else{ // 读失败
                    users[sockfd].close_conn(); // 关闭连接
                }
            }else if(events[i].events & EPOLLOUT){
                //printf("write\n");
                if(!users[sockfd].write()){ // 一次性写完所有数据read
                    users[sockfd].close_conn();
                }
            }
        }
    }

    close(epollfd);
    close(listenfd);
    delete [] users;
    delete pool;
    return 0;

}