#pragma once
#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
#include "graph.h"
#include <vector>
#include <algorithm>
template <typename T>
class GraphMatrix {
private:
	void make_2d_array(T **&x, int rows, int cols); //初始化二维数组
	void delete_2d_array(T **&x, int rows, int cols); //删除二维数组
protected:
	int n; //顶点个数
	int e;	//边的个数
	T **a; //邻接数组
	T noEdge; //表示不存在的边的值
public:
	GraphMatrix(int numberOfVertices = 0, T _noEdge = 0) {
		noexcept(numberOfVertices > 0);
		n = numberOfVertices;
		e = 0;
		noEdge = _noEdge;
		make_2d_array(a, n + 1, n + 1);
		for (int i = 1; i <= n; i++) {
			std::fill(a[i], a[i] + n + 1, noEdge);
		}
	}
	~GraphMatrix() {
		delete_2d_array(a, n + 1, n + 1);
	}
	void bfs(T, T* &, T); //广度优先搜索
	void checkVertex(T, T); //检查是否合法顶点
	bool directed() {
		return true;
	}
	bool weighted() {
		return true;
	}
	int numberOfVertices() {
		return n;
	}
	int numberOfEdges() {
		return e;
	}
	bool existsEdge(T i, T j) const {
		// 当且仅当(i,j)是图的一条边，返回值为真
		if (i<1 || j<1 || i>n || j>n || a[i][j] == noEdge)
			return false;
		else
			return true;
	}
	//插入边
	void insertEdge(Edge<T>* theEdge) {
		// 插入边，如果边范围出错，返回错误，如果边已存在，修改边的权值
		T v_from = theEdge->vertex_from;
		T v_to = theEdge->vertex_to;
		checkVertex(v_from, v_to);
		if (a[v_from][v_to] == noEdge) {
			e++;
		}
		a[v_from][v_to] = theEdge->weight;
	}
	//删除边 
	void eraseEdge(T v_from, T v_to) {
		noexcept(v_from >= 1 && v_from <= n && v_to >= 1 && v_to <= n && a[v_from][v_to] != noEdge);
		a[v_from][v_to] = noEdge;
	}
	//返回顶点的出度
	int outDegree(T v_from) {
		checkVertex(v_from);
		// 计算关联于顶点的边数
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			if (a[v_from][i] != noEdge) {
				sum++;
			}
		}
		return sum;
	}
	//返回顶点的入度
	int inDegree(T v_to) {
		checkVertex(v_to);
		// 计算关联到顶点的边数
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i][v_to] != noEdge) {
				sum++;
			}
		}
		return sum;
	}
};
template <typename T>
void GraphMatrix<T>::bfs(T v_from, T* & reach, T label) {
	// 广度优先搜索。reach数组用来标记从v_from顶点开始遍历可到达的所有顶点
	reach = new T[n+1];
	std::fill(reach, reach + n + 1, 0);
	std::vector<int> reach_tmp;
	reach[v_from] = label;
	reach_tmp.push_back(v_from);
	while (!reach_tmp.empty()) {
		T vertex = reach_tmp.back();
		reach_tmp.pop_back();
		for (int i = 1; i <= n; i++) {
			if (a[vertex][i] != noEdge && reach[i] != label) {
				reach[i] = label;
				reach_tmp.push_back(i);
			}
		}
	}
	reach_tmp.clear();
}
template <typename T>
void GraphMatrix<T>::checkVertex(T v_from, T v_to) {
	noexcept(v_from >= 1 && v_from <= n && v_to >= 1 && v_to <= n && v_from != v_to);
}
template <typename T>
void GraphMatrix<T>::delete_2d_array(T **&x, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		delete[]x[i];
	}
	delete[]a;
}
template <typename T>
void GraphMatrix<T>::make_2d_array(T **&x, int rows, int cols) {
	// 创建一个行指针
	x = new T*[rows];
	for (int i = 0; i < rows; i++) {
		x[i] = new T[cols];
	}
}
#endif // GRAPH_MATRIX_H