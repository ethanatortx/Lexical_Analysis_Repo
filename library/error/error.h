#ifndef ERROR_H
#define ERROR_H

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <exception>
#include <memory>

namespace error
{
	struct base : std::exception
	{
		virtual void format_error_message()const = 0;

		const char* what() const throw()
		{
			format_error_message();
			return error_message_buffer;
		}

		mutable char error_message_buffer[256];
	};

	struct with_array_index
	{
		with_array_index():
			array_index(0) {}

		void set_array_index(const int a)
			{ array_index = a; }

		int array_index;
	};

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

	struct array_index_out_of_bounds:
		base,
		with_array_index,
		with_errno
	{
		void format_error_message() const
		{
			if(errno_value != 0)
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					"Array index \"%d\" is out of array scope because \"%s\".",
					array_index, std::strerror(errno_value));
			}
			else
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					"Array index \"%d\" is out of array scope.",
					array_index);
			}
		}
	};

	struct with_iterator_range
	{
		with_iterator_range()
		{
			iterator_range = std::pair<int, int>(0, 0);
		}

		set_iterator_range(int first, int last)
		{
			iterator_range.first = first;
			iterator_range.second = last;
		}

		std::pair<int, int> iterator_range;
	};

	struct invalid_iterator_range:
		base,
		with_iterator_range
	{
		void format_error_message() const
		{
			if(iterator_range.first > iterator_range.second)
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					"Iterator range position \"%d\" to position \"%d\" is invalid, negative range is not possible.",
					iterator_range.first, iterator_range.second);
			}
			else
			{
				snprintf(error_message_buffer, sizeof(error_message_buffer),
					"Iterator range position \"%d\" to position \"%d\" is invalid.",
					iterator_range.first, iterator_range.second);
			}
		}
	};
};

#endif