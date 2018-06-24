#include<map>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<string,int> PAIR;
bool cmp_bu_value(const PAIR& lhs,const PAIR& rhs){
    return lhs.second < rhs.second;
}
struct CmpByValue{
    bool operator()(const PAIR& lhs,const PAIR& rhs){
    return lhs.second < rhs.second;
}
};

int main(){
    map<string,int>  name_score_map;
    name_score_map["Liin"] = 90;
    name_score_map["ZiLinMi"] = 79;
    name_score_map["BoB"] = 92;
    name_score_map.insert(make_pair("Bing",99));
    name_score_map.insert(make_pair("Albert",86));

    vector<PAIR> name_score_vector(name_score_map.begin(),name_score_map.end());
    sort(name_score_vector.begin(),name_score_vector.end(),CmpByValue());
    vector<PAIR>::iterator it;
    for(it=name_score_vector.begin();it!=name_score_vector.end();it++){
        cout<<(*it).first<<"  "<<(*it).second<<endl;
    }

}
//map默认按key排序，若key为复杂类型如struct，需要重载map的<操作符或按需重载操作符，
//函数对象即调用操作符的类，它是一个带模板的struct，本例是按value排序