//反向迭代器

#include <iostream> 
#include <vector>
using std::cout;
using std::endl;
using std::vector;

//正向迭代器
void test(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9};
    vector<int>::iterator it = vec.begin();
    for(  ; it != vec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

//反向迭代器
void test2(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9};
    vector<int>::reverse_iterator rit = vec.rbegin();
    for(  ; rit != vec.rend(); ++rit){
        cout << *rit << " ";
    }
    cout << endl;
}

int main()
{
    test();   
    test2();   
    return 0;
}
