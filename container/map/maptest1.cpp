//map的初始化、插入、遍历

#include <iostream> 
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::map;
using std::string;

void test()
{
    //初始化
    map<string,long int> addressBook = {
        {"Edward",18766210000},
        {"Amber",13381680000},
        {"Sam",18516540000}
    };

    //插入
    addressBook.insert({"Chole", 15677750000});

    //遍历
    for(auto &elem : addressBook){
        cout << elem.first << "'s number: " << elem.second << endl;
    }
}

int main()
{
    test();   
    return 0;
}
