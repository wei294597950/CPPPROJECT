#include<iostream>
#include<functional>
using namespace std;
typedef void(*ptr)(int *);
int A(int a,int b){
    std::cout<<a+b<<std::endl;
    return a+b;
}

int B(const std::function<int(int,int)> &f,int a,int b){
    return f(a,b);
}

void printvalue(int & i){
    std::cout<<"lvalue  "<<i<<std::endl;
}

void printvalue(int && i){
    std::cout<<"rvalue  "<<i<<std::endl;
}
// void noforward(int && i){
//     printvalue(i);
// }
template<typename T>
void forwards(T && i){
    printvalue(i);
    printvalue(std::forward<T>(i));//完美转发
}
int main()
{

    B(A,1,2);
    ptr c = [](int *p){delete p;};
    forwards(1);
    return 0;
}