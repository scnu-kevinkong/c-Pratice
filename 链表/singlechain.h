#pragma once
// ������
#ifndef _SINGLECHAIN_H
#define _SINGLECHAIN_H
#include <iostream>
template <typename T>
class LinkNode
{
public:
	T _value;
	LinkNode* _next;
public:
	LinkNode() {
		_value = 0;
		_next = nullptr;
	};
	LinkNode(T value, LinkNode * next)
		: _value(value), _next(next) {}
};
template <typename T>
class SingleLink : protected LinkNode<T> {
private:
	int count;
	LinkNode<T> *phead;
public:
	typedef LinkNode<T>* pointer;
	SingleLink();
	~SingleLink();
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
SingleLink<T>::SingleLink() {
	count = 0;
	phead = new LinkNode<T>;
}
template <typename T>
SingleLink<T>::~SingleLink() {
	LinkNode<T> *temp;
	while (phead != nullptr) {
		temp = phead->_next;
		delete phead;
		phead = temp;
	}
	delete phead;
}
template <typename T>
int SingleLink<T>::size() {
	return count;
}
template <typename T>
bool SingleLink<T>::isEmpty() {
	if (phead->_next == nullptr && count == 0) {
		return true;
	}
	else {
		return false;
	}
}
template <typename T>
bool SingleLink<T>::insert(int index, T value) {
	if (index >= 0 && index <= count) {
		LinkNode<T> *temp = getNode(index);
		LinkNode<T> *insert_node = new LinkNode<T>(value, temp->_next);
		insert_node->_next = temp->_next;
		temp->_next = insert_node;
		count++;
		return true;
	}
	else {
		return false;
	}
}
template <typename T>
LinkNode<T>* SingleLink<T>::getNode(int index) {
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
LinkNode<T>* SingleLink<T>::getNode_head() {
	return getNode(0);
}
template <typename T>
void SingleLink<T>::show_data() {
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
bool SingleLink<T>::insert_head(T value) {
	return insert(0, value);
}
template <typename T>
bool SingleLink<T>::insert_last(T value) {
	return insert(count, value);
}
template <typename T>
bool SingleLink<T>::del(int index) {
	if (index >= 1 && index <= count) {
		LinkNode<T> *result = getNode(index - 1);
		LinkNode<T> *temp = getNode(index);
		result->_next = temp -> _next;
		delete temp;
		count--;
		return true;
	}
	else {
		return false;
	}
}
template <typename T>
bool SingleLink<T>::del_head() {
	return del(1);
}
template <typename T>
bool SingleLink<T>::del_last() {
	return  del(count);
}
template <typename T>
T SingleLink<T>::get(int index) {
	LinkNode<T> *cur = getNode(index);
	if (cur != nullptr) {
		return cur->_value;
	}
}
template <typename T>
T SingleLink<T>::get_head() {
	return getNode(1)->_value;
}
template <typename T>
T SingleLink<T>::get_last() {
	return getNode(count)->_value;
}
#endif // _SINGLECHAIN_H