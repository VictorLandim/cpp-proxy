#pragma once
#include <string>
#include <map>

class Request {

private:
	void parse(std::string);

public:
	Request(std::string);

	std::string host;
	std::string path;
	std::string content;

	// std::map<std::string, std::string> headers;
	// std::string method;
	//std::string toString();
};