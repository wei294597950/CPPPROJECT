#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define CUSTOMER_NUM 10

sem_t sem;

//某行业营业厅只能服务两个顾客。有多个顾客到来，顾客如果发现窗口已满，就等待

void *get_service(void *thread_id){
    int customer_id = *((int*)thread_id);
    if(sem_wait(&sem) == 0){//表示当前信号量大于0，可以为该顾客服务，并将信号量-1
        usleep(100);
        printf("customer %d receive server..\n",customer_id);
        sem_post(&sem); //服务完成后将信号量的值加1，以便继续为其他顾客服务
    }
}

int main(){
    sem_init(&sem,0,2);//初始值为2,表示有两个可以同时进入
    pthread_t customers[CUSTOMER_NUM];
    int i,iRet;
    for(i=0;i<CUSTOMER_NUM;i++){
        int customer_id = i;
        iRet = pthread_create(&customers[i],NULL,get_service,&customer_id);
        if(iRet){
            printf("create error");
            return iRet;
        }
        else{
            printf("customer %d come \n",i);
        }
        usleep(10);
    }

    int j;
    for(j=0;j<10;j++){
        pthread_join(customers[j],NULL);
    }
    sem_destroy(&sem);
    return 0;

}