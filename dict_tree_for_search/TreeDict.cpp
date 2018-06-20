#include<iostream>

#include"TreeBuilder.hpp"
using namespace std;
int main()
{
    vector<string> str{"tea","to","ted","ten","A","in","inn"};
    TreeBuilder *tb = new TreeBuilder();
    for(int i=0;i<str.size();i++)
    {
        tb->addWord(str[i]);
    }
    string a = "t";
    vector<string> result  = tb->getAllWrodsByPrefix(a);
    for(int i=0;i<result.size();i++)
        cout<<result[i]<<endl;
}

//构建  root  root-> "t" ->"to"
                    //   ->"te->"tea,ten,ted"
//每个节点里的map存储一当前字母为前缀的节点

//getallwordsbyprefix -> 调用getallnextnode 在当前 “t"的map里查找到  “to，te” ,“to”没有map，加入result,
//弹出栈，"te"的map有值，调用getallnextnode找到“tea”,"ten","ted"入栈，处理发现都没有map，就都加入result，
//最后出栈
