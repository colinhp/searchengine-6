 ///
 /// @file    Configuration.cpp
 /// @author  TariaUnique
 /// @date    2017-07-17 20:19:22
 ///


#include "Configuration.hpp"
#include "GlobalDefine.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;

Configuration::Configuration(const std::string &filepath)
:filepath_(filepath)
{
	readConfiguration();
}

void Configuration::readConfiguration()
{
	std::ifstream ifs(filepath_.c_str());
	if(ifs.good())
	{
		std::string line;
		while(getline(ifs,line))
		{
			std::istringstream iss(line);
			std::string key;
			std::string value;
			iss>>key>>value;
			configMap_[key]=value;
		}
		std::cout<<"read configuration is over~"<<std::endl;
	}
	else{
		std::cout<<"ifstream open error"<<std::endl;
	}
}


std::map<std::string,std::string> & Configuration::getConfigMap()
{
	return configMap_;
}


std::set<std::string> & Configuration::getStopWordList()
{
	if(stopWordList_.size()>0)
		return stopWordList_;
	std::string stopWordFilePath=configMap_[STOP_WORD_KEY];
	std::ifstream ifs(stopWordFilePath.c_str());
	if(!ifs)
	{
		std::cout<<"StopWord ifstream open error!"<<std::endl;
	}
	std::string word;
	while(getline(ifs,word))
	{
		stopWordList_.insert(word);
	}

	return stopWordList_;
}













