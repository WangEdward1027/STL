//COW写时复制3:
//1.添加了CharProxy->CharProxy的赋值运算符重载
//2.添加了类型转换函数 operator char()

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class CowString
{
private:
    //引入代理类
    class CharProxy
    {
    public:
        CharProxy(CowString & self, size_t idx)
        : _self(self)
        , _idx(idx)
        {}
        
        //1.写时复制:左值是CharProxy,右值是char
        char & operator=(char ch);
       
        //2.类型转换函数:左值是char,右值是CharProxy
        operator char() const{
            cout << "类型转换函数 operator char()" << endl;
            return _self._pstr[_idx];
        }

        //3.左值是CharProxy,右值也是CharProxy
        char & operator=(const CharProxy & rhs);
       

        friend  //2.也要声明为内部类的友元函数
        ostream & operator<<(ostream & os, const CharProxy & rhs);
    private:
        CowString & _self;
        size_t _idx;
    };

public:
    CowString();
    CowString(const char *);
    CowString(const CowString &);
    CowString & operator=(const CowString &);
    ~CowString();

    const char * c_str() const{ return _pstr; }
    size_t size() const{ return strlen(_pstr); }

    int use_count(){
       return *(int*)(_pstr - kRefCountLength);
    }

    /* char & operator[](size_t idx); */
    CharProxy operator[](size_t idx);

    friend
    ostream & operator<<(ostream & os,const CowString & rhs);
    
    friend  //1.声明为外部类的友元函数
    ostream & operator<<(ostream & os, const CharProxy & rhs);
private:
    void initRefCount(){
        *(int*)(_pstr - kRefCountLength) = 1;
    }

    void increaseRefCount(){
        ++*(int*)(_pstr - kRefCountLength);
    }

    void decreaseRefCount(){
        --*(int*)(_pstr - kRefCountLength);
    }

    char * malloc(const char * pstr = nullptr)
    {
        if(pstr){
            return new char[strlen(pstr) + 1 + kRefCountLength]() + kRefCountLength;
        }else{
            return new char[1 + kRefCountLength]() + kRefCountLength;
        }
    }

    void release(){
        decreaseRefCount();
        if(use_count() == 0){
            delete [] (_pstr - kRefCountLength);
            _pstr = nullptr;
            cout << ">>>>delete heap" << endl;
        }
    }
private:
    static const int kRefCountLength = 4;
    char * _pstr;
};

CowString::CowString()
: _pstr(malloc())
{
    initRefCount();
}

CowString::CowString(const char * pstr)
: _pstr(malloc(pstr))
{
    strcpy(_pstr,pstr);
    initRefCount();
}

CowString::~CowString(){
    release();
}

CowString::CowString(const CowString & rhs)
: _pstr(rhs._pstr)//浅拷贝
{
    increaseRefCount();
}

CowString & CowString::operator=(const CowString & rhs){
    if(this != &rhs){// 1.判断自赋值情况
        release();   //2.尝试回收堆空间
        _pstr = rhs._pstr;  //3.浅拷贝
        increaseRefCount(); //4.新的空间引用计数+1
    }else{
        cout << "自复制" << endl;
    }
    return *this; //5.返回本对象
}

//友元函数形式重载输入流运算符
ostream & operator<<(ostream & os,const CowString & rhs){
    if(rhs._pstr){
        os << rhs._pstr;
    }else{
        os << endl;
    }
    return os;
}

//下标访问运算符的重载，改造为代理模式
CowString::CharProxy CowString::operator[](size_t idx){
    return CharProxy(*this, idx); //*this就是str1本身
}

//CharProxy中的赋值运算符函数1:右操作数是char
//写时复制
char & CowString::CharProxy::operator=(char ch){
    cout << "写时复制 char & CowString::CharProxy::operator=(char ch)" << endl;
    if(_idx < _self.size()){ 
        if(_self.use_count() > 1){
            //1.原本空间引用计数-1
            _self.decreaseRefCount();
            //2.深拷贝
            char * temp = _self.malloc(_self._pstr);
            strcpy(temp,_self._pstr);
            //3.改变指向
            _self._pstr = temp;
            //4.初始化新空间的引用计数
            _self.initRefCount();
        }
        //执行写操作
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    }else{
        cout << "下标超出String的范围,out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

//CharProxy中的赋值运算符函数2:右操作数是CharProxy
char & CowString::CharProxy::operator=(const CowString::CharProxy & rhs){
    if(&_self != &rhs._self || _idx != rhs._idx){  // 检查是否为自复制
        // _self._pstr[_idx] = rhs._self._pstr[_idx]; //不可以单纯这样修改,会跳过写时复制的逻辑
        char ch = rhs;  //1.调用类型转换函数
        *this = ch;     //2.调用写时复制
    }else{
        cout << "自复制" << endl;
    }
    return _self._pstr[_idx];  //赋值完成后,左操作数对应的char
}

ostream & operator<<(ostream & os, const CowString::CharProxy & rhs){
    if(rhs._idx < rhs._self.size()){
        os << rhs._self._pstr[rhs._idx];
    }else{
        os << "out of range";
    }
    return os;
}

void test1(){
    CowString str1 = "hello";
    cout << str1 << endl;
    CowString str2 = str1;
    cout << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << endl;

    str1[0] = 'H';  
    cout << str1 << endl;
    char c = str1[0]; //类型转换函数:CharProxy->char 
    cout << "c:" << c << endl;
    cout << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << endl;

    str2[0] = str1[0];  //CharProxy赋值给CharProxy,右边的CharProxy先转换为char
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << endl;
}

void test2(){
    CowString str1 = "hello";
    str1 = str1;
    cout << endl;

    CowString str2 = "Hello";
    str2[0] = str1[0];
    cout << str2 << endl;
    cout << endl;

    str1[0] = str1[0];
    cout << str1 << endl;
}

void test3(){
    CowString str1 = "hello";
    CowString str2 = str1;
    cout << str2 << endl;
    CowString str3 = "He";
    str1[0] = str3[0];
    cout << str1 << endl;
    cout << str2 << endl;
}

int main(void){
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}
