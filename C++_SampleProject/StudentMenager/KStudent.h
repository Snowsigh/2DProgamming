#include "KStd.h"
struct KInfo
{
public:
	std::string STRname;
	std::string STRaddress;
	std::string STRnumber;
};
 
 
struct KStudent
{
public:
	KInfo info;
	int iSubJect = 0;
	std::multimap<std::string, int > mapSubject;
	std::string STRtmp;
};

