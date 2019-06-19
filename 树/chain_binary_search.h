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
	BTree<T>* get_node(T); //获取值的结点
	BTree<T>* get_root(); //获取头节点
	bool remove_node(T); //删除指定结点
	T search_minimun(BTree<T>*); //查找节点最小值
	T search_maxmun(BTree<T>*); //查找结点最大值
	T search_maxmun_root(); //查找最大值
	T search_minimun_root(); //查找最小值
	bool remove(BTree<T>*); //删除
	BTree<T>* predecessor(BTree<T>*); //获取节点的前驱
	BTree<T>* successor(BTree<T>*); //获取节点的后继
	void destroy(BTree<T>*); //销毁二叉树
	BSTree() {
		root = nullptr;
	}
	~BSTree() {
		destroy(root);
	}
};
template <typename T>
void BSTree<T>::destroy(BTree<T>* pnode) {
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
T BSTree<T>::search_maxmun(BTree<T>* pnode) {
	if (pnode->rchild != nullptr)
		return search_maxmun(pnode->rchild);
	return pnode->value;
}
template <typename T>
T BSTree<T>::search_maxmun_root() {
	return search_maxmun(root);
}
template <typename T>
T BSTree<T>::search_minimun_root() {
	return search_minimun(root);
}
template <typename T>
T BSTree<T>::search_minimun(BTree<T>* pnode) {
	if (pnode->lchild != nullptr)
		return search_minimun(pnode->lchild);
	return pnode->value;
}
template <typename T>
bool BSTree<T>::remove(BTree<T>* p_del) {
	BTree<T>* pnode = nullptr;
	if (p_del->lchild == nullptr || p_del->rchild == nullptr)
		pnode = p_del;	//情况二三：被删除的节点只有左子树或右子树，或者没有孩子
	else
		pnode = predecessor(p_del);
	//此时，被删节点只有一个孩子（或没有孩子）.保存该孩子指针
	BTree<T>* p_child = nullptr;
	if (pnode->lchild != nullptr) {
		p_child = pnode->lchild;
	}
	else {
		p_child = pnode->rchild;
	}
	//让孩子指向被删除节点的父节点
	if (p_child != nullptr) {
		p_child->parent = pnode->parent;
	}
	//如果要删除的节点是头节点，注意更改root的值
	if (pnode->parent == nullptr) {
		root = p_child;
	}
	//如果要删除的节点不是头节点，要注意更改它的双亲节点指向新的孩子节点
	else if (pnode->parent->rchild == pnode) {
		pnode->parent->rchild = p_child;
	}
	else {
		pnode->parent->lchild = p_child;
	}
	if (p_del->value != pnode->value) {
		p_del->value = pnode->value;
	}
	delete pnode;
	return true;
}
template <typename T>
bool BSTree<T>::remove_node(T key) {
	BTree<T>* p_del = get_node(key);
	if (p_del != nullptr) {
		return remove(p_del);
	}
	else {
		return false;
	}
}
template <typename T>
BTree<T>* BSTree<T>::get_node(T key) {
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
BTree<T>* BSTree<T>::successor(BTree<T>* pnode) {
	if (pnode->rchild != nullptr) {
		pnode = pnode->rchild;
		while (pnode->lchild != nullptr) {
			pnode = pnode->lchild;
		}
		return pnode;
	}
	BTree<T>* parrent = pnode->parent;
	while (parrent != nullptr && parrent->rchild == pnode) {
		pnode = parrent;
		parrent = parrent->parent;
	}
	return parrent;
}
template <typename T>
BTree<T>* BSTree<T>::predecessor(BTree<T>* pnode) {
	if (pnode->lchild != nullptr) {
		pnode = pnode->lchild;
		while (pnode->rchild != nullptr) {
			pnode = pnode->rchild;
		}
		return pnode;
	}
	BTree<T>* parrent = pnode->parent;
	while (parrent != nullptr && parrent->lchild == pnode) {
		pnode = parrent;
		parrent = parrent->parent;
	}
	return parrent;
}
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
			pnode->parent = father;
		}
		else if (value > father->value) {
			father->rchild = pnode;
			pnode->parent = father;
		}
	}//则新节点为根
	return true;
}
template <typename T>
void BSTree<T>::pre_order(BTree<T>* node) {
	if (node != nullptr) {
		std::cout << node->value << ' ';
		pre_order(node->lchild);
		pre_order(node->rchild);
	}
}
template <typename T>
void BSTree<T>::mid_order(BTree<T>* node) {
	if (node != nullptr) {
		mid_order(node->lchild);
		std::cout << node->value << ' ';
		mid_order(node->rchild);
	}
}
template <typename T>
void BSTree<T>::last_order(BTree<T>* node) {
	if (node != nullptr) {
		last_order(node->lchild);
		last_order(node->rchild);
		std::cout << node->value << ' ';
	}
}
template <typename T>
BTree<T>* BSTree<T>::get_root() {
	return root;
}
#endif // _CHAIN_BINARY_SEARCH_TREE_H