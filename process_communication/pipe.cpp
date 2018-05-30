#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INPUT 0
#define OUTPUT 1
//　管道提供了简单的流控制机制。进程试图读空管道时，在有数据写入管道前，进程将一直阻塞。同样，管道已经满时，进程再试图写管道，在其它进程从管道中移走数据之前，写进程将一直阻塞。


int main(){
    int fd[2];
    pid_t pid;
    char buf[255];
    int returned_count;
    pipe(fd);//创建无名管道
    pid = fork();
    if(pid<0){
        printf("error\n");
        exit(1);
    }else if(pid == 0){
        printf("in child process ...\n");
        sleep(3);
        close(fd[INPUT]);
        write(fd[OUTPUT],"hello",strlen("hello"));
        exit(0);
    }else{
        printf("in parent process...\n");
        close(fd[OUTPUT]);
        returned_count = read(fd[INPUT],buf,sizeof(buf));
        printf("...%s\n",buf);

    }
    return 0;
}