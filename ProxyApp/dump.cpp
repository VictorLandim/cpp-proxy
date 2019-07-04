#include"Dump.hpp"

Dump::Dump(std::string target, std::string path){
	this->target = target;
	this->path = path;
}

std::map<std::string, std::string> Dump::dump_tree(std::string url,int depth) {
	//getting the home html
	this->url_map.clear();
	this->max_depth = depth;
	this->start_url = url;
	ProxyServer* proxyServer = new ProxyServer(8082);
	recursive(0, start_url, proxyServer);
	printToFile();
	return this->response_map;
}

std::string Dump::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	std::string ending = "\"";
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'

		int j = str.find_first_of("\"", start_pos);
		str.replace(j, ending.length(), "index.html\"");
	}
	return str;
}

void Dump::recursive(int depth, std::string url, ProxyServer* proxyServer) {
	std::string response, buff, request, original_response;
	url_ref root;
	int i = 0, j = 0;

	if (depth > this->max_depth) {
		return;
	}

	std::cout << "URL: " << url << std::endl;
	request = "GET " + url + " " + "HTTP/1.1\r\nHost: " + this->target + "\r\nConnection: close\r\n\r\n";

	proxyServer->makeRemoteRequest(request, this->target);
	response = proxyServer->response->body;
	proxyServer->response->body.clear();
	original_response = response;
	buff = ReplaceAll(original_response, "href=\"/", "href=\""+ this->path +"/");
	original_response.clear();
	original_response = buff;
	buff.clear();

	this->response_map.emplace(url, original_response);

	//std::cout << "RESPONSE: " << response << std::endl;

	//std::cout << "Analizing response" << std::endl;

	while (!response.empty()) {
		i = response.find("href=\"");
		if (i == std::string::npos)
			break; //End of parsing
		i += 6;
		j = response.find_first_of("\"",i);
		if (j == std::string::npos)
			break; //End of parsing
		buff = response.substr(i,j-i);
		if (buff.at(0) != '/') {
			if (buff.find("http") == std::string::npos) {
				std::string temp = buff;
				buff = "/" + temp;
			}
		}
		//std::cout << "URL " << buff << " found" << std::endl;
		root.urls.emplace_back(buff);
		buff.clear();
		buff = response.substr(j, std::string::npos);
		response.clear();
		response = buff;
		buff.clear();
		i = std::string::npos;
		j = std::string::npos;
	}
	//std::cout << "Response analyzed" << std::endl;
	if (!root.urls.empty()) {
		root.level = depth;
		this->url_map.emplace(url, root);
		for each (std::string url in root.urls) {
			if (this->url_map.find(url) == this->url_map.end() && (url.find_first_of('.') == std::string::npos || url.find(".htm") != std::string::npos)) {//No repeated entries
				if (url.find("http") != std::string::npos) {
					if (url.find(this->target) == std::string::npos)
						continue;
				}
				recursive(depth + 1, url, proxyServer);
			}
		}
	}
	if (this->url_map.find(this->start_url) == this->url_map.end()) {
		std::cout << "Erro, nao foi possivel carregar a url inicial" << std::endl;
	}
}

void Dump::printToFile() {
	std::cout << "starting dump" << std::endl;
	mkdir(this->path.c_str());
	for (std::pair<std::string, std::string> response : response_map) {
		std::cout << "path " << response.first << std::endl;
		std::string buff = this->path + response.first;
		mkdir(buff.c_str());
		myfile.open(buff + "index.html");
		if (!myfile.is_open()) {
			std::cout << "Erro, nao foi possivel abrir o arquivo de saida " << this->path + response.first + "index.html" << std::endl;
		}
		myfile << response.second;
		myfile.close();
	}
}
