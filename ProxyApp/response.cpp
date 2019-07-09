#include "response.hpp"
#include "utils.hpp"

Response::Response()
{
}

// ////////////// TODO!!!!!!!!!!
void Response::parse(std::string responseString)
{
	// ORGANIZE
	std::map<std::string, std::string> response;

	std::vector<std::string> splittedResponse = Utils::splitString(responseString, "\r\n");

	// find element that is ""
	int headerSplitIndex = splittedResponse.size();

	for (int i = 0; i < splittedResponse.size(); i++)
	{
		if (splittedResponse[i] == "")
		{
			headerSplitIndex = i;
			break;
		}
	}

	for (int i = 0; i < headerSplitIndex; i++)
	{
		if (i == 0)
		{
			this->firstLine = splittedResponse[i];
		}
		else
		{
			auto j = splittedResponse[i].find(":");

			if (j != std::string::npos)
			{
				std::string key = splittedResponse[i].substr(0, j);

				std::string value = splittedResponse[i].substr(j + 2, splittedResponse[i].size() - 1);
				std::pair<std::string, std::string> element(key, value);
				response.insert(element);
			}
		}
	}

	std::string body;

	for (int i = headerSplitIndex + 1; i < splittedResponse.size(); i++)
	{
		body += splittedResponse[i] + "\r\n";
	}

	this->headers = response;
	this->body = body;
}

void Response::clear()
{
	firstLine.clear();
	headers.clear();
	body.clear();
}

std::string Response::toString()
{
	std::string response;

	response.append(firstLine + "\r\n");

	for (auto itr = headers.begin(); itr != headers.end(); ++itr)
	{
		std::string line = itr->first + ": " + itr->second + "\r\n";
		response.append(line);
	}

	response.append("\r\n");

	response.append(body);

	return response;
}