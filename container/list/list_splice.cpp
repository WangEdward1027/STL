//list的三种移动元素方式：splice

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

//list的移动元素:splice
void test(){
    //1.将other链表中的元素全部移动
    list<int> number = {1, 3, 5, 7, 9};
    list<int> other = {11,22,33,44,55,66};
    auto it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;

    number.splice(it, other); //1.全部移动
    display(number);
    display(other);
}

void test2(){
    //2.将other链表中的某一个元素进行移动
    list<int> number = {1, 3, 5, 7, 9};
    list<int> other = {11,22,33,44,55,66};
    auto it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    
    auto it2 = other.end();
    --it2;
    cout << "*it2 = " << *it2 << endl;
    
    number.splice(it, other, it2); //2.移动一个指定位置的一个元素
    display(number);
    display(other);

    //移动一个元素,可以在同一个链表中操作
    cout << endl << "splice在同一个链表中进行操作" << endl;
    it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    
    it2 = number.end();
    --it2;
    cout << "*it2 = " << *it2 << endl;
    
    //目标链表.splice(目标位置,要移动的链表,被移动元素所在位置)
    number.splice(it2, number, it); 
    display(number);
}

void test3(){
    //3.将迭代器范围内的元素进行移动
    list<int> number = {1, 3, 5, 7, 9};
    list<int> other = {11,22,33,44,55,66};
    auto it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    
    auto it2 = other.begin();
    ++it2;
    cout << "*it2 = " << *it2 << endl;
    auto it3 = other.end();
    --it3;
    cout << "*it3 = " << *it3 << endl;
    
    number.splice(it, other, it2, it3); //左闭右开 [,),右边取不到
    display(number);
    display(other);
}

int main()
{
    /* test(); */   
    test2();   
    /* test3(); */   
    return 0;
}
