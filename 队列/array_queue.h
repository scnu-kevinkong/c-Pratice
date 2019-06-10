#pragma once
#ifndef _ARRAYQUEUE_H
#define _ARRAYQUEUE_H
template<typename T>
class ArrayQueue
{
public:
	ArrayQueue(int s = 50);    //Ĭ�ϵĶ�������Ϊ10
	~ArrayQueue();

public:
	T top();            //��ȡ���ж�Ԫ��
	bool push(T t);        //ѹ���в���
	T pop();            //�����в���
	bool isEmpty();        //�пղ���
	int size();            //����еĴ�С
	void show_data();		//��ʾ����ֵ��5��һ��
private:
	int count;            //���е�Ԫ������
	int head;			//���е�ͷָλ��
	int last;			//���е�βָλ��
	int capacity;        //���е�����
	T * array;            //�ײ�Ϊ����
};
/*���еĹ��캯��*/
template <typename T>
ArrayQueue<T>::ArrayQueue(int s) {
	capacity = s;
	head = 0;
	last = 0;
	array = new T[s]{};
};
/*���е���������*/
template <typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete array;
}
/*���е��пղ���*/
template <typename T>
bool ArrayQueue<T>::isEmpty()
{
	return count == 0; //����Ԫ��Ϊ0ʱΪ���п�
};

/*���ض��еĴ�С*/
template <typename  T>
int ArrayQueue<T>::size()
{
	return count;
};

/*����Ԫ��*/
template <typename T>
bool ArrayQueue<T>::push(T t)
{
	if (count < capacity)    //���ж��Ƿ������
	{
		count++;
		array[last++] = t;
		return true;
	}
	else {
		return false;
	}
};

/*������*/
template <typename T>
T ArrayQueue<T>::pop()
{
	if (count != 0)    //���ж��Ƿ��ǿն���
	{
		count--;
		T temp = array[head++];
		if (head > last) {
			head = 0;
		}
		return temp;
	}
};

/*��ȡ���ж�Ԫ��*/
template <typename T>
T ArrayQueue<T>::top()
{
	if (count != 0)
	{
		return array[head];
	}
};
/*��ʾ����ֵ��5��һ��*/
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