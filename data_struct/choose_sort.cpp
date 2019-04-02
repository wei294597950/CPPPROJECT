#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

int main(){
    vector<int> a = { 5 , 9 , 7 , 1 , 4,10,58};
    int n = a.size();
    int j;
    for(int i = 0;i<n-1;i++)
    {
        int minsum = i ;
        for(j=i+1;j<n;j++){
            if(a[j]<a[minsum]){
                minsum = j;
            }
        } 
        int temp = a[minsum];
        a[minsum] = a[i];
        a[i] = temp;
    }
        for(int i=0;i<n;i++){
        cout<< a[i] <<endl;
    }

}