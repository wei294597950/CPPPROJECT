#include<iostream>
#include<vector>
using namespace std;

int findMoreThanHalf(vector<int> &a)
{
    int times = 1;
    int result = a[0];
    for(int i=1;i<a.size();i++)
    {
        if(times == 0)
        {
            result = a[i];
            times = 1;
        }
        else if(result == a[i])
            times++;
        else
            times--;
    }
    return result;
}
int main()
{
    vector<int> a{2,1,5,1,4,1,1,2,1,1,2,1,3,3,3,3,3,3,3,3};
    cout<<findMoreThanHalf(a)<<endl;
    return 0;
}