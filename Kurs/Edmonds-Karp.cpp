#include <iostream>
#include <fstream>
#include <string>
#include "Edmonds-Karp.h"

// Search for unique vertices
void SearchUniqueVertexes(string& UniqueVertexes, int& VertexesNumber, ifstream& read)
{
	char temp = ' ';
	while (!read.eof())
	{
		temp = read.get();
		if (temp == ' ' || isdigit(temp) || temp == '\n')
			continue;
		if (!isdigit(temp))
		{
			for (int i = 0; i < VertexesNumber; ++i)
			{
				if (UniqueVertexes[i] == temp)
				{
					temp = ' ';
					break;
				}
			}
			if (temp == ' ')
				continue;
			else
			{
				UniqueVertexes += temp;
				VertexesNumber++;
			}
		}
	}
}

// Search for bandwidth and add it to a two-dimensional array
void SearchThroughput(int VertexesNumber, Graph* Throughput, char* Vertexes, ifstream& read)
{
	char temp = ' ';
	unsigned from = 0, to = 0;
	string temp_number = "";
	while (!read.eof())
	{
		temp = read.get();
		if (temp == '\n' || temp == ' ')
			continue;
		else if (!isdigit(temp))
		{

			for (unsigned i = 0; i < VertexesNumber; ++i)
			{
				if (Vertexes[i] == temp)
					from = i;
			}
			temp = read.get();
			temp = read.get();
			for (unsigned i = 0; i < VertexesNumber; ++i)
			{
				if (Vertexes[i] == temp)
					to = i;
			}
		}
		else if (isdigit(temp))
		{
			temp_number.push_back(temp);
			while (isdigit(temp = read.get()))
				temp_number.push_back(temp);
			Throughput->SetValue(from, to, atoi(temp_number.c_str()));
			//std::cout << "i: " << from << ", j: " << to << ", number: " << temp_number << endl;
			temp_number.clear();
			if (read.eof())
				break;
		}	
	}
}

// Sorting an array
void BubbleSort(int VertexesNumber, char* Vertexes)
{
	for (int i = 0; i < VertexesNumber - 1; ++i)
	{
		for (int j = 0; j < VertexesNumber - 1; ++j)
		{
			if (Vertexes[j] > Vertexes[j + 1] && (Vertexes[j] != 'S' && Vertexes[j + 1] != 'T'))
			{
				char temp = Vertexes[j];
				Vertexes[j] = Vertexes[j + 1];
				Vertexes[j + 1] = temp;
			}
		}
	}
}

// The Edmonds-Karp algorithm
unsigned EdmondsKarp(int VertexesNumber, Graph& Throughput)
{
	Graph* Flow = new Graph(VertexesNumber);
	List<int>* ShortestPath = new List<int>;
	ShortestPath = Throughput.BFS(*Flow);
	int* ResidualThroughput = new int[ShortestPath->GetSize() - 1];
	while (!(ShortestPath->isEmpty()) || ShortestPath->GetSize() == 1)
	{
		ShortestPath = Throughput.BFS(*Flow);
		ResidualThroughput = new int[ShortestPath->GetSize() - 1];
		if (ShortestPath->isEmpty() || ShortestPath->GetSize() == 1)
			break;
		for (int i = 0; i < ShortestPath->GetSize() - 1; ++i)
		{
			unsigned to = Throughput.GetValue(ShortestPath->at(i), ShortestPath->at(i + 1));
			unsigned from = Throughput.GetValue(ShortestPath->at(i + 1), ShortestPath->at(i));
			if (to != 0)
				ResidualThroughput[i] = to - Flow->GetValue(ShortestPath->at(i), ShortestPath->at(i + 1));
			else if (from != 0)
				ResidualThroughput[i] = Flow->GetValue(ShortestPath->at(i + 1), ShortestPath->at(i));
			else
				ResidualThroughput = 0;
		}
		unsigned min = ResidualThroughput[0];
		for (int i = 1; i < ShortestPath->GetSize() - 1; ++i)
			if (ResidualThroughput[i] < min)
				min = ResidualThroughput[i];
		for (int i = 0; i < ShortestPath->GetSize() - 1; ++i)
		{
			unsigned to = Flow->GetValue(ShortestPath->at(i), ShortestPath->at(i + 1));
			unsigned from = Flow->GetValue(ShortestPath->at(i + 1), ShortestPath->at(i));
			if (from == 0)
				Flow->SetValue(ShortestPath->at(i), ShortestPath->at(i + 1), to + min);
			else
				Flow->SetValue(ShortestPath->at(i + 1), ShortestPath->at(i), from - min);
		}
	}
	unsigned MaxFlow = 0;
	for (int i = 0; i < VertexesNumber; ++i)
	{
		if (Flow->GetValue(0, i) != 0)
			MaxFlow += Flow->GetValue(0, i);
	}
	delete[] ResidualThroughput;
	delete ShortestPath;
	delete Flow;
	return MaxFlow;
}

// How the program works
void Process(unsigned& MaxFlow, ifstream& read)
{
	int VertexesNumber = 0;
	string UniqueVertexes = "";
	SearchUniqueVertexes(UniqueVertexes, VertexesNumber, read);
	VertexesNumber = VertexesNumber - 1;
	char* Vertexes = new char[VertexesNumber];
	for (int k = 0; k < VertexesNumber; ++k)
		Vertexes[k] = UniqueVertexes[k];
	BubbleSort(VertexesNumber, Vertexes);
	read.clear();
	read.seekg(0, ios::beg);
	Graph* Throughput = new Graph(VertexesNumber);
	SearchThroughput(VertexesNumber, Throughput, Vertexes, read);
	MaxFlow = EdmondsKarp(VertexesNumber, *Throughput);
	delete Throughput;
	delete[] Vertexes;
}
