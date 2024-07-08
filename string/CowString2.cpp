//COW写时复制2：代理模式,引入内部类CharProxy,重载[]和<<运算符

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

        char & operator=(char ch);
        friend 
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
    
    friend
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
    }
    return *this;
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

//读操作
//问题:写操作会把两个String都修改
/* char & CowString::operator[](size_t idx){ */
/*     if(idx < size()){ */
/*         return _pstr[idx]; */
/*     }else{ */
/*         cout << "out of range" << endl; */
/*         static char nullchar = '\0'; */
/*         return nullchar; */
/*     } */
/* } */

//写操作
//问题:读操作也会深拷贝开辟空间
/* char & CowString::operator[](size_t idx){ */
/*     if(idx < size()){ */
/*         if(use_count() > 1){ */
/*             //1.原本空间引用计数-1 */
/*             decreaseRefCount(); */
/*             //2.深拷贝 */
/*             char * temp = malloc(_pstr); */
/*             strcpy(temp,_pstr); */
/*             //3.改变指向 */
/*             _pstr = temp; */
/*             //4.初始化新空间的引用计数 */
/*             initRefCount(); */
/*         } */
/*         return _pstr[idx]; */
/*     }else{ */
/*         cout << "下标超出String的范围,out of range" << endl; */
/*         static char nullchar = '\0'; */
/*         return nullchar; */
/*     } */
/* } */

//改造为代理模式
//str1[0]需要返回一个CharProxy对象,只能利用str1对象和下标0来进行创建
//所以CharProxy的构造函数写成如下形式:
//str1[0] = 'H'，需要给CharProxy定义赋值运算符函数
//cout << str1[0] << endl; 需要给CharProxy重载输出流运算符函数
//CharProxy类需要设计一个CowString引用,向上绑定str1对象
//以及一个size_t的数据成员保存下标值
CowString::CharProxy CowString::operator[](size_t idx){
    return CharProxy(*this, idx);
}

char & CowString::CharProxy::operator=(char ch){
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

ostream & operator<<(ostream & os, const CowString::CharProxy & rhs){
    if(rhs._idx < rhs._self.size()){
        os << rhs._self._pstr[rhs._idx];
    }else{
        os << "out of range";
    }
    return os;
}

//测试引用计数
void test0(){
    CowString str1;
    CowString str2 = str1;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << endl;
    
    CowString str3("hello");
    CowString str4 = str3;
    cout << "str3:" << str3 << endl;
    cout << "str4:" << str4 << endl;
    cout << str3.use_count() << endl;
    cout << str4.use_count() << endl;
    cout << endl;
    
    str2 = str3;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << "str3:" << str3 << endl;
    cout << "str4:" << str4 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << str3.use_count() << endl;
    cout << str4.use_count() << endl;
}

void test1(){
    CowString str1("hello");
    CowString str2 = str1;
    cout << str2[0] << endl;
    /* str2[0] = 'H'; */
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
}

void test2(){
    CowString str1 = "hello";
    cout << str1 << endl;

    CowString str2 = str1;
    cout << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;

    //现存的问题: []返回的是CharProxy对象,作为右值,无法转换为char类型
   /* char c = str1[0]; */  
    str1[0] = 'H';
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;

}

int main(void){
    test2();
    return 0;
}
