#include<iostream>
#include"thread_pool.hpp"
#include<unistd.h>
void printnum()
{
    std::cout<<"10"<<std::endl;
}

int main()
{
    thread_pool pool;
    for(int i=0;i<10;i++)
        pool.submit(printnum);
        //sleep(1);
}