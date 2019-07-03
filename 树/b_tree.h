#pragma once
#ifndef _B_TREE_
#define _B_TREE_
#include <string>
template <typename T>
class BTree
{
public:
	T value;
	int weight;
	int height;
	std::string huff_code;
	BTree<T>* lchild;
	BTree<T>* rchild;
	BTree<T>* parent;
public:
	BTree() {
		lchild = nullptr;
		rchild = nullptr;
		parent = nullptr;
		height = 0;
		huff_code = "";
	};
	BTree(T t, int weight = 0)
		: value(t), lchild(nullptr), rchild(nullptr), parent(nullptr), height(0), weight(weight), huff_code(""){}
	BTree(T t, BTree<T>* lchild, BTree<T>* rchild, int height, int weight)
		: value(t), lchild(lchild), rchild(rchild), parent(nullptr), height(height), weight(weight), huff_code(""){}
};
#endif // _B_TREE_
