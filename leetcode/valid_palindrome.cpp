#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

    bool isPalindrome(string s) {
        if(s == " " || s.size() == 1 )
            return true;
        int i=0;
        int j=s.size()-1;
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        while(isalpha(s[i])==0 )
                i++;
        while(isalpha(s[j])==0)
                j--;
        while(i<=j)
        {
            while(isalpha(s[i])==0 )
                i++;
            while(isalpha(s[j])==0)
                j--;
            if(s[i] == s[j])
            {
                i++;
                j--;
            }else
            {
                return false;
            }
        }
        return true;
    }

int main()
{
    bool ok = isPalindrome("0P");
    cout<<ok<<endl;
}