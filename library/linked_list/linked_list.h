#ifndef __LINKED_LIST_H_INCLUDED__
#define __LINKED_LIST_H_INCLUDED__

#include <iostream>
#include <utility>

template <class T>
class Node {

	T data;
	Node* next;

public:

	Node(const T& x, Node* y = nullptr): data(x), next(y) {}

	inline void set_date(const T& x) { data = x; }
	inline void set_next(Node* x) { next = x; }

	inline T data() const { return data; }
	inline Node* next() const { return next; }
};

// singly linked lists
template <class T>
class linked_list {
protected:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::ptrdiff_t difference_type;

private:
	Node<T>* head;

public:
	linked_list();
	linked_list(const linked_list<T>&);

	class iterator {
		Node<T>* n_ref;

	public:
		friend class linked_list;
		friend class const_iterator;
	};
	
	class const_iterator {
		Node<T>* n_ref;

	public:
		friend class linked_list;
		friend class iterator;
	};

	bool empty() const;

	void clear();

	void operator=(const linked_list<T>&);
	void operator=(linked_list<T>&&);

	bool operator==(const linked_list<T>&) const;
	bool operator!=(const linked_list<T>&) const;

	void push_back(const T&);
	void push_back(T&&);

	void pop();

	void erase(int);

	void erase_range(int, int);

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;
};

#endif