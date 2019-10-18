#pragma once
#ifndef GRAPH_TABLE_H
#define GRAPH_TABLE_H
#include "single_chain.h"
#include "graph_edge.h"
#include "min_heap.h"
#include<set>
#include <vector>
template <typename T>
class GraphTable : protected SingleLink<T> {
private:
	std::vector<SingleLink<T>*> root;
	int n; //顶点个数
	int e;	//边的个数
	T noEdge; //表示不存在的边的值
	JBMinHeap<Edge<T>> *min_heap; //连通图的顶点最小堆
	void checkVertex(T, T); //检查是否合法顶点
	void checkVertex(T); //检查是否合法顶点
	void r_dfs(T, T*&, T);
	bool dfs_find_path(T, T, int&, T*&, T*&); //深度递归寻找路径;
	bool check_vertex_circle(std::set<T> *, T, T); //检查加入是否回路
	void insert_edge_to_set(std::set<T> *&, T, T); //插入边到并查集
	void prim_init_minheap(T, T, std::set<T>);
public:
	~GraphTable() {
		root.clear();
	}
	GraphTable() {
	}
	// 新建一个点vector
	GraphTable(T a[], int size, T _noEdge = 0) {
		noexcept(size > 0);
		e = 0;
		noEdge = _noEdge;
		n = size;
		SingleLink<T>* tmp = new SingleLink<T>(0, nullptr, 0);
		root.push_back(tmp);
		min_heap = new JBMinHeap<Edge<T>>(2 * size);
		for (int i = 0; i < size; i++) {
			SingleLink<T>* tmp = new SingleLink<T>(a[i], nullptr, 0);
			root.push_back(tmp);
		}
	}
	void add_directioned (T, T, int); //有向图
	void add_no_direction(T, T, int); //无向图
	int numberOfVertices() {
		return n;
	}
	int numberOfEdges() {
		return e;
	}
	//返回顶点的出度
	int outDegree(T v_from) {
		checkVertex(v_from);
		// 计算关联于顶点的边数
		return root[v_from]->size();
	}
	//返回顶点的入度
	int inDegree(T v_to) {
		checkVertex(v_to);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			LinkNode<T>* p_head = root[i]->getNode_head();
			while (p_head->_next != nullptr) {
				p_head = p_head->_next;
				if (p_head->_value == v_to)
					sum++;
			}
		}
		return sum;
	}
	void bfs(T, T* &, T); //广度优先搜索
	//深度优先搜索
	void dfs(T v_from, T* & reach, T label) {
		reach = new T[n + 1];
		std::fill(reach, reach + n + 1, 0);
		r_dfs(v_from, reach, label);
	};
	T * find_path(T, T); //寻找合法路径;
	bool connected(); //确定一个无向图是否连通
	// 拓扑排序
	bool topologicalOrder(T *&);
	bool directed() {
		return true;
	}
	// 单源最短路径
	void shortestPaths(T, T, T*&, T*&);
	// 最小生成树(Kruskal算法,最小堆存储边,并-查集判断环路)
	void mintree_kruskal(Edge<T> *&);
	// 最小生成树(prim算法，set和dfs)
	void mintree_prim(Edge<T> *&);
};
template <typename T>
void GraphTable<T>::prim_init_minheap(T v_from ,T v_to, std::set<T> reach_vertex) {
	min_heap->clear_initial(n * 2);
	LinkNode<T> *tmp_link = root[v_from]->getNode_head();
	while (tmp_link->_next != nullptr) {
		tmp_link = tmp_link->_next;
		if (reach_vertex.count(tmp_link->_value) == 0) {
			min_heap->add(Edge<T>(v_from, tmp_link->_value, tmp_link->_weight));
		}
	}
	tmp_link = root[v_to]->getNode_head();
	while (tmp_link->_next != nullptr) {
		tmp_link = tmp_link->_next;
		if (reach_vertex.count(tmp_link->_value) == 0) {
			min_heap->add(Edge<T>(v_to, tmp_link->_value, tmp_link->_weight));
		}
	}
}
template <typename T>
void GraphTable<T>::mintree_prim(Edge<T> *& path) {
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

	std::cout<<1;
}
template <typename T>
void GraphTable<T>::insert_edge_to_set(std::set<T> *& reach_vertex_tmp, T v_from, T v_to) {
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
bool GraphTable<T>::check_vertex_circle(std::set<T> * reach_vertex_tmp, T v_from, T v_to) {
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
void GraphTable<T>::mintree_kruskal(Edge<T> *& path) {
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
void GraphTable<T>::shortestPaths(T v_from, T v_to, T* &distance_from_source, T* &precesssor) {
	// 寻找从源点v_from到点v_to的最短路径
	// 在数组distance_from_source中返回最短路径
	// 在数组precesssor中返回顶点
	std::set<T> reach_table;
	checkVertex(v_from, v_to);
	distance_from_source = new T[n + 1];
	precesssor = new T[n + 1];
	std::fill(distance_from_source, distance_from_source + n + 1, -1);
	std::fill(precesssor, precesssor + n + 1, -1);
	LinkNode<T> *tmp_link = root[v_from]->getNode_head();
	while (tmp_link->_next != nullptr) {
		tmp_link = tmp_link->_next;
		distance_from_source[tmp_link->_value] = tmp_link->_weight;
		precesssor[tmp_link->_value] = v_from;
		reach_table.insert(tmp_link->_value);
	}
	typename std::set<T>::iterator iter = reach_table.begin();
	while (iter != reach_table.end()) {
		T vertex = *iter;
		tmp_link = root[vertex]->getNode_head();
		while (tmp_link->_next != nullptr) {
			tmp_link = tmp_link->_next;
			if ((distance_from_source[tmp_link->_value] > distance_from_source[vertex] + tmp_link->_weight && !root[tmp_link->_value]->has_value(vertex)) || distance_from_source[tmp_link->_value] == -1) {
				precesssor[tmp_link->_value] = vertex;
				distance_from_source[tmp_link->_value] = distance_from_source[vertex] + tmp_link->_weight;
			}
			LinkNode<T> *point_link = root[tmp_link->_value]->getNode_head();
			while (point_link->_next != nullptr) {
				point_link = point_link->_next;
				reach_table.insert(point_link->_value);
			}
		}
		iter++;
	}
}
template <typename T>
bool GraphTable<T>::topologicalOrder(T *& theOrder) {
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
		LinkNode<T> *tmp_link = root[vertex]->getNode_head();
		while (tmp_link->_next != nullptr) {
			tmp_link = tmp_link->_next;
			in_degree[tmp_link->_value]--;
			if (in_degree[tmp_link->_value] == 0) {
				reach_tmp.push_back(tmp_link->_value);
			}
		}
	}
	if (num == n)
		return true;
	else
		return false;
}
template <typename T>
bool GraphTable<T>::connected() {
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
bool GraphTable<T>::dfs_find_path(T v_from, T v_to, int & length, T*& reach, T*& path) {
	//寻找路径的实际算法，从顶点v_from开始深度搜索
	//source不等于终点v_to
	reach[v_from] = 1;
	LinkNode<T> *tmp_link = root[v_from]->getNode_head();
	while (tmp_link->_next != nullptr) {
		tmp_link = tmp_link->_next;
		// 没被访问过并且是连通的，加入递归栈
		if (reach[tmp_link->_value] != 1) {
			path[++length] = tmp_link->_value; //路径中加入i
			if (tmp_link->_value == v_to || dfs_find_path(tmp_link->_value, v_to, length, reach, path)) {
				return true;
			}
			length--;
		}
	}
	return false;
}
template <typename T>
T* GraphTable<T>::find_path(T v_from, T v_to) {
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
void GraphTable<T>::r_dfs(T v_from, T* & reach, T label) {
	reach[v_from] = label;
	LinkNode<T>* tmp_link = root[v_from]->getNode_head();
	while (tmp_link->_next != nullptr) {
		tmp_link = tmp_link->_next;
		if (reach[tmp_link->_value] != label) {
			r_dfs(tmp_link->_value, reach, label);
		}
	}
}
template <typename T>
void GraphTable<T>::bfs(T v_from, T* & reach, T label) {
	// 广度优先搜索。reach数组用来标记从v_from顶点开始遍历可到达的所有顶点
	reach = new T[n + 1];
	std::fill(reach, reach + n + 1, 0);
	std::vector<int> reach_tmp;
	reach[v_from] = label;
	reach_tmp.push_back(v_from);
	while (!reach_tmp.empty()) {
		T vertex = reach_tmp.back();
		reach_tmp.pop_back();
		LinkNode<T>* sing_tmp = root[vertex]->getNode_head();
		while (sing_tmp->_next != nullptr) {
			sing_tmp = sing_tmp->_next;
			if (reach[sing_tmp->_value] != label) {
				reach[sing_tmp->_value] = label;
				reach_tmp.push_back(sing_tmp->_value);
			}
		}
	}
}
template <typename T>
void GraphTable<T>::checkVertex(T v_from) {
	noexcept(v_from >= 1 && v_from <= n);
}
template <typename T>
void GraphTable<T>::checkVertex(T v_from, T v_to) {
	noexcept(v_from >= 1 && v_from <= n && v_to >= 1 && v_to <= n && v_from != v_to);
}
template <typename T>
void GraphTable<T>::add_no_direction(T v_from, T v_to, int weight) {
	checkVertex(v_from, v_to);
	LinkNode<T>* tmpa = new LinkNode<T>(v_to, nullptr, weight);
	root[v_from]->insert_graph(tmpa);
	LinkNode<T>* tmpb = new LinkNode<T>(v_from, nullptr, weight);
	root[v_to]->insert_graph(tmpb);
	e++;
	min_heap->add(Edge<T>(v_from, v_to, weight));
}
template <typename T>
void GraphTable<T>::add_directioned(T v_from, T v_to, int weight) {
	checkVertex(v_from, v_to);
	LinkNode<T>* tmp = new LinkNode<T>(v_to, nullptr, weight);
	root[v_from]->insert_graph(tmp);
	e++;
	min_heap->add(Edge<T>(v_from, v_to, weight));
}
#endif // GRAPH_TABLE_H