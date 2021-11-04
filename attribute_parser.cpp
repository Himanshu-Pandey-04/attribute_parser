
#include <iostream>
#include "attribute_parser.h"

int main()
{
    string Str = "ths;fojg;wifh;sv";
    vector<string> Parts = split(Str, ';');
    for (auto part : Parts) cout << part << "\n";
}

