#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

class TreeNode{
    public:
        void setString(string str)
        {
            this->s = str;
        }
        string getString()
        {
            return s;
        }
        TreeNode* nextNode(char b)
        {
            if(dict_tree.find(b) == dict_tree.end())
                {
                    TreeNode *n = new TreeNode();
                    dict_tree.insert(make_pair(b,n));
                }
            return dict_tree[b];
        }
        TreeNode* getNode(char b)
        {
            return dict_tree[b];
        }
        vector<TreeNode*> getAllNextNodes()
        {
            vector<TreeNode*> arr;
            for(char c='a';c<='z';c++)
            {
                if(dict_tree.find(c) != dict_tree.end())
                    arr.push_back(dict_tree[c]);
            }
            return arr;
        }


    private:
        unordered_map<char,TreeNode*> dict_tree;
        string s = "";

 };