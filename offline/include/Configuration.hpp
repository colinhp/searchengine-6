 ///
 /// @file    Configuration.hpp
 /// @author  TariaUnique
 /// @date    2017-07-17 20:15:27
 ///
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <set>
#include <map>
#include <string>

using std::map;
using std::set;
using std::string;
class Configuration
{
public:
	Configuration(const std::string &filepath);
	std::map<string, string>& getConfigMap();
	std::set<std::string> &getStopWordList();
private:
	void readConfiguration();
private:
	std::string filepath_;
	std::map<string,string> configMap_;
	std::set<string> stopWordList_;
};

#endif
