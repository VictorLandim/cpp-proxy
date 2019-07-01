#pragma once
#include <string>
#include "proxyServer.hpp"

class Spider {
private:
	std::string target;
	ProxyServer* proxyServer;
public:
	std::vector<std::string> urls;
	Spider(std::string);
	std::vector<std::string> get_tree(int profundidade);
};