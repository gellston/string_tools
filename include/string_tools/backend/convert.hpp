#pragma once
#include <string_tools/serialize/serialize_types.hpp>

namespace string_tools::backend {
	template <typename IntegralType>
	std::string convert_to(IntegralType&&)		requires std::is_integral_v<std::remove_cvref_t<IntegralType>>;

	template <typename FloatType>
	std::string convert_to(FloatType&&)         requires std::is_floating_point_v<std::remove_cvref_t<FloatType>>;

	template <typename ConstructibleType>
	std::string convert_to(ConstructibleType&&) requires std::is_constructible_v<std::string, ConstructibleType>;
}

template <typename IntegralType>
std::string string_tools::backend::convert_to(IntegralType&& convert_target)	 requires std::is_integral_v<std::remove_cvref_t<IntegralType>>
{
	return std::to_string(convert_target);
}

template <typename FloatType>
std::string string_tools::backend::convert_to(FloatType&& convert_target)		 requires std::is_floating_point_v<std::remove_cvref_t<FloatType>>
{
	return std::to_string(convert_target);
}

template <typename ConstructibleType>
std::string string_tools::backend::convert_to(ConstructibleType&& convert_target) requires std::is_constructible_v<std::string, ConstructibleType>
{
	return std::string(convert_target);
}