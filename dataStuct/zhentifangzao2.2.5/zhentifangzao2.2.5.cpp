// zhentifangzao2.2.5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
struct LNode
{
  int data;
  LNode *next;
};
void ceatelistR(LNode *&C, int a[], int n) {
  LNode *s, *r; // s用来指向新申请的结点,r始终指向C的终端结点
  int i;
  C = (LNode *)malloc(sizeof(LNode)); // 申请C的头结点空间
  C->next = NULL;
  r = C; // r指向头结点，因为此时头结点就是终端结点。
  for (i = 0; i < n; i++) {
    s = (LNode *)malloc(sizeof(LNode));
    s->data = a[i];
    r->next = s;
    r = r->next;
  }
  r->next = NULL;
}
void initData(int(&temp)[100], int num) {
  for (int i = 0; i < num; i++) {
    std::cin >> temp[i];
  }
}
 void find(LNode *&c, LNode *&C, int data) {
   LNode *a = (LNode *)malloc(sizeof(LNode));
   a->next = NULL;
  while (c->next != NULL && c->data != data) {
    if (c->data < data) {
      c = c->next;
    }
    else {
      break;
    }
  }
  if (c->data == data) {
    C->data = data;
    C->next = a;
    c = c->next;
  }
}
void handle(LNode *A, LNode *B, LNode *& R) {
  LNode *a, *b, *T;
  T = R;
  a = A->next;
  b = B->next;
  while (b->next != NULL && a->next != NULL) {
    find(b, T, a->data);
    a = a->next;
  }
  if (b->next == NULL && b->data == a->data) {
    a = a->next;
  }
  if (a->next != NULL) {
    T->next = a;
  }
}
int main()
{
  LNode *A, *B, *R;
  R = (LNode *)malloc(sizeof(LNode));
  R->next = NULL;
  int a, b;
  int aList[100], bList[100];
  std::cin >> a >> b;
  initData(aList, a);
  initData(bList, b);
  ceatelistR(A, aList, a);
  ceatelistR(B, bList, b);
   handle(A, B, R);
  while (R->next != NULL) {
    R = R->next;
    std::cout << R->data << ',';
  }
  return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
