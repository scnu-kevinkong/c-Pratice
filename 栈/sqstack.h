#pragma once
#include <iostream>
using namespace std;
class SqStack {
	char *data;
	int top;
	int maxSize;
public:
	SqStack() {
		maxSize = 100;
		top = -1;
		data = new char[maxSize];
	}
	SqStack(int max, char arr[]) {
		maxSize = max;
		data = new char[max];
		while (*arr > 0) {
			top++;
			data[top] = *arr;
			arr++;
		}
	}
	~SqStack() {
		delete[] data;
	}
	bool is_empty();
	bool push(int);
	char pop();
	char getValue();
	void show_data();
};
bool SqStack::is_empty() {
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}
bool SqStack::push(int x) {
	if (top == maxSize - 1) {
		return false;
	}
	top++;
	data[top] = x;
	return true;
}
char SqStack::pop() {
	if (top == -1) {
		return -1;
	}
	char x = data[top];
	top--;

	return x;
}
void SqStack::show_data() {
	for (int i = 0; i <= top; i++) {
		if (i % 5 == 0 && i>0) {
			cout << data[i]<<endl;
		}
		else {
			cout << data[i] << '\t';
		}
	}
}
char SqStack::getValue() {
	return data[top];
}