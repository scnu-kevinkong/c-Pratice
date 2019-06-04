#pragma once
template<typename T>
class ArrayStack
{
public:
	ArrayStack(int s = 10);    //默认的栈容量为10
	~ArrayStack();

public:
	T top();            //获取栈顶元素
	bool push(T t);        //压栈操作
	T pop();            //弹栈操作
	bool isEmpty();        //判空操作
	int size();            //求栈的大小
	void show_data();		//显示所有值，5个一行
private:
	int count;            //栈的元素数量
	int capacity;        //栈的容量
	T * array;            //底层为数组
};
/*栈的构造函数*/
template <typename T>
ArrayStack<T>::ArrayStack(int s) {
	capacity = s;
	array = new T[s]{};
};
/*栈的析构函数*/
template <typename T>
ArrayStack<T>::~ArrayStack() {
	delete array;
}
/*栈的判空操作*/
template <typename T>
bool ArrayStack<T>::isEmpty()
{
	return count == 0; //栈元素为0时为栈空
};

/*返回栈的大小*/
template <typename  T>
int ArrayStack<T>::size()
{
	return count;
};

/*插入元素*/
template <typename T>
bool ArrayStack<T>::push(T t)
{
	if (count < capacity)    //先判断是否栈满
	{
		array[count++] = t;
		return true;
	}
	else {
		return false;
	}
};

/*弹栈*/
template <typename T>
T ArrayStack<T>::pop()
{
	if (count != 0)    //先判断是否是空栈
	{
		return array[--count];
	}
};

/*获取栈顶元素*/
template <typename T>
T ArrayStack<T>::top()
{
	if (count != 0)
	{
		return array[count - 1];
	}
};
/*显示所有值，5个一行*/
template <typename T>
void ArrayStack<T>::show_data() {
	for (int i = count; i > 0; i--) {
		if ((i - 1) % 5 == 0) {
			std::cout << array[i - 1] << std::endl;
		}
		else {
			std::cout << array[i - 1] << '\t';
		}
	}
}