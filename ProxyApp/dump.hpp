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

class Dump {
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
	void Dump::recursive(int, std::string, ProxyServer*);
public:
	std::unordered_map<std::string, url_ref> url_map;
	std::unordered_map<std::string, std::string> response_map;
	std::vector<std::string> ordered_urls;
	Dump(std::string, std::string);
	std::unordered_map<std::string, std::string> dump_tree(std::string url, int profundidade);
};