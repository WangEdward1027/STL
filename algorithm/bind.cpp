//bind、bind1st、bind2nd
    /* printf("%p\n", &main); */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> //包含 std::bind 和 std::placeholders
using std::cout;
using std::endl;
using std::vector;
using std::bind;
using std::function;
using namespace std::placeholders;

//使用bind1st
void test(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};

    //要删除所有大于5的元素
    //bind1st:固定住第一个参数
    auto it = remove_if(vec.begin(), vec.end(), bind1st(std::less<int>(), 5));
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " "; });
    cout << endl;
}

//使用bind2nd
void test2(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};

    //要删除所有大于5的元素
    //bind2nd:固定住第二个参数
    auto it = remove_if(vec.begin(), vec.end(), bind2nd(std::greater<int>(), 5));
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " "; });
    cout << endl;
}

//使用std::bind
void test3(){
    //要删除所有大于5的元素

    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    //std::bind :使用占位符_1，并固定第二个参数
    auto it = remove_if(vec.begin(), vec.end(), bind(std::greater<int>(), _1, 5));
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int val){cout << val << " ";});
    cout << endl;

    vector<int> vec2 = {1,2,3,4,5,6,7,8,9,10};
    auto it2 = remove_if(vec2.begin(), vec2.end(), bind(std::less<int>(), 5, _1));
    vec2.erase(it2, vec2.end());

    for_each(vec2.begin(), vec2.end(), [](int val){cout << val << " ";});
    cout << endl;
}

//测试一个三元函数
int add(int x, int y, int z){
    cout << "add(int x, int y, int z)" << endl;
    return x + y + z;
}

//bind绑定普通函数
void test4(){
    //bind: 固定第一个参数,并保留两个占位符
    /* auto func = bind(add, 100, _2, _3); */
    //用function<> 还原auto的类型
    function<int(int,int,int)> func = bind(add, 100, _2, _3);
    cout << func(666,10,1) << endl;
    function<int(int,int)> func2 = bind(add, 200, _1, _2);
    cout << func2(20,2) << endl;
    function<int(int)> func3 = bind(add, 300, _1, _1);
    cout << func3(10) << endl;
}

int main()
{
    /* test(); */
    /* test2(); */
    /* test3(); */
    test4();
    return 0;
}
