#include "request.hpp"

Request::Request()
{
}

std::vector<std::string> Request::splitString(std::string input, std::string delim)
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

void Request::parse(std::string requestString)
{
	// THIS IS WRONG

	if (requestString.find("GET") == std::string::npos)
	{
		std::cout << "# Unsupported HTTP method, only GET is allowed." << std::endl;
		return;
	}

	if (requestString.find("https") != std::string::npos)
	{
		std::cout << requestString << std::endl;
		system("pause");
		std::cout << "# HTTPS requests are not supported by this proxy." << std::endl;
		return;
	}

	// requestString will always start with:
	// G E T _ h t t p : / / google.com HTTP/1.X
	// 0 1 2 3 4 5 6 7 8

	std::string::size_type hostStart = 4;

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


	// ORGANIZE
	std::map<std::string, std::string> response;
	std::vector<std::string> splittedRequest = splitString(requestString, "\r\n");
	firstLine = splittedRequest[0];

	for (const std::string line : splittedRequest)
	{
		for (std::size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == ':')
			{
				std::string key = line.substr(0, i);
				
				// remove proxy-connection header
				if (key != "Proxy-Connection")
				{
					std::string value = line.substr(i + 2, line.size() - 1);
					std::pair<std::string, std::string> element(key, value);
					response.insert(element);
					break;
				}
			}
		}
	}

	// necessary!!!
	std::pair<std::string, std::string> element("Connection", "close");
	response.insert(element);

	this->headers = response;
}

std::string Request::toString()
{
	std::string response;
	response.append(firstLine + "\r\n");

	if(headers.size() > 0)
	{
		for (auto itr = headers.begin(); itr != headers.end(); ++itr) 
		{
			std::string line =  itr->first + ": " +  itr->second + "\r\n";
			response.append(line);
;		}

		response.append("\r\n");

		return response.c_str();
	}
	else 
	{
		return NULL;
	}
}