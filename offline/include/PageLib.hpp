 ///
 /// @file    PageLib.hpp
 /// @author  TariaUnique
 /// @date    2017-07-17 22:11:16
 ///


#ifndef PAGELIB_H
#define PAGELIB_H

#include <string>
#include <vector>

class Configuration;
class DirScanner;

class PageLib
{
public:
	PageLib(Configuration &conf, DirScanner &dirScanner);
	void create();
	void store();
private:
	Configuration & _conf;
	DirScanner & _dirScanner;
	std::vector<std::string> _vecPages;
};


#endif
