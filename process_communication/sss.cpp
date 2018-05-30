#include<stdio.h>

int main(){
    int b = 5;
    int c = 10;
    int *a;
    // a = &c;
    *a = b;
    //printf("%d\n",*a);
    return 0;
}

//指针   使用前    必须初始化

//ulimit -c unlimited  使产生的coredump文件不收大小限制 /etc/profile
//生成core文件后，gdb sss  core