#pragma once
#include "Graph.h"

void SearchUniqueVertexes(string& UniqueVertexes, int& VertexesNumber, ifstream& read);
void SearchThroughput(int VertexesNumber, Graph* Throughput, char* Vertexes, ifstream& read);
void BubbleSort(int VertexesNumber, char* Vertexes);
unsigned EdmondsKarp(int VertexesNumber, Graph& Throughput);
void Process(unsigned& MaxFlow, ifstream& read);