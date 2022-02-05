#pragma once
#include <string_tools/backend/reverse_convert.hpp>
#include <string_tools/split/split.hpp>

namespace string_tools {
	template <typename Iterator, typename TargetType, typename... RemainingType>
	void extract(Iterator&&, TargetType&&, RemainingType&&...);

	template <typename Iterator, typename TargetType>
	void extract(Iterator&&, TargetType&&);
}

template <typename Iterator, typename TargetType, typename... RemainingType>
void string_tools::extract(Iterator&& it, TargetType&& target, RemainingType&&... remaining)
{
	target = backend::reverse_convert_to<std::remove_cvref_t<TargetType>>(*it);
	extract(++it, std::forward<RemainingType>(remaining)...);
}

template <typename Iterator, typename TargetType>
void string_tools::extract(Iterator&& it, TargetType&& target)
{
	target = backend::reverse_convert_to<std::remove_cvref_t<TargetType>>(*it);
}