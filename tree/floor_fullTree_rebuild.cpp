//层序遍历 和 层序建树
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;


struct binaryTree
{
    int val;
    binaryTree *left;
    binaryTree *right;
};


binaryTree * buildtree(vector<int> arr,int num )
{

    binaryTree *root = NULL;
    if(num < arr.size())
    {
        root = new binaryTree();
        cout<<arr[num]<<endl;
        root->val = arr[num];
        root->left = buildtree(arr,2*num+1);
        root->right = buildtree(arr,2*num+2);
    }
    return root;
}

void level_search(binaryTree * root , vector<int> & a){
    if(root == NULL){
        return ;
    }
    a.push_back(root->val);
    level_search(root->left,a);
    level_search(root->right,a);
}

int main(){
    vector<int> arr = {10,8,15,7,9,12,11};
    vector<int> a;
    binaryTree *root = buildtree(arr,0);
    level_search(root,a);
    cout<<"#"<<endl;
    for(int i = 0;i<a.size();i++){
        cout<<a[i]<<endl;
    }
}