#include <exception>
#include <iterator>
#include "vector.h"

template<class T,
		 class Alloc>
class vector<T, Alloc>::const_iterator:
	virtual public std::iterator<std::random_access_iterator_tag, T>
{
	friend class vector;
	friend class vector<T, Alloc>::iterator;

	typedef const T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef std::size_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	vector<T, Alloc>::size_type position
	pointer _ref;
public:
	const_iterator(pointer ref):
		_ref(ref) {}
	const_iterator(const iterator& it):
		_ref(it._ref), position(other.position) {}
	const_iterator(const const_iterator& it):
		_ref(it._ref), position(other.position) {}

	inline const_iterator& operator=(const iterator& other)
	{
		_ref = other._ref;
		position = other.position;
	}

	inline const_iterator& operator=(const const_iterator& other)
	{
		_ref = other._ref;
		position = other.position;
	}

	inline const_iterator& operator++()
	{
		if(position++ > size())
		_ref = objects[position++];
		return tmp;
	}

	inline const_iterator operator++(int)
	{
		const_iterator tmp(*this);
		_ref = objects[position++];
		return tmp;
	}

	inline reference operator*() const
	{
		return *_ref;
	}

	inline pointer operator->() const
	{
		return this->_ref;
	}


};

template<class T,
		 class Alloc>
class vector<T, Alloc>::iterator:
	virtual public std::iterator<std::random_access_iterator_tag, T>,
	public vector::const_iterator
{
	friend class vector;
	friend class vector<T, Alloc>::const_iterator;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t difference_type;
	typedef std::random_access_iterator_tag iterator_category;

	pointer ref;
public:
	iterator(pointer ref):
		_ref(ref) {}
	iterator(const iterator& rhs):
		_ref(rhs._ref) {}

private:
};

template<class T,
		 class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[]( int index )
{
	#ifndef NO_CHECK
	if( index < 0 || index > this->_size )
		throw error::array_index_out_of_bounds( index, this->_size );
	#endif

	return objects[index];
}


template<class T,
		 class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[]( int index ) const
{
	#ifndef NO_CHECK
	if( index < 0 || index > this->_size )
		throw error::array_index_out_of_bounds( index, this->_size );
	#endif

	return objects[index];
}

template<class T,
		 class Alloc>
const vector<T, Alloc>& vector<T, Alloc>::operator=( const vector& rhs )
{
	if(this == &rhs) return *this;

	delete[] objects;
	this->_size = rhs.size();
	this->_capacity = rhs.capacity();

	this->objects = new vector<T, Alloc>::value_type[ _capacity ];
	for( vector<T, Alloc>::size_type it = 0; it < _size; it++ )
	{
		objects[it] = rhs.objects[it];
	}
	return *this;
}

template<class T,
		 class Alloc>
void vector<T, Alloc>::resize( vector<T, Alloc>::size_type size )
{
	if( size > _capacity )
	{
		this->reserve( size * 2 );
	}
	_size = size;
}

template<class T,
		 class Alloc>
void vector<T, Alloc>::reserve( vector<T, Alloc>::size_type capacity )
{
	T* oldarr = objects;

	vector<T, Alloc>::size_type copy_size = capacity < _size ? capacity : _size;
	copy_size += this->SPARE_CAPACITY;

	objects = new vector<T, Alloc>::value_type[capacity];
	for( int c = 0; c < size; c++ )
	{
		objects[c] = oldarr[c];
	}

	_size = copy_size;
	_capacity = capacity;
}

template<class T,
		 class Alloc>
void vector<T, Alloc>::shrink_to_fit()
{

}

template<class T,
		 class Alloc>
void vector<T, Alloc>::push_back( vector<T, Alloc>::const_reference data )
{
	if(_size == _capacity)
	{
		reserve( 2*_capacity + 1 );
	}
	objects[_size++] = data;
}

template<class T,
		 class Alloc>
void vector<T, Alloc>::push_back( vector<T, Alloc>::value_type&& data )
{
	if(_size == _capacity)
	{
		reserve( 2*_capacity + 1 );
	}
	objects[_size++] = data;
}

/* TODO: learn about variadic templates
template<class T,
		 class Alloc,
		 class... Args>
void vector<T, Alloc>::emplace_back( Args&&... args )
{
	if(_size == _capacity)
	{
		reserve( 2*_capacity + 1 );
	}
	objects[_size++] = args;
}

template<class T,
		 class Alloc,
		 class... Args>
vector<T, Alloc>::reference vector<T, Alloc>::emplace_back( Args&&... args )
{

}*/

template<class T,
		 class Alloc>
void vector<T, Alloc>::pop_back()
{
	if(empty()) throw error::underflow("cannot call 'pop' on an empty vector");
	_size--;
}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
{
	if(empty()) throw error::underflow("cannot call 'back' on an empty vector");
	return objects[_size-1];
}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
	typename vector<T, Alloc>::iterator pos, vector<T, Alloc>::const_reference data ) 
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
	vector<T, Alloc>::const_iterator pos, vector<T, Alloc>::const_reference data )
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
	vector<T, Alloc>::const_iterator pos, vector<T, Alloc>::value_type&& data ) 
{

}

template<class T,
		 class Alloc>
void vector<T, Alloc>::insert( typename vector<T, Alloc>::iterator pos,
	vector<T, Alloc>::size_type count, vector<T, Alloc>::const_reference data )
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert( vector<T, Alloc>::const_iterator,
	vector<T, Alloc>::size_type count, vector<T, Alloc>::const_reference )
{

}

template<class T,
		 class Alloc>
template<class InputIt>
void vector<T, Alloc>::insert( typename vector<T, Alloc>::iterator pos,
	InputIt first, InputIt last )
{

}

template<class T,
		 class Alloc>
template<class InputIt>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert( vector<T, Alloc>::const_iterator pos,
	InputIt first, InputIt last )
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert( vector<T, Alloc>::const_iterator pos,
	std::initializer_list<vector<T, Alloc>::value_type> ilist)
{

}

/* TODO: learn about variadic templates
template<class T,
		 class Alloc,
		 class... Args>
iterator emplace( vector<T, Alloc>::const_reference data,
	Args&&... args)
{

}*/

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( typename vector<T, Alloc>::iterator pos )
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( vector<T, Alloc>::const_iterator pos )
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( 
	typename vector<T, Alloc>::iterator pos, typename vector<T, Alloc>::iterator last )
{

}

template<class T,
		 class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
	vector<T, Alloc>::const_iterator first, typename vector<T, Alloc>::const_iterator last )
{

}

template<class T,
		 class Alloc>
void vector<T, Alloc>::clear()
{
	delete[] objects;
	objects = new T[_capacity];
}

template<class T,
		 class Alloc>
void vector<T, Alloc>::swap( vector<T, Alloc>& other )
{
	vector<T, Alloc> temp(*this);
	this->operator=( other );
	other = temp;
}

template<class T,
		 class Alloc >
void vector<T, Alloc>::print() const
{
	// TODO: finish print function
}