 ///
 /// @file    test_offline.cpp
 /// @author  TariaUnique
 /// @date    2017-07-18 16:06:48
 ///

#include "GlobalDefine.hpp"
#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "PageLib.hpp"
#include "WebPage.hpp"
#include "PageLibPreprocessor.hpp"
#include "WordSegmentation.hpp"

#include <stdio.h>
#include <time.h>

int main()
{
	Configuration conf("conf/conf.txt");
	DirScanner dirScanner(conf);
	dirScanner();
	PageLib pagelib(conf,dirScanner);

	time_t t1=time(NULL);
	pagelib.create();
	pagelib.store();
	time_t t2=time(NULL);
	printf(" raw lib creat and store time : %ld min \n",(t2-t1));

	PageLibPreprocessor libPreprocessor(conf);
	libPreprocessor.doProcess();

	return 0;
}

