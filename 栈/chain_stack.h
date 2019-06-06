#pragma once
#ifndef _CHAINSTACK_H
#define _CHAINSTACK_H
#include "single_chain.h"
template <typename T>
class ChainStack : public SingleLink<T> {
public:
	bool push(T);        //Ñ¹Õ»²Ù×÷
	T pop();            //µ¯Õ»²Ù×÷
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
#endif // _CHAINSTACK_H
