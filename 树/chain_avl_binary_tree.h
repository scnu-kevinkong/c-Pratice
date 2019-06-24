#pragma once
#ifndef _CHAIN_AVL_BINARY_TREE_H
#define _CHAIN_AVL_BINARY_TREE_H
#include "b_tree.h"
template <typename T>
class AVLTree : protected BTree<T> {
private:
	BTree<T>* root;
	int get_height(BTree<T>*); //获取树的高度
	int max_int(int, int); //获取int更大值
	bool insert(T, BTree<T>* &);    //插入指定值节点
	void rotate_left(BTree<T>* &); //左旋
	void rotate_right(BTree<T>* &); //右旋
public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
		destroy(root);
	}
	void destroy(BTree<T>*); //销毁结点
	void pre_order(BTree<T>*); //前序遍历
	void mid_order(BTree<T>*); //中序遍历
	void last_order(BTree<T>*); //后序遍历
	BTree<T>* get_node(T); //获取值的结点
	BTree<T>* get_root(); //获取头节点
	bool insert_value(T); //对外插入值函数
	int get_value_height(T); //获取某个值的高度
	T search_minimun(BTree<T>*); //查找节点最小值
	T search_maxmun(BTree<T>*); //查找结点最大值
	T search_maxmun_root(); //查找最大值
	T search_minimun_root(); //查找最小值
};
template <typename T>
T AVLTree<T>::search_maxmun(BTree<T>* pnode) {
	if (pnode->rchild != nullptr)
		return search_maxmun(pnode->rchild);
	return pnode->value;
}
template <typename T>
T AVLTree<T>::search_maxmun_root() {
	return search_maxmun(root);
}
template <typename T>
T AVLTree<T>::search_minimun_root() {
	return search_minimun(root);
}
template <typename T>
T AVLTree<T>::search_minimun(BTree<T>* pnode) {
	if (pnode->lchild != nullptr)
		return search_minimun(pnode->lchild);
	return pnode->value;
}
template <typename T>
int AVLTree<T>::get_value_height(T value) {
	return get_height(get_node(value));
}
template <typename T>
void AVLTree<T>::rotate_right(BTree<T>* &p_node) {
	BTree<T> *left = p_node->lchild;
	p_node->lchild = left->rchild;
	left->rchild = p_node;
	left->height = max_int(get_height(left->lchild), get_height(left->rchild)) + 1;
	p_node->height = max_int(get_height(p_node->lchild), get_height(p_node->rchild)) + 1;
	p_node = left;
}
template <typename T>
void AVLTree<T>::rotate_left(BTree<T>* &p_node) {
	BTree<T> *right = p_node->rchild;
	p_node->rchild = right->lchild;
	right->lchild = p_node;
	right->height = max_int(get_height(right->lchild), get_height(right->rchild)) + 1;
	p_node->height = max_int(get_height(p_node->lchild), get_height(p_node->rchild)) + 1;
	p_node = right;
}
template <typename T>
bool AVLTree<T>::insert_value(T value) {
	return insert(value, root);
}
template <typename T>
int AVLTree<T>::max_int(int a, int b) {
	return a >= b ? a : b;
}
template <typename T>
int AVLTree<T>::get_height(BTree<T>* p_node) {
	if (p_node != nullptr) {
		return p_node->height;
	}
	else {
		return -1;
	}
}
template <typename T>
bool AVLTree<T>::insert(T value, BTree<T>* &p_node) {
	if (p_node == nullptr) {
		p_node = new BTree<T>(value);
	}
	else if (value > p_node->value) {
		insert(value, p_node->rchild);
		if (get_height(p_node->rchild) - get_height(p_node->lchild) == 2) {
			if (value > p_node->rchild->value) {
				rotate_left(p_node);
			}
			else if (value < p_node->rchild->value) {
				rotate_right(p_node->rchild);
				rotate_left(p_node);
			}
		}
	}
	else if (value < p_node->value) {
		insert(value, p_node->lchild);
		if (get_height(p_node->lchild) - get_height(p_node->rchild) == 2) {
			if (value < p_node->lchild->value) {
				rotate_right(p_node);
			}
			else if (value > p_node->lchild->value)  {
				rotate_left(p_node->lchild);
				rotate_right(p_node);
			}
		}
	}
	p_node->height = max_int(get_height(p_node->lchild), get_height(p_node->rchild)) + 1;
	return true;
}
template <typename T>
void AVLTree<T>::destroy(BTree<T>* pnode) {
	if (pnode != nullptr) {
		if (pnode->lchild != nullptr) {
			destroy(pnode->lchild);
		}
		if (pnode->rchild != nullptr) {
			destroy(pnode->rchild);
		}
		delete pnode;
		pnode = nullptr;
	}
}
template <typename T>
void AVLTree<T>::pre_order(BTree<T>* node) {
	if (node != nullptr) {
		std::cout << node->value << ' ';
		pre_order(node->lchild);
		pre_order(node->rchild);
	}
}
template <typename T>
void AVLTree<T>::mid_order(BTree<T>* node) {
	if (node != nullptr) {
		mid_order(node->lchild);
		std::cout << node->value << ' ';
		mid_order(node->rchild);
	}
}
template <typename T>
void AVLTree<T>::last_order(BTree<T>* node) {
	if (node != nullptr) {
		last_order(node->lchild);
		last_order(node->rchild);
		std::cout << node->value << ' ';
	}
}
template <typename T>
BTree<T>* AVLTree<T>::get_node(T key) {
	BTree<T>* pnode = root;
	while (pnode != nullptr && pnode->value != key) {
		if (pnode->value > key) {
			pnode = pnode->lchild;
		}
		else {
			pnode = pnode->rchild;
		}
	}
	return pnode;
}
template <typename T>
BTree<T>* AVLTree<T>::get_root() {
	return root;
}
#endif // _CHAIN_AVL_BINARY_TREE_H