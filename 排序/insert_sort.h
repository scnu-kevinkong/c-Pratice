#pragma once
#pragma once
#ifndef INSERT_SORT_H
#define INSERT_SORT_H
#include <stdio.h>
template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
template <typename T>
void swap_array(T *arr_1, T *arr_2, int size) {
	for (int i = 0; i < size; i++) {
		swap(arr_1[i], arr_2[i]);
	}
}
template <typename T>
void insert_value(T* arr, T value, int index, int size) {
	for (int i = size; i > index; i--) {
		arr[i] = arr[i - 1];
	}
	arr[index] = value;
}
// 从小到大
template <typename T>
void insert_sort(T *arr, int size) {
	T *temp = new T[size];
	std::fill(temp, temp + size, NULL);
	if (size > 1) {
		temp[0] = arr[0];
		int index = 1;
		while (index < size) {
			int i = 0;
			for (i; i <= index - 1; i++) {
				if (temp[i] > arr[index]) {
					break;
				}
			}
			insert_value(temp, arr[index], i, index);
			index++;
		}
	}
	swap_array(arr, temp, size);
	delete[]temp;
}
template <typename T>
int binary_search(T* arr, int left, int right, T value) {
	if (left > right)
		return left;
	int mid = left + (right - left) / 2; // 防止整数溢出问题
	if (arr[mid] > value) {
		return binary_search(arr, left, mid - 1, value);
	}
	else if (arr[mid] < value) {
		return binary_search(arr, mid + 1, right, value);
	}
}
template <typename T>
int binary_search_shift(T* arr, int left, int right, T value) {
	if (left > right)
		return left;
	int mid = left + (right - left) / 2; // 防止整数溢出问题
	if (arr[mid] < value) {
		return binary_search_shift(arr, left, mid - 1, value);
	}
	else if (arr[mid] > value) {
		return binary_search_shift(arr, mid + 1, right, value);
	}
}
// 从小到大,二分查找插入
template <typename T>
void insert_sort_binary(T *arr, int size) {
	T *temp = new T[size];
	std::fill(temp, temp + size, NULL);
	if (size > 1) {
		temp[0] = arr[0];
		int index = 1;
		while (index < size) {
			int left = binary_search(temp, 0, index - 1, arr[index]);
			insert_value(temp, arr[index], left, index);
			index++;
		}
	}
	swap_array(arr, temp, size);
	delete[]temp;
}
// 从大到小,二分查找插入
template <typename T>
void insert_sort_binary_shift(T *arr, int size) {
	T *temp = new T[size];
	std::fill(temp, temp + size, NULL);
	if (size > 1) {
		temp[0] = arr[0];
		int index = 1;
		while (index < size) {
			int left = binary_search_shift(temp, 0, index - 1, arr[index]);
			insert_value(temp, arr[index], left, index);
			index++;
		}
	}
	swap_array(arr, temp, size);
	delete[]temp;
}
// 从大到小
template <typename T>
void insert_sort_shift(T *arr, int size) {
	T *temp = new T[size];
	std::fill(temp, temp + size, NULL);
	if (size > 1) {
		temp[0] = arr[0];
		int index = 1;
		while (index < size) {
			int i = 0;
			for (i; i <= index - 1; i++) {
				if (temp[i] < arr[index]) {
					break;
				}
			}
			insert_value(temp, arr[index], i, index);
			index++;
		}
	}
	swap_array(arr, temp, size);
	delete[]temp;
}
// 从小到大,希尔排序
template <typename T>
void shell_insort(T *arr, int size) {
	if (size > 1) {
		for (int gap = size / 2; gap > 0; gap /= 2) {
			for (int index = gap; index < size; index++) {
				T insert_value = arr[index];
				int i = index;
				while (i >= gap && insert_value < arr[i - gap]) {
					arr[i] = arr[i - gap];
					i -= gap;
				}
				arr[i] = insert_value;
			}
		}
	}
}
// 从大到小,希尔排序
template <typename T>
void shell_insort_shift(T *arr, int size) {
	if (size > 1) {
		for (int gap = size / 2; gap > 0; gap /= 2) {
			for (int index = gap; index < size; index++) {
				T insert_value = arr[index];
				int i = index;
				while (i >= gap && insert_value > arr[i - gap]) {
					arr[i] = arr[i - gap];
					i -= gap;
				}
				arr[i] = insert_value;
			}
		}
	}
}
#endif // INSERT_SORT_H