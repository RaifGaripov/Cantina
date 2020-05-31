#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class Queue
{
private:

	template <class T>
	class Node
	{
	private:
		T data;
		Node* next;
	public:
		Node() : next(NULL) {};
		~Node() {};
		// Sets the data field 
		void set_data(T data)
		{
			this->data = data;
		}
		// Returns data
		T get_data()
		{
			return data;
		}
		// Sets pointer to the next element in the queue
		void set_next(Node* pointer)
		{
			next = pointer;
		}
		// Returns pointer to the next element in the queue
		Node* get_next()
		{
			return next;
		}
	};

	int size;
	Node<T>* first, * last;
public:
	Queue() : size(0), first(NULL), last(NULL) {};

	~Queue()
	{
		while (first)
		{
			last = first;
			first = first->get_next();
			delete last;
		}
	}
	// Adds an element in the end of the queue
	void enqueue(T data)
	{
		size++;
		Node<T>* temp = new Node<T>;
		temp->set_data(data);
		if (first == NULL)
		{
			first = last = temp;
		}
		else
		{
			last->set_next(temp);
			last = temp;
		}
	}
	// Extracts the first element of the queue and returns its data
	T dequeue()
	{
		if (first == NULL)
			throw out_of_range("The queue is empty");
		size--;
		Node<T>* temp = first;
		first = first->get_next();
		T data = temp->get_data();
		delete temp;
		return data;
	}
	//Returns data information of the first element
	T peek()
	{
		if (first == NULL)
			throw out_of_range("The queue is empty");
		return first->get_data();
	}
	//Returns the size of the queue
	int get_size()
	{
		return size;
	}

	bool is_empty() {
		if (first == NULL)
			return true;
		else
			return  false;
	}

	T get_first()
	{
		return first->get_data();
	}
	T get_last()
	{
		return last->get_data();
	}
};