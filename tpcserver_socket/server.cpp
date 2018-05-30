#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 4096

int main(int args, char ** argv){
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;

    if( (listenfd =socket(AF_INET,SOCK_STREAM,0)) == -1 )//协议域，类型，协议
    {
        printf("creat socket error");
        return 0;
    }

    memset(&servaddr,0,sizeof(servaddr));//初始化
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//主机字节序转换为无符号长整形网络字节序
    servaddr.sin_port = htons(6666);//主机字节序转换为网络字节序

    if( bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))== -1){
        printf("bind error");
        return 0;
    }

    if( listen(listenfd,10) == -1)//最大连接数
    {
        printf("listen error");
        return 0;
    }

    printf("#######waiting client request####");

    while(1){
        if( (connfd = accept(listenfd, (struct sockaddr*)NULL,NULL)) == -1)
        {
            printf("no accept");
            continue;
        }
        n =recv(connfd, buff ,MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n",buff);
        close(connfd);
    }
    close(listenfd);
    return 0;

}