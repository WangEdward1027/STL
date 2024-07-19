//按值捕获、按引用捕获、仿函数(函数对象)

#include <iostream> 
#include <functional>
using std::cout;
using std::endl;

void test(){
    //[]是捕获列表,()是参数列表,{}是函数体
    [](int value){cout << "value = " << value << endl;}(20);
    
    //按值捕获
    int a = 10;
    [a]() mutable{//捕获的是const版本的副本,若要修改,加mutable
        ++a;
        cout << "按值捕获:a = "<< a << endl; //11
    }(); 
    cout << "外部的 a = " << a << endl; //仍为10

    //按引用捕获
    [&a](){ ++a; }();
    cout << "外部的 a = " << a << endl; //引用,修改了本源,11

    //lambda表达式的本质是 函数对象(仿函数)
    auto func = []{ cout << "hello" << endl; }; //没有参数列表,可省略()
    func();

    //返回值类型:写在参数列表后面  ->返回值类型
    std::function<void()> func2 = []()->void{};
}

int main()
{
    test();   
    return 0;
}
