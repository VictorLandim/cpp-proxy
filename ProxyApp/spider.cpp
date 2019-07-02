#include"spider.hpp"

Spider::Spider(std::string target){
	this->target = target;
}

std::vector<std::string> Spider::get_tree(std::string url,int depth) {
	//getting the home html
	this->url_map.clear();
	this->ordered_urls.clear();
	this->max_depth = depth;
	this->start_url = url;
	ProxyServer* proxyServer = new ProxyServer(8082);
	recursive(0, start_url, proxyServer);
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

	std::cout << "URL: " << url << std::endl;
	request = "GET " + url + " " + "HTTP/1.1\r\nHost: " + this->target + "\r\nConnection: close\r\n\r\n";

	proxyServer->makeRemoteRequest(request, this->target);
	response = proxyServer->response->body;
	proxyServer->response->body.clear();

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
			if (this->url_map.find(url) == this->url_map.end()) {//No repeated entries
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

void Spider::printToStream() {
	std::vector<std::string> redundancy_check;
	if (this->url_map.find(this->start_url) == this->url_map.end()) {
		std::cout << "Erro, nao foi possivel mostrar a url inicial" << std::endl;
		return;
	}
	std::cout << this->target + this->start_url << std::endl;
	this->ordered_urls.emplace_back(this->start_url);
	this->curr_depth = 0;
	for each (std::string url in url_map.at(this->start_url).urls){
		bool new_global = TRUE;
		bool new_local = TRUE;
		for each (std::string inserted in redundancy_check) {
			if (inserted == url)
				new_local = FALSE;
		}
		for each (std::string inserted in this->ordered_urls) {
			if (inserted == url)
				new_global = FALSE;
		}
		if (new_local) {//no repeat
			std::cout << "|->" << url << std::endl;
			this->ordered_urls.emplace_back(url);
			redundancy_check.emplace_back(url);
			if (new_global) {
				printToStream(url);
			}
		}
	}
}

void Spider::printToStream(std::string root) {
	this->curr_depth++;
	std::vector<std::string> redundancy_check;
	if (this->url_map.find(root) == this->url_map.end()) {
		this->curr_depth--;
		return;//end of depth
	}
	url_ref ref = this->url_map.at(root);
	for each (std::string url in ref.urls) {
		bool new_global = TRUE;
		bool new_local = TRUE;
		for each (std::string inserted in redundancy_check) {
			if (inserted == url)
				new_local = FALSE;
		}
		for each (std::string inserted in this->ordered_urls) {
			if (inserted == url)
				new_global = FALSE;
		}
		if (new_local) {//no repeat
			for (int i = 0; i < this->curr_depth; i++) {
				std::cout << "   ";
			}
			std::cout << "|->" << url << std::endl;
			this->ordered_urls.emplace_back(url);
			redundancy_check.emplace_back(url);
			if (new_global && this->curr_depth == ref.level) {
				printToStream(url);
			}
		}
	}
	this->curr_depth--;
}
