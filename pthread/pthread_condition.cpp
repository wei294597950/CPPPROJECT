//如果线程在等待共享数据里的某个条件出现，那会发生什么？它可能重复对互斥对象加锁和解锁，每次都会检查共享数据结构
//，以查找某个值，但这样频繁的查询效率极低也浪费时间和资源。
//条件变量：当线程等待某些条件满足时使线程进入睡眠状态，一旦条件满足，就唤醒因等待满足特定条件而睡眠的线程。
//惊群现象：每当有资源可用，所有的进程和线程都来竞争资源

#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;//初始构造条件变量
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;//初始构造锁

int x =10;
int y = 20;

void *func1(void *arg){
    cout<<"func1 start"<<endl;
    pthread_mutex_lock(&qlock);
    while(x<y){
        pthread_cond_wait(&qready,&qlock);
    }
    pthread_mutex_unlock(&qlock);
    sleep(3);
    cout<<"func1 end"<<endl;
}

void *func2(void *arg){
    cout<<"func2 start "<<endl;
    pthread_mutex_lock(&qlock);
    x = 20;
    y = 10;
    cout<<"has change x and y"<<endl;
    pthread_mutex_unlock(&qlock);
    if(x>y){
        pthread_cond_signal(&qready);
    }
    cout<<"func2 end"<<endl;
}

int main(int argc,char ** argv){
    pthread_t tid1,tid2;
    int iRet;
    iRet = pthread_create(&tid1,NULL,func1,NULL);
    if(iRet){
        cout<<"pthread1 create error"<<endl;
        return iRet; 
    }
    sleep(2);
    iRet = pthread_create(&tid2,NULL,func2,NULL);
    if(iRet){
        cout<<"pthread2 create error"<<endl;
        return iRet;
    }
    sleep(5);
    return 0;

}