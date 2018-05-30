#include<iostream>
#include<set>
#include<map>

using namespace std;
using aa = map<int,int>;
struct A{  //当map或set的关键字蔚struct时，要重载小于运算符
    string label;
    int value;
    bool operator<(const A &a) const{
        return a.label > label;
    }
};
struct cmp{
    bool operator()(const int &d,const int & f) const{ //重载map中key的比较方式
        return d > f;
    }
};

int main(){
    set<A> atr{{"a",10},{"b",11}};
    map<int,int , cmp > cc{{2,3},{1,4}};
    for(auto & p : cc){
        cout<<p.first<<"--"<<p.second<<endl;
    }
}

//若想按value排序，可将map放入vector中，在重载sort的排序比较函数