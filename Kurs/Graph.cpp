#include "Graph.h"

// Constructor
Graph::Graph(int dimension)
{
	this->dimension = dimension;
	matrix = new int* [dimension];
	for (int i = 0; i < dimension; ++i)
		matrix[i] = new int[dimension];
	for (int k = 0; k < dimension; ++k)
		for (int l = 0; l < dimension; ++l)
			matrix[k][l] = 0;
}

// Destructor
Graph::~Graph()
{
	for (int i = 0; i < this->dimension; ++i)
		delete[] matrix[i];

	delete[] matrix;
}

// Setting the value by index
void Graph::SetValue(int V1, int V2, int data)
{
	matrix[V1][V2] = data;
}

// Getting a value by index
int Graph::GetValue(int V1, int V2)
{
	return matrix[V1][V2];
}

// Breadth-first search
List<int>* Graph::BFS(Graph& Flow)
{
	List<int> queue;
	List<int>* path = new List<int>;
	int* level = new int[dimension];
	bool* visited = new bool[dimension];
	std::fill(visited, visited + dimension, false);
	level[0] = 0;
	queue.push_back(0);
	visited[0] = true;
	while (!(queue.isEmpty()))
	{
		int u = queue.at(0);
		queue.pop_front();
		for (int i = 0; i < dimension; i++)
		{
			if (u == i)
				continue;
			int V = matrix[u][i];
			int V0 = Flow.GetValue(u, i);
			int V1 = Flow.GetValue(i, u);
			int V2 = matrix[i][u];
			if (!visited[i] && ((V != V0) || ((V2 != V1) && V1 != 0)))
			{
				queue.push_back(i);
				visited[i] = true;
				level[i] = level[u] + 1;
			}
		}
	}
	int Max = level[dimension - 1];
	path->push_front(dimension - 1);
	while (Max != 0 && Max >= 0)
	{
		for (int j = 0; j < dimension; ++j)
		{
			int V = matrix[j][path->at(0)];
			int V0 = Flow.GetValue(j, path->at(0));
			int V1 = Flow.GetValue(path->at(0), j);
			int V2 = matrix[path->at(0)][j];
			if (level[j] == Max - 1 && ((V != V0) || ((V2 != V1) && V1 != 0)))
			{
				if (level[j] == Max - 1)
				{
					path->push_front(j);
					Max--;
					break;
				}
			}
		}
	}
	delete[] level;
	delete[] visited;
	return path;
}
