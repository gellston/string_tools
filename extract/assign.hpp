#pragma once
#include <string>
#include <string_view>

namespace string_tools {

	void assign_to(int		   & dst, std::string&& src)   { dst = std::stoi(src); }
	void assign_to(unsigned int& dst, std::string&& src)   { dst = std::stoi(src); }

	void assign_to(short		 & dst, std::string&& src) { dst = std::stoi(src); }
	void assign_to(unsigned short& dst, std::string&& src) { dst = std::stoi(src); }

	void assign_to(long			& dst, std::string&& src)  { dst = std::stoi(src); }
	void assign_to(unsigned long& dst, std::string&& src)  { dst = std::stoi(src); }

	void assign_to(float & dst, std::string&& src) { dst = std::stof(src); }
	void assign_to(double& dst, std::string&& src) { dst = std::stof(src); }

	void assign_to(std::string& dst, std::string&& src) { dst = src; }


	void assign_to(int		   & dst, std::string_view&& src)   { std::string __cvt(src); dst = std::stoi(__cvt); }
	void assign_to(unsigned int& dst, std::string_view&& src)   { std::string __cvt(src); dst = std::stoi(__cvt); }

	void assign_to(short		 & dst, std::string_view&& src) { std::string __cvt(src); dst = std::stoi(__cvt); }
	void assign_to(unsigned short& dst, std::string_view&& src) { std::string __cvt(src); dst = std::stoi(__cvt); }

	void assign_to(long			& dst, std::string_view&& src)  { std::string __cvt(src); dst = std::stol(__cvt); }
	void assign_to(unsigned long& dst, std::string_view&& src)  { std::string __cvt(src); dst = std::stol(__cvt); }

	void assign_to(float & dst, std::string_view&& src)			{ std::string __cvt(src); dst = std::stof(__cvt); }
	void assign_to(double& dst, std::string_view&& src)			{ std::string __cvt(src); dst = std::stof(__cvt); }

	void assign_to(std::string	   & dst, std::string_view&& src) { dst = src; }
	void assign_to(std::string_view& dst, std::string_view&& src) { dst = src; }
}