#pragma once
#include <string>
#include <unordered_map>
#include "proxyServer.hpp"
#include <iostream>
#include <fstream>
#include <direct.h>

typedef struct _url_ref {
	int level;
	std::vector<std::string> urls;
} _url_ref;

class Dump {
private:
	int max_depth;
	int curr_depth;
	std::string target;
	std::string start_url;
	ProxyServer* proxyServer;
	std::ofstream myfile;
	std::string path;
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	void printToFile();
	void Dump::recursive(int, std::string, ProxyServer*);
public:
	std::unordered_map<std::string, _url_ref> url_map;
	std::map<std::string, std::string> response_map;
	std::vector<std::string> ordered_urls;
	Dump(std::string, std::string path = "../Dump");
	std::map<std::string, std::string> dump_tree(std::string url, int profundidade);
};