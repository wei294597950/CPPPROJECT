#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    string str = "2216";
    cout<<str[0]<<endl;
    vector<int> a(str.size(),0);
    a[0] = 1;
    a[1] = 2;
    for(int i=2;i<str.size();i++)
    {
        if(str[i] == '0' && (str[i-1] == '1' || str[i-1] == '2') )
        {
            a[i] = a[i-2];
        }else if(str[i] !='0')
        {
            if(str[i-1] == '1' || (str[i-1] == '2' && str[i] > '0' && str[i] <= '6'))
            {
                a[i] = a[i-1] + a[i-2];
            }else{
                a[i] = a[i-1];
            }
        }else{
            return 0;
        }
    }
    cout<< a[str.size()-1]<<endl;
}

