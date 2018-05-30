#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define MAXLINE 4096

int main(int argc,char ** argv){
    int socketfd, n;
    char recvline[4096], sendline[4096];
    struct sockaddr_in servaddr;

    if(argc !=2){
        printf("usage:./client <ipaddress>\n");
    }

    if( (socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        printf("create socket error\n");
    }

    memset(&servaddr,0,sizeof(servaddr));//初始化servaddr，将&servaddr地址开始的sizeof字节初始化为0
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666); //主机字节序转换为网络字节序
    if(inet_pton(AF_INET, argv[1],&servaddr.sin_addr) <= 0){ //将点分十进制转换为二进制
        printf("inet_pton error");
        return 0;
    }

    if ( connect(socketfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
        printf("error connect");
        return 0;
    }

    printf("send msg:\n");
    while(1){
        fgets(sendline,4096,stdin);
        // if( send(socketfd,sendline,strlen(sendline),0) < 0){
        if( send(socketfd,sendline,strlen(sendline),MSG_OOB) < 0){    
        printf("send error");
        return 0;
        }
        if(sendline == "q")
        break;
    }

    close(socketfd);
    return 0;


}