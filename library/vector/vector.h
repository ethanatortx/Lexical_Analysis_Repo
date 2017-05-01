#ifndef VECTOR_H
#define VECTOR_H

#include "error\error.h"
#include <initializer_list>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

template<class T,
		 class Allocator = std::allocator<T>>
class vector
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef Allocator allocator_type;
	
	class const_iterator;
	class iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	explicit vector( size_type = 0 );
	vector(const vector& rhs);
	~vector();

	bool empty() const;
	size_type size() const;
	size_type max_size() const;
	size_type capacity() const;

	reference operator[]( size_type index );
	const_reference operator[]( size_type index ) const;

	vector& operator=( const vector& rhs );
	void resize( size_type size );
	void reserve( size_type capacity );
	void shrink_to_fit();

	void push_back( const_reference data );
	void push_back( value_type&& data );

	template<class... Args>
	reference emplace_back( Args&&... args );

	void pop_back();
	const_reference back() const;

	iterator insert( const_iterator pos, const_reference data );
	iterator insert( const_iterator pos, value_type&& data );
	iterator insert( const_iterator pos, size_type count, const_reference data );

	template<class... Args>
	iterator emplace( const_iterator pos, Args&&... args );

	iterator erase( iterator pos );
	iterator erase( const_iterator pos );
	iterator erase( iterator first, iterator last );
	iterator erase( const_iterator first, const_iterator last );

	void clear();

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator crbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	reverse_iterator rend();
	const_reverse_iterator rend() const;
	const_reverse_iterator crend() const;

	std::string to_string(const char = ' ') const;
	void print(const char = ' ') const;

	template<class E, class A_M>
	friend void swap( vector<E, A_M>& lhs, vector<E, A_M>& rhs );
	template<class E, class A_M>
	friend std::ostream& operator<<(std::ostream&, const vector<E, A_M>&);
	template<class E, class A_M>
	friend std::istream& operator>>(std::istream&, vector<E, A_M>&);

	enum { SPARE_CAPACITY = 16 };

private:
	size_type _size;
	size_type _capacity;
	pointer objects;
};


// vector comparator specializations
template<class T, class Alloc>
bool operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if(lhs.size() != rhs.size()) return false;

	typename vector<T, Alloc>::const_iterator lhs_iter = lhs.begin();
	typename vector<T, Alloc>::const_iterator rhs_iter = rhs.begin();

	while((*lhs_iter) == (*rhs_iter))
	{
		++lhs_iter;
		++rhs_iter;
		if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end())) break;
	}

	if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end()))
		return true;
	else
		return false;
}
template<class T, class Alloc>
bool operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if(lhs.size() != rhs.size()) return true;

	typename vector<T, Alloc>::const_iterator lhs_iter = lhs.begin();
	typename vector<T, Alloc>::const_iterator rhs_iter = rhs.begin();

	while((*lhs_iter) == (*rhs_iter))
	{
		++lhs_iter;
		++rhs_iter;
		if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end())) break;
	}

	if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end()))
		return false;
	else
		return true;
}
template<class T, class Alloc>
bool operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if(lhs.size() < rhs.size())
		return true;
	else if(lhs.size() > rhs.size())
		return false;
	else if(lhs.size() == rhs.size())
	{
		typename vector<T, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename vector<T, Alloc>::const_iterator rhs_iter = rhs.begin();

		while((*lhs_iter) == (*rhs_iter))
		{
			if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end())) break;
			++lhs_iter;
			++rhs_iter;
		}

		if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end()))
			return false;
		else if((*lhs_iter) < (*rhs_iter))
			return true;
		else if((*lhs_iter) > (*rhs_iter))
			return false;
	}
}
template<class T, class Alloc>
bool operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if(lhs.size() < rhs.size())
		return true;
	else if(lhs.size() > rhs.size())
		return false;
	else if(lhs.size() == rhs.size())
	{
		typename vector<T, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename vector<T, Alloc>::const_iterator rhs_iter = rhs.begin();

		while((*lhs_iter) == (*rhs_iter))
		{
			if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end())) break;
			++lhs_iter;
			++rhs_iter;
		}

		if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end()))
			return true;
		else if((*lhs_iter) < (*rhs_iter))
			return true;
		else if((*lhs_iter) > (*rhs_iter))
			return false;
	}
}
template<class T, class Alloc>
bool operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if(lhs.size() > rhs.size())
		return true;
	else if(lhs.size() < rhs.size())
		return false;
	else if(lhs.size() == rhs.size())
	{
		typename vector<T, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename vector<T, Alloc>::const_iterator rhs_iter = rhs.begin();

		while((*lhs_iter) == (*rhs_iter))
		{
			if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end())) break;
			++lhs_iter;
			++rhs_iter;
		}

		if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end()))
			return false;
		else if((*lhs_iter) > (*rhs_iter))
			return true;
		else if((*lhs_iter) < (*rhs_iter))
			return false;
	}
}
template<class T, class Alloc>
bool operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if(lhs.size() > rhs.size())
		return true;
	else if(lhs.size() < rhs.size())
		return false;
	else if(lhs.size() == rhs.size())
	{
		typename vector<T, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename vector<T, Alloc>::const_iterator rhs_iter = rhs.begin();

		while((*lhs_iter) == (*rhs_iter))
		{
			if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end())) break;
			++lhs_iter;
			++rhs_iter;
		}

		if((lhs_iter == lhs.end()) && (rhs_iter == rhs.end()))
			return false;
		else if((*lhs_iter) > (*rhs_iter))
			return true;
		else if((*lhs_iter) < (*rhs_iter))
			return false;
	}
}
template<class T, class Alloc>
void swap( vector<T, Alloc>& a, vector<T, Alloc>& b )
{
	vector<T, Alloc> a_old(a);
	a.operator=(b);
	b.operator=(a_old);
}

template<class T, class Alloc>
class vector<T, Alloc>::const_iterator
{
	friend class vector;
	friend class vector<T, Alloc>::iterator;
public:
	typedef T value_type;
	typedef T const* pointer;
	typedef T const& reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	const_iterator(T const* _obj = nullptr, int pos = 0):
		position(pos), arr_ref(_obj)
	{}
	const_iterator(const iterator& other):
		position(other.position), arr_ref(other.arr_ref)
	{}
	const_iterator(const const_iterator& other):
		position(other.position), arr_ref(other.arr_ref)
	{}

	inline const_iterator& operator=(const iterator& rhs)
	{
		this->position = rhs.position;
		return *this;
	}
	inline const_iterator& operator=(const const_iterator& rhs)
	{
		this->position = rhs.position;
		return *this;
	}

	inline const_iterator& operator++()
	{
		++position;
		return *this;
	}
	inline const_iterator operator++(int)
	{
		const_iterator tmp(*this);
		++position;
		return tmp;
	}

	inline const_iterator& operator+=(int offset)
	{
		position+=offset;
		return *this;
	}
	inline const_iterator& operator+(int offset)
	{
		return const_iterator(arr_ref, position + offset);
	}

	inline const_iterator& operator--()
	{
		--position;
		return *this;
	}
	inline const_iterator operator--(int)
	{
		const_iterator tmp(*this);
		--position;
		return tmp;
	}

	inline const_iterator& operator-=(int offset)
	{
		position -= offset;
		return *this;
	}
	inline const_iterator& operator-(int offset)
	{
		return const_iterator(arr_ref, position - offset);
	}
	inline int operator-(const const_iterator& rhs)
	{
		return (this->position - rhs.position);
	}
	
	inline pointer operator->() const
		{ return (arr_ref); }

	inline reference operator*() const
		{ return (arr_ref)[position]; }

	inline bool operator==(const const_iterator& rhs)
		{ return (this->position == rhs.position); }

	inline bool operator!=(const const_iterator& rhs)
		{ return (this->position != rhs.position); }

	inline bool operator>(const const_iterator& rhs)
		{ return (this->position > rhs.position); }

	inline bool operator>=(const const_iterator& rhs)
		{ return (this->position >= rhs.position); }

	inline bool operator<(const const_iterator& rhs)
		{ return (this->position < rhs.position); }

	inline bool operator<=(const const_iterator& rhs)
		{ return (this->position <= rhs.position); }

	inline void swap(typename vector<T, Alloc>::const_iterator& rhs)
	{
		typename vector<T, Alloc>::const_iterator tmp(*this);
		this->operator=(rhs);
		rhs.operator=(tmp);
	}

private:
	int position;
	T const* arr_ref;
};

template<class T, class Alloc>
class vector<T, Alloc>::iterator:
	vector<T, Alloc>::const_iterator
{
	friend class vector;
	friend class vector<T, Alloc>::const_iterator;

public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	iterator(T* _obj = nullptr, int pos = 0):
		position(pos), arr_ref(_obj) {}
	iterator(const iterator& rhs):
		position(rhs.position), arr_ref(rhs.arr_ref) {}

	inline iterator& operator=(const iterator& rhs)
	{
		this->position = rhs.position;
		return *this;
	}

	inline iterator& operator++()
	{
		++position;
		return *this;
	}
	inline iterator operator++(int)
	{
		iterator tmp(*this);
		++position;
		return tmp;
	}

	inline iterator& operator+=(int offset)
	{
		position += offset;
		return *this;
	}
	inline iterator operator+(int offset)
	{
		return iterator(arr_ref, position + offset);
	}

	inline iterator& operator--()
	{
		--position;
		return *this;
	}
	inline iterator operator--(int)
	{
		iterator tmp(*this);
		--position;
		return tmp;
	}

	inline iterator& operator-=(int offset)
	{
		position -= offset;
		return *this;
	}
	inline iterator operator-(int offset)
	{
		return iterator(arr_ref, position - offset);
	}
	inline int operator-(iterator other)
	{
		return (this->position - other.position);
	}

	inline pointer operator->() const
		{ return arr_ref; }

	inline reference operator*() const
		{ return arr_ref[position]; }

	inline bool operator==(const typename vector<T, Alloc>::iterator& rhs)
		{ return (this->position == rhs.position); }
	
	inline bool operator!=(const typename vector<T, Alloc>::iterator& rhs)
		{ return (this->position != rhs.position); }
	
	inline bool operator>(const typename vector<T, Alloc>::iterator& rhs)
		{ return (this->position > rhs.position); }
	
	inline bool operator>=(const typename vector<T, Alloc>::iterator& rhs)
		{ return (this->position >= rhs.position); }
	
	inline bool operator<(const typename vector<T, Alloc>::iterator& rhs)
		{ return (this->position < rhs.position); }
	
	inline bool operator<=(const typename vector<T, Alloc>::iterator& rhs)
		{ return (this->position <= rhs.position); }
	
	inline void swap(typename vector<T, Alloc>::iterator& rhs)
	{
		typename vector<T, Alloc>::iterator tmp(*this);
		this->operator=(rhs);
		rhs->operator=(tmp);
	}
private:
	int position;
	T* arr_ref;
};

//////////////////////////////
//							//
//		Vector Class 		//
//							//
//////////////////////////////
// construct from size
template<class T, class Alloc>
vector<T, Alloc>::vector( typename vector<T, Alloc>::size_type size ):
	_size(size), _capacity(size + SPARE_CAPACITY)
{
	objects = new vector<T, Alloc>::value_type[_capacity];
}

// copy constructor
template<class T, class Alloc>
vector<T, Alloc>::vector( const vector<T, Alloc>& rhs )
{
	this->operator=(rhs);
}

template<class T, class Alloc>
vector<T, Alloc>::~vector()
{
	clear();
	_capacity = 0;
	delete[] objects;
}

// return true if empty
template<class T, class Alloc>
bool vector<T, Alloc>::empty() const
{
	return (_size == 0);
}

// return size
template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
{
	return _size;
}

// return maximum element count
template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
{
	return std::numeric_limits<typename vector<T, Alloc>::size_type>::max();
}

// return capacity
template<class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
{
	return _capacity;
}

// return data at position
template<class T, class Alloc>
inline typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](typename vector<T, Alloc>::size_type pos)
{
	if(pos > _size-1)
	{
		error::array_index_out_of_bounds oob;
		oob.set_array_index(pos);
		throw oob;
	}
	return objects[pos];
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](typename vector<T, Alloc>::size_type pos) const
{
	if(pos > _size-1)
	{
		error::array_index_out_of_bounds oob;
		oob.set_array_index(pos);
		throw oob;
	}
	return objects[pos];
}

// assignment operator
template<class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& rhs)
{
	delete[] objects;
	_size = rhs._size;
	_capacity = rhs._capacity;

	objects = new vector<T, Alloc>::value_type[_capacity];

	for(vector<T, Alloc>::iterator it = rhs.begin();
		it != rhs.end();
		++it)
	{
		push_back(*it);
	}

	return *this;
}

// resize the array
template<class T, class Alloc>
void vector<T, Alloc>::resize(vector<T, Alloc>::size_type size)
{
	if(size > _capacity)
	{
		_capacity = size*2;

		typename vector<T, Alloc>::pointer old = objects;
		delete[] objects;

		objects = new typename vector<T, Alloc>::value_type[_capacity];

		for(int i = 0; i < _size; ++i)
		{
			objects[i] = old[i];
		}

		delete[] old;
	}

	_size = size;
}

// allocate additional memory for the vector
template<class T, class Alloc>
void vector<T, Alloc>::reserve(vector<T, Alloc>::size_type capacity)
{
	if(capacity <= _capacity) return;

	_capacity = capacity;

	typename vector<T, Alloc>::pointer old = objects;
	delete[] objects;
	objects = new typename vector<T, Alloc>::value_type[_capacity];

	for(int i = 0; i < _size; ++i)
	{
		objects[i] = old[i];
	}

	delete[] old;
}

template<class T, class Alloc>
void vector<T, Alloc>::shrink_to_fit()
{
	typename vector<T, Alloc>::pointer old = objects;
	_capacity = _size;
	delete[] objects;
	objects = new typename vector<T, Alloc>::value_type[_capacity];

	for(int i = 0; i < _capacity; ++i)
	{
		objects[i] = old[i];
	}
	delete[] old;
}

// push value to end of list
template<class T, class Alloc>
void vector<T, Alloc>::push_back(vector<T, Alloc>::const_reference data)
{
	if(_size+1 > _capacity)
	{
		reserve((_size+1)*2);
	}

	objects[_size] = data;
	++_size;
}

template<class T, class Alloc>
void vector<T, Alloc>::push_back(vector<T, Alloc>::value_type&& data)
{
	if(_size+1 > _capacity)
	{
		reserve((_size+1)*2);
	}

	objects[_size] = data;
	++_size;
}

// TODO: implement emplace_back func
template<class T, class Alloc> template<class... Args>
typename vector<T, Alloc>::reference vector<T, Alloc>::emplace_back(Args&&... args)
{}

template<class T, class Alloc>
inline void vector<T, Alloc>::pop_back()
{
	if(!empty()) --_size;
}

template<class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
{
	return objects[_size];
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
	typename vector<T, Alloc>::const_iterator pos,
	typename vector<T, Alloc>::const_reference data)
{
	auto index = pos.position;

	if((_size+1) > _capacity)
	{
		reserve((_size + 1) * 2);
	}

	for(int i = _size-1; i >= index; --i)
	{
		objects[i + 1] = objects[i];
		
		if(i == index)
		{
			objects[i] = data;
		}
	}

	++_size;

	return iterator(objects, index);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
	typename vector<T, Alloc>::const_iterator pos,
	typename vector<T, Alloc>::value_type&& data)
{
	auto index = pos.position;

	if((_size+1) > _capacity)
	{
		reserve((_size + 1) * 2);
	}

	for(int i = _size-1; i >= index; --i)
	{
		objects[i + 1] = objects[i];
	
		if(i == index)
		{
			objects[i] = data;
		}
	}

	++_size;

	return iterator(objects, index);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
	typename vector<T, Alloc>::const_iterator pos,
	typename vector<T, Alloc>::size_type count,
	typename vector<T, Alloc>::const_reference data)
{
	auto index = (pos.position);

	if(_size + count > _capacity) reserve((_size+count) * 2);

	for(int i = _size; i >= index; --i)
	{
		objects[i+count] = objects[i];

		if(i == index)
		{
			for(int k = 0; k < count; ++k)
			{
				objects[i+k] = data;
			}
		}
	}

	_size += count;

	return iterator(objects, index);
}

// TODO: emplace function
template<class T, class Alloc> template<class... Args>
typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(
	typename vector<T, Alloc>::const_iterator pos, Args&&... args)
{}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
	typename vector<T, Alloc>::iterator pos)
{
	auto index = pos.position;

	for(int i = index; i < _size; ++i)
	{
		objects[i] = objects[i+1];
	}

	--_size;

	return iterator(objects, index);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
	typename vector<T, Alloc>::const_iterator pos)
{
	auto index = pos.position;

	for(int i = index; i < _size; ++i)
	{
		objects[i] = objects[i+1];
	}

	--_size;

	return iterator(objects, index);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
	typename vector<T, Alloc>::iterator first,
	typename vector<T, Alloc>::iterator last)
{
	auto difference = (last.position - first.position);

	for(int i = first.position; i < (_size - difference); ++i)
	{
		objects[i] = objects[i+difference];
	}

	_size -= difference;

	return iterator(objects, first.position);
}

template<class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
	typename vector<T, Alloc>::const_iterator first,
	typename vector<T, Alloc>::const_iterator last)
{
	auto difference = (last.position - first.position);

	for(int i = first.position; i < (_size - difference); ++i)
	{
		objects[i] = objects[i+difference];
	}

	_size -= difference;

	return iterator(objects, first.position);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::clear()
{
	_size = 0;
	delete[] objects;
	objects = new typename vector<T, Alloc>::value_type[_capacity];
}

// iterator access for beginning
template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::begin()
	{ return typename vector<T, Alloc>::iterator(objects, 0); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const
	{ return typename vector<T, Alloc>::const_iterator(objects, 0); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin() const
	{ return typename vector<T, Alloc>::const_iterator(objects, 0); }

template<class T, class Alloc>
inline typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()
	{ return typename vector<T, Alloc>::reverse_iterator(objects, 0); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const
	{ return typename vector<T, Alloc>::const_reverse_iterator(objects, 0); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crbegin() const
	{ return typename vector<T, Alloc>::const_reverse_iterator(objects, 0); }

// iterator access for end
template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::end()
	{ return typename vector<T, Alloc>::iterator(objects, _size); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const
	{ return typename vector<T, Alloc>::const_iterator(objects, _size); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend() const
	{ return typename vector<T, Alloc>::const_iterator(objects, _size); }

template<class T, class Alloc>
inline typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend()
	{ return typename vector<T, Alloc>::reverse_iterator(objects, _size); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const
	{ return typename vector<T, Alloc>::const_reverse_iterator(objects, _size); }
template<class T, class Alloc>
inline typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crend() const
	{ return typename vector<T, Alloc>::const_reverse_iterator(objects, _size); }

template<class T, class Alloc>
std::string vector<T, Alloc>::to_string(const char delim) const
{
	std::stringstream ss;
	for(typename vector<T, Alloc>::const_iterator it = begin();
		it != end();
		++it)
	{
		ss << (*it) << delim;
	}

	return (ss.str());
}

template<class T, class Alloc>
std::ostream& operator<<(std::ostream& os, const vector<T, Alloc>& vec)
{
	os << (vec.to_string());
	return os;
}

template<class T, class Alloc>
std::istream& operator>>(std::istream& is, vector<T, Alloc>& vec)
{
	T x;
	is >> x;
	vec.push_back(x);
	return is;
}

#endif