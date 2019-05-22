#pragma once
#include<iostream>
using namespace std;
struct LNode {
	LNode *next;
	char data;
};
class LStack {
	LNode *head;
public:
	LStack() {
		head = new LNode;
		head->next = NULL;
	}
	int is_empty();
	void push(char);
	char pop();
	void show_data();
	char get_value();
};
int LStack::is_empty() {
	if (head->next == NULL) {
		return 1;
	}
	else {
		return -1;
	}
}
void LStack::push(char x) {
	LNode *p = new LNode;
	p->next = head->next;
	p->data = x;
	head->next = p;
}
char LStack::pop() {
	if (head->next == NULL) {
		return '$';
	}
	LNode *p = head->next;
	char ch = p->data;
	head->next = p->next;
	free(p);
	return ch;
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
char LStack::get_value() {
	int isEmpty = is_empty();
	if (isEmpty == -1) {
		return head->next->data;
	}
	else {
		return '$';
	}
}