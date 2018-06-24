#include<iostream>
#include "file1.h"
#include<stdlib.h>
using namespace std;

void func(){
    int *x = (int *)malloc(10 * sizeof(int));
    x[10] = 0;
}

int main(){
    cout<<"file2"<<endl;
    File1Print();
    func();
    return 0;
}