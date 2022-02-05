#pragma once
#include <string>
#include <string_view>

#include <type_traits>
#include <concepts>

namespace string_tools::backend {
	
	template <std::integral IntegralType>
	IntegralType reverse_convert_to(std::string&);

	template <std::floating_point FloatType>
	FloatType    reverse_convert_to(std::string&);

	template <typename AnyType, typename AnyConverter>
	AnyType		 reverse_convert_to(std::string&, AnyConverter&&) requires std::is_invocable_v<AnyConverter, std::string&>
																		   && std::is_same_v	 <std::invoke_result_t<AnyConverter>, std::remove_cvref_t<AnyType>>;
}

template <std::integral IntegralType>
IntegralType string_tools::backend::reverse_convert_to(std::string& str)
{
	return std::stoi(str);
}

template <std::floating_point FloatType>
FloatType string_tools::backend::reverse_convert_to(std::string& str)
{
	return std::stof(str);
}

template <typename AnyType, typename AnyConverter>
AnyType string_tools::backend::reverse_convert_to(std::string& str, AnyConverter&& cvt) requires std::is_invocable_v<AnyConverter, std::string&>
																							  && std::is_same_v	    <std::invoke_result_t<AnyConverter>, std::remove_cvref_t<AnyType>>
{
	return cvt(str);
}