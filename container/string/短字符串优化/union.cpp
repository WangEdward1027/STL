//union测试：
//union中所有成员共享一块内存空间,修改一个成员,可能导致其他成员也发生改变

#include <iostream> 
using std::cout;
using std::cin;
using std::endl;

union Buffer{
    char * _pointer = nullptr;// 初始化 _pointer 为 nullptr
    char _local[16];
};

int main()
{
    Buffer buffer;
    if(buffer._pointer == nullptr) {
        printf("_pointer is nullptr\n");
    }else{
        printf("_pointer is not nullptr\n");
    }
    cout << endl;
    
    buffer._local[0] = 'a';   //修改 _local 的内容,
    if(buffer._pointer == nullptr){ //却导致pointer的内容也发生修改
        printf("_pointer is nullptr\n"); //因为union是共享内存空间
    }else{
        printf("_pointer is not nullptr\n");
    }
    
    return 0;
}
