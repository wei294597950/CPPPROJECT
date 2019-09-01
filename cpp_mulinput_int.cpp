#include <iostream>                                                                     
#include <vector>                                                                       
#include <string>                                                                       
#include <sstream>                                                                      

using namespace std;



int main(int argc, const char* argv[])                                                               
{                                                                                                             
    // @param要得到其他类型对string进行转换即可，例：std::stoi                                       
    std::string tmp;                                                                                 
    std::vector< vector<int>  > input_info; 
	int i=0;                                            
    while ( getline(cin, tmp) )                                                                 
    {                                                                                                
        vector<int> input_tmp;                                                          
        //@param  way 1                                                                              
        istringstream mystream(tmp);  //istream的派生类                                                                                                                   

        int  s;                                                                              
        while (mystream >> s){                                                                       
            input_tmp.push_back(s);                                                                  
        }                                                                                            
        input_info.push_back(input_tmp);                                                             
        tmp="";    
		i++;
		if(i==3)
		break;                                                                                  
    }                                                                                                

    //测试一下                                                                                       
    vector< vector<int>   >::iterator it;                                         
                                                                              
    for ( it=input_info.begin()  ;it != input_info.end() ; it++ ){                                   
        vector<int>::iterator it_child;                                                 

        for( it_child = (*it).begin(); it_child != (*it).end(); it_child++ ){  
            cout << *it_child << " ";                                     
        }                                                                      
        cout << endl;                                                                                                      
    }                                                                          
    return 0;
} 
