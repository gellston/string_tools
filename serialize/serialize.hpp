#pragma once
#include <string>
#include <string_view>

namespace string_tools {

	template <typename StringType, typename... NextArgs>
	void __serialize(char*, StringType&&, NextArgs&&...);

	template <typename StringType>
	void __serialize(char*, StringType&&);

	template <typename... StringType>
	void serialize  (char* s_ptr, StringType&&... s_next) { __serialize(s_ptr, std::forward<StringType>(s_next)...); }
}

template <typename StringType, typename... NextArgs>
void string_tools::__serialize(char* s_ptr, StringType&& s_str, NextArgs&&... s_next)
{
	std::memcpy(s_ptr,  s_str.data()  , s_str.length());
	__serialize(s_ptr + s_str.length(), std::forward<NextArgs>(s_next)...);
}

template <typename StringType>
void string_tools::__serialize(char* s_ptr, StringType&& s_str)
{
	std::memcpy(s_ptr, s_str.data(), s_str.length());
}