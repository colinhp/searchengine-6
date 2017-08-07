 ///
 /// @file    WebPage.cpp
 /// @author  TariaUnique
 /// @date    2017-07-18 10:26:58
 ///


#include "WebPage.hpp"
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>

using std::cout;
using std::endl;
using std::priority_queue;
using std::pair;
using std::make_pair;

struct WordFreqCompare
{
	bool operator()(const pair<string,int> &left, const pair<string, int> &right)
	{
		if(left.second < right.second)
		{
			return true;
		}
		else if(left.second == right.second &&left.first>right.first)
		{
			return true;
		}
		else{
			return false;
		}
	}
};


WebPage::WebPage(string &doc, Configuration &config, WordSegmentation &jieba)
:_doc(doc)
{
	_topWords.reserve(20);
	processDoc(doc,config,jieba);
}
void WebPage::processDoc(const string &doc, Configuration &config,WordSegmentation &jieba)
{
	string docIdHead="<docid>";
	string docIdTail="</docid>";
	string docUrlHead ="<link>";
	string docUrlTail="</link>";
	string docTitleHead="<title>";
	string docTitleTail="</title>";
	string docContentHead="<content>";
	string docContentTail="</content>";

	int bpos = doc.find(docIdHead);
	int epos=doc.find(docIdTail);
	string docId=doc.substr(bpos+docIdHead.size(),epos-bpos-docIdHead.size());
	_docId=atoi(docId.c_str());

	bpos=doc.find(docTitleHead);
	epos=doc.find(docTitleTail);
	_docTitle=doc.substr(bpos+docTitleHead.size(),epos-bpos-docTitleHead.size());


	bpos=doc.find(docContentHead);
	epos=doc.find(docContentTail);
	_docContent=doc.substr(bpos+docContentHead.size(),epos-bpos-docContentHead.size());
		
	vector<string> wordsVec =jieba(_docContent.c_str());
	set<string> &stopWordList = config.getStopWordList();
	calcTopK(wordsVec,TOPK_NUMBER,stopWordList);
}


void WebPage::calcTopK(vector<string> &wordsVec, int k, set<string> & stopWordList)
{
	for(auto iter = wordsVec.begin();iter!=wordsVec.end();++iter)
	{
		auto sit=stopWordList.find(*iter);
		if(sit==stopWordList.end())
		{
			++_wordsMap[*iter];
		}

	}

	priority_queue<pair<string,int>,vector<pair<string,int>>, WordFreqCompare>
		wordFreqQue(_wordsMap.begin(),_wordsMap.end());
	while(!wordFreqQue.empty())
	{
		string top = wordFreqQue.top().first;
		wordFreqQue.pop();
		if(top.size()==1 && (static_cast<unsigned int>(top[0]) ==10 || static_cast<unsigned int> (top[0]) ==13))
		{
			continue;
		}
		_topWords.push_back(top);
		if(_topWords.size() >=static_cast<size_t>(k))
		{
			break;
		}
	}
}

bool operator == (const WebPage &lhs, const WebPage &rhs)
{
	int commNum=0;
	auto lIter = lhs._topWords.begin();
	for(;lIter !=lhs._topWords.end();++lIter)
	{
		commNum+=std::count(rhs._topWords.begin(),rhs._topWords.end(),*lIter);
	}

	int lhsNum=lhs._topWords.size();
	int rhsNum=rhs._topWords.size();
	int totalNum=lhsNum<rhsNum? lhsNum : rhsNum;

	if(static_cast<double>(commNum)/totalNum >0.75)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator<(const WebPage &lhs, const WebPage &rhs)
{
	if(lhs._docId < rhs._docId)
		return true;
	else
		return false;
}






