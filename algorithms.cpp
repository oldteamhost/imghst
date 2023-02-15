#include "algorithms.h"
#include "generatetoken.h"
#include "connectcurl.h"
#include <iostream>

void algorithms::GrabPhotoStandart(std::string format, std::string site, std::string path, std::string token)
{
    generatetoken gt;
    connectcurl c;

    resultGen = token;
    outFile = path + resultGen + format;
    link = "https://" + site + "/" + resultGen + format;

    const char* linkConverted = link.c_str();
    const char* outFileConverted = outFile.c_str();
    c.DownloadFile(linkConverted, outFileConverted);
}