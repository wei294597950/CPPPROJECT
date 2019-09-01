#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

class solution{
    public:
    static vector<vector<int> > memo;
    int back01(vector<int> &w,vector<int> &v,int index ,int c){
        //终止条件
        if(index <= 0 || c <=0)
        return 0;
        if(memo[index][c] != -1)
            return memo[index][c];
        int res = back01(w,v,index-1,c);
        if( c >= w[index]){
            res = max(res,back01(w,v,index-1,c-w[index])+v[index]);
        }
        memo[index][c] = res;
        return res;
    }
};

void main(){
    solution A;
    vector<int> w{1,2,3};
    vector<int> v{6,10,12};
    int c = 5;
    solution::memo = vector<vector<int> >(w.size(),vector<int>(c+1,-1));
    cout<<A.back01(w,v,2,5);

    // A.back01();
}

class solutionb{
    public:
    
    int back01(vector<int> &w,vector<int> &v,int c){
        vector<vector<int> > dp(w.size(),vector<int>(c+1,0));
        for(int i=0;i<c+1;i++){
            dp[0][i] = w[0] <= i ? v[0] : 0;
        }
        for(int i = 1 ;i < 3 ;i++)
        for(int j = 0;j<c+1;j++){
            dp[i][j] = dp[i-1][j];
            if(j>=w[i]){
                dp[i][j] = max(dp[i][j],dp[i-1][j-w[i]]+v[i]);
            }
        }
        return dp[w.size()-1][c];
    }
};