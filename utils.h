#pragma once
// ��ȡ���鳤��
template <typename T>
int length(T &arr) {
	return sizeof(arr) / sizeof(arr[0]);
}