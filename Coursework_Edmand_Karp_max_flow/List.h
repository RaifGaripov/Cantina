#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;
template<typename T>
class List
{
private:
	class Node
	{
	private:
		T data;
		Node* next, * prev;
	public:
		Node() : next(NULL), prev(NULL), data(0) {};
		Node(T data) {
			this->data = data;
			next = NULL;
			prev = NULL;
		}
		~Node() {
			next = NULL;
			prev = NULL;
		}
		void set_data(T data) {
			this->data = data;
		}
		T get_data() {
			return data;
		}
		Node* get_next() {
			return next;
		}
		Node* get_prev() {
			return prev;
		}
		void set_next(Node* pointer) {
			next = pointer;
		}
		void set_prev(Node* pointer) {
			prev = pointer;
		}
	};
	Node* head, * tail;
	int size;
	Node* get_pointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}
			return temp;
		}
	}
public:
	List() : head(NULL), tail(NULL), size(0) {}
	List(int size, T value) {
		head = NULL;
		tail = NULL;
		this->size = 0;
		while (size--) {
			push_back(value);
		}
	}
	List(const List<T>& list) {
		List();
		Node* temp = list.head;
		while (temp) {
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	~List()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		size = 0;
		head = NULL;
	}
	void push_back(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		size++;
		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		size++;
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	void push_front(List& ls2)
	{
		Node* temp = ls2.tail;
		size_t n = ls2.get_size();
		size += ls2.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			Node* temp = tail;
			tail = tail->get_prev();
			tail->set_next(NULL);
			size--;
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = tail;
			tail = head = NULL;
			size--;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	void pop_front()
	{
		if (head != tail)
		{
			Node* temp = head;
			head = head->get_next();
			head->set_prev(NULL);
			size--;
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = head;
			head = tail = NULL;
			size--;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	void insert(size_t index, T data)
	{
		Node* temp;
		temp = get_pointer(index);
		if (temp == head)
			push_front(data);
		else
		{
			Node* newElem = new Node;
			newElem->set_data(data);
			temp->get_prev()->set_next(newElem);
			newElem->set_prev(temp->get_prev());
			newElem->set_next(temp);
			temp->set_prev(newElem);
			size++;
		}
	}
	T at(size_t index)
	{
		Node* temp;
		temp = get_pointer(index);
		return temp->get_data();
	}
	void remove(size_t index)
	{
		Node* temp;
		temp = get_pointer(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			size--;
			delete temp;
		}
	}
	void remove(T data) {
		Node* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Invalid argument");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			size--;
			delete temp;
		}
	}
	size_t get_size()
	{
		return size;
	}
	void print_to_console()
	{
		Node* temp = head;
		while (temp)
		{
			cout << temp->get_data();
			temp = temp->get_next();
		}
	}
	void clear()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		size = 0;
	}
	void set(size_t index, T data)
	{
		Node* temp;
		temp = get_pointer(index);
		temp->set_data(data);
	}
	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}
	bool compare(List<T> ls) {
		if (get_size() != ls.get_size())
			return false;
		for (int i = 0; i < get_size(); i++) {
			if (at(i) != ls.at(i))
				return false;
		}
		return true;
	}
	bool contains(T elem) {
		Node* temp = head;
		while (temp) {
			if (temp->get_data() == elem)
				return true;
			temp = temp->get_next();
		}
		return false;
	}
	bool contains(List<char>& ls) {
		Node* temp = head;
		while (temp) {
			if (temp->get_data().compare(ls))
				return true;
			temp = temp->get_next();
		}
		return false;
	}
	void nullify() {
		head = NULL;
		tail = NULL;
		size = 0;
	}
	void reverse() {
		Node* temp1 = head, * temp2 = tail;
		T value;
		for (size_t i = 0; i < get_size() / 2; i++) {
			value = temp1->get_data();
			temp1->set_data(temp2->get_data());
			temp2->set_data(value);
			temp1 = temp1->get_next();
			temp2 = temp2->get_prev();
		}
	}

	int get_index(T symbol) {
		Node* temp = head;
		size_t index = 0;
		while (temp) {
			if (temp->get_data() == symbol)
				return index;
			index++;
			temp = temp->get_next();
		}
		throw invalid_argument("Incorrect argument");
	}
};