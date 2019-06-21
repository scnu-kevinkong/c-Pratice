#pragma once
#ifndef _B_TREE_
#define _B_TREE_
template <typename T>
class BTree
{
public:
	T value;
	int height;
	BTree<T>* lchild;
	BTree<T>* rchild;
	BTree<T>* parent;
public:
	BTree() {
		lchild = nullptr;
		rchild = nullptr;
		parent = nullptr;
		height = 0;
	};
	BTree(T t)
		: value(t), lchild(nullptr), rchild(nullptr), parent(nullptr), height(0) {}
};
#endif // _B_TREE_
