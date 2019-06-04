#pragma once
// ˫������
#ifndef _DOUBLECHAIN_H
#define _DOUBLECHAIN_H
#include <iostream>
template <typename T>
class LinkNode
{
public:
	T _value;
	LinkNode* _prev;
	LinkNode* _next;
public:
	LinkNode() {
		_value = 0;
		_prev = nullptr;
		_next = nullptr;
	};
	LinkNode(T value, LinkNode *prev, LinkNode *next)
		: _value(value), _prev(prev), _next(next){}
};
template <typename T>
class DoubleLink : protected LinkNode<T> {
private:
	int count;
	LinkNode<T> *phead;
public:
	typedef LinkNode<T>* pointer;
	DoubleLink();
	~DoubleLink();
	int size();                         //��ȡ����
	bool isEmpty();                     //�п�
	bool insert(int, T);  //��ָ��λ�ò����½ڵ�
	bool insert_head(T); //ͷ����
	bool insert_last(T); //β����
	bool del(int); //ָ��λ��ɾ��
	bool del_head(); //ɾ��ͷ
	bool del_last(); //ɾ��β
	LinkNode<T>* getNode(int); //����ָ��λ��ָ��
	LinkNode<T>* getNode_head(); //����ͷָ��
	T get(int); //����ָ��λ�õ�ֵ
	T get_head();//����ͷ��ֵ
	T get_last(); //����β��ֵ
	void show_data();//��ӡ����ֵ, 5��һ��
};
template <typename T>
DoubleLink<T>::DoubleLink() {
	count = 0;
	phead = new LinkNode<T>;
}
template <typename T>
DoubleLink<T>::~DoubleLink() {
	LinkNode<T> *temp;
	while (phead != nullptr) {
		temp = phead->_next;
		delete phead;
		phead = temp;
	}
	delete phead;
}
template <typename T>
int DoubleLink<T>::size() {
	return count;
}
template <typename T>
bool DoubleLink<T>::isEmpty() {
	if (phead->_next == nullptr && count == 0) {
		return true;
	}
	else {
		return false;
	}
}
template <typename T>
bool DoubleLink<T>::insert(int index, T value) {
	if (index >= 0 && index <= count) {
		LinkNode<T> *prev_item = getNode(index);
		LinkNode<T> *next_item = getNode(index+1);
		LinkNode<T> *insert_node = new LinkNode<T>(value, prev_item, next_item);
		prev_item->_next = insert_node;
		if (next_item != nullptr) {
			next_item->_prev = insert_node;
		}
		count++;
		return true;
	}
	else {
		return false;
	}
}
template <typename T>
LinkNode<T>* DoubleLink<T>::getNode(int index) {
	LinkNode<T> *head = phead;
	if (index >= 0 && index <= count) {
		for (int i = 0; i < index; i++) {
			head = head->_next;
		}
		return head;
	}
	else {
		return nullptr;
	}
}
template <typename T>
LinkNode<T>* DoubleLink<T>::getNode_head() {
	return getNode(0);
}
template <typename T>
void DoubleLink<T>::show_data() {
	LinkNode<T> *head = phead;
	int i = 0;
	while (head->_next != nullptr) {
		i++;
		head = head->_next;
		if (i % 5 == 0) {
			std::cout << head->_value << std::endl;
		}
		else {
			std::cout << head->_value << '\t';
		}
	}
}
template <typename T>
bool DoubleLink<T>::insert_head(T value) {
	return insert(0, value);
}
template <typename T>
bool DoubleLink<T>::insert_last(T value) {
	return insert(count, value);
}
template <typename T>
bool DoubleLink<T>::del(int index) {
	if (index >= 1 && index <= count) {
		LinkNode<T> *result = getNode(index - 1);
		LinkNode<T> *temp = getNode(index);
		result->_next = temp->_next;
		if (temp->_next != nullptr) {
			temp->_next->_prev = result;
		}
		delete temp;
		count--;
		return true;
	}
	else {
		return false;
	}
}
template <typename T>
bool DoubleLink<T>::del_head() {
	return del(1);
}
template <typename T>
bool DoubleLink<T>::del_last() {
	return  del(count);
}
template <typename T>
T DoubleLink<T>::get(int index) {
	LinkNode<T> *cur = getNode(index);
	if (cur != nullptr) {
		return cur->_value;
	}
}
template <typename T>
T DoubleLink<T>::get_head() {
	return getNode(1)->_value;
}
template <typename T>
T DoubleLink<T>::get_last() {
	return getNode(count)->_value;
}
#endif // _DOUBLECHAIN_H