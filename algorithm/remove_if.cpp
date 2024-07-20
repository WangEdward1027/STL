//remove_if + erase:删除容器中满足第三个参数(一元断言)的元素

#include <iostream> 
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::remove_if;

//一元断言:返回值是bool,一个参数
bool func(int value){
    return value > 5;
}

void test(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    
    //2.remove_if的第三个参数是一元断言
    auto it = remove_if(vec.begin(), vec.end(), func);
    vec.erase(it, vec.end());
    
    //1.for_each的第三个参数是一元函数
    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " "; });
    cout << endl;
}

//一元断言
bool isOdd(int value){
    return value % 2 != 0;
}

void test2(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    //使用remove_if移除所有奇数
    auto it = remove_if(vec.begin(), vec.end(), isOdd);//it指向覆盖后要擦除的首位置
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " ";});
    cout << endl;
}

//一元函数和一元断言都用lamb表达式
void test3(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    auto it = remove_if(vec.begin(), vec.end(), [](int value)->bool{
                        return value > 5;
                        });
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " ";});
    cout << endl;
}

//一元函数和一元断言都用lamb表达式
void test4(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    //lambda表达式可省略函数返回值类型,编译器会根据return语句自动推导
    auto it = remove_if(vec.begin(), vec.end(), [](int value){ return value % 2 == 0; });
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int value){ cout << value << " ";});
    cout << endl;
}

int main()
{
    /* test(); */   
    /* test2(); */   
    test3();   
    test4();   
    return 0;
}
