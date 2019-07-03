#pragma once
#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include "b_tree.h"
#include<algorithm>
#include <deque>
template <typename T>
class HuffmanTree : protected BTree<T> {
private:
	BTree<T>* root; //哈夫曼树头结点
	std::deque<BTree<T>*> forest; //森林
	void destory(BTree<T>*);
	void calculate_huffcode(BTree<T>* &, std::string); //计算哈夫曼编码
public:
	HuffmanTree() {
		root = nullptr;
	}
	~HuffmanTree() {
		destory(root);
	}
	BTree<T>* get_root(); //获取头节点
	void init_tree(T [], int);
	void pre_order(BTree<T>*); //前序遍历
	void mid_order(BTree<T>*); //中序遍历
	void last_order(BTree<T>*); //后序遍历
};
template <typename T>
void HuffmanTree<T>::calculate_huffcode(BTree<T>* &p_node, std::string code) {
	if (p_node != nullptr) {
		p_node->huff_code = code;
		code += "0";
		calculate_huffcode(p_node->lchild, code);
		code.pop_back();
		code += "1";
		calculate_huffcode(p_node->rchild, code);
	}
}
template <typename T>
void HuffmanTree<T>::pre_order(BTree<T>* node) {
	if (node != nullptr) {
		std::cout << node->value << ' ';
		pre_order(node->lchild);
		pre_order(node->rchild);
	}
}
template <typename T>
void HuffmanTree<T>::mid_order(BTree<T>* node) {
	if (node != nullptr) {
		mid_order(node->lchild);
		std::cout << node->value << ' ';
		mid_order(node->rchild);
	}
}
template <typename T>
void HuffmanTree<T>::last_order(BTree<T>* node) {
	if (node != nullptr) {
		last_order(node->lchild);
		last_order(node->rchild);
		std::cout << node->value << ' ';
	}
}
template <typename T>
BTree<T>* HuffmanTree<T>::get_root() {
	return root;
}
template <typename T>
void HuffmanTree<T>::init_tree(T a[], int size) {
	for (int i = 0; i < size;i++) {
		BTree<T>* tmp = new BTree<T>(a[i], a[i]);
		forest.push_back(tmp);
	}
	while (forest.size() > 1) {
		//排序，以选出根节点权值最小两棵树
		stable_sort(forest.begin(), forest.end(), [](BTree<T>* a, BTree<T>*b) {return a->weight < b->weight; });
		BTree<T>* node = new BTree<T>(forest[0]->weight + forest[1]->weight, forest[0], forest[1], forest[0]->height + 1, forest[0]->weight + forest[1]->weight);
		forest.push_back(node);
		forest.pop_front();
		forest.pop_front();
	}
	root = forest.front();
	forest.clear();
	calculate_huffcode(root, "");
}
template <typename T>
void HuffmanTree<T>::destory(BTree<T>* p_node) {
	if (p_node != nullptr) {
		if (p_node->lchild != nullptr) {
			destory(p_node->lchild);
		}
		if (p_node->rchild != nullptr) {
			destory(p_node->rchild);
		}
		delete p_node;
		p_node = nullptr;
	}
}
#endif // _HUFFMAN_TREE_H