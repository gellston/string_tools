#pragma once
#include <Windows.h>
#include <cstring>
#include <cstddef>

#include <iostream>

#define PAGE_SIZE				 4096
#define BOUND_TO_PAGE_SIZE(size) size + (PAGE_SIZE - (size % PAGE_SIZE))

namespace string_tools {
namespace allocator    {

	union __memory_expr
	{
		void* expr_pointer;
		std::size_t expr_integer;
	};


	template <typename AllocateType>
	class page
	{
	public:
		typedef AllocateType   value_type;
		typedef std::size_t    size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::true_type propagate_on_container_move_assignment;
		typedef std::true_type is_always_equal;

	public:
		constexpr page();

		constexpr AllocateType* allocate  (std::size_t);
		constexpr void			deallocate(AllocateType*, std::size_t);

	protected:

		constexpr void* __create_bound()
		{
			// Creates New Memory Bound.
		}

		constexpr void* __expand_bound()
		{
			/*
			* Expends Committed Area, like following diagram.
			* Before calling __expand_bound(), 
			* Continuity of the reserved and committed memory area must be guaranteed.
			* 
			* +-------------------------+-------------------------+
			* |							|						  |
			* |		Committed Area		|		Reserved Area	  |
			* |							|						  |
			* +-------------------------+-------------------------+
			*							^						  ^
			*						memory_sentry			   memory_end
			* 
			* 
			* --> * +-------------------------+-------------------------+
			*		|						  						    |
			*		|	         Committed Area + Reserved Area 	    |
			*		|						  						    |
			*		+-------------------------+-------------------------+			     -->
			*															^			 	 ^
			*														memory_sentry	  memory_end
			*/
			
			if (memory_sentry.expr_integer == memory_end.expr_integer)
				return nullptr; // Cannot Expand Memory Bound.

			__memory_expr expanded_bound;
			std::size_t   prev_bound_size = (memory_end.expr_integer - memory_start.expr_integer);

			expanded_bound.expr_pointer = VirtualAlloc(memory_end.expr_pointer, prev_bound_size, MEM_RESERVE, PAGE_READWRITE);
			expanded_bound.

		}

		constexpr void __reserve_bound()
		{

		}

	protected:
		__memory_expr memory_start, memory_sentry, memory_end;
		__memory_expr memory_current;
	};
}
}

/*
* +-----------------------------+ <-- reserved_end
* |								|
* |		Reserved Memory Area	|
* |								|
* +-----------------------------+ <-- bound_start, reserved_start
* |								|
* |		In-Bound Memory Area	|
* |								|
* +-----------------------------+ <-- bound_start
* 
*/

template <typename AllocateType>
constexpr string_tools::allocator::page<AllocateType>::page()
{
	memory_start.expr_pointer  = VirtualAlloc(nullptr				   , PAGE_SIZE * 2, MEM_RESERVE, PAGE_READWRITE);
	memory_start.expr_pointer  = VirtualAlloc(memory_start.expr_pointer, PAGE_SIZE	  , MEM_COMMIT , PAGE_READWRITE);

	memory_end.expr_integer	   = memory_start.expr_integer + PAGE_SIZE * 2;
	memory_sentry.expr_integer = memory_start.expr_integer + PAGE_SIZE;
	memory_current			   = memory_start;
}

template <typename AllocateType>
constexpr AllocateType* string_tools::allocator::page<AllocateType>::allocate(std::size_t size)
{
	__memory_expr alloc_memory;

	if (memory_current.expr_integer + size > memory_sentry.expr_integer) { // Exceed the Committed Memory Range.
		/*
	 	* (memory_current.expr_integer + size > memory_end.expr_integer) means that,
		* allocate() function failed to reserve continuous memory region at previous call.
		* 
		* Thus allocate() function will allocate new region of the memory, which size is same with previous.
		*/
		size_type prev_size				= memory_end.expr_integer - memory_start.expr_integer;
		if (memory_current.expr_integer + size > memory_end.expr_integer)
		{
			memory_start.expr_pointer  = VirtualAlloc(nullptr, prev_size * 2, MEM_RESERVE, PAGE_READWRITE);

			memory_sentry.expr_integer = memory_start.expr_integer + prev_size;
			memory_end	 .expr_integer = memory_start.expr_integer + prev_size * 2;

			alloc_memory			    = memory_current;
			memory_current.expr_integer = memory_start.expr_integer + size;
		}
		else
		{
			__memory_expr new_region;
			new_region   .expr_pointer = VirtualAlloc(memory_end.expr_pointer, prev_size, MEM_RESERVE, PAGE_READWRITE);
			memory_sentry.expr_pointer = VirtualAlloc(memory_sentry.expr_pointer,
													 (memory_end.expr_integer - memory_sentry.expr_integer),
													  MEM_COMMIT, PAGE_READWRITE);

			memory_sentry				 = memory_end;
			if (new_region.expr_integer == memory_end.expr_integer) // Continuous
				memory_end	  = new_region;

			alloc_memory				 = memory_current;
			memory_current.expr_integer += size;
		}
	}
	else {
		alloc_memory				 = memory_current;
		memory_current.expr_integer += size;
	}
	
	return (AllocateType*)alloc_memory.expr_pointer;
}

template <typename AllocateType>
constexpr void			string_tools::allocator::page<AllocateType>::deallocate(AllocateType* ptr, std::size_t size)
{
	VirtualFree(ptr, size, MEM_DECOMMIT);
}