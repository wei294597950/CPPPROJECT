#ifndef PROCESSPOOL_H
#define PROCESSPOOL_H

#include<sys/time.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<pthread.h>
#include<sys/epoll.h>
#include<signal.h>

class process{
    public:
        process():m_pid(-1){}

    public:
        pid_t m_pid;
        int m_pipefd[2];

};

template<typename T>
class processpool{
    private:
        processpool(int listenfd,int process_number = 8);

    public:
        static processpool<T> * create(int listenfd,int process_number = 8){
            if(!m_instance){
                m_instance = new processpool<T>(listenfd,process_number);
            }
            return m_instance;
        }
        ~processpool(){
            delete [] m_sub_process;
        }

        void run();
    private:
    void setup_sig_pipe();
    void run_parent();
    void run_child();

    private:
        static const int MAX_PROCESS_NUMBER = 16;
        static const int USER_PER_PROCESS = 65535;
        static const int MAX_EVENT_NUMBER = 10000;

        int m_porcess_number;
        int m_idx;
        int m_epollfd;
        int m_listenfd;
        int m_stop;
        process * m_sub_process;
        static processpool<T> * m_instance;

};

template<typename T>
processpool<T> *  processpool<T>::m_instance = NULL;

static int sig_pipefd[2];

 //阻塞和非阻塞的区别在于没有数据到达的时候是否立刻返回.阻塞的socket必须等待数据返回才能执行下去
static int setnonblocking(int fd){  //fcntl指定对文件描述符的操作
    int old_option = fcntl(fd,F_GETFL); //读取文件描述符标识
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);//设置成非阻塞的
    return old_option; 
}

static void addfd(int epollfd,int fd){ //在epollfd标识的epoll内核事件表中添加fd上的注册事件
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}

static  void removefd(int epollfd,int fd){
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,0);
    close(fd);
}

static void sig_handler(int sig){
    int save_errno =  errno;
    int msg = sig;
    send(sig_pipefd[1],(char*)&msg,1,0);//信号处理函数在管道的写端写入信号
    errno = save_errno;
}

static void addsig(int sig,void(handler)(int),bool restart = true){
    struct sigaction sa;
    memset(&sa,'\0',sizeof(sa));
    sa.sa_handler = handler;
    if(restart){
        sa.sa_flags |= SA_RESTART;//重启被信号中断的系统调用
    }
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig,&sa,NULL)!=-1);

}

template<typename T>
processpool<T>::processpool(int listenfd,int process_number):m_listenfd(listenfd),m_porcess_number(process_number),
m_idx(-1),m_stop(false)
{
    assert( (process_number>0) && (process_number <= MAX_PROCESS_NUMBER));
    m_sub_process = new process[process_number];
    assert(m_sub_process);

    for(int i = 0;i<process_number;i++){
        int ret = socketpair(PF_UNIX, SOCK_STREAM,0,m_sub_process[i].m_pipefd);
        //创建双端读写的socket，本例即是全双工的管道
        assert( ret==0);
        //fork()时子进程继承了父进程的文件描述符，相当与m_pipefd父子进程都有一份，关闭另一端可防止同时读和同时 
        //写的阻塞
        m_sub_process[i].m_pid = fork();
        assert( m_sub_process[i].m_pid >=0);
        if(m_sub_process[i].m_pid >0){
            close(m_sub_process[i].m_pipefd[1]);
            continue;
        }else{
            close(m_sub_process[i].m_pipefd[0]);
            m_idx = i;
            break;
        }
    }


}

//统一事件源
template<typename T>
void processpool<T>::setup_sig_pipe(){
    m_epollfd = epoll_create(5);
    assert(m_epollfd != -1);

    int ret = socketpair(PF_UNIX,SOCK_STREAM,0,sig_pipefd);
    assert(ret!= -1);

    setnonblocking(sig_pipefd[1]);
    addfd(m_epollfd,sig_pipefd[0]);//主程序io复用函数监听管道的读端

    // 设置信号处理函数 ，在管道的写端，写入信号进行发送
    addsig(SIGCHLD,sig_handler);
    addsig(SIGTERM,sig_handler);
    addsig(SIGINT,sig_handler);
    addsig(SIGPIPE,SIG_IGN); 

}

template<typename T>
void processpool<T>::run(){
    if(m_idx != -1){//子进程在池中的序号
        run_child();
        return;
    }
    run_parent();
}

template<typename T>
void processpool<T>::run_child(){
    setup_sig_pipe();//统一事件源

    int pipefd = m_sub_process[m_idx].m_pipefd[1];
        //子进程需要监听管道描述符pipefd，因为父进程通过它来通知子进程accpet新链接
    addfd(m_epollfd,pipefd);

    epoll_event events[MAX_EVENT_NUMBER];
    T * users = new T[USER_PER_PROCESS];
    assert(users);

    int number = 0;
    int ret = -1;
    while(!m_stop){
        number = epoll_wait(m_epollfd,events,MAX_EVENT_NUMBER,-1);
        if((number < 0) && (errno != EINTR)){
            printf("epoll faied\n");
            break;
        }
        for(int i=0;i<number;i++){
            int sockfd = events[i].data.fd;
            //新的客户连接到来
            if((sockfd==pipefd) && (events[i].events & EPOLLIN)){
                printf("新的客户连接到来\n");
                int client=0;
                ret = recv(sockfd,(char*)&client,sizeof(client),0);
                if(((ret < 0) && (errno != EAGAIN)) || ret ==0){
                    continue;
                }
                else{
                    struct sockaddr_in client_address;
                    socklen_t client_addrlength = sizeof(client_address);
                    int connfd = accept(m_listenfd,(struct sockaddr*)&client_address,&client_addrlength);

                    if(connfd <0){
                        printf("errno is :%d\n",errno);
                        continue;
                    }

                    addfd(m_epollfd,connfd);

                    users[connfd].init(m_epollfd,connfd,client_address);
                }
            }
            //处理子进程接受到的信号

            else if((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN)){
                printf("处理子进程接受到的信号\n");
                int sig;
                char signals[1024];
                ret = recv(sig_pipefd[0],signals,sizeof(signals),0);
                if(ret<=0){
                    continue;
                }
                else{
                    for(int i=0;i<ret ;i++){
                        switch(signals[i]){
                            case SIGCHLD :
                            {
                                pid_t pid;
                                int stat;
                                while((pid = waitpid(-1,&stat,WNOHANG)) >0){
                                    continue;
                                }
                                break;
                            }
                            case SIGTERM:
                            case SIGINT:{
                                m_stop = true;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        
                        }
                    }
                }
            
            }
            //其他数据可读，客户请求到来
            else if( events[i].events & EPOLLIN){
                printf("其他数据可读，客户请求到来\n");
                users[sockfd].process();//创建进程个数的cgi_conn来作为处理函数
            }else{
                continue;
            }
        }
    }
    delete [] users;
    users = NULL;
    close(pipefd);
    close(m_epollfd);
}

template<typename T>
void processpool<T>::run_parent(){
    setup_sig_pipe();
    //父进程监听m_listenfd
    addfd(m_epollfd,m_listenfd);

    epoll_event events[MAX_EVENT_NUMBER];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;

    while(!m_stop){
        number = epoll_wait(m_epollfd,events,MAX_EVENT_NUMBER,-1);
        if((number<0) && (errno!= EINTR)){
            printf("epoll failure\n");
            break;
        }
        for(int i=0;i<number;i++){
            int sockfd = events[i].data.fd;
            if(sockfd == m_listenfd){
                int i = sub_process_counter;
                do{
                    if(m_sub_process[i].m_pid != -1){
                        break;
                    }
                    i = (i+1)%m_porcess_number;
                }
                while( i != sub_process_counter);

                if(m_sub_process[i].m_pid == -1){
                    m_stop = true;
                    break;
                }
                sub_process_counter = (i+1)%m_porcess_number;
                send(m_sub_process[i].m_pipefd[0],(char*)&new_conn,sizeof(new_conn),0);
                printf("send request to child %d\n",i);
            }

            //处理父进程接受到的信号,主要是子进程相关
            else if((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN)){
                int sig;
                char signals[1024];
                ret = recv(sig_pipefd[0],signals,sizeof(signals),0);
                if(ret<=0){
                    continue;
                }
                else{
                    for(int i = 0;i<ret ;i++){
                        switch( signals[i]){
                            case SIGCHLD://子进程状态发生变化
                            {
                                pid_t pid;
                                int stat;
                                while((pid = waitpid(-1,&stat,WNOHANG))>0){
                                    for(int i=0;i<m_porcess_number;i++){
                                        if( m_sub_process[i].m_pid == pid){
                                            printf("child %d join\n",i);
                                            close(m_sub_process[i].m_pipefd[0]);
                                            m_sub_process[i].m_pid = -1 ;
                                        }
                                    }
                                }
                                //如果所有子进程退出，则父进程也退出
                                m_stop = true;
                                for(int i=0;i<m_porcess_number;++i){
                                    if( m_sub_process[i].m_pid != -1){
                                        m_stop = false;
                                    }
                                }
                                break;
                            }
                            case  SIGTERM:
                            case  SIGINT://键盘输入以中断进程
                            {
                                printf("kill all \n");
                                for(int i=0;i<m_porcess_number;++i){
                                    int pid = m_sub_process[i].m_pid;
                                    if(pid!=-1){
                                        kill(pid,SIGTERM);
                                    }
                                }
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else{
                continue;
            }
        }
    }
    close(m_epollfd);

}
#endif


            //m_pipefd用于父子进程通信，主要时通知子进程接受新链接
            //sig_pipefd用于信号的监听与触发，主要是系统信号，比如键盘中断，子进程退出
            //io事件通信