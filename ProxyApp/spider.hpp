#pragma once
#include <string>
#include <unordered_map>
#include "proxyServer.hpp"
#include <iostream>

typedef struct url_ref {
	int level;
	std::vector<std::string> urls;
} url_ref;

class Spider {
private:
	int max_depth;
	std::string target;
	ProxyServer* proxyServer;
	void printToStream();
	void printToStream(std::string);
	void Spider::recursive(int, std::string, ProxyServer*);
public:
	std::unordered_map<std::string, url_ref> url_map;
	std::vector<std::string> ordered_urls;
	Spider(std::string);
	std::vector<std::string> get_tree(int profundidade);
};