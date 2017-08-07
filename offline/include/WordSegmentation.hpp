 ///
 /// @file    WordSegmentation.hpp
 /// @author  TariaUnique
 /// @date    2017-07-17 23:07:58
 ///
 
#ifndef WORDSEGMENTATION_H
#define WORDSEGMENTATION_H

#include "cppjieba/Jieba.hpp"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

const char * const DICT_PATH="/home/taria/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_PATH="/home/taria/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_PATH="/home/taria/cppjieba/dict/user.dict.utf8";

class WordSegmentation
{
public:
	WordSegmentation()
	:_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH)
	{
		cout<<"cppjieba init!"<<endl;
	}

	vector<string> operator()(const char * src)
	{
		vector<string> words;
		_jieba.CutAll(src,words);
		return words;
	}

private:
	cppjieba::Jieba _jieba;
};


#endif
