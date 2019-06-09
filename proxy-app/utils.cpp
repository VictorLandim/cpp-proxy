#include <string>
#include <iostream>
#include "utils.hpp"
#include <sstream>
#include <iterator>

std::map<std::string, std::string> Utils::parseRequest(std::string request)
{
	std::map<std::string, std::string> response;
	std::vector<std::string> splittedRequest = Utils::splitString(request, "\r\n");

	for (auto &req : splittedRequest)
	{
		std::cout << req << std::endl;
	}

	return response;
		
	for (const std::string line : splittedRequest)
	{
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == ':')
			{
				std::string key = line.substr(0, i);
				std::string value = line.substr(i + 2, line.size() - 1);
				std::pair<std::string, std::string> element(key, value);
				response.insert(element);
				break;
			}
		}
	}

	return response;
}

std::string Utils::parseResponse(std::string response)
{
	return 0;
}

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