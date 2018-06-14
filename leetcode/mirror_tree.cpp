#include<iostream>

struct TreeNode{
    int val;
    TreeNode *left,*right;
};
class solution{
    void mirrorTree(TreeNode *root)
    {
    if(root == NULL)
        return;
    if(root->left == NULL && root->right == NULL)
        return;
    TreeNode* tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    if(root->left)
        mirrorTree(root->left);
    if(root->right)
        mirrorTree(root->right);

    }
};
