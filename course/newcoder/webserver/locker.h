#ifndef LOCKER_H
#define LOCKER_H

#include <pthread.h>
#include <exception>
#include <semaphore.h>

// 线程同步机制封装类

// 互斥锁类
class locker{

private:
    pthread_mutex_t m_mutex; //互斥量

public:
    // 构造函数
    locker() {
        // 初始化互斥锁
        if(pthread_mutex_init(&m_mutex,NULL) != 0){
            // 失败，抛出异常
            throw std::exception();
        }
    }

    // 析构函数
    ~locker() {
        // 销毁互斥锁
        pthread_mutex_destroy(&m_mutex);
    }
    // 上锁
    bool lock(){
        return pthread_mutex_lock(&m_mutex);
    }

    // 解锁
    bool unlock() {
        return pthread_mutex_unlock(&m_mutex);
    }

    // 获取互斥量
    pthread_mutex_t *get() {
        return &m_mutex;
    }




};


// 条件变量类

class cond{

private:

    pthread_cond_t m_cond; //条件变量

public:
    // 构造函数：条件变量初始化
    cond() {
        // 条件变量初始化
        if(pthread_cond_init(&m_cond,NULL) != 0) {
            throw std::exception();
        }
    }
    // 析构函数：销毁条件变量
    ~cond() {
        pthread_cond_destroy(&m_cond);
    }

    // 条件变量和互斥锁搭配着使用
    // https://zhuanlan.zhihu.com/p/514410572

    bool wait(pthread_mutex_t *mutex) {
        return pthread_cond_wait(&m_cond,mutex) == 0; 
    }

    bool timewait(pthread_mutex_t *mutex,struct timespec t) {
        return pthread_cond_timedwait(&m_cond,mutex,&t) == 0; 
    }

    bool signal() {
        return pthread_cond_signal(&m_cond) == 0; 
    }

    bool broadcast() {
        return pthread_cond_broadcast(&m_cond) == 0; 
    }



};


// 信号量类
class sem{

private:
    sem_t m_sem;

public:
    sem() {
        if(sem_init(&m_sem,0,0)!=0){
            throw std::exception();
        }
    }
    ~sem() {
        sem_destroy(&m_sem);
    }

    // 等待信号量
    bool wait() {
        return sem_wait(&m_sem) == 0;
    }

    // 增加信号量
    bool post() {
        return sem_post(&m_sem) == 0;
    }


};


#endif
