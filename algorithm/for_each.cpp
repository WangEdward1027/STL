//第五种遍历方式:for_each()

#include <algorithm>  //for_each的头文件

void func(int value){
	cout << value << " ";
}

void test(){
	vector<int> vec= {1,3,5,7,9};
	//将for_each函数中的第一个参数到第二个参数范围中的元素，传入到第三个参数中
	for_each(vec.begin(), vec.end(), func);
	cout << endl;
}
