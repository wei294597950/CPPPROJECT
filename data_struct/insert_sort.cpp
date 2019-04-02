#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> a = { 5 , 9 , 7 , 1 , 4,10,58};
    int n = a.size();
    for(int i=1;i<n;i++){
        int temp = i-1;
        int num = a[i];
        while(temp>=0 && a[temp] > num){
            a[temp+1] = a[temp];
            temp--;
        }
        a[temp+1] = num;
    }
    for(int i=0;i<n;i++){
        cout<< a[i] <<endl;
    }
}