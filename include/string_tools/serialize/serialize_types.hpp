#pragma once
#include <type_traits>

#include <string>
#include <string_view>

namespace string_tools {
	template <typename T>
	struct is_serializable { static constexpr bool value = std::is_integral_v<T> || std::is_floating_point_v<T> 
														|| std::is_same_v<std::decay_t<T>, std::string> || std::is_same_v<std::decay_t<T>, std::string_view>; };
}