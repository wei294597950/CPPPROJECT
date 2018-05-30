#include<stdio.h>
#include<string.h>
#include <malloc.h>
using namespace std;

void test(){
    char *str = (char *)malloc(100);
    strcpy(str,"hello");
    printf("%c\n",str[0]);
    free(str);
}

int main(){
    test();
    return 0;
}