#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Response {

public:
	Response();
	void parse(std::string);
	void clear();

	std::string firstLine;
	std::map<std::string, std::string> headers;
	std::string body;

	std::string toString();
};