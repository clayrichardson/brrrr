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

EquationParser::EquationParser(vector<string> lines) {
    for (auto line: lines) {
        vector<string> split_equation = splitOnChar(line, '=');
        left_hash[split_equation[0]] = split_equation[1];
    }
}

void EquationParser::updateMap(string key, string value) {
    left_hash[key] = value;
}

void EquationParser::dumpMap() {
    cout << "dumping map..." << endl;
    for (auto item : left_hash) {
        cout << item.first << " => " << item.second << endl;
    }
}

vector<string> EquationParser::splitOnChar(string line, char character) {
    stringstream ss_line(line);
    string segment;
    vector<string> seglist;

    while(getline(ss_line, segment, character)) {
        seglist.push_back(trim(segment));
    }
    stringstream output;
    output << "[";
    for (auto item: seglist) {
        output << item << ",";
    }
    return seglist;
}

string EquationParser::trim(string rawString) {
    if(rawString.empty()) {
        return rawString;
    }

    string left_trim = regex_replace(rawString, regex("^\\s+\\b"), "");
    string right_trim = regex_replace(left_trim, regex("\\b\\s+$"), "");

    return right_trim;
}

bool EquationParser::isInteger(string input) {
    regex re ("^\\d+$");
    if (regex_match(input, re)) return true;
    else return false;
}

bool EquationParser::containsOperator(string input) {
    regex re ("^.*\\++.*$");
    if (regex_match(input, re)) return true;
    else return false;
}

string EquationParser::resolveVariable(string query) {
    return left_hash[query];
}

string EquationParser::compute(string input) {
    int result = 0;
    vector<string> expanded_string;

    if (isInteger(input)) {
        return input;
    } else if (containsOperator(input)) {
        expanded_string = splitOnChar(input, '+');
        for (auto item: expanded_string) {
            if (isInteger(item)) {
                result += stoi(item);
            } else {
                result += stoi(compute(resolveVariable(item)));
            }

        }
    } else {
        result += stoi(compute(resolveVariable(input)));
    }
    return to_string(result);
}

string EquationParser::evaluate() {
    vector<string> operation_array;
    stringstream formatted_return;

    for (auto item: left_hash) {
        int result = 0;
        stringstream return_line;
        operation_array = splitOnChar(item.second, '+');
        for(auto operand: operation_array) {
            result += stoi(compute(operand));
        }
        updateMap(item.first, to_string(result));
        return_line << item.first << " = " << result << endl;
        formatted_return << return_line.str();
    }
    return formatted_return.str();
}
