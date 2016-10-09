#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <regex>
#include "../includes/equationparser.h"

using namespace std;

int main(int argc, char *argv[]) {
    string line;
    vector<string> lines;

    if (argc < 2) {
        cerr << "Usage: equationparser <path_to_input_file>" << endl;
        return 1;
    }

    fstream inputFile;
    try {
        inputFile.open(argv[1], ios::in);
        while(getline(inputFile, line)) {
            lines.push_back(line);
        }
    }
    catch (exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    if (lines.size() == 0) {
        cerr << "Error: empty file" << endl;
        return 1;
    }

    EquationParser equation_parser(lines);
    cout << equation_parser.evaluate();
}
