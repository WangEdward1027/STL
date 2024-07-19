//vector的创建和初始化

#include <iostream> 
#include <vector>
using std::cout;
using std::endl;
using std::vector;

template<typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

//vector的创建和初始化
void test(){
    //1.创建无参对象
    vector<int> vec;
    display(vec);
    
    //2.count个value
    vector<int> vec2(3,6);
    display(vec2);
    
    //3.迭代器范围
    vector<int> vec3(vec2.begin(), vec2.end());
    display(vec3);
    
    //4.拷贝构造或移动构造函数
    vector<int> vec4 = vec3;
    vector<int> vec44 = std::move(vec4); //move后,vec4为空
    display(vec4);
    display(vec44);

    //5.初始化列表 {  }
    vector<int> vec5{10,9,8,7,6};      //直接初始化
    vector<int> vec55 = {10,9,8,7,6};  //拷贝初始化
    display(vec5);
    display(vec55);
    vec4 = {10,9,8,7};         //赋值操作必须用等号
    display(vec4);
}

int main()
{
    test();   
    return 0;
}
