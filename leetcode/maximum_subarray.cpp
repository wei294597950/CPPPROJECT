#include<iostream>
#include<algorithm>
#include "limits.h"
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& a) {
    int sum = 0;
    int start = 0;
    int end = 0;
    int maxsum = INT_MIN;;
    for(int i=0;i<a.size();i++)
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
            
            maxsum = max(maxsum,sum);
            sum = 0;

        }

        
    }
        return maxsum;
        
    }
};

//最大子序列和