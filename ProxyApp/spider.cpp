#include"spider.hpp"
Spider::Spider(std::string target){
	this->target = target;
	ProxyServer* proxyServer = new ProxyServer();
}

std::vector<std::string> Spider::get_tree(int level) {
	//getting the home html
	std::string url;
	std::string buff;
	proxyServer->makeRemoteRequest("/index.html",target);
	buff = proxyServer->response->body;
	//parsing html to url on this level
	return urls;
}