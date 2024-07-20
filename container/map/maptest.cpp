//测试:map和unordered_map
//1.插入 2.按key删除

#include <iostream> 
#include <map>
#include <unordered_map>
using std::cout;
using std::endl;
using std::map;
using std::unordered_map;

template<typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem.first << " " << elem.second << endl;
    }
    cout << endl;
}

void test(){
    map<int,int> mymap;
    //1.测试直接赋值,发现可以直接插入
    mymap[1] = 10;
    mymap[2] = 20;
    display(mymap);

    //2.测试map可以直接删除指定的key,不需要用迭代器
    mymap.erase(2);
    display(mymap);
}

void test2(){
    //3.测试unordered_map的erase
    unordered_map<int,int> um;
    um[1] = 100;
    um[2] = 200;
    display(um);
    
    um.erase(2);
    display(um);
}

int main()
{
    /* test(); */   
    test2();   
    return 0;
}
