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

int main(){
    int keyboard;
    int ret , i;
    char c;
    fd_set readfd;
    struct timeval timeout;
    keyboard = open("/dev/tty",O_RDONLY | O_NONBLOCK);
    assert(keyboard > 0);
    while(1){
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        FD_ZERO(&readfd);
        FD_SET(keyboard,&readfd);
        ret=select(keyboard+1,&readfd,NULL,NULL,&timeout);//fd数量+1,readfd集合，writefd集合，fd错误集合，超时时间
        if(ret<0)
        {
            printf("error\n");
        }else if(ret){
                    if(FD_ISSET(keyboard,&readfd)){
            i=read(keyboard,&c,1);//从文件描述符keyboard中读取1个字节到缓冲区&c开始的地址处
            if('\n'==c){
                continue;
            }
            printf("input is %c\n",c);
            if('q'==c)
            break;
        }
        }else if(ret==0){
            printf("timeout\n");
        }

    }
    return 0;
}

//select函数监听负责的文件描述符集，即不断调用select是否可读的fd，如果有，select返回并调用read，将数据从
//内核读到用户进程   
//返回值是就绪的文件描述符个数，若出错，返回-1,若timeout返回0
