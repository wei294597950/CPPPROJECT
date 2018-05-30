#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER;
int total = 20;

void *sell_ticket(void *args){
    for(int i=0;i<20;i++){
        pthread_mutex_lock(&mutex_x);
        if(total>0){
            sleep(1);
            printf("sell %d\n",20-total+1);
            total--;
        }
        pthread_mutex_unlock(&mutex_x);
    }
    return 0;
}

int main(){
    int iRet;
    pthread_t tids[4];

    for(int i=0;i<4;i++){
        int iRet = pthread_create(&tids[i],NULL,sell_ticket,NULL);
        if(iRet){
            printf("error create \n");
            return iRet;
        }
    }
    void *reval;
    for(int i=0;i<4;i++){
        iRet = pthread_join(tids[i],&reval);
        if(iRet){
            printf("join error");
            return iRet;
        }
        printf("%ld\n",(long*)reval);
    }
    return 0;
}