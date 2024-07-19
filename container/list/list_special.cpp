//list的五种特殊操作:这里是前4种
//反转reverse、排序sort、去重unique、合并merge、移动splice
//splice有三种,放在另一个cpp里了

#include <iostream> 
#include <list>
using std::cout;
using std::endl;
using std::list;

template<class Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

void test(){
    //1.list反转:reverse()
    list<int> ls{1,2,2,0,100,101};
    ls.reverse();
    display(ls);

    //2.排序:sort()
    ls.sort(std::greater<int>()); //从大到小
    display(ls);
    ls.sort();  //默认从小到大
    ls.sort(std::less<int>()); //从小到大 
    display(ls);

    //3.去除连续重复元素:unique(),需要先排序
    ls.unique();
    display(ls);

    //4.链表合并:merge()
    list<int> other{11,22,33,44,55};
    ls.merge(other);
    display(ls);

    //5.移动元素:splice()
}

int main()
{
    test();   
    return 0;
}
