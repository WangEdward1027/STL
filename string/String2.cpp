//string类的模拟实现2

#include <string.h>
#include <iostream> 
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

class String 
{
public:
	String();
	String(const char *);
	String(const String &);
	~String();
	String &operator=(const String &);
	String &operator=(const char *);

	String &operator+=(const String &);
	String &operator+=(const char *);
	
	char &operator[](size_t index);
	const char &operator[](size_t index) const;
	
	size_t size() const;
	const char* c_str() const;
	
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
	
	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);
	
	friend ostream &operator<<(ostream &os, const String &s);
	friend istream &operator>>(istream &is, String &s);

    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char *, const String &);

private:
	char * _pstr;
};

//无参构造
String::String()
:_pstr(new char[1]())
{
    cout << "String()" << endl;
}

//有参构造
String::String(const char * pstr)
:_pstr(new char[strlen(pstr) + 1]())
{
    cout << "String(const char * pstr)" << endl;
    strcpy(_pstr, pstr);
}

//拷贝构造
String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr) + 1]())
{
    cout << "String(const String & rhs)" << endl;
    strcpy(_pstr, rhs._pstr);
}

//析构函数
String::~String(){
    cout << "~String()" << endl;
    if(_pstr){
        delete [] _pstr;
        _pstr = nullptr; //安全回收
    }
}

//赋值运算符函数
String & String::operator=(const String & rhs){
    if(this != &rhs){
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

//赋值运算符函数  
String & String::operator=(const char * pstr){
    if(_pstr){
        delete [] _pstr;
    }
    _pstr = new char[strlen(pstr) + 1]();
    strcpy(_pstr, pstr);
    return *this;
}

String & String::operator+=(const String & rhs){
    strcat(_pstr,rhs._pstr);
    return *this;
}

String & String::operator+=(const char * pstr){
    strcat(_pstr, pstr);
    return *this;
}

bool operator==(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) != 0;
}

bool operator<(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String & lhs, const String & rhs){
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

String operator+(const String & lhs, const String & rhs){
    String temp = lhs;  
    strcat(temp._pstr, rhs._pstr);
    return temp;
}

String operator+(const String & lhs, const char * pstr){
    String temp = lhs;
    strcat(temp._pstr, pstr);
    return temp;
}

String operator+(const char * pstr, const String & rhs){
    char * tmp = nullptr;
    strcpy(tmp,pstr);
    String temp = strcat(tmp, rhs._pstr);
    return temp;
}

char& String::operator[](size_t index){
    size_t len = strlen(_pstr);
    if(index < len){
        return _pstr[index];
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

const char& String::operator[](size_t index) const{
    size_t len = strlen(_pstr);
    if(index < len){
        return _pstr[index];
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

ostream &operator<<(ostream &os, const String &s){
    os << s._pstr;
    return os;
}

istream &operator>>(istream &is, String &s){
    is >> s._pstr;
    return is;
}

size_t String::size() const{
    return strlen(_pstr);
}

const char* String::c_str() const{
    return _pstr;
}

void test(){
    String str1 = "H";  //构造
    String str2 = "e";
    String str3 = str1 + str2; // +  =  拷贝构造
    cout << str3 << endl; // << 
    
    if(str3 > str1){ // >
        cout << "str3 > str1" << endl;
    }
 
    str1 += str2; // +=
    
    if(str3 == str1){ // ==
        cout << "str3 == str1" << endl;
    }

    if(str3 >= str1){ // >=
        cout << "str3 >= str1" << endl;
    }
    
    cout << "str1:" << str1 << endl;
    cout << "str3:" << str3 << endl;

    cin >> str1 >> str3;  // >>
    cout << "str1:" << str1 << endl;
    cout << "str3:" << str3 << endl;
    
    str2 = str1; //赋值
    cout << "str2.size():" << str2.size() << endl;  // .size()

    for(size_t i = 0; i < str2.size(); ++i){
        cout << str2[i]; //[]
    }
    cout << endl;
}

int main()
{
    test();       
    return 0;
}
