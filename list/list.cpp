//list的插入与删除

#include <iostream> 
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::list;
using std::vector;

template<typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

//list的插入:尾部插入、首部插入、4种中间插入
void test(){
    list<int> ls = {4,5,6,7};
    //尾部插入
    ls.push_back(8);
    //头部插入
    ls.push_front(1);
    //遍历打印
    display(ls);  //1 4 5 6 7 8

    //四种中间插入:insert()
    //1.第一种中间插入:找一个迭代器位置,插入一个元素
    auto it = ls.begin();
    ++it; //4
    ls.insert(it, 2);
    display(ls);
    cout << "*it = " << *it << endl;
    
    //2.第二种中间插入:找一个迭代器位置,插入count个元素
    ls.insert(it, 2, 3);
    display(ls);
    cout << "*it = " << *it << endl;
    
    //3.第三种中间插入:找一个迭代器位置,插入迭代器范围的元素
    vector<int> vec = {999,1111};
    ls.insert(it, vec.begin(), vec.end());
    display(ls);
    cout << "*it = " << *it << endl;
    

    //4.第四种中间插入:找一个迭代器位置,插入大括号范围内的元素
    it = ls.begin();
    ++it; //2
    ls.insert(it, {500, 400, 300});
    display(ls);
    cout << "*it = " << *it << endl;
}

//list的删除
void test2(){
    //删除重复连续元素:删除list中所有的2
    list<int> ls = {1,2,2,2,3,4,5,2,2,2,6,7,8,2,2,9};
    
    for(auto it = ls.begin(); it != ls.end();  ){
        if(*it == 2){
            it = ls.erase(it);
        }else{
            ++it;
        }
    }

    display(ls);
}

int main()
{
    /* test(); */   
    test2();   
    return 0;
}
