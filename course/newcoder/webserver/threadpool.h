#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <exception>
#include <cstdio>
#include <list>
#include "locker.h"

// 线程池：定义成模板类是为了代码复用，模板参数T就是任务类
template<typename T>
class threadpool
{
private:
    /* data */
    int m_thread_number;                // 线程的数量
    pthread_t * m_threads;              // 线程池数组，大小m_thread_number
    int m_max_requests;                 // 请求队列中最多允许的，等待处理的请求数量
    std::list< T*> m_workqueue;         // 请求队列，里面放的任务
    locker m_queuelocker;               // 互斥锁
    sem m_queuestat;                    // 信号量用来判断是否有任务需要处理
    bool m_stop;                        // 是否结束线程

private:
    static void * worker(void * arg);
    void run();

public:
    threadpool(int thread_number = 8,int max_requests = 10000);
    ~threadpool();
    bool append(T* request); // 添加任务
    
};

template<typename T>
threadpool<T>::threadpool(int thread_number,int max_requests):
    m_thread_number(thread_number),
    m_max_requests(max_requests),
    m_stop(false),
    m_threads(NULL){
    
    // 判断输入
    if((thread_number <= 0)||(max_requests <= 0)){
        throw std::exception();
    }

    // 创建thread_number个线程，并将他们设置为线程脱离
    m_threads = new pthread_t[m_thread_number];
    if(!m_threads){
        throw std::exception();
    }
    for(int i = 0;i < thread_number;++i)
    {
        printf("create the %dth thread\n",i);
        // 创建线程
        if(pthread_create(m_threads + i,NULL,worker,this) != 0){
            delete [] m_threads;
            throw std::exception();
        }
        // 线程脱离
        if(pthread_detach(m_threads[i])){
            delete [] m_threads;
            throw std::exception();
        }
    }

}

template<typename T>
threadpool<T>::~threadpool(){
    delete [] m_threads; // 删除掉线程池
    m_stop = true;
}

template<typename T>
bool threadpool<T>::append(T* request){
    
    m_queuelocker.lock(); // 上锁
    if(m_workqueue.size() > m_max_requests){
        m_queuelocker.unlock(); // 解锁
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock(); // 解锁
    m_queuestat.post(); 
    return true;
}

// worker是static类型，访问不到类里的非static成员，所以通过this指针传递
template<typename T>
void* threadpool<T>::worker(void * arg){
    // 传入的参数是this指针
    threadpool * pool = (threadpool *) arg;
    pool->run(); // 线程跑起来

    return pool;


}

template<typename T>
void threadpool<T>::run(){
    // 线程池没有关闭
    while(!m_stop){
        m_queuestat.wait(); // 等待添加任务，等post
        m_queuelocker.lock();// 上锁
        if(m_workqueue.empty()){ // 任务池是空的
            m_queuelocker.unlock(); //解锁
            continue;
        }
        T* request = m_workqueue.front(); // 取出任务
        m_workqueue.pop_back(); //从任务池里弹出
        m_queuelocker.unlock(); //解锁
        // 没有任务，跳过
        if(!request){
            continue;
        }
        request->process(); // 任务线程开始运行
    }
}

#endif