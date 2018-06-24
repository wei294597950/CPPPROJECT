// #include<stdio.h>

// void wordReverse(char *start,char *end)
// {
//     if(start == NULL || end == NULL)
//     return ;
//     while(start < end)
//     {
//         char temp = *start;
//         *start = *end;
//         *end = temp;

//         start++;
//         end--;
//     }
// }
// char* solve(char *p)
// {
//     char *start = p;
//     char *end = p;
//     while(*end != '\0')
//     {
//         end++;
//     }
//     end--;
//     while(*start != '\0')
//     {
//         if(*start = ' ')
//         {
//             start++;
//             end++;
//         }else if(*end == '\0' || *end == ' ')
//         {
//              wordReverse(start,end--);
//              start = end++;
//         }else{
//             end++;
//         }
//     }
   
//     return p;
// }
// int main()
// {
//     char str[] = "abcd";////////////////////////////////////////////这样声明
//     char *c = solve(str);
//     while(*c != '\0')
//     {
//         printf("%c",*c);
        
//     }
//     return 0;
    

// }

#include <iostream>
using namespace std;
char strr[]="Jenny, I love you.";
void Reverse(char *pBegin,char *pEnd)
{
	if(NULL==pBegin || NULL==pEnd)
		return;
	while(pBegin<pEnd)
	{
		char temp=*pEnd;
		*pEnd=*pBegin;
		*pBegin=temp;
		pBegin++;
		pEnd--;
	}
}
char * ReverseSentence(char *str)
{
	if(NULL==str)
		return NULL;
	char *pBegin=str;
	char *pEnd=str;
	while(*pEnd!='\0')
		pEnd++;
	pEnd--;
	//第一步：先翻转整个句子；
	Reverse(pBegin,pEnd);
	//第二步：再翻转句子中的每个单词；
	pBegin=pEnd=str;
	while(*pBegin!='\0')
	{
		if(*pBegin==' ')
		{
			pBegin++;
			pEnd++;
		}
		else if(*pEnd==' ' || *pEnd=='\0')
		{
			Reverse(pBegin,--pEnd);
			pBegin=++pEnd;
		}
		else
			pEnd++;
	}
	return str;
}
int main()
{
	char *pp=NULL;
	cout<<"未翻转前："<<strr<<endl;
	pp=ReverseSentence(strr);
	cout<<"翻转后："<<pp<<endl;
	
	return 0;
}