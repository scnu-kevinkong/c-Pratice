#pragma once
#include "single_chain.h"
template <typename T>
class ChainStack : public SingleLink<T> {
public:
	bool push(T);        //压栈操作
	T pop();            //弹栈操作
};
template <typename T>
bool ChainStack<T>::push(T t) {
	return SingleLink<T>::insert_last(t);
}
template <typename T>
T ChainStack<T>::pop() {
	if (SingleLink<T>::isEmpty()) {
		return NULL;
	}
	else {
		T result = SingleLink<T>::get_last();
		SingleLink<T>::del_last();
		return result;
	}
}
