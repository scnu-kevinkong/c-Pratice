#pragma once
#include <iostream>
using namespace std;
class Sqlist {
	int *data;
	int length;
	int max_size;
public:
	Sqlist() {
		data = new int[100];
		length = 0;
		max_size = 100;
	}
	Sqlist(int maxSize, int arr[]) {
		data = new int[maxSize];
		while (*arr > 0) {
			data[length] = *arr;
			length++;
			arr++;
		}
	}
	~Sqlist() {
		delete[] data;
	}
	int find_elem(int);
	int get_elem(int);
	int insert_elem(int, int);
	int delete_elem(int);
	void sqlist_show();
};
int Sqlist::find_elem(int e) {
	for (int i = 0; i < length; i++) {
		if (data[i] == e) {
			return i;
		}
	}
	return -1;
}
int Sqlist::get_elem(int p) {
	if (p < 0 || p > length - 1) {
		return -1;
	}
	return data[p];
}
int Sqlist::insert_elem(int p, int e) {
	if (p < 0 || p > length || length == max_size) {
		return -1;
	 }
	for (int i = length - 1; i >= p; i--) {
		data[i + 1] = data[i];
	}
	data[p] = e;
	++length;
	return 1;
}
int Sqlist::delete_elem(int p) {
	if (p < 0 || p > length - 1) {
		return -1;
	}
	for (int i = p; i < length - 1; i++) {
		data[i] = data[i + 1];
	}
	--length;
	return 1;
}
void Sqlist::sqlist_show() {
	for (int i = 0; i < length; i++) {
		cout << data[i] << '\t';
	}
	cout << endl;
}
