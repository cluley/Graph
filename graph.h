#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class Graph {
public:
	Graph(ifstream& idxs);
	~Graph();
	void depth_traversal();
	bool is_cyclic();
	void components();
private:
	int vrtcs = 0;
	bool* used = nullptr;
	int** mtx = nullptr;
	template <typename T>
	void deleter(T array);
	void dfs(int v);
	bool cycle_dfs(int v, int prev);
	void components_dfs(int v, int cmpnt);
};