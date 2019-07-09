#include "request.hpp"

Request::Request()
{
}

void Request::parse(std::string requestString)
{
	clear();
	
	std::vector<std::string> splittedRequest = splitString(requestString, "\r\n");

	std::map<std::string, std::string> response;

	for (auto line = 0; line < splittedRequest.size(); line++)
	{
		// if is the FIRST line, grab method, host and path
		if (line == 0)
		{
			if (splittedRequest[line].find("GET") == std::string::npos)
			{
				std::cout << splittedRequest[line] << std::endl;
				throw std::exception("Request dropped. Unsupported HTTP method, only GET is allowed.");
			}

			if (splittedRequest[line].find("https") != std::string::npos)
			{
				std::cout << splittedRequest[line] << std::endl;
				throw std::exception("Request dropped. HTTPS requests are not supported by this proxy.");
			}

			std::string firstLine = splittedRequest[line];

			// requestString will always start with:
			// G E T _ h t t p : / / g o o g l e . c o m / h o m e HTTP/1.X
			// 0 1 2 3 4 5 6 7 8 9 1 2 3

			std::string::size_type hostStart = 4;

			// remove protocol (http://)
			firstLine.erase(hostStart, 7);

			std::string::size_type hostEnd = firstLine.find('/', hostStart);

			// TODO: add WWW later!
			std::string host = firstLine.substr(hostStart, hostEnd - hostStart);

			firstLine.erase(hostStart, hostEnd - hostStart);

			std::string::size_type pathEnd = firstLine.find(' ', hostStart);
			std::string path = firstLine.substr(hostStart, pathEnd - hostStart);

			this->content = firstLine;
			this->firstLine = firstLine;
			this->host = host;
			this->path = path;
		}
		else
		{
			auto i = splittedRequest[line].find(":");

			if (i != std::string::npos)
			{
				std::string key = splittedRequest[line].substr(0, i);

				std::string value = splittedRequest[line].substr(i + 2, splittedRequest[line].size() - 1);
				std::pair<std::string, std::string> element(key, value);
				response.insert(element);
			}
		}
	}

	// necessary!!!
	response.erase("Range");
	response.erase("If-Range");
	response["Connection"] = "close";
	response["Proxy-Connection"] = "close";
	response["Accept-Encoding"] = "identity";

	this->headers = response;
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

void Request::clear()
{
	host.clear();
	path.clear();
	content.clear();
	firstLine.clear();
	headers.clear();
}