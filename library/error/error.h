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
	// base
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

	/* array errors */
	struct with_array_index
	{
		with_array_index():
			array_index(0) {}

		void set_array_index(const int a)
			{ array_index = a; }

		int array_index;
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
	}; /* array errors end */

	/* iterator errors */
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
	}; /* end iterator errors */

	/* math errors */
	#include <cmath>


	struct with_coord /* "with coordinate" base virtual function holder */
	{
		virtual int check_dimensions()=0;
	};

	#include "math\cartesian.h"
	struct with_cartesian: /* cartesian coordinate base */
		virtual with_coord
	{
		with_cartesian()
		{
			this->init_cartesian();
		}

		void init_cartesian()
		{
			dimensions = 0;
			x = INFINITY;
			y = INFINITY;
			z = INFINITY;
		}

		void set_cartesian(coord c)
		{
			int i = 3;
			for( ; i > 0; --i)
			{
				switch(i)
				{
					case 0: if(c.x != INFINITY) ++dimensions; this->x = c.x; break;
					case 1: if(c.y != INFINITY) ++dimensions; this->y = c.y; break;
					case 2: if(c.z != INFINITY) ++dimensions; this->z = c.z; break;
				}
			}
		}

		int check_dimensions(int d)
		{
			dimensions = 0;
			if(this->x != INFINITY) ++dimensions;
			if(this->y != INFINITY) ++dimensions;
			if(this->z != INFINITY) ++dimensions;
			return dimensions;
		}

		int dimensions;
		double x;
		double y;
		double z;
	}; /* cartesian coordinate base setup end */

	#include "polar.h"
	struct with_polar:
		virtual with_coord
	{
		with_polar()
		{
			this->init_polar();
		}

		void init_polar()
		{
			dimensions = 0;
			radial = INFINITY;
			degree = INFINITY;
			azimuth = INFINITY;
		}

		void set_polar(polar p)
		{
			int i = 3;
			for( ; i > 0; --i)
			{
				switch(i)
				{
					case 0: if(p.radial != INFINITY) ++dimensions; this->radial = p.radial; break;
					case 1: if(p.degree != INFINITY) ++dimensions; this->degree = p.degree; break;
					case 2: if(p.azimuth != INFINITY) ++dimensions; this->azimuth = p.azimuth; break;
				}
			}
		}

		int check_dimensions()
		{
			dimensions = 0;
			if(this->radial != INFINITY) ++dimensions;
			if(this->degree != INFINITY) ++dimensions;
			if(this->azimuth != INFINITY) ++dimensions;
			return dimensions;
		}

		int dimensions;
		double radial;
		double degree;
		double azimuth;
	};

	struct needs_more_data_to_convert:
		base,
		with_cartesian,
		with_polar
	{
		void format_error_message()const
		{
		}
	}


};

#endif