#include<iostream>
// #include<algorithm>
#include<vector>
using namespace std;

void adjust_heap(vector<int> &a , int max , int size){

    int left = 2*max+1;
    int right = 2*max+2;
    int temp = max;
    if(left < size && a[left]>a[temp])
        temp = left;
    if(right < size && a[right]> a[temp])
        temp = right;     //max继续向下调整
    if(temp != max){
        swap(a[temp],a[max]);
        adjust_heap(a,temp,size);
    }
}

void heap_build(vector<int> &a, int size){  // 构建大根堆（从最后一个非叶子节点向上）

    for(int i=size/2 - 1; i >= 0; i--)
    {
        adjust_heap(a, i, size);
    }
}

void heapSort(vector<int> &a, int size)
{
    // 构建大根堆（从最后一个非叶子节点向上）
    // heap_build(a,size);
 
    // 调整大根堆
    for(int i = size - 1; i >= 1; i--)
    {
        swap(a[0], a[i]);           // 将当前最大的放置到数组末尾
        adjust_heap(a, 0, i);              // 将未完成排序的部分继续进行堆排序
    }
}

void heap_insert(vector<int> &a, int val){
    a.push_back(val);
    heap_build(a,a.size());
}

void heap_delete(vector<int> &a){ //
    swap(a[0],a[a.size()-1]);
    a.pop_back();
    heap_build(a,a.size());

}

int main(){

    vector<int> a = {8, 2, 14, 3, 21, 5, 7, 10};
    
    heap_build(a,a.size());
    heap_delete(a);
    // heapSort(a,a.size());
    // heap_insert(a,4);
    // heap_insert(a,9);

    for(int i = 0;i<a.size();i++){
        cout<<a[i]<<endl;
    }
    
} 