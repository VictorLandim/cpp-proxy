#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

// Represents a GET HTTP request only!
class Request {

private:
	void clear();
	std::vector<std::string> splitString(std::string, std::string);

public:
	Request();
	void parse(std::string);

	std::string host;
	std::string path;
	std::string content;
	std::string firstLine;

	std::map<std::string, std::string> headers;
	std::string toString();
};