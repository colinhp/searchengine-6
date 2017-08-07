 //
 /// @file    DirScanner.hpp
 /// @author  TariaUnique
 /// @date    2017-07-17 20:37:43
 ///
#ifndef DIRSCANNER_H
#define DIRSCANNER_H

#include <string>
#include <vector>


class Configuration;

const int kFileNo=10000;

class DirScanner
{
public:
	DirScanner(Configuration &conf);
	void operator()();
	std::vector<std::string> & files();

private:
	void traverse(const std::string &dirName);
private:
	Configuration & conf_;
	std::vector<std::string> vecFiles_;
};

#endif
