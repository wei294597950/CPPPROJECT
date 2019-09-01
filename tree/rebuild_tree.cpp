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
binaryTree* constructorCore(int *startp ,int *endp ,int *startO , int *endO){

    binaryTree* root = new binaryTree();
    root->val = startp[0];
    root->left = root->right = NULL;

    if(startO == endO && *startp == * startO)
    return root;

    //在中序遍历中找到根节点的值
    int * newroot = startO;
    while(newroot != endO && *newroot != root->val)
        newroot++;
    int leftlength = newroot - startO;
    int *leftpreorderEnd = startp + leftlength;
    if(leftlength > 0){
        root->left = constructorCore(startp+1,leftpreorderEnd,startO,newroot-1);


    }
    if(leftlength<endp-startp){
        root->right = constructorCore(leftpreorderEnd+1,endp,newroot+1,endO);
    }
    return root;
}
binaryTree* constructor(int *a,int *b,int n){
    if(a == NULL || b == NULL
     || n == 0)
     return NULL;
     return constructorCore(a,a+n-1,b,b+n-1);
}
void levelOrder(binaryTree* root,int level,vector<vector<int> > &a)
    {
        if(root == NULL)
            return;
        if(level>a.size())
            a.push_back(vector<int>());
        a[level-1].push_back(root->val);
        levelOrder(root->left,level+1,a);   
        levelOrder(root->right,level+1,a);
    }
vector<vector<int>> levelOrders(binaryTree* root) {

        vector<vector<int> > a;
        levelOrder(root,1,a);
        return a;
}
    


int main(){
    int a[] = { 1,2,4,7,3,5,6,8};
    int b[] = { 4,7,2,1,5,3,8,6};
    int n = 8;
    // cout<< n <<endl;
    vector<vector<int> > k = levelOrders(constructor(a,b,n));
    for(int i=0;i<k.size();i++){
        for(int j=0;j<k[i].size();j++){
            cout<< k[i][j]<<endl;
        }
    }

}