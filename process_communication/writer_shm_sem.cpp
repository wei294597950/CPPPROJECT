//共享内存并用信号量同步
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<sys/shm.h>
#define SEM_KEY 4002
#define SHM_KEY 5672

union sem_un{
    int val;
};

int main(void){
    int semid,shmid;
    shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT | 0666);
    printf("shmid : %d \n",shmid);
    if(shmid <0){
        printf("create shm error");
        return -1;
    }
    void *shmptr;
    shmptr = shmat(shmid,NULL,0);//将共享内存链接到自身地址空间
    if(shmptr == (void*)-1){
        printf("shmat error %s\n",strerror(errno));
        return -1;
    }
    int *data = (int *)shmptr;
    semid = semget(SEM_KEY,2,0666);//创建两个semid，并设置两个信号量
    struct sembuf sembuf1;
    union sem_un semun1;//下面初始化两个信号量

    while(1){
        sembuf1.sem_num = 1;
        sembuf1.sem_op = -1;
        sembuf1.sem_flg = SEM_UNDO;
        semop(semid,&sembuf1,1);

        scanf("input :%d\n",data);

        sembuf1.sem_num = 0;
        sembuf1.sem_op = 1;
        sembuf1.sem_flg = SEM_UNDO;
        semop(semid,&sembuf1,1);
    }
    return 0;
}