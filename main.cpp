#include "graph.h"

int main(int argc, char** argv) {
	ifstream idxs("input.txt");

	if (!idxs.is_open()) {
		cout << "Файл input поврежден." << endl;
		return 1;
	}

	Graph graph(idxs);

	graph.depth_traversal();

	cout << '\n' << endl;

	if (graph.is_cyclic()) {
		cout << "В графе есть цикл!" << endl;
	}
	else {
		cout << "В графе нет циклов" << endl;
	}

	cout << '\n';

	graph.components();

	return 0;
}