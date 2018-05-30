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
#include<sys/wait.h>
#include"processpool.h"

class cgi_conn{
    public:
        cgi_conn(){}
        ~cgi_conn(){}

        void init(int epollfd,int sockfd,const sockaddr_in& client_addr){
            m_epollfd = epollfd;
            m_sockfd = sockfd;
            m_address = client_addr;
            memset(m_buf,'\0',BUFFER_SIZE);
            m_read_idx = 0;
        }

        void process(){
            int idx=0;
            int ret = -1;
            while(true){
                idx = m_read_idx;
                ret = recv(m_sockfd,m_buf+idx,BUFFER_SIZE-1-idx,0);
                if(ret<0){
                    if(errno != EAGAIN){
                        removefd(m_epollfd,m_sockfd);
                    }
                    break;
                }else if(ret == 0){//如果对方关闭链接，则服务器也关闭链接
                    printf("如果对方关闭链接，则服务器也关闭链接\n");
                    removefd(m_epollfd,m_sockfd);
                    break;
                }else{
                    m_read_idx += ret;//标记缓冲区中已经读入的数据的最后一个字节的下一个位置
                    printf("user content is %s\n",m_buf);
                    for(;idx<m_read_idx;++idx){
                        //如果遇到字符“\r\n”,则开始处理用户请求
                        if((idx>=1)&&(m_buf[idx-1]=='\r')&&(m_buf[idx] == '\n')){
                            break;
                        }
                    }
                    if(idx == m_read_idx){
                        continue;
                    }
                    m_buf[idx-1] = '\n';

                    char * file_name = m_buf;
                    //判断用户要运行的cgi程序是否存在,,确定访问权限
                    if(access(file_name,F_OK) == -1)
                    {
                        removefd(m_epollfd,m_sockfd);
                        break;
                    }
                    else if(ret >0){
                        removefd(m_epollfd,m_sockfd);
                        break;
                    }else
                    {
                        //子进程将标准输出丁丁到m_sockfd，并执行cgi程序
                        close(STDOUT_FILENO);
                        dup(m_sockfd);
                        execl(m_buf,m_buf,0);
                        exit(0);
                    }
                    
                }
            }
        }

        private:
            static const int BUFFER_SIZE = 1024;
            static int m_epollfd;
            int m_sockfd;
            sockaddr_in m_address;
            char m_buf[BUFFER_SIZE];
            int m_read_idx;
};
int cgi_conn::m_epollfd = -1;

int main(int argc,char ** argv){

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

    processpool<cgi_conn> * pool = processpool<cgi_conn>::create(listenfd);
    if(pool){
        pool->run();
        delete pool;
    }
    close(listenfd);

    return 0;
    
}