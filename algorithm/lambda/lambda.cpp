//1.引入lambda表达式的好处:原本的函数指针,现在声明和实现可以写在一起
//2.lambda表达式的形式: [](){}

#include <iostream> 
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;

void func(int value){
    cout << value << " ";
}

void test(){
    vector<int> vec = {1,3,5,7,9};
    for_each(vec.begin(), vec.end(), func);
    cout << endl;
}

//为了避免func在不同的文件中,考虑用lambda表达式,就可以把声明和实现写在一起了
void test2(){
    vector<int> vec = {2,4,6,8,10};
    //将func用lambda表达式实现
    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " "; });
    cout << endl;
}

int main()
{
    test();   
    test2();   
    return 0;
}
