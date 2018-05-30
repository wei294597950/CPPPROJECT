#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<vector<int> > a{{2},{3,4},{6,5,7},{4,1,8,3}};
    for(int i=a.size()-2;i>=0;i--)
    for(int j=0;j<i+1;j++)
    {
        a[i][j] += min(a[i+1][j],a[i+1][j+1]);
    }
    cout<<a[0][0]<<endl;
    return 0;
}