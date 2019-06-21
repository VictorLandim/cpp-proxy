#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Response {

public:
	Response();
	int parse(std::string);

	std::string firstLine;
	std::map<std::string, std::string> headers;
	std::string body;

	std::string toString();
};