#pragma once
#include <iostream>
#include <concepts>
#include <string_tools/extract/assign.hpp>

/*
* Something like scanf(...).
*/

namespace string_tools {

	template <typename StringArg, typename... NextArgs>
	void extract(std::string&, std::string, StringArg&&, NextArgs&&...);

	template <typename StringArg>
	void extract(std::string&, std::string, StringArg&&);

	template <typename StringArg, typename... NextArgs>
	void extract(std::string_view&, std::string, StringArg&&, NextArgs&&...);

	template <typename StringArg>
	void extract(std::string_view&, std::string, StringArg&&);

}

template <typename StringArg, typename... NextArgs>
void string_tools::extract(std::string& target, std::string delim, StringArg&& arg, NextArgs&&... next) 
{
	std::size_t pos       = target.find(delim, 0);
	if (pos == std::string::npos) { // Cannot find anything identical with "delim".
		pos					  = target.length();
		string_tools::assign_to(arg, target.substr(0, pos));

		return;
	}
	else
		string_tools::assign_to(arg, target.substr(0, pos));

	std::string			  next_str (target, pos + delim.length(), delim.length() - pos);
	string_tools::extract(next_str, delim, next...);
}

template <typename StringArg>
void string_tools::extract(std::string& target, std::string delim, StringArg&& arg) 
{
	std::size_t   pos     = target.find(delim, 0);
	string_tools::assign_to(arg, target.substr(0, pos));
}

template <typename StringArg, typename... NextArgs>
void string_tools::extract(std::string_view& target, std::string delim, StringArg&& arg, NextArgs&&... next)
{
	std::size_t pos		 = target.find(delim, 0), 
			    next_pos = pos + delim.length();
	if (pos == std::string_view::npos) {
		pos			= target.length();
		string_tools::assign_to(arg, target.substr(0, pos));

		return;
	}
	else
		string_tools::assign_to(arg, target.substr(0, pos));

	std::string_view      next_str(target.data() + next_pos, target.length() - next_pos);
	string_tools::extract(next_str, delim, next...);
}

template <typename StringArg>
void string_tools::extract(std::string_view& target, std::string delim, StringArg&& arg)
{
	std::size_t pos = target.find(delim, 0);
	if (pos == std::string_view::npos)
		string_tools::assign_to(arg, target.substr(0, target.length()));
	else
		string_tools::assign_to(arg, target.substr(0, pos));
}