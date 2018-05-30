//EPOLLONESHOW事件，ET模式：在epoll_wait检测到文件描述符上有事件发生并将次事件通知应用程序后，应用程序必须立即处理
//后续不再通知该事件。。。LT模式：通知后应用程序可以不立即处理，后续epoll_wait将再次通知此事件

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

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds{
    int epollfd;
    int sockfd;
};

int setnonblocking(int fd){  //fcntl指定对文件描述符的操作
    int old_option = fcntl(fd,F_GETFL); //读取文件描述符标识
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);//设置成非阻塞的
    return old_option; 
}

//将fd上的epollin和epollet事件注册到eopllfd指向的epoll内核时间表中，参数oneshot指定是否注册fd上的epolloneshot事件
void addfd(int epollfd,int fd,bool oneshot){
    epoll_event event;
    event.data.fd = fd;//用户数据，含有fd和指定fd相关用户数据的uinon
    event.events = EPOLLIN | EPOLLET;//epoll事件
    if(oneshot){
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}   

void reset_oneshot(int epollfd,int fd){
    epoll_event event;
    event.data.fd = fd; 
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}

void* worker(void *arg){
    int sockfd = ((fds*)arg)->sockfd;
    int epollfd = ((fds*)arg)->epollfd;
    printf("start new thread to receive data on fd: %d\n",sockfd);
    char buf[BUFFER_SIZE];
    memset(buf,'\0',BUFFER_SIZE);
    while(1){
        int ret = recv(sockfd,buf,BUFFER_SIZE-1,0);
        if(ret == 0){
            close(sockfd);
            printf("foregin closed connection\n");
            break;
        }else if(ret <0){
            if(errno == EAGAIN){
                reset_oneshot(epollfd,sockfd);
                printf("read later\n");
                break;
            }
        }else{
                printf("getcontent:%s\n",buf);
                sleep(5);
        }
    }
        printf("end thread rev data on fd :%d\n",sockfd);
    
}

int main(int argc,char **argv){
    if(argc < 2){
        printf("22");
        return 1;
    }
    const char * ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    assert(listenfd>0);
    ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd,5);//connect之后，产生新的sockfd即listenfd
    printf("listenfd is  %d\n",listenfd);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    printf("epollfd is  %d\n",epollfd);
    assert(epollfd > 0);

    addfd(epollfd,listenfd,false);

    while(1){
        int ret = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);//listen(),connect()事件会触发epoll_wait()
        if(ret<0){                                               //当然啊，connect时说明client发送的是就绪状态，说明新的socket就绪，新的socketfd活跃
            printf("epoll failure\n");
            break;
        }
        for(int i=0;i<ret;i++){
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd){
                struct sockaddr_in client_address;
                socklen_t client_addlenth = sizeof(client_address);
                printf("in listenfd is %d\n",listenfd);
                int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addlenth);
                //接受连接后，返回新的描述符，标识此次连接
                addfd(epollfd,connfd,true);
            }else if(events[i].events & EPOLLIN){
                pthread_t thread;
                fds fds_for_new_worker;
                fds_for_new_worker.epollfd = epollfd;
                fds_for_new_worker.sockfd = sockfd;
                printf("new thread for epoll\n");
                pthread_create(&thread,NULL,worker,(void*)&fds_for_new_worker);
            }else{
                printf("error happen\n");
            }
        }
    }
    close(listenfd);
    return 0;
    
}