#pragma once
#ifndef GRAPH_TABLE_H
#define GRAPH_TABLE_H
#include "single_chain.h"
#include <vector>
template <typename T>
class GraphTable : protected SingleLink<T> {
private:
	std::vector<SingleLink<T>*> root;
	int n; //顶点个数
	int e;	//边的个数
	T noEdge; //表示不存在的边的值
	void checkVertex(T, T); //检查是否合法顶点
	void checkVertex(T); //检查是否合法顶点
	void r_dfs(T, T*&, T);
	bool dfs_find_path(T, T, int&, T*&, T*&); //深度递归寻找路径;
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
};
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
}
template <typename T>
void GraphTable<T>::add_directioned(T v_from, T v_to, int weight) {
	checkVertex(v_from, v_to);
	LinkNode<T>* tmp = new LinkNode<T>(v_to, nullptr, weight);
	root[v_from]->insert_graph(tmp);
	e++;
}
#endif // GRAPH_TABLE_H