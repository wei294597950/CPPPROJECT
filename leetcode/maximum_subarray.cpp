#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    //int a[]= {-2,1,-3,4,-1,2,1,-5,4};
    int a[] = {-2,1,-3};
    int length = sizeof(a)/sizeof(a[0]);
    int sum = 0;
    int start = 0;
    int end = 0;
    int maxsum = 0;
    for(int i=0;i<length;i++)
    {
        sum += a[i];

        //maxsum = max(maxsum,sum);
        if(sum > maxsum)
        {
            maxsum = sum;
            end = i;
        }
        if(sum <= 0)
        {
            sum = 0;
        }

        
    }
    int temp = maxsum;
    int j = end;
    for(;temp >0;j--)
    {
        temp-= a[j];
        
    }
    start = j+1;
    cout<<maxsum<<endl;
    cout<<start<<endl;
    cout<<end<<endl;
}

//最大子序列和