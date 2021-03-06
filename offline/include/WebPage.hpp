 ///
 /// @file    WebPage.hpp
 /// @author  TariaUnique
 /// @date    2017-07-18 00:43:17
 ///
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include "Configuration.hpp"
#include "WordSegmentation.hpp"

#include <string>
#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std::vector;
using std::set;

class WebPage
{
	friend bool operator==(const WebPage &lhs, const WebPage &rhs);
	friend bool operator<(const WebPage &lhs, const WebPage &rhs);

public:
	const static int TOPK_NUMBER = 20;

	WebPage(string &doc,Configuration &config,WordSegmentation &jieba);
	int getDocId()
	{
		return _docId;
	}
	map<string,int> &getWordMap()
	{
		return _wordsMap;
	}
	string getDoc()
	{
		return _doc;
	}
private:
	void processDoc(const string &doc, Configuration &config, WordSegmentation & jieba);
	void calcTopK(vector<string> &wordsVec,int k,set<string> & stopWordList);



private:
	string _doc;
	int _docId;
	string _docTitle;
	string _docUrl;
	string _docContent;
	string _docSummary;

	vector<string> _topWords;
	map<string, int> _wordsMap;
};

#endif
