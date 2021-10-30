#pragma once
#include <string>
#include <string_view>

namespace string_tools {
	void trim(std::string&, std::string);
}

void string_tools::trim(std::string& target, std::string delim)
{
	std::size_t pos;
	for (pos = target.find(delim); pos != std::string::npos; pos = target.find(delim))
		target.erase(pos, delim.length());
}