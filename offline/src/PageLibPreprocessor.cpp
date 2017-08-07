 ///
 /// @file    PageLibPreprocessor.cpp
 /// @author  TariaUnique
 /// @date    2017-07-18 12:49:29
 ///

#include "PageLibPreprocessor.hpp"
#include "GlobalDefine.hpp"

#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;

PageLibPreprocessor::PageLibPreprocessor(Configuration &conf)
:_conf(conf)
{}

void PageLibPreprocessor::doProcess()
{
	readInfoFromFile();
	time_t t1=time(NULL);
	cutRedundantPages();
	buildInvertIndexTable();
	time_t t2=time(NULL);
	printf("preprocess time :%ld min\n", (t2-t1)/60);

	storeOnDisk();
	time_t t3 = time(NULL);
	printf("store time :%ld min \n",(t3-t2)/60);
}


void PageLibPreprocessor::readInfoFromFile()
{
	map<string, string> &configMap = _conf.getConfigMap();
	string pageLibPath= configMap[RIPEPAGELIB_KEY];
	string offsetLibPath = configMap[OFFSETLIB_KEY];
	ifstream pageIfs(pageLibPath.c_str());
	ifstream offsetIfs(offsetLibPath.c_str());

	if((!pageIfs.good()) || (!offsetIfs.good()))
	{
		cout<<"page or offset lib open error"<<endl;
	}

	string line;
	int docId, docOffset, docLen;
	while(getline(offsetIfs,line))
	{
		stringstream ss(line);
		ss>>docId>>docOffset>>docLen;
		string doc;
		doc.resize(docLen,' ');
		pageIfs.seekg(docOffset,pageIfs.beg);
		pageIfs.read(&*doc.begin(),docLen);
		WebPage webPage(doc,_conf,_jieba);
		_pageLib.push_back(webPage);
		_offsetLib.insert(std::make_pair(docId,std::make_pair(docOffset,docLen)));//去重之后无效
	}
}

void PageLibPreprocessor::cutRedundantPages()
{
	for(size_t i=0;i!=_pageLib.size()-1;++i)
	{
		for(size_t j=i+1;j!=_pageLib.size();++j)
		{
			if(_pageLib[i]==_pageLib[j])
			{
				_pageLib[j]=_pageLib[_pageLib.size()-1];
				_pageLib.pop_back();
				--j;
			}
		}
	}
}

void PageLibPreprocessor::buildInvertIndexTable()
{
	for(auto page:_pageLib)
	{
		map<string, int> &wordsMap = page.getWordMap();
		for(auto wordFreq : wordsMap)
		{
			_invertIndexTable[wordFreq.first].push_back(std::make_pair(page.getDocId(),wordFreq.second));
		}
	}
	map<int ,double> weightSum;
	int totalPageNum = _pageLib.size();
	for(auto &item :_invertIndexTable)
	{
		int df=item.second.size();
		double idf=log(static_cast<double>(totalPageNum)/df+ 0.05)/log(2);
		for(auto &sitem : item.second)
		{
			double weight = sitem.second *idf;
			weightSum[sitem.first]+=pow(weight,2);
			sitem.second = weight;
		}
	}

	for(auto& item : _invertIndexTable)
	{
		for(auto & sitem: item.second)
		{
			sitem.second = sitem.second / sqrt(weightSum[sitem.first]);
		}
	}
}


void PageLibPreprocessor::storeOnDisk()
{
	sort(_pageLib.begin(),_pageLib.end());
	ofstream ofsPageLib(_conf.getConfigMap()[NEWPAGELIB_KEY].c_str());
	ofstream ofsOffsetLib(_conf.getConfigMap()[NEWOFFSETLIB_KEY].c_str());

	if(!ofsPageLib.good() || ! ofsOffsetLib.good())
	{
		cout<<"new page or offset lib ofstream open error!"<<endl;
	}

	for(auto & page : _pageLib)
	{
		int id=page.getDocId();
		int length=page.getDoc().size();
		ofstream::pos_type offset = ofsPageLib.tellp();
		ofsPageLib<<page.getDoc();
		ofsOffsetLib<<id<<'\t'<<offset<<'\t'<<length<<'\n';
	}
	ofsPageLib.close();
	ofsOffsetLib.close();
	
	ofstream ofsInvertIndexTable(_conf.getConfigMap()[INVERTINDEX_KEY].c_str());
	if(!ofsInvertIndexTable.good())
	{
		cout<<"invert index table ofstream open error!"<<endl;
	}
	for(auto item : _invertIndexTable)
	{
		ofsInvertIndexTable<<item.first<<"\t";
		for(auto sitem : item.second)
		{
			ofsInvertIndexTable<<sitem.first<<"\t"<<sitem.second<<"\t";
		}
		ofsInvertIndexTable<<endl;
	}
	ofsInvertIndexTable.close();
}




	







	



