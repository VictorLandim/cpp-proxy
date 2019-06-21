#include "response.hpp"
#include "utils.hpp"

Response::Response()
{
}


// ////////////// TODO!!!!!!!!!!
int Response::parse(std::string responseString)
{
	// ORGANIZE
	std::map<std::string, std::string> response;
	std::vector<std::string> splittedRequest = Utils::splitString(responseString, "\r\n");
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

	return 0;
}

std::string Response::toString()
{
	std::string response;
	response.append(firstLine + "\r\n");

	if (headers.size() > 0)
	{
		for (auto itr = headers.begin(); itr != headers.end(); ++itr)
		{
			std::string line = itr->first + ": " + itr->second + "\r\n";
			response.append(line);
		}

		response.append("\r\n");

		response.append(body);

		response.append("\r\n");

		return response;
	}
	else
	{
		return NULL;
	}
}