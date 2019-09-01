 #include<iostream>
 #include<vector>
 using namespace std;   
    
    void merge(vector<int>& A, int m, vector<int>& B, int n) {

        int i , j , k ;
        for( i = m - 1, j = n - 1, k = n + m -1; k >= 0; --k)
        {
            if( i >= 0 &&(j < 0 || A[i] >= B[j]) )//此时数组B已经遍历完，j=0，k还在--，所以要保证数组A中剩下的元素不变
            
                A[k] = A[i--];
            else            
                A[k] = B[j--];  
        }
    }
    

    int main()
    {
        vector<int> nums1{-1,0,0,3,3,3,0,0,0};
        vector<int> nums2{1,2,2};
        merge(nums1,6,nums2,3);
        for(int i=0;i<nums1.size();i++)
        {
            cout<<nums1[i]<<endl;
        }
    }