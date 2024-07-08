#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class CowString
{
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

    char & operator[](size_t idx);

    friend
    ostream & operator<<(ostream & os,const CowString & rhs);
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

ostream & operator<<(ostream & os,const CowString & rhs){
    if(rhs._pstr){
        os << rhs._pstr;
    }else{
        os << endl;
    }
    return os;
}

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
    if(this != &rhs){// 判断自赋值情况
        release();//尝试回收堆空间
        _pstr = rhs._pstr; //浅拷贝
        increaseRefCount(); //新的空间引用计数+1
    }
    return *this;
}

/* char & CowString::operator[](size_t idx){ */
/*     if(idx < size()){ */
/*         return _pstr[idx]; */
/*     }else{ */
/*         cout << "out of range" << endl; */
/*         static char nullchar = '\0'; */
/*         return nullchar; */
/*     } */
/* } */


char & CowString::operator[](size_t idx){
    if(idx < size()){
        if(use_count() > 1){
            //1.原本空间引用计数-1
            decreaseRefCount();
            //2.深拷贝
            char * temp = malloc(_pstr);
            strcpy(temp,_pstr);
            //3.改变指向
            _pstr = temp;
            //4.初始化新空间的引用计数
            initRefCount();
        }
        return _pstr[idx];
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}


void test0(){
    CowString str1;
    CowString str2 = str1;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;

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

int main(void){
    test1();
    return 0;
}
