#include "request.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>
#include <ostream>

Request::Request(std::string requestString)
{
	this->parse(requestString);
}

void Request::parse(std::string requestString)
{
	if (requestString.find("GET") == std::string::npos)
	{
		std::cout << "Unsupported HTTP method, only GET is allowed." << std::endl;
		// TODO: cleanup above layer
		exit(0);
		return;
	}

	// requestString will always start with:
	// G E T _ h t t p : / / google.com HTTP/1.X
	// 0 1 2 3 4 5 6 7 8

	std::string::size_type hostStart = 4;

	if (requestString.substr(hostStart, 5) == "https")
	{
		std::cout << "HTTPS requests are not supported by this proxy." << std::endl;
		return;
	}

	// remove protocol (http://)
	requestString.erase(hostStart, 7);

	std::string::size_type hostEnd = requestString.find('/', hostStart);


	// TODO: add WWW later!
	std::string host = requestString.substr(hostStart, hostEnd - hostStart);

	requestString.erase(hostStart, hostEnd - hostStart);

	std::string::size_type pathEnd = requestString.find(' ', hostStart);
	std::string path = requestString.substr(hostStart, pathEnd - hostStart);

	this->content = requestString;
	this->host = host;
	this->path = path;
}

