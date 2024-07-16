//list的五种创建和初始化方式

#include <iostream> 
#include <list>
using std::cout;
using std::endl;
using std::list;

template<typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

//3.list的创建和初始化
void test3(){
    //1.创建无参对象
    list<int> ls;
    display(ls);
    
    //2.count个value
    list<int> ls2(5,6);
    display(ls2);
    
    //3.迭代器范围
    list<int> ls3(ls2.begin(),ls2.end());
    display(ls3);

    //4.拷贝构造或移动构造
    list<int> ls4 = ls3;
    list<int> ls44 = std::move(ls4);
    display(ls4);
    display(ls44);

    //5.初始化列表 {  }
    list<int> ls5{1,2,3,4,5};    //直接初始化
    list<int> ls55 = {5,4,3,2,1}; //构造初始化
    display(ls5);
    display(ls55);
}

int main()
{
    test3();   
    return 0;
}
