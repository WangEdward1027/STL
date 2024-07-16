//set的插入、删除：insert、erase

#include <iostream> 
#include <set>
#include <utility>
#include <vector>
using std::cout;
using std::endl;
using std::set;
using std::pair;
using std::vector;

template <typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

void test(){
    set<int> s = {1,2,3,4,5,6};
    display(s);
    
    //set的insert操作
    //1.插入一个元素
    cout << "set插入一个元素" << endl;
    pair<set<int>::iterator, bool> ret = s.insert(7);
    if(ret.second){
        cout << "插入成功: " << *ret.first << endl;
    }else{
        cout << "插入失败,该元素存在set中" << endl;
    }
    display(s);

    //2.插入迭代器范围的元素
    cout << "set迭代器范围的元素" << endl;
    vector<int> vec{8,9,10};
    s.insert(vec.begin(), vec.end());
    display(s);

    //3.set插入大括号范围的元素
    cout << "set插入大括号范围的元素" << endl;
    s.insert({11,12,13,14,15});
    display(s);
}

//set的删除操作
void test2(){
    set<int> s{1,2,3,4,5,6,7,10,8,9,10}; //set会自动去重
    //1.删除指定元素
    s.erase(10);
    display(s);

    //2.删除迭代器指定位置
    auto it = s.begin();
    ++it;
    s.erase(it);
    display(s);

    //3.删除迭代器范围的元素
    it = s.begin();
    ++it;
    auto it2 = s.end();
    --it2;
    s.erase(it,it2);
    display(s);
}

int main()
{
    /* test(); */
    test2();
    return 0;
}
