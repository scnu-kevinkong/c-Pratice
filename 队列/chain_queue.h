#pragma once
#ifndef _CHAINQUEUE_H
#define _CHAINQUEUE_H
#include "single_chain.h"
template <typename T>
class ChainQueue : public SingleLink<T> {
public:
	bool push(T);        //压队列操作
	T pop();            //弹队列操作
	void show_data();  //打印值
};
template <typename T>
bool ChainQueue<T>::push(T t) {
	return SingleLink<T>::insert_last(t);
}
template <typename T>
T ChainQueue<T>::pop() {
	if (SingleLink<T>::isEmpty()) {
		return NULL;
	}
	else {
		T result = SingleLink<T>::get_head();
		SingleLink<T>::del_head();
		return result;
	}
}
template <typename T>
void ChainQueue<T>::show_data() {
	SingleLink<T>::show_data();
}
#endif // _CHAINQUEUE_H