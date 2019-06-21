#include <string>
#include <iostream>
#include "utils.hpp"
#include <sstream>
#include <iterator>

std::vector<std::string> Utils::splitString(std::string input, std::string delim)
{
	std::vector<std::string> strings;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = input.find(delim, prev)) != std::string::npos)
	{
		strings.push_back(input.substr(prev, pos - prev));
		prev = pos + delim.size();
	}

	// To get the last substring (or only, if delimiter is not found)
	strings.push_back(input.substr(prev));

	return strings;
}