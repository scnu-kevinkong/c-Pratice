#pragma once
template<typename T>
class ArrayStack
{
public:
	ArrayStack(int s = 10);    //Ĭ�ϵ�ջ����Ϊ10
	~ArrayStack();

public:
	T top();            //��ȡջ��Ԫ��
	bool push(T t);        //ѹջ����
	T pop();            //��ջ����
	bool isEmpty();        //�пղ���
	int size();            //��ջ�Ĵ�С
	void show_data();		//��ʾ����ֵ��5��һ��
private:
	int count;            //ջ��Ԫ������
	int capacity;        //ջ������
	T * array;            //�ײ�Ϊ����
};
/*ջ�Ĺ��캯��*/
template <typename T>
ArrayStack<T>::ArrayStack(int s) {
	capacity = s;
	array = new T[s]{};
};
/*ջ����������*/
template <typename T>
ArrayStack<T>::~ArrayStack() {
	delete array;
}
/*ջ���пղ���*/
template <typename T>
bool ArrayStack<T>::isEmpty()
{
	return count == 0; //ջԪ��Ϊ0ʱΪջ��
};

/*����ջ�Ĵ�С*/
template <typename  T>
int ArrayStack<T>::size()
{
	return count;
};

/*����Ԫ��*/
template <typename T>
bool ArrayStack<T>::push(T t)
{
	if (count < capacity)    //���ж��Ƿ�ջ��
	{
		array[count++] = t;
		return true;
	}
	else {
		return false;
	}
};

/*��ջ*/
template <typename T>
T ArrayStack<T>::pop()
{
	if (count != 0)    //���ж��Ƿ��ǿ�ջ
	{
		return array[--count];
	}
};

/*��ȡջ��Ԫ��*/
template <typename T>
T ArrayStack<T>::top()
{
	if (count != 0)
	{
		return array[count - 1];
	}
};
/*��ʾ����ֵ��5��һ��*/
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