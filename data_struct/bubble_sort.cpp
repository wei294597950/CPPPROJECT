#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

int main(){
    vector<int> a = { 5 , 9 , 7 , 1 , 4,10,58};
    int n = a.size();
    int maxnum = INT_MIN;
    for(int i = n-1 ; i>=0;i--){
        for(int j = 0 ;j<i-1;j++)
        {
            if(a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }

    }
    for(int i=0;i<n;i++){
        cout<< a[i] <<endl;
    }
}