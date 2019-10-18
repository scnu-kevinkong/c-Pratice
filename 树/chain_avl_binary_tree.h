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
	bool del_node_func(BTree<T>* &, T); //删除结点
public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
		destroy(root);
	}
	void destroy(BTree<T>*); //销毁全部结点
	bool del_node(T); //删除值结点
	void pre_order(BTree<T>*); //前序遍历
	void mid_order(BTree<T>*); //中序遍历
	void last_order(BTree<T>*); //后序遍历
	BTree<T>* get_node(T); //获取值的结点
	BTree<T>* get_root(); //获取头节点 
	bool insert_value(T); //对外插入值函数
	int get_value_height(T); //获取某个值的高度
	BTree<T>* search_minimun(BTree<T>*); //查找最小值节点
	BTree<T>* search_maxmun(BTree<T>*); //查找最大值结点
	T search_maxmun_root(); //查找最大值
	T search_minimun_root(); //查找最小值
};
template <typename T>
bool AVLTree<T>::del_node_func(BTree<T>* & p_node, T value) {
	// 值为空，返回
	if (p_node == nullptr)
		return false;
	else if (p_node->value > value) {
		// 值小于结点当前值，继续递归删除结点左孩子
		del_node_func(p_node->lchild, value);
		// 递归回来后，树不平衡
		// 右边树大于左边的树，且相差为2
		if (get_height(p_node->rchild) - get_height(p_node->lchild) == 2) {
			BTree<T>* right_tree = p_node->rchild;
			if (get_height(right_tree->rchild) > get_height(right_tree->lchild)) {
				rotate_left(p_node);
			}
			else {
				rotate_right(right_tree);
				rotate_left(p_node);
			}
		}
	}
	else if (p_node->value < value) {
		// 值大于结点当前值，继续递归删除结点右孩子
		del_node_func(p_node->rchild, value);
		// 递归回来后，树不平衡
		// 左边树大于右边的树，且相差为2
		if (get_height(p_node->lchild) - get_height(p_node->rchild) == 2) {
			BTree<T>* left_tree = p_node->lchild;
			if (get_height(left_tree->lchild) > get_height(left_tree->rchild)) {
				rotate_right(p_node);
			}
			else {
				rotate_left(left_tree);
				rotate_right(p_node);
			}
		}
	}
	else {
		if (p_node->lchild != nullptr && p_node->rchild != nullptr) {
			// 如果tree的左子树比右子树高；
			// 则(01)找出tree的左子树中的最大节点
			//   (02)将该最大节点的值赋值给tree。
			//   (03)删除该最大节点。
			// 这类似于用"tree的左子树中最大节点"做"tree"的替身
			 // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
			if (get_height(p_node->lchild) > get_height(p_node->rchild)) {
				BTree<T>* max_left = search_maxmun(p_node->lchild);
				p_node->value = max_left->value;
				del_node_func(p_node->lchild, max_left->value);
			}
			else {
				// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				// 则(01)找出tree的右子树中的最小节点
				//   (02)将该最小节点的值赋值给tree。
				//   (03)删除该最小节点。
				// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
				BTree<T>* min_right = search_minimun(p_node->rchild);
				p_node->value = min_right->value;
				del_node_func(p_node->rchild, min_right->value);
			}
		}
		else {
			BTree<T>* tmp = p_node;
			p_node = p_node->lchild == nullptr ? p_node->rchild : p_node->lchild;
			delete tmp;
		}
	}
	return true;
}
template <typename T>
bool AVLTree<T>::del_node(T value) {
	BTree<T>* p_node = get_node(value);
	if (p_node != nullptr) {
		return del_node_func(root, value);
	}
	else
		return false;
}
template <typename T>
BTree<T>* AVLTree<T>::search_maxmun(BTree<T>* pnode) {
	if (pnode->rchild != nullptr)
		return search_maxmun(pnode->rchild);
	return pnode;
}
template <typename T>
T AVLTree<T>::search_maxmun_root() {
	return search_maxmun(root)->value;
}
template <typename T>
T AVLTree<T>::search_minimun_root() {
	return search_minimun(root)->value;
}
template <typename T>
BTree<T>* AVLTree<T>::search_minimun(BTree<T>* pnode) {
	if (pnode->lchild != nullptr)
		return search_minimun(pnode->lchild);
	return pnode;
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
		// 如果值大于结点，插入到右孩子
		insert(value, p_node->rchild);
		// 如果右边树不平衡
		if (get_height(p_node->rchild) - get_height(p_node->lchild) == 2) {
			// 值比右孩子的值大，RR结构，需要结点左旋
			if (value > p_node->rchild->value) {
				rotate_left(p_node);
			}
			// 值比右孩子的值小，RL结构，需要先把右孩子右旋，再结点左旋
			else if (value < p_node->rchild->value) {
				rotate_right(p_node->rchild);
				rotate_left(p_node);
			}
		}
	}
	else if (value < p_node->value) {
		// 如果值小于结点，插入到左孩子
		insert(value, p_node->lchild);
		// 如果左边树不平衡
		if (get_height(p_node->lchild) - get_height(p_node->rchild) == 2) {
			// 值比左孩子的值小，LL结构，需要结点右旋
			if (value < p_node->lchild->value) {
				rotate_right(p_node);
			}
			// 值比左孩子的值大，LR结构，需要先把左孩子左旋，再结点右旋
			else if (value > p_node->lchild->value)  {
				rotate_left(p_node->lchild);
				rotate_right(p_node);
			}
		}
	}
	// 自底向上根据左右孩子的最大高度+1，赋值到当前结点高度
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
		else 
		{
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