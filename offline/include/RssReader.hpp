 ///
 /// @file    RssReader.hpp
 /// @author  TariaUnique
 /// @date    2017-07-17 21:04:06
 ///

#ifndef RSSREADER_H
#define RSSREADER_H

#include "tinyxml2.h"
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using namespace tinyxml2;

struct RssItem
{
	string _title;
	string _link;
	string _pubDate;
	string _content;
};


class RssReader
{
public:
	RssReader(vector<string> &files);
	~RssReader();
	void loadFeedFiles();
	void loadFeedFile(const string &filename);
//	void initWithRssString(const string &res);
	void makePages(vector<string> &pages);//传出参数

private:
	void parseRss(XMLDocument &doc);
private:
	vector<shared_ptr<RssItem>> _items;
	vector<string> & _files;  
};


#endif


