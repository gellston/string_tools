#pragma once
#include <vector>

#include <string>
#include <string_view>

namespace string_tools {

	using result_string		 = std::vector<std::string>;
	using result_string_view = std::vector<std::string_view>;

	result_string      tokenize(std::string		& target, std::string delim);
	result_string_view tokenize(std::string_view& target, std::string delim);

}

using string_tools::result_string;
using string_tools::result_string_view;

result_string string_tools::tokenize(std::string& target, std::string delim)
{
	std::size_t   tok_begin = 0, tok_end;
	result_string tok_res;

	for (tok_end = target.find(delim, tok_begin); tok_end != std::string::npos; tok_end = target.find(delim, tok_begin))
	{
		tok_res    .push_back(target.substr(tok_begin, tok_end - tok_begin));
		tok_begin = tok_end + delim.length();
	}

	tok_res.push_back(target.substr(tok_begin, target.length() - tok_begin));
	return  tok_res;
}

result_string_view string_tools::tokenize(std::string_view& target, std::string delim)
{
	std::size_t		   tok_begin = 0, tok_end;
	result_string_view tok_res;

	for (tok_end = target.find(delim, tok_begin); tok_end != std::string::npos; tok_end = target.find(delim, tok_begin))
	{
		tok_res    .push_back(target.substr(tok_begin, tok_end - tok_begin));
		tok_begin = tok_end + delim.length();
	}

	tok_res.push_back(target.substr(tok_begin, target.length() - tok_begin));
	return  tok_res;
}