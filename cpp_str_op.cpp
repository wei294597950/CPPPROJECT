1.应用于查找的find()函数

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin>>str;

    cout<<"ab在str中的位置:"<<str.find("ab")<<endl;
    //查找一个字符串出现的位置是找到该字符串第一个字符出现的位置
    cout<<"ab在str[2]str[n-1]范围的位置:"<<str.find("ab",2)<<endl;
    //在这个范围内部查找，但是出现的位置是从0开始数
    cout<<"ab在str[0]str[2]范围的位置:"<<str.rfind("ab",2)<<endl;
    return 0;
}

2.字串（substr()函数）

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin>>str;

    cout<<"返回str[3]以后的子串:"<<str.substr(3)<<endl; 
    cout<<"返回从2开始的4个字符组成的字符串，包括2位置的字符:"<<str.substr(2,4)<<endl;
    return 0;
}


3.替换

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin>>str;

    cout<<"返回把 [2]到[2+(4-1)] 的内容替换为'lk'后的新字符串:"<<str.replace(2,4,"lk")<<endl; 
    cout<<"返回把 [2]到[2+(4-1)] 的内容替换为 'abcd''的前3个字符后的新字符串:"<<str.replace(2,4,"abcd",3)<<endl;
    return 0;
}
 


4.插入：insert()函数

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin>>str;

    cout<<"从 [2] 位置开始添加字符串'kjh'并返回形成的新字符串:"<<str.insert(2,"kjh")<<endl; 
    return 0;
}



4.追加字符：pushback()函数和append()函数

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin>>str;

    cout<<"在输入字符串的尾部添加字符串avs:"<<str.append("avs")<<endl;

    cout<<"在str字符串后面加一个字符m:";
    str.push_back('m');
    cout<<str<<endl;
    return 0;
}




5.交换字符：swap()函数

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str1,str2;
    cin>>str1>>str2;

    cout<<"交换两个字符串之前:"<<"str1="<<str1<<" "<<"str2="<<str2<<endl;
    str1.swap(str2);
    cout<<"交换两个字符串之后:"<<"str1="<<str1<<" "<<"str2="<<str2<<endl;



    return 0;
}

结果： 


6.字符串大小 
size()函数和length()函数

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cin>>str;

cout<<"size()函数获取大小:"<<str.size()<<endl;
cout<<"length()函数获取大小:"<<str.length();

    return 0;
}




7.字符串比较函数：compare()

#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str1,str2;
    cin>>str1>>str2;
//结果为负数，0，正数    
cout<<"字符串比较结果:"<<str1.compare(str2)<<endl;
    return 0;
}

8.另外基本的操作函数

strcpy(s1,s2) ：复制字符串s2到s1
strcat(s1,s2) :连接s2到s1的末尾
strlen(s1) :返回字符串s1的长度
strcmp(s1,s2) :若s1和s2是相同的，则返回0，s1< s2,返回值小于0，若s1>s2，返回值大于0
strchr(s1,ch) :返回一个指针，指向字符串s1中字符ch第一次出现的位置
strstr(s1,s2) : 返回一个指针，指向字符串s1中字符串s2的第一次出现位置
