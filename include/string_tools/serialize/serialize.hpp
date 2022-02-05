#pragma once
#include <string_tools/backend/convert.hpp>

namespace string_tools {
	template <typename... SerializeObject>
	std::string serialize(std::string, SerializeObject&&...);

	template <typename SerializeObject, typename... Remaining>
	std::string serialize(std::string, SerializeObject&&, Remaining&&...);

	template <typename SerializeObject>
	std::string serialize(std::string, SerializeObject&&);
}

template <typename... SerializeObject>
std::string string_tools::serialize(std::string interval, SerializeObject&&... target)
{
	return serialize(interval, target...);
}

template <typename SerializeObject, typename... Remaining>
std::string string_tools::serialize(std::string interval, SerializeObject&& target, Remaining&&... remaining)
{
	return backend::convert_to(target) + interval + serialize(interval, remaining...);
}

template <typename SerializeObject>
std::string string_tools::serialize(std::string interval, SerializeObject&& target)
{
	return backend::convert_to(target);
}