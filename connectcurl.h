#pragma once
#include "curl/curl.h"
class connectcurl
{
public:
	void DownloadFile(const char* link, const char* outfile);
	bool CheckNet();
};