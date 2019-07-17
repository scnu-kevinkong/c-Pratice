#pragma once
#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H
#include "graph_edge.h"
template<typename T>
class JBMinHeap
{
	friend bool operator < (const Edge<T> & left, const Edge<T> & right);
	friend bool operator <= (const Edge<T> & left, const Edge<T> & right);
	friend bool operator > (const Edge<T> & left, const Edge<T> & right);
	friend bool operator >= (const Edge<T> & left, const Edge<T> & right);
private:
	//申请堆空间
	T *_minHeap = nullptr;
	int _index, _maxSize;
public:
	JBMinHeap(int maxSize) {
		_maxSize = maxSize;
		_minHeap = new T[_maxSize];
		_index = -1;
	}
	JBMinHeap(JBMinHeap &h) {
		_index = h._index;
		_maxSize = h._maxSize;
		_minHeap = new T[_maxSize];
		for (int i = 0; i < _maxSize;i++) {
			*_minHeap[i] = *h._minHeap[i];
		}
	}
	~JBMinHeap() {
		delete[]_minHeap;
	}
	//获取整个最小堆的头部指针
	T  getMinHeap() {
		return _minHeap[0];
	}
	//判断堆是不是空的
	bool isEmpty() {
		return _index == -1;
	}
	bool isFull() {
		return _index == _maxSize;
	}
	//堆进行向下调整
	void adjustDown(int index);
	//队进行向上调整
	void adjustUp(int index);
	bool add(T x) {
		if (isFull()) {
			return false;
		}
		_index++;
		_minHeap[_index] = x;
		adjustUp(_index);
		return true;
	}
	//建堆运算
	void createMinHeap() {
		if (isEmpty()) {
			return;
		}
		for (int i = (_index - 1) / 2; i > -1; i--) {//直接从倒数第二层 逐层向下调整
			adjustDown(i);
		}
	}
	bool pop() {
		if (isEmpty()) {
			return false;
		}
		_minHeap[0] = _minHeap[_index];
		_index--;
		adjustDown(0);
		return true;
	}
};
template<typename T>
void JBMinHeap<T>::adjustDown(int index) {
	if (isEmpty()) {
		return;
	}
	while (index < _index)
	{
		T temp = _minHeap[index];//将当前索引的位置的值保存下来
		int oneC = 2 * index + 1;//获取到两个孩子的位置
		int twoC = 2 * index + 2;
		if (oneC == _index && _minHeap[oneC] < _minHeap[index]) {//若第一个孩子是整个堆最后一个位置，并且小于头结点 则直接执行交换操作并结束执行
			_minHeap[index] = _minHeap[oneC];
			_minHeap[oneC] = temp;
			return;
		}
		if (twoC > _index) {//如果第二个孩子的索引位置越界 结束执行
			return;
		}
		if (_minHeap[oneC] <= _minHeap[twoC]) {//正常情况的数据交互执行
			if (temp > _minHeap[oneC]) {
				_minHeap[index] = _minHeap[oneC];
				_minHeap[oneC] = temp;
				index = oneC;
			}
			else {//如果该处索引值已经是比两个孩子小 则结束循环
				index = _index;
			}
		}
		else
		{
			if (temp > _minHeap[twoC]) {
				_minHeap[index] = _minHeap[twoC];
				_minHeap[twoC] = temp;
				index = twoC;
			}
			else
			{
				index = _index;
			}
		}
	}
}
template<typename T>
void JBMinHeap<T>::adjustUp(int index) {
	if (index > _index) {//大于堆的最大值直接return
		return;
	}
	while (index > -1)
	{
		T temp = _minHeap[index];
		int father = (index - 1) / 2;
		if (father >= 0) {//若果索引没有出界就执行想要的操作
			if (temp < _minHeap[father]) {
				_minHeap[index] = _minHeap[father];
				_minHeap[father] = temp;
				index = father;
			}
			else {//若果已经是比父亲大 则直接结束循环
				index = -1;
			}
		}
		else//出界就结束循环
		{
			index = -1;
		}
	}
}
template<typename T>
bool operator < (Edge<T> &left, Edge<T> &right) {
	return left.weight < right.weight;
}
template<typename T>
bool operator <= (const Edge<T> &left, const Edge<T> &right) {
	return left.weight <= right.weight;
}
template<typename T>
bool operator > (const Edge<T> &left, const Edge<T> &right) {
	return left.weight > right.weight;
}
template<typename T>
bool operator >= (const Edge<T> &left, const Edge<T> &right) {
	return left.weight >= right.weight;
}
#endif // _MIN_HEAP_H