#pragma once
#include <iostream>
#include <string>

using namespace std;

template<class data_T>
class List
{
public:
	List();
	~List();
	void push_back(data_T data);
	void push_front(data_T data);
	void pop_back();
	void pop_front();
	void clear();
	size_t GetSize();	
	data_T at(const int index);
	bool isEmpty();
	void remove(size_t index);
	void set(size_t index, data_T data);
	void insert(size_t index, data_T data);
	void reverse();
	void print_to_console();
	data_T top();
	int search(data_T info);

private:

	class Node
	{
	public:
		Node* next;
		Node* prev;
		data_T data;
		Node(data_T data = "\0", Node* next = nullptr, Node* prev = nullptr)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};
	Node* head;
	Node* tail;
	size_t size;
};
#include "List.inl"