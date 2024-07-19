//三种插入迭代器(属于输出迭代器):
//1.back_inserter:插入尾部
//2.front_inserter:插入头部
//3.inserter:插入中间

#include <iostream> 
#include <vector>
#include <list>
#include <set>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::set;
using std::ostream_iterator;
using std::copy;

void test(){
    vector<int> vec = {1,2,3,4,5};
    list<int> ls = {6,7,8,9,10};
    //将list中的元素插入到vector的尾部
    copy(ls.begin(), ls.end(), back_inserter(vec));
    //用输出流迭代器对容器进行输出
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));//创建临时对象
    cout << endl;
}

void test2(){
    vector<int> vec = {1,2,3,4,5};
    list<int> ls = {6,7,8,9,10};
    //将vector中的元素插入到list的头部: 头插,会形成逆序的效果
    copy(vec.begin(), vec.end(), front_inserter(ls));
    //用输出流迭代器对容器进行输出
    copy(ls.begin(), ls.end(), ostream_iterator<int>(cout, " "));//创建临时对象
    cout << endl;
}

//插入中间
void test3(){
    vector<int> vec = {9,7,5,3,1};
    set<int> st = {10,8,6,4,2};
    
    //将vector中的元素插入到set
    auto it = st.begin();
    copy(vec.begin(), vec.end(), inserter(st, it));
    
    //用输出流迭代器对容器进行输出
    copy(st.begin(), st.end(), ostream_iterator<int>(cout, " "));//创建临时对象
    cout << endl;
}

int main()
{
    test();   
    test2();   
    test3();   
    return 0;
}
