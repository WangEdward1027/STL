//vector的构造、遍历、基本操作

#include <iostream> 
#include <vector>
using std::cout;
using std::endl;
using std::vector;

//1.vector的构造
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

//2.vector的遍历
void test2(){
    vector<int> vec = {1,2,3,4,5};
    //1.下标方式遍历
    for(size_t idx = 0; idx < vec.size(); idx++){
        cout << vec[idx] << " ";
    }
    cout << endl;

    //2.增强for循环遍历
    for(auto & ele : vec){
        cout << ele << " ";
    }
    cout << endl;

    //3.迭代器方式遍历
    for(auto it = vec.begin(); it != vec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

//3.vector的基本操作
void test3(){
    vector<int> vec = {1,2,3};
    cout << "*vec.begin():" << *vec.begin() << endl;
    cout << "*(vec.end()-1):" << *(vec.end()-1) << endl;

    vec.push_back(4);
    cout << "vec.size():" << vec.size() << endl;
    cout << "vec.capacity():" << vec.capacity() << endl;

    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    cout << "vec.empey():" << vec.empty() << endl;
    cout << "vec.size():" << vec.size() << endl;
    cout << "vec.capacity():" << vec.capacity() << endl;
    
    for(int i = 1; i < 8; i++){
        vec.push_back(i);
    }
    cout << "vec.size():" << vec.size() << endl;
    cout << "vec.capacity():" << vec.capacity() << endl;
    
    vec.clear();
    cout << "vec.size():" << vec.size() << endl;
    cout << "vec.capacity():" << vec.capacity() << endl;

    vec.shrink_to_fit();
    cout << "vec.size():" << vec.size() << endl;
    cout << "vec.capacity():" << vec.capacity() << endl;

    vec.reserve(100);
    cout << "vec.size():" << vec.size() << endl;
    cout << "vec.capacity():" << vec.capacity() << endl;
}

//4.vector的自动扩容
void test4(){
    vector<int> vec8(5,8);
    cout << "nums's size: " << vec8.size() << endl;
    cout << "nums's capacity: " << vec8.capacity() << endl;
    cout << sizeof(vec8) << endl;
}

//5.在堆上创建vector对象
void test5(){
    //vector对象可以创建在栈上,也可以创建在堆上
    vector<int> * vec = new vector<int>();
    vec->push_back(10);
    delete vec;
}

int main()
{
    /* test1(); */   
    test2();   
    /* test3(); */   
    return 0;
}
