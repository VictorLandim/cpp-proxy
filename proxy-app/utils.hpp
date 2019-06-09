#pragma once
#include <string>
#include <vector>
#include <map>

namespace Utils
{

	// returns request key-value pairs
	std::map<std::string, std::string> parseRequest(std::string);
	std::string parseResponse(std::string);
	std::vector<std::string> splitString(std::string, std::string);
}
