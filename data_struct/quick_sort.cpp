#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;


int partition(vector<int> &a , int low , int high){
    int key = a[low];

    while(low<high){
        while(low< high && a[high]>key)
            high--;
        a[low] = a[high];
        while(low < high && a[low]<key)
            low++;
        a[high] = a[low];
    }
    a[low] = key;
    return low;
}

void qsort(vector<int> &a ,int low ,int high){

    if(low < high){
        int key = partition(a,low,high);
        qsort(a,low,key);
        qsort(a,key+1,high);
    }
}


int main(){
    vector<int> a = { 5 , 9 , 7 , 1 , 4,10,58,3};
    int n = a.size();
    qsort(a,0,n-1);
    for(int i=0;i<n;i++){
        cout<< a[i] <<endl;
    }
}