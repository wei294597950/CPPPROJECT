#include"TreeNode.hpp"
#include<stack>

class TreeBuilder{
    private:
        TreeNode *root = NULL;
        stack<TreeNode*> st;
    public:
        void addWord(string s);
        void addNodeListToStack(vector<TreeNode*> nodes);
        vector<string> getAllWrodsByPrefix(string prefix);


};

void TreeBuilder::addWord(string s)
{
    if(root == NULL)
    root = new TreeNode();

    TreeNode *node  = root;
    int l = 0;
    while(l < s.length())
    {
        node = node->nextNode(s[l]);
        l++;
    }
    node->setString(s);
}

void TreeBuilder::addNodeListToStack(vector<TreeNode*> nodes)
{
    for(int i=0;i<nodes.size();i++)
        st.push(nodes[i]);
}

vector<string> TreeBuilder::getAllWrodsByPrefix(string prefix)
{
    int l =0;
    TreeNode *node = root;

    while(l<prefix.length())
    {
        node = node->getNode(prefix[l]);
        if(node == NULL)
        break;
        l++;
    }




    addNodeListToStack(node->getAllNextNodes());//getallnextnode返回找到的dict_tree 返回vector加入stack
    vector<string> allWords;
    while(st.empty() == false)
    {
        TreeNode *n = st.top(); 
        st.pop();
        if(n->getString().empty() == false)
            allWords.push_back(n->getString());
        addNodeListToStack(n->getAllNextNodes());
        //找到并处理的顺序 node为t -> 找到to，加入allword然后出站 -> 找到ten,ted,tea,加入allword并出站
    }
    return allWords;
}
