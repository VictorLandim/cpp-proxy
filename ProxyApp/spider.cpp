#include"spider.hpp"

Spider::Spider(std::string target){
	this->target = target;
}

std::vector<std::string> Spider::get_tree(int depth) {
	//getting the home html
	this->url_map.clear();
	this->ordered_urls.clear();
	this->max_depth = depth;
	ProxyServer* proxyServer = new ProxyServer(8082);
	recursive(0, "/", proxyServer);
	printToStream();
	return ordered_urls;
}

void Spider::recursive(int depth, std::string url, ProxyServer* proxyServer) {
	std::string response, buff, request;
	url_ref root;
	int i = 0, j = 0;

	if (depth > this->max_depth) {
		return;
	}

	request = "GET " + url + " " + "HTTP/1.1\r\nHost: " + this->target + "\r\nConnection: close\r\n\r\n";

	proxyServer->makeRemoteRequest(request, this->target);
	response = proxyServer->response->body;

	std::cout << "RESPONSE: " << response << std::endl;

	std::cout << "Analizing response" << std::endl;

	while (!response.empty()) {
		i = response.find("href=\"");
		if (i == std::string::npos)
			break; //End of parsing
		i += 6;
		j = response.find_first_of("\"",i);
		if (j == std::string::npos)
			break; //End of parsing
		buff = response.substr(i,j-i);
		std::cout << "URL " << buff << " found" << std::endl;
		if (buff.find(this->target) != std::string::npos) {
			root.urls.emplace_back(buff.substr(buff.find(this->target)+this->target.length()));
		}
		else {
			root.urls.emplace_back(buff);
		}
		buff.clear();
		buff = response.substr(j, std::string::npos);
		response.clear();
		response = buff;
		buff.clear();
		i = std::string::npos;
		j = std::string::npos;
	}
	std::cout << "Response analyzed" << std::endl;
	if (!root.urls.empty()) {
		root.level = depth;
		this->url_map.emplace(url, root);
		for each (std::string url in root.urls) {
			if (this->url_map.find(url) == this->url_map.end())//No repeated entries
				recursive(depth + 1, url, proxyServer);
		}
	}
	if (this->url_map.find("/") == this->url_map.end()) {
		std::cout << "Erro, nao foi possivel carregar index.html" << std::endl;
	}
}

void Spider::printToStream() {
	if (this->url_map.find("/") == this->url_map.end()) {
		std::cout << "Erro, nao foi possivel carregar index.html" << std::endl;
		return;
	}
	std::cout << this->target + "/" << std::endl;
	this->ordered_urls.emplace_back("/");
	for each (std::string url in url_map.at("/").urls){
		bool new_url = TRUE;
		for each (std::string inserted in this->ordered_urls) {
			if (inserted == url)
				new_url = FALSE;
		}
		if (new_url) {//no repeat
		std::cout << '\t' << url << std::endl;
		this->ordered_urls.emplace_back(url);
			printToStream(url);
		}
	}
}

void Spider::printToStream(std::string url) {
	if (this->url_map.find(url) == this->url_map.end())
		return;//end of depth
	url_ref ref = this->url_map.at(url);
	for each (std::string url in ref.urls) {
		bool new_url = TRUE;
		for each (std::string inserted in this->ordered_urls) {
			if (inserted == url)
				new_url = FALSE;
		}
		for (int i = 0; i < ref.level; i++) {
			std::cout << '\t';
		}
		if (new_url) {//no repeat
		std::cout << url << std::endl;
		this->ordered_urls.emplace_back(url);
			printToStream(url);
		}
	}
}
