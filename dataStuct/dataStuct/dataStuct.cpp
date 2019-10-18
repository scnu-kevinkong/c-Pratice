// dataStuct.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

struct Sqlist
{
  int data[100];
  int length;
};
void initList(Sqlist *L, int a[], int size) {
  L->length = size;
  int i;
  for (i = 0; i < size; i++) {
    L->data[i] = a[i];
  }
};
int merge(Sqlist *L, int l, int r, int lsize, int rsize, Sqlist *R, int &rindex) {
  if (l < 0 || r < 0 || l > r || r > rsize) return -1;
  while (l <= lsize && r <= rsize) {
    if (L->data[l] <= L->data[r]) {
      R->data[rindex] = L->data[l];
      l++;
      rindex++;
    }else {
      R->data[rindex] = L->data[r];
      r++;
      rindex++;
    }
  }
  rindex--;
  if (l > lsize) {
    for (int temp = r; temp < L->length; temp++) {
      R->data[rindex] = L->data[temp];
      rindex++;
    }
  }
  else {
    for (int temp = l; temp < lsize; temp++) {
      R->data[rindex] = L->data[temp];
      rindex++;
    }
  }
}
int main()
{
  Sqlist *M = (Sqlist*)malloc(sizeof(Sqlist));
  Sqlist *R = (Sqlist*)malloc(sizeof(Sqlist));
  int l, r;
  std::cin >> l >> r;
  int m[1000];
  int rarr[1000];
  for (int i = 0; i < l + r; i++) {
    std::cin >> m[i];
  }
  initList(M, m, l+r);
  initList(R, rarr, l+r);
  int rindex;
  rindex = 0;
  merge(M, 0, l, l, l + r, R, rindex);
  for (int i = 0; i < R->length; i++) {
    std::cout << R->data[i] << '\n';
  }
  system("Pause");
  return 1;
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
