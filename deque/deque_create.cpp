//deque的五种创建和初始化

#include <iostream> 
#include <vector>
#include <deque>
using std::cout;
using std::endl;
using std::vector;
using std::deque;

template<typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

//2.deque的五种创建和初始化
void test2(){
    //1.创建无参对象
    deque<int> dq;
    display(dq);
    
    //2.count个value
    deque<int> dq2(3,6);
    display(dq2);

    //3.迭代器范围
    deque<int> dq3(dq2.begin(),dq2.end());
    display(dq3);

    //4.拷贝构造或移动构造函数
    deque<int> dq4 = dq3;
    deque<int> dq44 = std::move(dq4); //move后dq4为空
    display(dq4);
    display(dq44);

    //5.初始化列表 {  }
    deque<int> dq5{11,12,13,14,15};    //直接初始化
    deque<int> dq55 = {15,14,13,12,11}; //拷贝初始化
    display(dq5);
    display(dq55);

    dq4 = dq5;
    display(dq4);
    dq4 = {20,20,20}; //直接赋值必须用赋值号
    display(dq4);
}

int main()
{
    test2();   
    return 0;
}
