#pragma once
#include <iostream>
class algorithms
{
public:
	std::string link;
	std::string outFile;
	void GrabPhotoStandart(std::string format, std::string site, std::string path, std::string token);
private:
	std::string resultGen;
};
