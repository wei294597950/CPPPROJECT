#include<iostream>
#include<unordered_map>
using namespace std;

struct RandomList{
    int value;
    RandomList *next,*random;
    RandomList(int x):value(x),next(NULL),random(NULL){}
};

RandomList*  CopyRandomlist(RandomList* head)
{
    if(head == NULL)
        return NULL;
    RandomList *pnode = head;
    unordered_map<RandomList *,RandomList *> map1;
    while(pnode->next!=NULL)
    {
        RandomList *pnew = new RandomList(pnode->value);
        map1[pnode] = pnew;
        pnode = pnode->next;
    }
    pnode = head;
    while(pnode->next!=NULL)
    {
        map1[pnode]->next = map1[pnode->next];
        map1[pnode]->random = map1[pnode->random];
        pnode = pnode->next;
    }
    return map1[head];
}