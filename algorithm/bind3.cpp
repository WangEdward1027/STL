//bind固定部分参数(改变函数的类型),返回值为function类型的对象
//bind绑定普通函数、成员函数、函数对象

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using namespace std::placeholders; //占位符
using std::function;

//1.普通函数
int sub(int a, int b)
{
    return a - b;
}

//1.bind绑定普通函数
void test1()
{
    // 将add函数的第一个参数绑定为15
    auto add_two = bind(sub, 15, _1);
    // 调用新的函数对象，传递第二个参数
    cout << "Result: " << add_two(6) << endl;  // 输出：Result: 5
}


//2.自定义类
class MyClass {
public:
    void display(int value) const
    {
        cout << "Value: " << value << endl;
    }
};

//2.bind绑定成员函数
void test2()
{
    MyClass obj;
    //std::bind绑定成员函数时,传递的第一个参数是成员函数指针
    //第二个参数是this指针,即对象实例的指针
    function<void(int)> bind_display = bind(&MyClass::display, &obj, _1);
    // 调用绑定后的成员函数
    bind_display(66);  // 输出：Value: 66
}


//3.函数对象
class Multiply
{
public:
    int operator()(int a, int b) const
    {  //重载了函数调用运算符的类的对象称为函数对象
        return a * b;
    }
};

//3.bind绑定函数对象
void test3()
{
    Multiply multiply;  //函数对象
    // 将Multiply对象的第一个参数绑定为5
    function<int(int)> func = bind(multiply, 5, _1);
    /* auto func = bind(multiply, 5, _1); */
    // 调用新的函数对象，传递第二个参数
    cout << "Result: " << func(10) << endl;  // 输出：Result: 50
}


int main()
{
    test1();
    test2();
    test3();
    return 0;
}
