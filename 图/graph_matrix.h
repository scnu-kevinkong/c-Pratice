#pragma once
#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
#include "graph.h"
#include "graph_edge.h"
#include "min_heap.h"
#include<set>
#include <vector>
#include <algorithm>
template <typename T>
class GraphMatrix {
private:
	bool check_vertex_circle(std::set<T> *, T, T); //检查加入是否回路
	void insert_edge_to_set(std::set<T> *&, T, T); //插入边到并查集
	void make_2d_array(T **&x, int rows, int cols); //初始化二维数组
	void delete_2d_array(T **&x, int rows, int cols); //删除二维数组
	bool dfs_find_path(T, T, int&, T*&, T*&); //深度递归寻找路径;
	void r_dfs(T, T*&, T);
	void prim_init_minheap(T, T, std::set<T>);
protected:
	int n; //顶点个数
	int e;	//边的个数
	T **a; //邻接数组
	T noEdge; //表示不存在的边的值
	JBMinHeap<Edge<T>> *min_heap; //连通图的顶点最小堆
public:
	
	GraphMatrix(int numberOfVertices = 0, T _noEdge = 0) {
		noexcept(numberOfVertices > 0);
		n = numberOfVertices;
		e = 0;
		noEdge = _noEdge;
		make_2d_array(a, n + 1, n + 1);
		min_heap = new JBMinHeap<Edge<T>>((n - 1) * n);
		for (int i = 1; i <= n; i++) {
			std::fill(a[i], a[i] + n + 1, noEdge);
		}
	}
	~GraphMatrix() {
		delete_2d_array(a, n + 1, n + 1);
	}
	bool connected(); //确定一个无向图是否连通
	void bfs(T, T* &, T); //广度优先搜索
	//深度优先搜索
	void dfs(T v_from, T* & reach, T label) {
		reach = new T[n + 1];
		std::fill(reach, reach + n + 1,0);
		r_dfs(v_from, reach, label);
	};
	T * find_path(T, T); //寻找合法路径;
	void checkVertex(T, T); //检查是否合法顶点
	void checkVertex(T); //检查是否合法顶点
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
	//无向图插入边
	void insertEdge_double(Edge<T> theEdge) {
		// 插入边，如果边范围出错，返回错误，如果边已存在，修改边的权值
		T v_from = theEdge.vertex_from;
		T v_to = theEdge.vertex_to;
		checkVertex(v_from, v_to);
		if (a[v_from][v_to] == noEdge) {
			e++;
		}
		a[v_from][v_to] = theEdge.weight;
		if (a[v_to][v_from] == noEdge) {
			e++;
		}
		a[v_to][v_from] = theEdge.weight;
		min_heap->add(theEdge);
		min_heap->add(Edge<T>(v_to, v_from, theEdge.weight));
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
	// 拓扑排序
	bool topologicalOrder(T *&);
	// 单源最短路径
	void shortestPaths(T, T, T*&, T*&);
	// 最小生成树(Kruskal算法,最小堆存储边,并-查集判断环路)
	void mintree_kruskal(Edge<T> *&);
	// 最小生成树(prim算法，set和dfs)
	void mintree_prim(Edge<T> *&);
};
template <typename T>
void GraphMatrix<T>::prim_init_minheap(T v_from, T v_to, std::set<T> reach_vertex) {
	min_heap->clear_initial(n * (n - 1));
	for (int i = 1; i <= n; i++) {
		if (a[v_from][i] != noEdge) {
			if (reach_vertex.count(i) == 0) {
				min_heap->add(Edge<T>(v_from, i, a[v_from][i]));
			}
		}
		else if (a[v_to][i] != noEdge) {
			if (reach_vertex.count(i) == 0) {
				min_heap->add(Edge<T>(v_to, i, a[v_to][i]));
			}
		}
	}
}
template <typename T>
void GraphMatrix<T>::mintree_prim(Edge<T> *& path) {
	path = new Edge<T>[n];
	int *distance_from_source;
	T* precesssor;
	std::set<T> reach_vertex;
	T v_from;
	T v_to;
	Edge<T> edge;
	int size = 0;
	while (size != n - 1) {
		if (size == 0) {
			edge = min_heap->getMinHeap();
			v_from = edge.vertex_from;
			v_to = edge.vertex_to;
			path[size++] = edge;
			reach_vertex.insert(v_from);
			reach_vertex.insert(v_to);
			prim_init_minheap(v_from, v_to, reach_vertex);
		}
		else {
			edge = min_heap->getMinHeap();
			v_from = edge.vertex_from;
			v_to = edge.vertex_to;
			path[size++] = edge;
			reach_vertex.insert(v_from);
			reach_vertex.insert(v_to);
			prim_init_minheap(v_from, v_to, reach_vertex);
		}
	}

	std::cout << 1;
}
template <typename T>
void GraphMatrix<T>::insert_edge_to_set(std::set<T> *& reach_vertex_tmp, T v_from, T v_to) {
	bool is_insert = false;
	int first_null = 1;
	for (int i = 0; i < n - 1; i++) {
		if (!reach_vertex_tmp[i].empty()) {
			if (reach_vertex_tmp[i].count(v_from) || reach_vertex_tmp[i].count(v_to)) {
				reach_vertex_tmp[i].insert(v_from);
				reach_vertex_tmp[i].insert(v_to);
				is_insert = true;
			}
		}
		else {
			first_null = i;
		}
	}
	if (!is_insert) {
		std::set<T> temp;
		temp.insert(v_from);
		temp.insert(v_to);
		reach_vertex_tmp[first_null] = temp;
	}
	else {
		int complex_pos = -1;
		for (int i = 0; i < n - 1; i++) {
			if (!reach_vertex_tmp[i].empty()) {
				if (reach_vertex_tmp[i].count(v_from) || reach_vertex_tmp[i].count(v_to)) {
					if (complex_pos == -1) {
						complex_pos = i;
					}
					else {
						reach_vertex_tmp[complex_pos].insert(reach_vertex_tmp[i].begin(), reach_vertex_tmp[i].end());
						reach_vertex_tmp[i].clear();
					}
				}
			}
		}
	}
}
template <typename T>
bool GraphMatrix<T>::check_vertex_circle(std::set<T> * reach_vertex_tmp, T v_from, T v_to) {
	for (int i = 0; i < n - 1; i++) {
		if (!reach_vertex_tmp[i].empty()) {
			if (reach_vertex_tmp[i].count(v_from) && reach_vertex_tmp[i].count(v_to)) {
				return false;
			}
		}
	}
	return true;
}
template <typename T>
void GraphMatrix<T>::mintree_kruskal(Edge<T> *& path) {
	// 在数组path中返回顶点路径
	path = new Edge<T>[n];
	int k = 0;
	std::set<T>* reach_vertex = new std::set<T>[n - 1];
	while (k < n - 1 || !min_heap->isEmpty()) {
		Edge<T> edge = min_heap->getMinHeap();
		min_heap->pop();
		if (k > 0) {
			if (check_vertex_circle(reach_vertex, edge.vertex_from, edge.vertex_to)) {
				path[k++] = edge;
				insert_edge_to_set(reach_vertex, edge.vertex_from, edge.vertex_to);
			}
		}
		else {
			path[k++] = edge;
			std::set<T> temp;
			temp.insert(edge.vertex_from);
			temp.insert(edge.vertex_to);
			reach_vertex[0] = temp;
		}
	}
}
template <typename T>
void GraphMatrix<T>::shortestPaths(T v_from, T v_to, T* &distance_from_source, T* &precesssor) {
	// 寻找从源点v_from到点v_to的最短路径
	// 在数组distance_from_source中返回最短路径
	// 在数组precesssor中返回顶点
	std::vector<T> reach_table;
	checkVertex(v_from, v_to);
	distance_from_source = new T[n + 1];
	precesssor = new T[n + 1];
	for (int i = 1; i <= n; i++) {
		if (a[v_from][i] != noEdge) {
			if (i == v_from) {
				distance_from_source[i] = 0;
				precesssor[i] = -1;
			}
			else {
				distance_from_source[i] = a[v_from][i];
				precesssor[i] = v_from;
				reach_table.push_back(i);
			}
		}
		else
		{
			precesssor[i] = -1;
			distance_from_source[i] = -1;
		}
	}
	while (!reach_table.empty()) {
		T vertex = reach_table.back();
		reach_table.pop_back();
		for (int i = 1; i <= n; i++) {
			if (a[vertex][i] != noEdge) {
				if (distance_from_source[i] > distance_from_source[vertex] + a[vertex][i] || distance_from_source[i] == -1) {
					precesssor[i] = vertex;
					distance_from_source[i] = distance_from_source[vertex] + a[vertex][i];
				}
				for (int j = 1; j <= n; j++) {
					if (a[i][j] != noEdge) {
						reach_table.push_back(j);
					}
				}
			}
		}
	}
}
template <typename T>
bool GraphMatrix<T>::topologicalOrder(T *&theOrder) {
	int *in_degree = new int[n + 1];
	theOrder = new T[n + 1];
	std::vector<int> reach_tmp;
	for (int i = 1; i <= n; i++) {
		in_degree[i] = inDegree(i);
		if (in_degree[i] == 0) {
			reach_tmp.push_back(i);
		}
	}
	int num = 0;
	while (!reach_tmp.empty()) {
		T vertex = reach_tmp.back();
		reach_tmp.pop_back();
		theOrder[num++] = vertex;
		for (int i = 1; i <= n; i++) {
			if (a[vertex][i] != noEdge) {
				in_degree[i]--;
				if (in_degree[i] == 0) {
					reach_tmp.push_back(i);
				}
			}
		}
	}
	if (num == n)
		return true;
	else
		return false;
}
template <typename T>
bool GraphMatrix<T>::connected() {
	noexcept(!directed());
	T *reach = new T[n + 1];
	std::fill(reach, reach + n + 1, 0);
	dfs(1, reach, 1);
	for (int i = 1; i <= n; i++) {
		if (reach[i] == 0)
			return false;
	}
	return true;
}
template <typename T>
bool GraphMatrix<T>::dfs_find_path(T v_from, T v_to, int & length, T*& reach, T*& path) {
	//寻找路径的实际算法，从顶点v_from开始深度搜索
	//source不等于终点v_to
	reach[v_from] = 1;
	for (int i = 1; i <= n; i++) {
		// 没被访问过并且是连通的，加入递归栈
		if (a[v_from][i] != noEdge && i != v_from && reach[i] != 1) {
			path[++length] = i; //路径中加入i
			if (i == v_to || dfs_find_path(i, v_to, length, reach, path)) {
				return true;
			}
			length--;
		}
	}
	return false;
}
template <typename T>
T* GraphMatrix<T>::find_path(T v_from, T v_to) {
	// v_from为起点，v_to为要到达的点
	// 最后返回一个数组path,path[0]为路径长度，path[1]开始为路径
	// 如果不存在返回nullptr
	checkVertex(v_from, v_to);
	T *path = new T[n + 1];
	path[0] = 1; //第一个点肯定能访问到
	path[1] = v_from;
	int length = 1;
	T *reach = new T[n + 1];
	std::fill(reach, reach + n + 1, 0);
	// 搜索路径
	if (v_from == v_to || dfs_find_path(v_from, v_to, length, reach, path)) {
		path[0] = length - 1;
	}
	else {
		delete[]path;
		path = nullptr;
	}
	delete[] reach;
	return path;
}
template <typename T>
void GraphMatrix<T>::r_dfs(T v_from, T* & reach, T label) {
	reach[v_from] = label;
	for (int i = 1; i <= n; i++) {
		if (a[v_from][i] != noEdge && i != v_from && reach[i] != label) {
			r_dfs(i, reach, label);
		}
	}
}
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
void GraphMatrix<T>::checkVertex(T v_from) {
	noexcept(v_from >= 1 && v_from <= n);
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