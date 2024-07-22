//bind绑定成员函数: 要加&,对应this指针位置传对象的地址

#include <iostream> 
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using std::function;

int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

int multiply(int x, int y, int z)
{
    cout << "int multiply(int, int, int)" << endl;
    return x * y * z;
}

class Example
{
public:
    //成员函数的第一个参数,是隐藏的this指针, Example * const this
    int add(int x, int y){
        cout << "int Example::add(int,int)" << endl;
        return x + y;
    }
};

//bind可以绑定一元函数、二元函数、甚至n元函数
//既可以绑定普通函数,也可以绑定成员函数
void test(){
    //1.bind绑定二元普通函数
    auto f = bind(add, 1 , 2);
    cout << "f() = " << f() << endl;
    //2.bind绑定三元普通函数
    auto f2 = bind(&multiply, 3, 4, 5);
    cout << "f2() = " << f2() << endl;
    //3.bind绑定成员函数(三元函数)
    Example ex;
    auto f3 = bind(&Example::add, &ex, 10, 20); //成员函数就必须加引用
    cout << "f3() = " << f3() << endl;
    
    //占位符
    using namespace std::placeholders;
    function<int(int,int)> f4 = bind(add, _2, 100); //尽量用_1,需要多写参数,而且没用
    cout << "f4() = " << f4(1,2) << endl;
    
    function<int(int)> f5 = bind(add, _1, 100);     
    cout << "f5() = " << f5(6) << endl;
}

int main()
{
    test();   
    return 0;
}
