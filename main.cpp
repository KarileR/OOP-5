#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <regex>
#include <cwchar>
#include <cstring>
#include <stdio.h>
#include <ctype.h>

#include "text.hpp"

using std::cout;
using std::string;
using std::endl;

int main(int argc, char** argv)
{

    std::ifstream cin("text.txt");
    Tekstas tekstas1;

    if(cin.fail()) throw "Source file not found!";

    std::string line;
    int lineNR = 0;

    while (getline(cin, line))
    {
        lineNR ++;

        std::istringstream in(line);
        std::string zodis;

        while (in >> zodis)
        {
            tekstas1.insert_word(lineNR,zodis);
        }
    }

    tekstas1.set_Line_number(lineNR);
    tekstas1.isvesti_URL();
    tekstas1.isvesti_pasikartojancius();
    tekstas1.isvesti_zodzius1();
    tekstas1.isvesti_zodzius2();

   

    return 0;
}