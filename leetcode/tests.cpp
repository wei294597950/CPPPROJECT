#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>
#include<list>
#include<algorithm>
using namespace std;

class Solution {
public:
    int minDistance(string w1, string w2) {
        int n1=w1.size(),n2=w2.size();
        int dp[n1+1][n2+1];
        int maxsum = 0;
        //i,j 分别代表w1和w2的第i，j位的字符。i=0,j=0代表公共字符串为空
        for(int i=0;i<=n1;++i)
        {
            for(int j=0;j<=n2;++j)
            {
                //当i ==0 || j ==0: dp(i,j)=0;
                if(i==0||j==0)
                    dp[i][j]=0;
                else if(w1[i-1]==w2[j-1])
                {
                    //当word2[i]=word2[j]: dp(i,j)=dp(i-1,j-1)+1;
                    
                    
                      dp[i][j]=dp[i-1][j-1]+1;
                      maxsum = max(maxsum, dp[i][j]);
                    
                        
                    //当word1[i]!=word2[j]: dp(i,j)=max(dp(i-1,j),dp(i,j-1))
                    // else
                    //     dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
                // else{  //最长公共子串
                //   dp[i][j] =0;
                // }
                else  //最长公共子序列
                {
                   dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return maxsum;
    }
};
  int main(){  
    Solution a;
    int c = a.minDistance("acdcc","abcdec");
    cout<< c << endl;
    return 0;
  }