//vector的构造、遍历

#include <iostream> 
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void test1(){
    //vector<int>代表一个特点的类
    //vector可以代表一类类,vector是类模板实现的
    //1.无参构造的vector是空的
    vector<int> vec;
    for(auto & ele : vec){
        cout << ele << " ";
    }
    cout << endl;

    //2.传一个参数,规定了vector的个数,默认初始化为类型对应的默认值
    vector<long> vec2(10); //存放10个0,类型对应的默认值
    for(auto & ele : vec2){
        cout << ele << " ";
    }
    cout << endl;

    //3.第一个参数是个数,第二个参数是初始化的值
    vector<long> vec3(10, 3);
    for(auto & ele : vec3){
        cout << ele << " ";
    }
    cout << endl;
    
    //4.大括号形式
    vector<int> vec4 {1,2,3,4,5,6,7,8,9,10};
    for(auto & ele : vec4){
        cout << ele << " ";
    }
    cout << endl;

    //5.拷贝构造
    vector<int> vec5(vec4);
    for(auto & ele : vec5){
        cout << ele << " ";
    }
    cout << endl;

    //6.迭代器
    vector<int> vec6(vec5.begin(), vec5.end()-2);
    for(auto & ele : vec6){
        cout << ele << " ";
    }
    cout << endl;

    int arr[10] = {1,3,5,7,9,2,4,6,8,10};
    vector<int> vec7(arr, arr+10);
    for(auto & ele : vec7){
        cout << ele << " ";
    }
    cout << endl;
}

void test2(){
    vector<int> vec8(5,8);
    cout << "nums's size: " << vec8.size() << endl;
    cout << "nums's capacity: " << vec8.capacity() << endl;
    cout << sizeof(vec8) << endl;
}

void test3(){
    //vector对象可以创建在栈上,也可以创建在堆上
    vector<int> * vec = new vector<int>();
    vec->push_back(10);
    delete vec;
}

int main()
{
    test1();   
    /* test2(); */   
    return 0;
}
