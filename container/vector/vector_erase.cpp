//vector删除连续重复元素
//要注意,删除某元素后,后面的元素会自动前移一格
//如果此时无脑++it,会导致漏判一个元素。即被删元素的后一个元素。
//所以应该用if else，若erase，则不移动迭代器

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

void test(){
    //题意：删除vector中所有值为4的元素。
    vector<int> vec{1, 3, 5, 4, 4, 4, 7, 8,4, 9};
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        if(4 == *it){
            vec.erase(it);
        }
    }
    //发现删除后有些4没有删除掉,可以推测出是什么原因吗？是那些4没有删除呢？
    //答案:是因为vector删除的时候,后面的元素会自动前移一格。这时候再++it,
    //就会漏掉删除位置后面的那个元素

    //正确解法：
    for (auto it = vec.begin(); it != vec.end();    ){
        if (4 == *it){
            vec.erase(it);
        }else{
            ++it;
        }
    }
    display(vec);
}

void test2(){
    vector<int> vec{1, 3, 5, 4, 4, 4, 7, 8,4, 9};
    //vec.erase(4); //error, vector的erase不能删除指定元素
}

int main()
{
    /* test(); */   
    test2();   
    return 0;
}
