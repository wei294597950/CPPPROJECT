// #include<iostream>
// #include<vector>
// class Solution {
// public:
//     int climbStairs(int n) {
//         int n1=0;
//         int n2=1;
//         int tmp = 0;
//         for(int i=0;i<n;i++)
//         {
//             tmp = n1+n2;
//             n1 = n2;
//             n2 = tmp;
//         }
//         return tmp;
//     }
// };

// class Solution {
// public:
//     int climbStairs(int n) {
//         if (n <= 1) return 1;
//         vector<int> dp(n);
//         dp[0] = 1; dp[1] = 2;
//         for (int i = 2; i < n; ++i) {
//             dp[i] = dp[i - 1] + dp[i - 2];
//         }
//         return dp.back();
//     }
// };