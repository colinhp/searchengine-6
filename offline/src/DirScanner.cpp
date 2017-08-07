 ///
 /// @file    DirScanner.cpp
 /// @author  TariaUnique
 /// @date    2017-07-17 20:40:41
 ///
#include "DirScanner.hpp"
#include "Configuration.hpp"
#include "GlobalDefine.hpp"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>

using std::cout;
using std::endl;

DirScanner::DirScanner(Configuration &conf)
:conf_(conf)
{
	vecFiles_.reserve(kFileNo);
}

void DirScanner::operator()()
{
	std::map<std::string, std::string > &confMap=conf_.getConfigMap();
	std::string dirName = confMap[YULIAO_KEY];
	traverse(dirName);
}

std::vector<std::string> &DirScanner::files()
{
	return vecFiles_;
}


void DirScanner::traverse(const std::string &dirName)
{
	DIR *dp;
	cout<<"dirName: "<<dirName<<endl;
	if((dp=opendir(dirName.c_str()))==NULL)
	{
		perror("opendir error !");
		exit(-1);
	}

	struct dirent *mdirent;
	char buf[128]={0};
	while((mdirent=readdir(dp))!=NULL)
	{
		if(mdirent->d_type==4){
			if(strcmp(mdirent->d_name,".")==0|| strcmp(mdirent->d_name,"..")==0){
				continue;
			}
			else{
				bzero(buf,sizeof(buf));
				sprintf(buf,"%s%c%s",dirName.c_str(),'/',mdirent->d_name);
				traverse(buf);
			}
		}
		else 
		{
			std::string filename="";
			filename=filename+dirName.c_str();
			filename=filename+"/"+mdirent->d_name;
			vecFiles_.push_back(filename);
			
		}
	}
	closedir(dp);
}

