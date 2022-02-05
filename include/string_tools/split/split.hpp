#pragma once
#include <vector>

#include <string>
#include <string_view>

namespace string_tools {
	template <typename CharType>
	class split
	{
	public:
		class															 iterator;
		typedef std::basic_string <CharType, std::char_traits<CharType>> string_type;

	public:
		split(string_type, string_type);

	public:
		iterator begin();
		iterator end  ();

	private:
		std::vector<string_type> __M_split_vector;
	};

	template <typename CharType>
	class split<CharType>::iterator
	{
		friend class split<CharType>;
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;

		using vector_type       = std::vector<typename split<CharType>::string_type>;
		using offset_type		= vector_type::size_type;
		
		using value_type		= typename split<CharType>::string_type;
		using pointer		    = value_type*;
		using reference			= value_type&;

	public:
		reference    operator* ();
		
		iterator&    operator= (std::string&);
		iterator&	 operator= (const iterator&);

		bool		 operator==(iterator&);
		bool		 operator!=(iterator&);

		iterator&    operator++();

	private:
		iterator(vector_type&, offset_type off = 0);

	private:
		vector_type& __M_iterator_vector;
		offset_type	 __M_iterator_offset;
	};
}

template <typename CharType>
string_tools::split<CharType>::split(string_type delim, string_type target)
{
	std::string::size_type it_start = 0, it_end = target.find(delim, it_start);
	
	for ( ; it_end  != target.npos; 
			it_start = it_end + delim.length(), it_end = target.find(delim, it_start))
		__M_split_vector.push_back(target.substr(it_start, it_end - it_start));
		__M_split_vector.push_back(target.substr(it_start, target.length()));
}

template <typename CharType>
string_tools::split<CharType>::iterator string_tools::split<CharType>::begin()
{
	return split<CharType>::iterator(__M_split_vector);
}

template <typename CharType>
string_tools::split<CharType>::iterator string_tools::split<CharType>::end  ()
{
	return split<CharType>::iterator(__M_split_vector, __M_split_vector.size());
}

template <typename CharType>
string_tools::split<CharType>::iterator::iterator(vector_type& vec, offset_type off) : __M_iterator_vector(vec),
																							     __M_iterator_offset(off) { }

template <typename CharType>
typename string_tools::split<CharType>::iterator::reference string_tools::split<CharType>::iterator::operator* ()
{
	return __M_iterator_vector[__M_iterator_offset];
}

template <typename CharType>
string_tools::split<CharType>::iterator& string_tools::split<CharType>::iterator::operator= (std::string& target)
{
	__M_iterator_vector[__M_iterator_offset] = target;
	return *this;
}

template <typename CharType>
string_tools::split<CharType>::iterator& string_tools::split<CharType>::iterator::operator= (const iterator& target)
{
	__M_iterator_vector[__M_iterator_offset] = target.__M_iterator_vector[target.__M_iterator_offset];
	return *this;
}

template <typename CharType>
bool		 string_tools::split<CharType>::iterator::operator==(iterator& target)
{
	return target.__M_iterator_offset == __M_iterator_offset;
}

template <typename CharType>
bool		 string_tools::split<CharType>::iterator::operator!=(iterator& target)
{
	return target.__M_iterator_offset != __M_iterator_offset;
}

template <typename CharType>
string_tools::split<CharType>::iterator& string_tools::split<CharType>::iterator::operator++()
{
	if (__M_iterator_vector.size() == 0)
		return *this;

	if (__M_iterator_offset < __M_iterator_vector.size())
		__M_iterator_offset++;

	return *this;
}