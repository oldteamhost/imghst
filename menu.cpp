#include "menu.h"

void helpMenu()
{
    system("cls");
    std::cout << "\n  PhotoHostKiller - by lomaster | OldTeam\n\n";
    std::cout << "    usage:\n";
    std::cout << "      ./parser [options]     run parser\n\n";
    std::cout << "    options:\n";
    std::cout << "      -D, --domain           set domain\n";
    std::cout << "      -F, --format           set format\n";
    std::cout << "      -P, --path             set path\n";
    std::cout << "      -G, --generate         set method\n";
    std::cout << "      -GC, --generatecount   set generate lenght\n\n";
    std::cout << "      -C, --count            set count\n\n";
    std::cout << "    optional arguments:\n";
    std::cout << "      -h, --help            show this help message\n\n";
}
