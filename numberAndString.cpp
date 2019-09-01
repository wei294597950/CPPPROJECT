C++数值类型与string的相互转换
1.数值类型转换为string
1.1使用函数模板+ostringstream
使用函数模板将基本数据类型（整型、字符型、实型、布尔型）转换成string。


//ostringstream对象用来进行格式化的输出，常用于将各种类型转换为string类型
//ostringstream只支持<<操作符
template<typename T> string toString(const T& t){
    ostringstream oss;  //创建一个格式化输出流
    oss<<t;             //把值传递如流中
    return oss.str();  
}
 
cout<<toString(14.2)<<endl;  //实型->string：输出14.2
cout<<toString(12301)<<endl; //整型->string：输出12301
cout<<toString(123456789785)<<endl;//长整型->string：输出123456789785
cout<<toString(true)<<endl;  //布尔型->string：输出1
　　

1.2使用标准库函数std::to_string()
std命令空间下有一个C++标准库函数std::to_string()，可用于将数值类型转换为string。使用时需要include头文件<string>。

函数原型申明如下：


string to_string (int val);
string to_string (long val);
string to_string (long long val);
string to_string (unsigned val);
string to_string (unsigned long val);
string to_string (unsigned long long val);
string to_string (float val);
string to_string (double val);
string to_string (long double val);
　　

2.string转换为数值类型
2.1使用函数模板+ istringstream
stringstream在int或float类型转换为string类型的方法中已经介绍过， 这里也能用作将string类型转换为常用的数值类型。


#include <iostream> 
#include <sstream>    //使用stringstream需要引入这个头文件 
using namespace std; 
 
//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性） 
template <class Type> 
Type stringToNum(const string& str){ 
    istringstream iss(str); 
    Type num; 
    iss >> num; 
    return num;     
} 
 
int main(int argc, char* argv[])  { 
    string str("00801"); 
    cout << stringToNum<int>(str) << endl; 
 
    system("pause"); 
    return 0; 
} 
　　

2.2使用C标准库函数
具体做法是先将string转换为char*字符串，再通过相应的类型转换函数转换为想要的数值类型。需要包含标准库函数<stdlib.h>。 
（1）string转换为int32_t

string love="77";
int ilove=atoi(love.c_str());
 
//或者16位平台转换为long int
int ilove=strtol(love.c_str(),NULL,10);
　　（2）string转换为uint32_t


//str:待转换字符串
//endptr:指向str中数字后第一个非数字字符
//base：转换基数（进制），范围从2至36
unsigned long int strtoul (const char* str, char** endptr, int base);
 
#示例
string love="77";
unsigned long ul;
ul = strtoul(love.c_str(), NULL, 10);
　　（3）string转换为uint64_t


string love="77";
long long llLove=atoll(love.c_str());
　　（4）string转换为uint64_t


unsigned long long int strtoull (const char* str, char** endptr, int base);
 
#示例
string love="77";
unsigned long long ull;
ull = strtoull (love.c_str(), NULL, 0);
　　（5）string转换为float或double


string love="77.77";
float fLove=atof(love.c_str());
double dLove=atof(love.c_str());
　　（6）string转换为long double

1
long double strtold (const char* str, char** endptr);
　　

2.3使用C++标准库函数
使用C++11引入的C++库函数将string转换为数值类型，相应的库函数申明于头文件<string>中。

名称	原型	说明
stoi	int stoi (const string& str, size_t* idx = 0, int base = 10);
int stoi (const wstring& str, size_t* idx = 0, int base = 10);	Convert string to integer (function template )
stol	long stol (const string& str, size_t* idx = 0, int base = 10);
long stol (const wstring& str, size_t* idx = 0, int base = 10);	Convert string to long int (function template)
stoul	unsigned long stoul (const string& str, size_t* idx = 0, int base = 10);
unsigned long stoul (const wstring& str, size_t* idx = 0, int base = 10);	Convert string to unsigned integer (function template)
stoll	long long stoll (const string& str, size_t* idx = 0, int base = 10);
long long stoll (const wstring& str, size_t* idx = 0, int base = 10);	Convert string to long long (function template)
stoull	unsigned long long stoull (const string& str, size_t* idx = 0, int base = 10);
unsigned long long stoull (const wstring& str, size_t* idx = 0, int base = 10);	Convert string to unsigned long long (function template)
stof	float stof (const string& str, size_t* idx = 0);
float stof (const wstring& str, size_t* idx = 0);	Convert string to float (function template )
stod	double stod (const string& str, size_t* idx = 0);
double stod (const wstring& str, size_t* idx = 0);	Convert string to double (function template )
stold	long double stold (const string& str, size_t* idx = 0);
long double stold (const wstring& str, size_t* idx = 0);	Convert string to long double (function template)

形参说明： 
str：重载了string和wstring版本，表示被转换的字符串。

idx：表示一个size_t*的指针类型，默认为空值。不为空时，转换成功时获取第一个非数值字符的下标。一般情况下，因为它是直接char型指针把最后非数值字符的地址值和起始地址值相减，所以也表示成功转换的字符数量，如”10”转成功为数值10时，*idx的值为2。

base：表示转换基准，默认是10进制。