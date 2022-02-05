#include <string_tools/split/split.hpp>
#include <iostream>

template <typename CharType>
string_tools::split<std::string>::split(std::string delim, std::string target)
{
	std::string::size_type it_start = 0, it_end = target.find(delim, it_start);
	
	for ( ; it_end  != target.npos; 
			it_start = it_end + delim.length(), it_end = target.find(delim, it_start))
		__M_split_vector.push_back(target.substr(it_start, it_end - it_start));
		__M_split_vector.push_back(target.substr(it_start, target.length()));
}

string_tools::split<std::string>::iterator string_tools::split<std::string>::begin()
{
	return split<std::string>::iterator(__M_split_vector);
}

string_tools::split<std::string>::iterator string_tools::split<std::string>::end  ()
{
	return split<std::string>::iterator(__M_split_vector, __M_split_vector.size());
}

string_tools::split<std::string>::iterator::iterator(std::vector<std::string>& vec, offset_type off) : __M_iterator_vector(vec),
																									   __M_iterator_offset(off) { }

std::string& string_tools::split<std::string>::iterator::operator* ()
{
	return __M_iterator_vector[__M_iterator_offset];
}

string_tools::split<std::string>::iterator& string_tools::split<std::string>::iterator::operator= (std::string& target)
{
	__M_iterator_vector[__M_iterator_offset] = target;
	return *this;
}

string_tools::split<std::string>::iterator& string_tools::split<std::string>::iterator::operator= (const iterator& target)
{
	__M_iterator_vector[__M_iterator_offset] = target.__M_iterator_vector[target.__M_iterator_offset];
	return *this;
}

bool		 string_tools::split<std::string>::iterator::operator==(iterator& target)
{
	return target.__M_iterator_offset == __M_iterator_offset;
}

bool		 string_tools::split<std::string>::iterator::operator!=(iterator& target)
{
	return target.__M_iterator_offset != __M_iterator_offset;
}

string_tools::split<std::string>::iterator& string_tools::split<std::string>::iterator::operator++()
{
	if (__M_iterator_vector.size() == 0)
		return *this;

	if (__M_iterator_offset < __M_iterator_vector.size())
		__M_iterator_offset++;

	return *this;
}