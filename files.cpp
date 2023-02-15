#include "files.h"
#include <fstream>
#include <stdio.h>
#include <filesystem>
#include <algorithm>
#include <sstream>

bool files::CheckSize(std::string path)
{
    int size = 0;
    std::fstream file(path);
    std::string del = "rm " + path;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    if (size == 0)
    {
        remove(path.c_str());
        return false;
    }
    else
    {
        return true;
    }
}

std::string files::VersionCheck()
{
    std::string line;

    std::ifstream in("version");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            return line;
        }
    }
    in.close();

    return "0";
}