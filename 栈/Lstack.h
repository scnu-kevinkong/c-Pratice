#pragma once
#include<iostream>
using namespace std;
struct LNode {
	LNode *next;
	int data;
};
class LStack {
	LNode *head;
public:
	LStack() {
		head = new LNode;
		head->next = NULL;
	}
	int is_empty();
	void push(int);
	int pop();
	void show_data();
};
int LStack::is_empty() {
	if (head->next == NULL) {
		return 1;
	}
	else {
		return -1;
	}
}
void LStack::push(int x) {
	LNode *p = new LNode;
	p->next = head->next;
	p->data = x;
	head->next = p;
}
int LStack::pop() {
	if (head->next == NULL) {
		return -1;
	}
	LNode *p = head->next;
	head->next = p->next;
	free(p);
	return 1;
}
void LStack::show_data() {
	LNode *p = head->next;
	int i = 0;
	while (p != NULL) {
		if (i % 4 == 0 && i > 0) {
			cout << p->data << endl;
		}
		else {
			cout << p->data << '\t';
		}
		i++;
		p = p->next;
	}
}