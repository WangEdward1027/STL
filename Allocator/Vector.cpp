//空间配置器

#include <iostream> 
#include <memory>
using std::cout;
using std::endl;

template<typename T> 
class Vector 
{ 
public:     
    Vector()
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
    {
        cout << "Vector()" << endl;
    }   

    ~Vector(){
        cout << "~Vector()" << endl;
        clear();
        if(_start){
            _alloc.deallocate(_start, capacity());
        }
    }          
    
    void push_back(const T & value){
        if(_finish == _end_of_storage){
            reallocate();
        }
        /* _alloc.construct(_finish, value); */
        /* _finish++; */
        _alloc.construct(_finish++, value);
    }   

    void pop_back(){
        if(_finish != _start){
            /* --_finish; */
            /* _alloc.destroy(_finish); */
            _alloc.destroy(--_finish);
        }
    }         
    
    int size() const{
        return _finish - _start;
    }

    int capacity() const{
        return _end_of_storage - _start;
    }

private:     
    //重新分配内存,动态扩容要用的 
    void reallocate(){
        //新空间大小
        int old_capacity = capacity();
        int new_capacity = old_capacity==0 ? 1 : 2*old_capacity;
        
        //临时指针
        T* new_start = _alloc.allocate(new_capacity);
        T* new_finish = new_start;
    
        //将旧空间的元素移动到新申请的空间
        /* uninitialized_copy(_start, _finish, new_start); */
        
        for(T* it = _start; it != _finish; ++it){
            _alloc.construct(new_finish++, std::move(*it));
            _alloc.destroy(it);
        }

        //释放旧空间的内存
        if(_start){
            _alloc.deallocate(_start, old_capacity);
        }
        
        //三个指针置位,与新空间产生联系
        _start = new_start;
        _finish = new_finish;
        _end_of_storage = _start + new_capacity;
    }   

    void clear(){
        while(_finish != _start){
            _alloc.destroy(--_finish);
        }
    }

private:                       
    static std::allocator<T> _alloc;  //空间的申请 与 对象的构建 分开         
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};

//静态数据成员要在类外进行初始化
template<typename T>
std::allocator<T> Vector<T>::_alloc; //无参构造空间配置器对象

template<typename T>
void printVector(const Vector<T> & con){
    cout << "size() = " << con.size() << endl;
    cout << "capacity() = " << con.capacity() << endl;
    cout << endl;
}


int main()
{
    Vector<int> vec;
    printVector(vec);
    
    vec.push_back(1);   
    printVector(vec);
    
    vec.push_back(2);   
    printVector(vec);

    vec.push_back(3);   
    printVector(vec);
    
    vec.push_back(4);   
    printVector(vec);

    vec.push_back(5);   
    printVector(vec);
  
    return 0;
}
