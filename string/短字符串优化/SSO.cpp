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
:_size(strlen(pstr))
{
    if(_size<=15){
        _capacity = 15;
        memset(_buffer._local, 0, sizeof(_buffer._local));
        strcpy(_buffer._local, pstr);
    }else{ //_size > 15
        _capacity = _size;
        _buffer._pointer = new char[strlen(pstr)+1];
        strcpy(_buffer._pointer, pstr);
    }
    cout << "String(const char * pstr)" << endl;
}

//union会导致_pointer不再是空指针
String::~String(){
    if(_size > 15){
        /* if(_buffer._pointer){ */
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        /* } */
    }
    cout << "~String()" << endl;
}

//成员函数重载
char & String::operator[](size_t idx){
    if(idx > _size - 1){
        cout << "out of range" << endl; 
             static char nullchar = '\0'; 
             return nullchar; 
    }
    if(_size <= 15){
        return _buffer._local[idx];
    }else{ //_size > 15
        return _buffer._pointer[idx];
    }
    cout << "operator[](size_t idx)" << endl;
}

//友元函数重载
ostream & operator<<(ostream & os,const String & rhs){
    if(rhs._size > 15){
        /* if(rhs._buffer._pointer){ */
            os << rhs._buffer._pointer;
        /* } */
    }else{
        os << rhs._buffer._local;
    }
    return os;
}

size_t String::size(){
    return _size;
}

size_t String::capacity(){
    return _capacity;
}

void test0(){
    String str1("hello");
    String str2("hello,world!!!!!");
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
