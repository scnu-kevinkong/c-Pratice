#pragma once
#ifndef SWITCH_SORT_H
#define SWITCH_SORT_H
template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
// 从小到大，冒泡排序
template <typename T>
void bubble_sort(T *arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) {
				swap(arr[i], arr[j]);
			}
		}
	}
}
template <typename T>
/*序列划分函数*/
int  partition(T* arr, int p, int r) {
	int key = arr[p];//取第一个
	int i = r;
	for (int j = p + 1; j <= i; j++)
	{
		if (arr[j] > key)
		{
			//i一直代表小于key元素的最后一个索引，当发现有比key小的a[j]时候，i+1 后交换         
			swap(arr[i], arr[j]);
			i--;
		}
	}
	swap(arr[i], arr[p]);//将key切换到中间来，左边是小于key的，右边是大于key的值。
	return i;
}
template <typename T>
// 从小到大，基本快速排序
void quick_sort(T *arr, int left, int right) {
	int position = 0;
	if (left < right) {
		position = partition(arr, left, right);//返回划分元素的最终位置
		quick_sort(arr, left, position - 1); //划分左边递归
		quick_sort(arr, position + 1, right); //划分右边递归
	}
}
#endif // SWITCH_SORT_H