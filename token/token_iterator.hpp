#pragma once
#include <string>
#include <string_view>

#include <iostream>

namespace string_tools {

	template <typename StringObject = std::string>
	class token_iterator
	{
	public:
		typedef StringObject string_type;
		typedef string_type& string_reference;

	public:
		token_iterator(string_reference, std::string);

		operator bool		  () { return !(token_begin_pos == token_string.length()); }
		string_type operator* () { return   token_string.substr(token_begin_pos, token_end_pos - token_begin_pos); }
		
		void		operator++()   ;
		void		operator++(int);

	protected:
		std::size_t      token_begin_pos, token_end_pos,
						 token_delim_len, token_string_len;

		string_reference token_string;
		std::string      token_delim ;
	};

	template <typename FuncType, typename... FuncArgs>
	void			   tokenize_for_each(std::string& target, std::string delim, FuncType&& func, FuncArgs&&... args);
	template <typename FuncType, typename... FuncArgs>
	void			   tokenize_for_each(std::string_view& target, std::string delim, FuncType&& func, FuncArgs&&... args);

	template <typename FuncType, typename... FuncArgs>
	void			   tokenize_for_each(token_iterator<std::string>&    , FuncType&& func, FuncArgs&&... args);
	template <typename FuncType, typename... FuncArgs>
	void			   tokenize_for_each(token_iterator<std::string_view>&, FuncType&& func, FuncArgs&&... args);
}

template <typename StringObject>
string_tools::token_iterator<StringObject>::token_iterator(string_reference target, std::string delim)
	: token_string    (target), 
	  token_delim     (delim) ,
	  token_string_len(target.length()),
	  token_delim_len (delim .length())
{
	token_begin_pos = 0;
	token_end_pos   = token_string.find(token_delim, 0);

	if (token_end_pos == string_type::npos || token_delim == "")
		token_end_pos = token_string_len;
}

template <typename StringObject>
void string_tools::token_iterator<StringObject>::operator++()
{
	if (token_end_pos + token_delim_len >= token_string_len) {
		token_end_pos   = token_string_len;
		token_begin_pos = token_end_pos;

		return;
	}

	token_begin_pos = token_end_pos + token_delim_len;
	token_end_pos   = token_string.find(token_delim, token_begin_pos);

	if (token_end_pos == string_type::npos)
		token_end_pos = token_string_len;
}

template <typename StringObject>
void string_tools::token_iterator<StringObject>::operator++(int)
{
	if (token_end_pos == token_string_len) {
		token_begin_pos = token_end_pos;
		return;
	}

	token_begin_pos = token_end_pos + token_delim_len;
	token_end_pos   = token_string.find(token_delim, token_begin_pos);

	if (token_end_pos == string_type::npos)
		token_end_pos = token_string_len;
}

template <typename FuncType, typename... FuncArgs>
void string_tools::tokenize_for_each(std::string& target, std::string delim, FuncType&& func, FuncArgs&&... args)
{
	token_iterator<std::string> it(target, delim);
	while (it) {
		func(*it, std::forward<FuncArgs>(args)...);
		it++;
	}
}

template <typename FuncType, typename... FuncArgs>
void string_tools::tokenize_for_each(std::string_view& target, std::string delim, FuncType&& func, FuncArgs&&... args)
{
	token_iterator<std::string_view> it(target, delim);
	while (it) {
		func(*it, std::forward<FuncArgs>(args)...);
		it++;
	}
}

template <typename FuncType, typename... FuncArgs>
void string_tools::tokenize_for_each(token_iterator<std::string>& it, FuncType&& func, FuncArgs&&... args)
{
	while (it) {
		func(*it, std::forward<FuncArgs>...);
		it++;
	}
}

template <typename FuncType, typename... FuncArgs>
void string_tools::tokenize_for_each(token_iterator<std::string_view>& it, FuncType&& func, FuncArgs&&... args)
{
	while (it) {
		func(*it, std::forward<FuncArgs>...);
			it++;
	}
}