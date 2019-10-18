#pragma once
// 获取数组长度
template <typename T>
int length(T &arr) {
	return sizeof(arr) / sizeof(arr[0]);
}