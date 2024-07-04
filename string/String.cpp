//string类的模拟实现1

#include <string.h>
#include <iostream> 
using std::cout;
using std::cin;
using std::endl;

//实现一个自定义的String类，保证main函数正确执行。实现时，记得采用增量编写的方式，逐一测试。
class String
{
public:
    //无参构造
    String()
    :_pstr(new char[1]()) //申请一个字节空间,并用()初始化为'\0'
    {
        cout << "String()" << endl;
    }

    //有参构造
    String(const char *pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
        cout << "String(const char *pstr)"  << endl;
    }

    //拷贝构造
    String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1])
    {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String &rhs)"  << endl;
    }

    //赋值运算符函数
    String &operator=(const String &rhs){
        if(this != &rhs){   //1.判断是否是自复制
            delete [] _pstr; //2.回收左操作数管理的堆空间
            _pstr = new char[strlen(rhs._pstr) + 1](); //3.深拷贝
            strcpy(_pstr, rhs._pstr);    //以及其他数据成员的拷贝
        }
        return *this;   //4.返回本对象
        cout << "String &operator=(const String &rhs)" << endl;
    }

    //析构函数
    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr; //安全回收
        }
        cout << "~String()" << endl;
    }

    void print() const{
        cout << _pstr << endl;
    }

    size_t length() const{
        return strlen(_pstr);
    }

    const char * c_str() const{
        return _pstr;
    }

private:
	char * _pstr;
};

int main()
{
	String str1; //无参构造
	str1.print();

	String str2 = "Hello,world";  //有参构造
	String str3("wangdao");       //有参构造
	str2.print();
	str3.print();

	String str4 = str3;     //拷贝构造函数
	str4.print();

	str4 = str2;          //赋值运算符函数
	str4.print();

    cout << "str4.length():" << str4.length() << endl;
    
    char * p = new char(str4.length() + 1);
    strcpy(p, str4.c_str());
    printf("%s\n",p);

	return 0;
}
