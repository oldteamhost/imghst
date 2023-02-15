#include <iostream>
#include "algorithms.h"
#include "generatetoken.h"
#include "connectcurl.h"
#include "files.h"
#include <iostream>
#include <ctime>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

algorithms a;
generatetoken ga;
connectcurl c;
files f;

std::string what;
std::string what1;
std::string what2;
std::string what3;
std::string run;

char* count;

int what4;
int temp_gen;
int gen_count;

int a2i(const char* s)
{
    int sign = 1;
    if (*s == '-') {
        sign = -1;
        s++;
    }
    int num = 0;
    while (*s) {
        num = ((*s) - '0') + num * 10;
        s++;
    }
    return num * sign;
}

void Check() {
    std::cout << "\n";
    std::cout << "  Imghst " << "0.0.3-release";
    std::cout << "";
    std::cout << "\n  ---------------------------------------------";
    if (c.CheckNet() == true)
    {
        std::cout << "\n  | Connect...." << "true\n";
    }
    else
    {
        std::cout << "\n  | Connect.... " << "false\n\n";
        system("PAUSE");
        exit(1);
    }
    std::cout << "  | Folder...." << "true\n";
    std::cout << "  ---------------------------------------------\n";
    std::cout << "  | Domain...."<< what1 << std::endl;
    if (std::filesystem::exists(what3))
    {
        if (what3 == "out/") {
            std::cout << "  | Path...." << "default" << std::endl;
        }
        else {
            std::cout << "  | Path...." << what3 << std::endl;
        }

        std::cout << "  | Format...." << what2 << std::endl;

        if (temp_gen == 1) {
            std::cout << "  | Gen.Mode...." << "default" << std::endl;
        }
        else {
            std::cout << "  | Gen.Mode...." << temp_gen << std::endl;
        }
        if (gen_count == 5) {
            std::cout << "  | Gen.Lenght...." << "default" << std::endl;
        }
        else {
            std::cout << "  | Gen.Lenght...." << gen_count << std::endl;
        }
        std::cout << "  | Count...." << what4 << std::endl;
        std::cout << "  ---------------------------------------------\n";
    }
    else
    {
        std::cout << "  ---------------------------------------------\n";
        std::cout << "  ERROR: path not found\n\n";
        system("PAUSE");
        exit(1);
    }
}

void HelpMenu() {
    std::cout << "\n\n  HelpMenu\n";
    std::cout << "  ------------------------------\n";
    std::cout << "  Easy: -eh\n";
    std::cout << "  Standart: -sh\n";
    std::cout << "  Pro: -ph\n\n";
}
void EasyRunHelp() {
    std::cout << "\n\n  EASY\n";
    std::cout << "  ------------------------------\n";
    std::cout << "  usage:\n";
    std::cout << "      imghst.exe [option]\n\n";
    std::cout << "  options:\n";
    std::cout << "      --imgur\n";
    std::cout << "      --lightshot\n";
    std::cout << "      --freeimage\n";
    std::cout << "      --pasteboard\n\n";
}

void StandartRunHelp() {
    std::cout << "\n\n  STANDART\n";
    std::cout << "  ------------------------------\n";
    std::cout << "  usage:\n";
    std::cout << "      imghst.exe [options]\n\n";
    std::cout << "  options:\n";
    std::cout << "      -d          domain\n";
    std::cout << "      -f          format\n";
    std::cout << "      -c          count\n\n";
}

void ProRunHelp() {
    std::cout << "\n\n  PRO\n";
    std::cout << "  ------------------------------\n";
    std::cout << "  usage:\n";
    std::cout << "      imghst.exe [options]\n\n";
    std::cout << "  options:\n";
    std::cout << "      -d          domain\n";
    std::cout << "      -f          format\n";
    std::cout << "      -p          path\n";
    std::cout << "      -m          mode (0-2)\n";
    std::cout << "      -l          lenght\n";
    std::cout << "      -c          count\n\n";
}

void Menu() {
    fs::create_directories("out");
    system("cls");
    Check();
}
int main(int argc, char* argv[])
{
    if (argc == 1) {
        system("cls");
        std::cout << "\n  ERROR: \"\wrong run\"\n";
        std::cout << "\n  OPEN:   Open cmd\n";
        std::cout << "  WRITE:  cd [this folder path]\n";
        std::cout << "  WRITE:  imghst.exe -h\n\n\n";
        std::cout << "  Created by lomaster\n\n";
        system("pause");
        return 0;
    }
    if (std::string(argv[1]) == "-h") {
        system("cls");
        HelpMenu();
        return 0;
    }
    if (std::string(argv[1]) == "-eh") {
        system("cls");
        EasyRunHelp();
        return 0;
    }
    if (std::string(argv[1]) == "-sh") {
        system("cls");
        StandartRunHelp();
        return 0;
    }
    if (std::string(argv[1]) == "-ph") {
        system("cls");
        ProRunHelp();
        return 0;
    }
    if (argc == 2) {
        if (std::string(argv[1]) == "--imgur") {
            what1 = "i.imgur.com";
            what2 = ".png";
            what3 = "out/";
            what4 = 10000;
            temp_gen = 1;
            gen_count = 5;
        }
        else if (std::string(argv[1]) == "--lightshot") {
            what1 = "prnt.sc";
            what2 = ".png";
            what3 = "out/";
            what4 = 10000;
            temp_gen = 1;
            gen_count = 5;
        }
        else if (std::string(argv[1]) == "--freeimage") {
            what1 = "iili.io";
            what2 = ".png";
            what3 = "out/";
            what4 = 10000;
            temp_gen = 1;
            gen_count = 7;
        }
        else if (std::string(argv[1]) == "--pasteboard") {
            what1 = "gcdnb.pbrd.co/images";
            what2 = ".png";
            what3 = "out/";
            what4 = 10000;
            temp_gen = 1;
            gen_count = 12;
        }
        else {
            system("cls");
            EasyRunHelp();
            return 1;
        }
    }
    else {
        if (argc == 7) {
            if (std::string(argv[1]) != "-d") {
                system("cls");
                StandartRunHelp();
                return 1;
            }
            else {
                what1 = argv[2];
            }
            if (std::string(argv[3]) != "-f") {
                system("cls");
                StandartRunHelp();
                return 1;
            }
            else {
                what2 = argv[4];
            }
            if (std::string(argv[5]) != "-c") {
                system("cls");
                count = argv[5];
                StandartRunHelp();
                return 1;
            }
            else {
                what4 = a2i(argv[6]);
            }
            what3 = "out/";
            temp_gen = 1;
            gen_count = 5;
        }
        else {
            if (std::string(argv[1]) != "-d") {
                system("cls");
                ProRunHelp();
                return 1;
            }
            else {
                what1 = argv[2];
            }
            if (std::string(argv[3]) != "-f") {
                system("cls");
                ProRunHelp();
                return 1;
            }
            else {
                what2 = argv[4];
            }
            if (std::string(argv[5]) != "-p") {
                system("cls");
                ProRunHelp();
                return 1;
            }
            else {
                what3 = argv[6];
            }
            if (std::string(argv[7]) != "-m") {
                system("cls");
                ProRunHelp();
                return 1;
            }
            else {
                temp_gen = a2i(argv[8]);
            }
            if (std::string(argv[9]) != "-l") {
                system("cls");
                ProRunHelp();
                return 1;
            }
            else {
                gen_count = a2i(argv[10]);
            }
            if (std::string(argv[11]) != "-c") {
                system("cls");
                ProRunHelp();
                return 1;
            }
            else {
                what4 = a2i(argv[12]);
            }
        }
    }
    Menu();

    if (temp_gen == 0) {
#define generate ga.Generate0(gen_count)
    }
    else if (temp_gen == 1) {
#define generate ga.Generate1(gen_count)
    }
    else if (temp_gen == 2) {
#define generate ga.Generate2(gen_count)
    }
    else {
        std::cout << "  ERROR: gen_mode (0-2)\n\n";
        exit(1);
    }
    auto begin = std::chrono::steady_clock::now();
    for (int i = 1; i <= what4; i++) {
        
        auto begin = std::chrono::steady_clock::now();
        a.GrabPhotoStandart(what2, what1, what3, generate);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        if (f.CheckSize(a.outFile) == true)
        {
            std::cout << "  [+] " << a.outFile << " << "  << a.link << " | " << elapsed_ms.count() << " ms" << " | " << "[" << i << "]" << std::endl;
        }
        else
        {
            std::cout << "  [-] " << a.outFile << " << " << a.link << " | " << elapsed_ms.count() << " ms" << " | " << "[" << i << "]" << std::endl;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "  ---------------------------------------------\n";
    std::cout << "  Count: " << what4 << std::endl;
    std::cout << "  Time: " << elapsed_ms.count() << "ms";
    std::cout << "\n\n";
    system("PAUSE");
}
