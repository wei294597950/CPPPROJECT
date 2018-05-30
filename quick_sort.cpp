#include<stdio.h>

int partition(int a[], int low, int high){

    int key = a[low];
    while(low<high){
        while(low<high && a[high] >= key)
            high--;
        if(low < high) 
        a[low] = a[high];
        while(low<high && a[low] <= key)
            low++;
        if(low < high) 
        a[high] = a[low];
        }    
        a[low] = key; 
        return low;
   

   
}

void qsort(int a[],int low , int high){
    int mid;
    if(low >= high)
    return;
    if(low < high){  //这里 if只是一次  ，while是无限次，只要内部条件满足
        mid = partition(a,low,high);
        qsort(a,low,mid-1);
        qsort(a,mid+1,high);
    }

}
void QuickSort(int arrayNum[]){  
    qsort(arrayNum,0,4);  
} 
void Qsort4(int s[], int l, int r)//白话经典算法系列之六 快速排序 http://blog.csdn.net/morewindows/article/details/6684558#
{  
    if (l < r)  
    { 
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数  
                j--;    
            if(i < j)   
                s[i++] = s[j];  
              
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数  
                i++;    
            if(i < j)   
                s[j--] = s[i];  
        }
        s[i] = x;  
        Qsort4(s, l, i - 1); // 递归调用   
        Qsort4(s, i + 1, r);  
    }
}
int main(){
    int a[5]={3,5,1,2,4};
    printf("begin:\n");
    qsort(a,0,4);
    //Qsort4(a,0,4);
    //QuickSort(a);
    for(int i=0;i<5;i++){
        printf("%d",a[i]);
    }
    return 0;
}