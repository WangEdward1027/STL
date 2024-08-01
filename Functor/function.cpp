//function:函数包装器
//包装:普通函数、lambda表达式、成员函数、函数对象

#include <iostream>
#include <functional>
#include <math.h>
#include <string>
using std::cout;
using std::endl;
using std::function;
using std::string;

//1.普通函数
int add(int a, int b) 
{
    return a + b;
}

//1.使用function包装普通函数
void test1(){
    // 使用std::function包装普通函数
    function<int(int, int)> func = add;

    // 调用包装的函数
    cout << "Result: " << func(2, 3) << endl;  // 输出：Result: 5
}


//2.使用function包装lambda表达式
void test2(){
    // 使用std::function包装Lambda表达式
    function<int(int, int)> func = [](int a, int b){
        return a * b;
    };
    // 调用包装的Lambda表达式
    cout << "Result: " << func(2, 3) << endl;  // 输出：Result: 6
}


//3.自定义类
class MyClass 
{
public:
    int power(int a, int b)
    {
        return pow(a,b);
    }

    void display(const string & message)
    {
        cout << message << endl;
    }
};

//3.使用function包装成员函数
void test3() {
    MyClass obj;
    //使用std::function包装MyClass::power成员函数
    function<int(MyClass&, int, int)> func = &MyClass::power;
    //调用包装的成员函数
    cout << "Result: " << func(obj, 2, 3) << endl;  // 输出：Result: 5

    //定义一个std::function类型,包装MyClass::display成员函数
    function<void(MyClass&,const string &)> func2 = &MyClass::display;
    func2(obj, "Hello,World!"); //需要传入对象实例
}


//4.函数对象
class Multiply
{
public:
    //重载了函数调用运算符的类的对象,称为函数对象
    int operator()(int a, int b) const
    {
        return a * b;
    }
};

//4.function包装函数对象
void test4(){
    Multiply multiply; //函数对象实例
    // 使用std::function包装函数对象
    function<int(int, int)> func = multiply;
    cout << "Result: " << func(3, 5) << endl;  // 输出：Result: 15
}


int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
