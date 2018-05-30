#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/msg.h>
#define MAX_TEXT 512

struct msg_st{
    long int msg_type;
    char text[BUFSIZ];
};
int main(){
    int running = 1;
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;
    //建立消息队列
    msgid = msgget((key_t)1234,0666 | IPC_CREAT);
    if(msgid == -1){
        fprintf(stderr,"msgget failed with error :%d\n",errno);
        exit(EXIT_FAILURE);
    }

    while(running){
        printf("enter text:");
        fgets(buffer,BUFSIZ,stdin);
        data.msg_type = 1;
        strcpy(data.text,buffer);
        if(msgsnd(msgid,(void*)&data,MAX_TEXT,0) == -1){ //msgflag==0阻塞空或满等待
            fprintf(stderr,"msgget failed with error :%d\n",errno);
            exit(EXIT_FAILURE);
        }
        if(strncmp(buffer,"end",3) == 0){
            running = 0;

        }
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}