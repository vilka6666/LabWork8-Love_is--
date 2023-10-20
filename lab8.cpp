#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

struct Node {
	int inf;
	Node* next;
};

void BFS_OCH(const std::vector < std::vector < int>>& matrix, int num_vertices, int start_vertex) {
	std::vector<int> visited(num_vertices, 0);
	bool hasPath = false; // Добавленная переменная

	for (int i = 0; i < num_vertices; ++i) {
		if (matrix[start_vertex][i] == 1) {
			hasPath = true;
			break;
		}
	}

	if (!hasPath) {
		printf("От стартовой вершины %d нет путей.\n", start_vertex);
		return;
	}

	Node* head = nullptr;
	Node* last = nullptr;

	Node* newNode = new Node;
	newNode->inf = start_vertex;
	newNode->next = nullptr;
	head = last = newNode;

	while (head != nullptr) {
		int current_vertex = head->inf;

		if (!visited[current_vertex]) {
			printf("%d ", current_vertex);
			visited[current_vertex] = 1;

			for (int i = 0; i < num_vertices; ++i) {
				if (matrix[current_vertex][i] == 1 && !visited[i]) {
					Node* newNode = new Node;
					newNode->inf = i;
					newNode->next = nullptr;

					if (last == nullptr) {
						head = last = newNode;
					}
					else {
						last->next = newNode;
						last = newNode;
					}
				}
			}
		}

		Node* temp = head;
		head = head->next;
		delete temp;
	}
}


void BFS(const vector < vector < int>>& G, int start_vertex) {
	int size_G = G.size();
	vector<bool> NUM(size_G, false);
	queue<int> Q;

	bool hasPath = false; // Добавленная переменная

	for (int i = 1; i < size_G; ++i) {
		if (G[start_vertex][i] == 1) {
			hasPath = true;
			break;
		}
	}

	if (!hasPath) {
		printf("От стартовой вершины %d нет путей.\n", start_vertex);
		return;
	}

	Q.push(start_vertex);
	NUM[start_vertex] = true;

	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		printf("%d ", v);

		for (int i = 1; i < size_G; ++i) {
			if (G[v][i] == 1 && !NUM[i]) {
				Q.push(i);
				NUM[i] = true;
			}
		}
	}
	printf("\n");
}


void BFS_list(const vector < vector < int>>& adjacency_list, int start_vertex) {
	int size_G = adjacency_list.size();
	vector<bool> NUM(size_G, false);
	bool hasPath = false; // Добавленная переменная

	if (!adjacency_list[start_vertex].empty()) {
		hasPath = true;
	}

	if (!hasPath) {
		printf("От стартовой вершины %d нет путей.\n", start_vertex);
		return;
	}

	queue<int> Q;
	Q.push(start_vertex);
	NUM[start_vertex] = true;

	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		printf("%d ", v);

		for (const int& neighbor : adjacency_list[v]) {
			if (!NUM[neighbor]) {
				Q.push(neighbor);
				NUM[neighbor] = true;
			}
		}
	}

	// Проверка на изолированные вершины
	/*for (int i = 1; i < size_G; ++i) {
		if (!NUM[i]) {
			printf("%d ", i);
		}
	}*/
	printf("\n");
}




vector < vector < int>> generateAndPrintMatrix(int num_vertices, double edge_probability) {
	vector < vector < int>> adjacency_matrix(num_vertices + 1, vector<int>(num_vertices + 1, 0));
	int num_edges = 0;

	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = i + 1; j <= num_vertices; ++j) {
			if (static_cast<double>(rand()) / RAND_MAX < edge_probability) {
				adjacency_matrix[i][j] = 1;
				adjacency_matrix[j][i] = 1;
				num_edges++;
			}
		}
	}

	printf("Матрица смежности:\n");
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			printf("%d ", adjacency_matrix[i][j]);
		}
		printf("\n");
	}
	return adjacency_matrix;
}

vector < vector < int>> matrixToList(const vector < vector < int>>& matrix) {
	int num_vertices = matrix.size() - 1;
	vector < vector < int>> adjacency_list(num_vertices + 1);

	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			if (matrix[i][j] == 1) {
				adjacency_list[i].push_back(j);
			}
		}
	}

	return adjacency_list;
}

void printList(const vector < vector < int>>& list) {
	printf("Список смежности:\n");
	for (int i = 1; i < list.size(); ++i) {
		printf("%d: ", i);
		for (const int& j : list[i]) {
			printf("%d ", j);
		}
		printf("\n");
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	int num_vertices;
	double edge_probability;


	printf("Введите количество вершин в графе: ");
	scanf("%d", &num_vertices);

	printf("Введите вероятность наличия ребра в графе (0 - 1): ");
	scanf("%lf", &edge_probability);

	srand(static_cast<unsigned int>(time(nullptr)));
	clock_t start, end;
	double cpu_time_used;

	printf("Первый граф:\n");
	auto matrix1 = generateAndPrintMatrix(num_vertices, edge_probability);
	auto list1 = matrixToList(matrix1);
	printList(list1);

	printf("Обход в ширину:\n");
	BFS(matrix1, 1);
	start = clock();
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Время выполнения: %f секунд\n", cpu_time_used);

	printf("Обход в ширину (список смежности):\n");
	BFS_list(list1, 1);

	printf("Обход в ширину при помощи очереди:\n");
	start = clock();
	BFS_OCH(matrix1, num_vertices, 1);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Время выполнения: %f секунд\n", cpu_time_used);


	return 0;
}