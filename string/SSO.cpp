//string的第三种实现:短字符串优化 SSO
//<=15字节的存在栈区, >15字节的存在堆区

#include <fstream>
#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;

class String {
public:
    String(const char * pstr);
    ~String();
    char & operator[](size_t idx);

    friend
    ostream & operator<<(ostream & os,const String & rhs);
    
    size_t size();
    size_t capacity();

private:
	union Buffer{
		char * _pointer = nullptr;
		char _local[16];
	};
	size_t _size;
	size_t _capacity;
    Buffer _buffer;
};

String::String(const char * pstr)
:_size(strlen(pstr)+1)
{
    if(_size<=15){
        _capacity = 15;
        strcpy(_buffer._local, pstr);
    }else{ //_size > 15
        _capacity = _size;
        _buffer._pointer = new char[_size];
        strcpy(_buffer._pointer, pstr);
    }
    cout << "String(const char * pstr)" << endl;
}

String::~String(){
    if(_size > 15){
        if(_buffer._pointer){
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }
    cout << "~String()" << endl;
}

//成员函数重载
char & String::operator[](size_t idx){
    if(_size <= 15){
        size_t len = strlen(_buffer._local);
        if(idx < len){
            return _buffer._local[idx];
        }else{
            cout << "out of _local range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }else{ //_size > 15
        size_t len = strlen(_buffer._pointer);
        if(idx < len){
            return _buffer._pointer[idx];
        }else{
            cout << "out of _pointer range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    cout << "operator[](size_t idx)" << endl;
}

//友元函数重载
ostream & operator<<(ostream & os,const String & rhs){
    if(rhs._size > 15){
        if(rhs._buffer._pointer){
            os << rhs._buffer._pointer;
        }
        return os;
    }else{
        os << rhs._buffer._local;
        return os;
    }
}

size_t String::size(){
    return _size;
}

size_t String::capacity(){
    return _capacity;
}

void test0(){
    String str1("hello");
    String str2("hello,world!!!!");
    cout << str1.size() << endl;
    cout << str1.capacity() << endl;
    cout << str2.size() << endl;
    cout << str2.capacity() << endl;
    
    cout << str1[0] << endl;
    cout << str1[6] << endl;
    cout << str2[0] << endl;
    cout << str2[16] << endl;

    cout << &str1 << endl;
    printf("%p\n",&str1[0]);
    cout << &str2 << endl;
    printf("%p\n",&str2[0]);
}

int main(){
    test0();
}
