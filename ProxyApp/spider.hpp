#pragma once
#include <string>
#include <unordered_map>
#include "proxyServer.hpp"
#include <iostream>
#include <fstream>

typedef struct url_ref {
	int level;
	std::vector<std::string> urls;
} url_ref;

class Spider {
private:
	int max_depth;
	int curr_depth;
	std::string target;
	std::string start_url;
	ProxyServer* proxyServer;
	std::ofstream myfile;
	std::string filename;
	void printToFile();
	void printToStream(std::string);
	void Spider::recursive(int, std::string, ProxyServer*);
public:
	std::unordered_map<std::string, url_ref> url_map;
	std::vector<std::string> ordered_urls;
	Spider(std::string, std::string filename = "./Spider_output.txt");
	std::vector<std::string> get_tree(std::string url, int profundidade);
};