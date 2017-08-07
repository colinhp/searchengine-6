 ///
 /// @file    PageLibPreprocessor.hpp
 /// @author  TariaUnique
 /// @date    2017-07-18 12:41:50
 ///


#ifndef PAGELIBPREPROCESSOR_H
#define PAGELIBPREPROCESSOR_H


#include "WebPage.hpp"
#include "WordSegmentation.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::unordered_map;
using std::set;

class PageLibPreprocessor
{
public:
	PageLibPreprocessor(Configuration &conf);
	void doProcess();
private:
	void readInfoFromFile();
	void cutRedundantPages();
	void buildInvertIndexTable();
	void storeOnDisk();

private:
	Configuration & _conf;
	WordSegmentation _jieba;
	vector<WebPage> _pageLib;
	unordered_map<int,pair<int, int>> _offsetLib;
	unordered_map<string,vector<pair<int,double>>> _invertIndexTable;

};


#endif

