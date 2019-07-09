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
};
template <typename T>
void GraphTable<T>::r_dfs(T v_from, T* & reach, T label) {
	reach[v_from] = label;
	LinkNode<T>* tmp_link = root[v_from]->getNode_head();
	while (tmp_link->_next != nullptr) {
		t
	}
	for (int i = 1; i <= n; i++) {
		if (a[v_from][i] != noEdge && i != v_from && reach[i] != label) {
			r_dfs(i, reach, label);
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