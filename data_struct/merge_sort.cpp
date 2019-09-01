#include<iostream>
#include<vector>

using namespace std;

void Merge(int *arr, int n)
{
    // vector<int> temp(n,0);
    int *temp = (int *)malloc(n*sizeof(int));
    int b = 0;  // 辅助数组的起始位置
    int mid = n / 2;    // mid将数组从中间划分，前一半有序，后一半有序
    int first = 0, second = mid;    // 两个有序序列的起始位置
 
    while (first < mid && second < n)
    {
        if (arr[first] <= arr[second])   // 比较两个序列
            temp[b++] = arr[first++];
        else
            temp[b++] = arr[second++];
    }
 
    while(first < mid)              // 将剩余子序列复制到辅助序列中
            temp[b++] = arr[first++];
    while(second < n)
            temp[b++] = arr[second++];
    for (int i = 0; i < n; ++i)// 辅助序列复制到原序列
        arr[i] = temp[i];
}
 
void MergeSort(int *arr, int n)
{
    if (n <= 1)// 递归出口
        return;
    if (n > 1)
    {
        MergeSort(arr, n / 2);// 对前半部分进行归并排序
        MergeSort(arr + n / 2, n - n / 2);// 对后半部分进行归并排序
        Merge(arr, n);// 归并两部分
    }

}

int main(){
    int a[8] = { 5 , 9 , 7 , 1 , 4,10,58,3};
    int n = 8;
    MergeSort(a,8);
    for(int i=0;i<n;i++){
        cout<< a[i] <<endl;
    }
}