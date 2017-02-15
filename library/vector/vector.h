#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>
#include <exception>
#include <limits>
#include <memory>
#include <stdio.h>
#include <string>

namespace error
{
	// error base error
	struct base: std::exception
	{
		virtual void format_error_message() const = 0;

		const char* what() const throw()
		{
			format_error_message();
			return error_message_buffer;
		}

		mutable char error_message_buffer[256];
	};

	// set errno value
	struct with_errno
	{
		with_errno()
		{
			errno_value = 0;
		}

		void set_errno(int errno_value)
		{
			this->errno_value = errno_value;
		}

		int errno_value;
	};

	// underflow array error
	struct underflow:
		base,
		with_errno
	{
		underflow()
		{
			underflow_flag = 0;
		}

		underflow(const char* msg_buffer)
		{
			underflow_flag = 0;
			this->msg_buffer = new char[std::strlen("Operating out of bounds of array: ")
										+std::strlen(msg_buffer)+1];
			std::strcpy(this->msg_buffer, "Operating out of bounds of array: ");
			std::strcpy(this->msg_buffer, msg_buffer);
		}

		void set_underflow(int underflow_flag)
		{
			this->underflow_flag = underflow_flag;
		}
		
		void format_error_message() const
		{
			if(errno_value != 0)
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					msg_buffer);
			}
		}

		char* msg_buffer;
		int underflow_flag;
	};

	// overflow array error
	struct overflow:
		base,
		with_errno
	{
		overflow()
		{
			overflow_flag = 0;
		}

		overflow(const char* msg_buffer)
		{
			overflow_flag = 0;
			this->msg_buffer = new char[std::strlen("Operating out of bounds of array: ")
										+std::strlen(msg_buffer)+1];
			std::strcpy(this->msg_buffer, "Operating out of bounds of array: ");
			std::strcpy(this->msg_buffer, msg_buffer);
		}

		void set_overflow(int overflow_flag)
		{
			this->overflow_flag = overflow_flag;
		}

		void format_error_message() const
		{
			if(errno_value != 0)
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					msg_buffer);
			}
		}

		char* msg_buffer;
		int overflow_flag;
	};

	// index out of bounds of array
	struct array_index_out_of_bounds:
		base,
		with_errno
	{
		array_index_out_of_bounds(int index, int arr_size)
		{
			this->index = index;
			this->arr_size = arr_size;
		}

		void format_error_message() const
		{
			if(errno_value != 0)
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					"Index %c outside bounds of array of size %c",
					index, arr_size);
			}
		}

		int index;
		int arr_size;
	};
}

template<class T,
		 class Allocator = std::allocator<T>>
class vector
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef Allocator allocator_type;

public:
	class const_iterator;
	class iterator;

	explicit vector( size_type size = 0 ): _size(size), _capacity(size)
	{
		objects = new value_type[_capacity];
	}
	vector(const vector& rhs): objects( NULL )
	{
		this->operator=(rhs);
	}
	~vector()
	{
		delete[] objects;
	}

	inline bool empty() const { return _size; }
	inline size_type size() const { return _size; }
	inline size_type max_size() const { return std::numeric_limits<size_type>::max(); }
	inline size_type capacity() const { return _capacity; }

	reference operator[]( int index );
	const_reference operator[]( int index ) const;

	const vector& operator=( const vector& rhs );
	void resize( size_type size );
	void reserve( size_type capacity );
	void shrink_to_fit();

	void push_back( const_reference data );
	void push_back( value_type&& data );

	template<class... Args>
	void emplace_back( Args&&... args );
	template<class... Args>
	reference emplace_back( Args&&... args );

	void pop_back();
	const_reference back() const;

	iterator insert( iterator pos, const_reference data );
	iterator insert( const_iterator pos, const_reference data );
	iterator insert( const_iterator pos, value_type&& data );
	void insert( iterator pos, size_type count, const_reference data );
	iterator insert( const_iterator pos, size_type count, const_reference data );
	template<class InputIt>
	void insert( iterator pos, InputIt first, InputIt last );
	template<class InputIt>
	iterator insert( const_iterator pos, InputIt first, InputIt last );
	iterator insert( const_iterator pos, std::initializer_list<value_type> ilist );

	template<class... Args>
	iterator emplace( const_reference data, Args&&... args );

	iterator erase( iterator pos );
	iterator erase( const_iterator pos );
	iterator erase( iterator first, iterator last );
	iterator erase( const_iterator first, const_iterator last );

	void clear();

	void swap( vector& other );

	inline iterator begin() { return iterator(&objects[ 0 ]); }
	inline const_iterator begin() const { return const_iterator(&objects[ 0 ]); }
	inline const_iterator cbegin() const { return const_iterator(&objects[ 0 ]); }

	inline iterator end() { return iterator(&objects[ 0 ]); }
	inline const_iterator end() const { return const_iterator(&objects[ 0 ]); }
	inline const_iterator cend() const { return const_iterator(&objects[ 0 ]); }

	void print() const;

	enum { SPACE_CAPACITY = 16 };

private:
	size_type _size;
	size_type _capacity;
	pointer objects;
};


// vector comparator specializations
template<class T, class Alloc>
bool operator==( const vector<T, Alloc>& lhs,
				 const vector<T, Alloc>& rhs );
template<class T, class Alloc>
bool operator!=( const vector<T, Alloc>& lhs,
				 const vector<T, Alloc>& rhs );
template<class T, class Alloc>
bool operator<( const vector<T, Alloc>& lhs,
				const vector<T, Alloc>& rhs );
template<class T, class Alloc>
bool operator<=( const vector<T, Alloc>& lhs,
				 const vector<T, Alloc>& rhs );
template<class T, class Alloc>
bool operator>( const vector<T, Alloc>& lhs,
				const vector<T, Alloc>& rhs );
template<class T, class Alloc>
bool operator>=( const vector<T, Alloc>& lhs,
				 const vector<T, Alloc>& rhs );


// iterator comparator specializations
template<class T, class Alloc>
bool operator==( const typename vector<T, Alloc>::iterator& lhs,
				 const typename vector<T, Alloc>::iterator& rhs );
template<class T, class Alloc>
bool operator!=( const typename vector<T, Alloc>::iterator& lhs,
				 const typename vector<T, Alloc>::iterator& rhs );
template<class T, class Alloc>
bool operator<( const typename vector<T, Alloc>::iterator& lhs,
				const typename vector<T, Alloc>::iterator& rhs );
template<class T, class Alloc>
bool operator<=( const typename vector<T, Alloc>::iterator& lhs,
				 const typename vector<T, Alloc>::iterator& rhs );
template<class T, class Alloc>
bool operator>( const typename vector<T, Alloc>::iterator& lhs,
				const typename vector<T, Alloc>::iterator& rhs );
template<class T, class Alloc>
bool operator>=( const typename vector<T, Alloc>::iterator& lhs,
				 const typename vector<T, Alloc>::iterator& rhs );

// const_iterator comparator specializations
template<class T, class Alloc>
bool operator==( const typename vector<T, Alloc>::const_iterator& lhs,
				 const typename vector<T, Alloc>::const_iterator& rhs );
template<class T, class Alloc>
bool operator!=( const typename vector<T, Alloc>::const_iterator& lhs,
				 const typename vector<T, Alloc>::const_iterator& rhs );
template<class T, class Alloc>
bool operator<( const typename vector<T, Alloc>::const_iterator& lhs,
				const typename vector<T, Alloc>::const_iterator& rhs );
template<class T, class Alloc>
bool operator<=( const typename vector<T, Alloc>::const_iterator& lhs,
				 const typename vector<T, Alloc>::const_iterator& rhs );
template<class T, class Alloc>
bool operator>( const typename vector<T, Alloc>::const_iterator& lhs,
				const typename vector<T, Alloc>::const_iterator& rhs );
template<class T, class Alloc>
bool operator>=( const typename vector<T, Alloc>::const_iterator& lhs,
				 const typename vector<T, Alloc>::const_iterator& rhs );

template<class T, class Alloc>
void swap( vector<T, Alloc>& a, vector<T, Alloc>& b );


#endif