//vector在尾部插入自定义类型对象
//用emplace_back，创建临时对象后直接插入
//比push_back少一次拷贝构造

#include <iostream> 
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Point
{
public:
    Point()
    :_ix(0)
    ,_iy(0)
    {
        cout << "Point无参构造" << endl;
    }

    Point(int ix, int iy)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point有参构造" << endl;
    }

    Point(const Point &rhs)
    :_ix(rhs._ix)
    ,_iy(rhs._iy)
    {
        cout << "Point拷贝构造" << endl;
    }

private:
    int _ix;
    int _iy;
};

void test(){
    vector<Point> vec;
    
    /* vec.push_back(Point(1,2)); */
    /* cout << endl; */

    vec.emplace_back(1,2);
}

int main()
{
    test();   
    return 0;
}
