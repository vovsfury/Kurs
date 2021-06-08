#pragma once
#include "List.h"

class Graph
{
private:

	int dimension;
	int** matrix;

public:

	Graph(int V);
	~Graph();
	void SetValue(int V1, int V2, int data);
	int GetValue(int V1, int V2);
	List<int>* BFS(Graph& Flow);
};