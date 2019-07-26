#pragma once
#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
// 递归
template <typename T>
int half_find_recursion(T data[], int left, int right, T target) {
	if (left > right)
		return -1;
	int mid = left + (right - left) / 2; // 防止整数溢出问题
	if (data[mid] > target) {
		return half_find_recursion(data, left, mid - 1, target);
	}
	else if (data[mid] < target) {
		return half_find_recursion(data, mid + 1, right, target);
	}
	else {
		return mid;
	}
}
// 非递归
template <typename T>
int half_find(T data[], int left, int right, T target) {
	while (left <= right) {
		int mid = left + (right - left) / 2; // 防止整数溢出问题
		if (data[mid] > target) {
			right = mid - 1;
		}
		else if (data[mid] < target) {
			left = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}
#endif // BINARY_SEARCH_H