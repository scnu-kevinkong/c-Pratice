#pragma once
#ifndef _ARRAYQUEUE_H
#define _ARRAYQUEUE_H
template<typename T>
class ArrayQueue
{
public:
	ArrayQueue(int s = 50);    //默认的队列容量为10
	~ArrayQueue();

public:
	T top();            //获取队列顶元素
	bool push(T t);        //压队列操作
	T pop();            //弹队列操作
	bool isEmpty();        //判空操作
	int size();            //求队列的大小
	void show_data();		//显示所有值，5个一行
private:
	int count;            //队列的元素数量
	int head;			//队列的头指位置
	int last;			//队列的尾指位置
	int capacity;        //队列的容量
	T * array;            //底层为数组
};
/*队列的构造函数*/
template <typename T>
ArrayQueue<T>::ArrayQueue(int s) {
	capacity = s;
	head = 0;
	last = 0;
	array = new T[s]{};
};
/*队列的析构函数*/
template <typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete array;
}
/*队列的判空操作*/
template <typename T>
bool ArrayQueue<T>::isEmpty()
{
	return count == 0; //队列元素为0时为队列空
};

/*返回队列的大小*/
template <typename  T>
int ArrayQueue<T>::size()
{
	return count;
};

/*插入元素*/
template <typename T>
bool ArrayQueue<T>::push(T t)
{
	if (count < capacity)    //先判断是否队列满
	{
		count++;
		array[last++] = t;
		return true;
	}
	else {
		return false;
	}
};

/*弹队列*/
template <typename T>
T ArrayQueue<T>::pop()
{
	if (count != 0)    //先判断是否是空队列
	{
		count--;
		T temp = array[head++];
		if (head > last) {
			head = 0;
		}
		return temp;
	}
};

/*获取队列顶元素*/
template <typename T>
T ArrayQueue<T>::top()
{
	if (count != 0)
	{
		return array[head];
	}
};
/*显示所有值，5个一行*/
template <typename T>
void ArrayQueue<T>::show_data() {
	for (int i = head; i < last; i++) {
		if (i % 5 == 0 && i > 0) {
			std::cout << array[i] << std::endl;
		}
		else {
			std::cout << array[i] << '\t';
		}
	}
}
#endif // _ARRAYQUEUE_H