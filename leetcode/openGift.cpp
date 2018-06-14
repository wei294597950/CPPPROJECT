#include <iostream>
using namespace std;
int main()
{
    char s[1000];
    while(cin>>s)
    {
        int count=0;
        for(int i=0;i<sizeof(s);i++)
        {
            if(s[i]=='(')
                count++;
            else if(s[i]==')')
                count--;
            else if(s[i]=='B')
                break;
        }
    cout<<count<<endl;
    }
    return 0;
}

//open gift (B)