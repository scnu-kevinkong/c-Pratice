#pragma once
#ifndef MERGE_SORT_H
#define MERGE_SORT_H
template <typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
//二路一次归并过程的算法
//left为本次二路归并排序的第1有序区的第1个元素，i指向第1个元素, mid为第1有序区的最后1个元素
template <typename T>
void binary_merge(T *arr, int left, int mid, int right) {
	//mid+1为第2有序区第1个元素，mid为第1有序区的最后1个元素
	//i 指向第 1 有序区的第 1 个元素
	int i = left;
	//j 指向第 2 有序区的第 1 个元素，high 为第 2 有序区的最后一个元素
	int j = mid + 1;
	//temp数组暂存合并的有序序列
	T *temp = new T[right - left + 1];
	//设置临时数组的指示标志 k
	int k = 0;
	noexcept(temp);
	//顺序选取两个有序区的较小元素，存储到t数组中，因为是递增排序
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	//比完之后，假如第1个有序区仍有剩余，则直接全部复制到 temp 数组
	while (i <= mid) {
		temp[k++] = arr[i++];
	}
	//比完之后，假如第2个有序区仍有剩余，则直接全部复制到 temp 数组
	while (j <= right) {
		temp[k++] = arr[j++];
	}
	//将排好序的序列，重存回到 list 中 left 到 right 区间
	for (i = left, k = 0; i <= right; i++, k++) {
		arr[i] = temp[k];
	}
	delete[]temp;
}
// 2路归并递归
template <typename T>
void binary_merge_sort_dg(T *arr, int left, int right) {
	int mid = left + (right - left) / 2;
	if (left < right) {
		binary_merge_sort_dg(arr, left, mid);
		binary_merge_sort_dg(arr, mid + 1, right);
		binary_merge(arr, left, mid, right);
	}
}
template <typename T>
void binary_merge_sort(T *arr, int length) {
	//回忆图解的过程，二路归并算法的流程，不同于递归，递归是先递归语句，然后归并函数，这样归并函数是倒序执行（和递归函数执行顺序相反）
	int size = 1;
	int low;
	int mid;
	int high;
	//size 是标记当前各个归并序列的high-low，从1，2，4，8，……，2*size
	while(size <= length - 1) {
		//从第一个元素开始扫描，low代表第一个分割的序列的第一个元素
		low = 0;
		// 当前的归并算法结束的条件
		while (low + size <= length - 1) {
			//mid代表第一个分割的序列的最后一个元素
			mid = low + size - 1;
			//high 代表第二个分割的序列的最后一个元素
			high = mid + size;
			if (high > length - 1) {
				high = length - 1;
			}
			//调用归并函数，进行分割的序列的分段排序
			binary_merge(arr, low, mid, high);
			//打印出每次归并的区间
			std::cout << "low:" << low << " mid:" << mid << " high:" << high << std::endl;
			//下一次归并时第一序列的第一个元素位置
			low = high + 1;
		}
		//范围扩大一倍，二路归并的过程
		size *= 2;
	}
}
#endif // MERGE_SORT_H