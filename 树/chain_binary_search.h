#pragma once
#ifndef _CHAIN_BINARY_SEARCH_TREE_H
#define _CHAIN_BINARY_SEARCH_TREE_H
#include "b_tree.h"
#include <iostream>
template <typename T>
class BSTree : protected BTree<T> {
private:
	BTree<T> *root;
public:
	bool insert(T);    //插入指定值节点
	void pre_order(BTree<T>*); //前序遍历
	void mid_order(BTree<T>*); //中序遍历
	void last_order(BTree<T>*); //后序遍历
	BTree<T>* get_root(); //获取头节点
	BSTree() {
		root = nullptr;
	}
};
template <typename T>
bool BSTree<T>::insert(T value) {
	BTree<T>* father = nullptr;//父节点
	BTree<T>* pparent = root;
	BTree<T>* pnode = new BTree<T>(value);//插入值节点
	//寻找合适的插入位置
	while (pparent != nullptr) {
		if (value > pparent->value) {
			father = pparent;//指明新节点的父节点
			pparent = pparent->rchild;
		}
		else if (value < pparent->value) {
			father = pparent;//指明新节点的父节点
			pparent = pparent->lchild;
		}
		else {
			return false;
		}
	}
	if (root == nullptr) {
		root = pnode;
	}
	else {
		if (value < father->value) {
			father->lchild = pnode;
		}
		else if (value > father->value) {
			father->rchild = pnode;
		}
	}//则新节点为根
	return true;
}
template <typename T>
void BSTree<T>::pre_order(BTree<T>* node) {
	if (node != nullptr) {
		pre_order(node->lchild);
		pre_order(node->rchild);
		std::cout << node->value << ' ';
	}
}
template <typename T>
void BSTree<T>::mid_order(BTree<T>* node) {
	if (node != nullptr) {
		pre_order(node->lchild);
		std::cout << node->value << ' ';
		pre_order(node->rchild);
	}
}
template <typename T>
void BSTree<T>::last_order(BTree<T>* node) {
	if (node != nullptr) {
		std::cout << node->value << ' ';
		pre_order(node->lchild);
		pre_order(node->rchild);
	}
}
template <typename T>
BTree<T>* BSTree<T>::get_root() {
	return root;
}
#endif // _CHAIN_BINARY_SEARCH_TREE_H