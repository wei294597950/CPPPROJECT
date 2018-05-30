#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/msg.h>

struct msg_st{
    long int msg_type;
    char text[BUFSIZ];
};

int main(){
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0;

    //建立消息队列
    msgid = msgget((key_t)1234,0666 | IPC_CREAT);
    if(msgid == -1){
        fprintf(stderr,"msgget failed with error :%d\n",errno);
        exit(EXIT_FAILURE);
    }
    while(running){
        if(msgrcv(msgid,(void*)&data,BUFSIZ,msgtype,0) == -1){
            fprintf(stderr,"msgget failed with error :%d\n",errno);
            exit(EXIT_FAILURE);
        }
        printf("you wrote %s\n",data.text);
        if(strncmp(data.text,"end",3) == 0){
            running = 0;
        }
    }
    //删除消息队列
    if(msgctl(msgid,IPC_RMID,0) == -1){
            fprintf(stderr,"msgget failed with error :%d\n",errno);
            exit(EXIT_FAILURE);       
    }
    exit(EXIT_SUCCESS);
}