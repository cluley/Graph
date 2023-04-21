#include "graph.h"

Graph::Graph(ifstream& idxs) {
	idxs >> vrtcs;
	used = new bool[vrtcs]();

	mtx = new int* [vrtcs]();

	for (int i = 0; i < vrtcs; i++) {
		mtx[i] = new int[vrtcs]();
	}

	for (int i = 0; i < vrtcs; ++i) {
		for (int j = 0; j < vrtcs; ++j) {
			idxs >> mtx[i][j];
		}
	}
}

template <typename T>
void Graph::deleter(T array) {
	delete[] array;
	array = nullptr;
}

Graph::~Graph() {
	for (int i = 0; i < vrtcs; ++i) {
		delete[] mtx[i];
	}

	deleter(mtx);
	deleter(used);
}

void Graph::dfs(int v) {
	if (used[v]) {
		return;
	}
	else {
		used[v] = true;

		cout << ' ' << v + 1;

		for (int i = 0; i < vrtcs; ++i) {
			if(mtx[v][i] && !used[i]) {
				dfs(i);
			}
		}
	}
}

void Graph::depth_traversal() {
	memset(used, false, vrtcs * sizeof(bool));

	cout << "Порядок обхода вершин: ";

	for (int i = 0; i < vrtcs; ++i) {
		if (!used[i]) {
			dfs(i);
		}
	}
}

bool Graph::cycle_dfs(int v, int prev) {
	used[v] = true;

	for (int i = 0; i < vrtcs; ++i) {
		if (mtx[v][i] && !used[i]) {
			if (cycle_dfs(i, v)) {
				return true;
			}
		}
		else if (mtx[v][i] && used[i] && (i != prev)) {
			return true;
		}
	}

	return false;
}

bool Graph::is_cyclic() {
	memset(used, false, vrtcs * sizeof(bool));
	
	for (int i = 0; i < vrtcs; ++i) {
		if (!used[i]) {
			if (cycle_dfs(i, i)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void Graph::components_dfs(int v, int cmpnt) {
	if (used[v]) {
		return;
	}
	else {
		used[v] = true;

		cout << v + 1 << " - " << cmpnt << '\n';

		for (int i = 0; i < vrtcs; ++i) {
			if (mtx[v][i] && !used[i]) {
				components_dfs(i, cmpnt);
			}
		}
	}
}

void Graph::components() {
	memset(used, false, vrtcs * sizeof(bool));
	int cnt(1);

	cout << "Принадлежность вершин компонентам связности:\n";

	for (int i = 0; i < vrtcs; ++i) {
		if (!used[i]) {
			components_dfs(i, cnt);
			++cnt;
		}
	}

	cout << "Количество компонентов связности в графе: " << --cnt << endl;
}