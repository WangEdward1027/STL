//双向迭代器、随机访问迭代器

#include <iostream> 
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::list;
using std::vector;

//双向迭代器:list、set、map
void test(){
    list<int> ls = {1,2,3,4,5};
    list<int>::iterator iter1 = ls.begin(), iter2 = ls.end();
    //list的迭代器不支持比较操作,仅支持 == 和 !=
    /* while(iter1 < iter2){ */
    while(iter1 != iter2){
        cout << "*iter1 = " << *iter1 << " " << endl;
        ++iter1;
    }
}

//随机访问迭代器:vector、deque
void test2(){
    vector<int> vec = {1,2,3,4,5,6};
    vector<int>::iterator it1 = vec.begin(), it2 = vec.end();
    //vector是随机访问迭代器,支持比较操作
    while(it1 < it2){
        cout << "*it1 = " << *it1 << endl;
        ++it1;
    }
}

int main()
{
    /* test(); */   
    test2();   
    return 0;
}
