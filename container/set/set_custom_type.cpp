//set针对自定义类型的三种方法

#include <math.h>
#include <iostream> 
#include <set>
using std::cout;
using std::endl;
using std::set;
using std::ostream;

template<typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << endl;
    }
}

class Point
{
public:
    Point(int x = 0, int y = 0)
    : _ix(x)
    , _iy(y)
    {
        /* cout << "Point(int x = 0, int y = 0)" << endl; */
    }

    Point(const Point &rhs)
    : _ix(rhs._ix)
    , _iy(rhs._iy)
    {
        /* cout << "Point(const Point &rhs)" << endl; */
    }

    float getDistance() const{
        return hypot(_ix,_iy);
    }

    friend bool operator<(const Point &lhs, const Point &rhs);
    /* bool operator<(const Point &rhs) const; */
    friend ostream & operator<<(ostream &os, const Point &rhs);
    friend struct ComparePoint;   
    
    int getX() const{
        return _ix;
    }
    
    int getY() const{
        return _iy;
    }

private:
    int _ix;
    int _iy;
};

ostream & operator<<(ostream &os, const Point &rhs){
    os << "(" << rhs._ix << "," << rhs._iy << ")";
    return os;
}

/* //成员函数形式重载operator< */
/* bool Point::operator<(const Point &rhs) const{ */
/*     if(this->getDistance() < rhs.getDistance()) */
/*     { */
/*         return true; */
/*     } */
/*     else if(this->getDistance() == rhs.getDistance()) */
/*     { */
/*         if(this->_ix < rhs._ix) */
/*         { */
/*             return true; */
/*         } */
/*         else if(this->_ix == rhs._ix) */
/*         { */
/*             if(this->_iy < rhs._iy) */
/*             { */
/*                 return true; */
/*             } */
/*             else */
/*             { */
/*                 return false; */
/*             } */
/*         } */
/*         else */
/*         { */
/*             return false; */
/*         } */
/*     } */
/*     else */
/*     { */
/*         return false; */
/*     } */
/* } */

//方法二:运算符重载的版本:重载operator<运算符，可以比较Point类型
//全局普通函数声明为友元形式重载operator<
bool operator<(const Point &lhs, const Point &rhs){
    cout << "bool operator<"<< endl;
    //先比距离,再比横坐标,再比纵坐标
    if(lhs.getDistance() < rhs.getDistance()){
        return true;
    }else if(lhs.getDistance() == rhs.getDistance()){
        if(lhs._ix < rhs._ix){
            return true;
        }else if(lhs._ix == rhs._ix){
            if(lhs._iy < rhs._iy){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

//方法三:函数对象的版本:自己写Compare类
struct ComparePoint{
    bool operator()(const Point &lhs, const Point &rhs) const {
        cout << "struct ComparePoint" << endl;
        if(lhs.getDistance() < rhs.getDistance()){
            return true;
        }else if(lhs.getDistance() == rhs.getDistance()){
            if(lhs._ix < rhs._ix){
                return true;
            }else if(lhs._ix == rhs._ix){
                if(lhs._iy < rhs._iy){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};

//方法一:模板特化的版本:模板特化
//如果第二个模板参数不传,走std::less,则模板特化的优先级高于重载operator<
    
    //库里的std::less源码是这样写的
/* namespace std{ */
/* template<class T> */
/* struct less */
/* { */
/*     bool operator()(const T &lhs, const T &rhs) const{ */
/*         return lhs < rhs; */
/*     } */
/* }; */
/* } */

    //我们对其进行模板特化:模板的全特化
namespace std{
template<>
struct less<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const{
        /* return lhs < rhs; */
        cout << "template<> struct less<Point>" << endl;
        if(lhs.getDistance() < rhs.getDistance()){
            return true;
        }else if(lhs.getDistance() == rhs.getDistance()){
            if(lhs.getX() < rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() < rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};
}

void test(){
    set<int> num = {1,2,3};
    set<Point> number = {
    /* set<Point, ComparePoint> number = { */
        Point(1,0),
        Point(0,1),
        Point(1,1),
        Point(1,1),
        Point(2,0),
    };
    display(number);
}

int main()
{
    test();    
    return 0;
}
