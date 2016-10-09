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

using namespace std;

class EquationParser {
public:
    EquationParser(vector<string> lines);
    string evaluate();
    void dumpMap();

private:
    map<string, string> left_hash;
    vector<string> splitOnChar(string, char);
    bool containsOperator(string);
    bool isInteger(string);
    string trim(string);
    string resolveVariable(string);
    string compute(string);
    void updateMap(string, string);
};

EquationParser::EquationParser(vector<string> lines){
    for (auto line: lines){
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

vector<string> EquationParser::splitOnChar(string line, char character){
    stringstream ss_line(line);
    string segment;
    vector<string> seglist;

    while(getline(ss_line, segment, character)){
	seglist.push_back(trim(segment));
    }
    stringstream output;
    output << "[";
    for (auto item: seglist){
	output << item << ",";
    }
    return seglist;
}

string EquationParser::trim(string rawString){
    if(rawString.empty()){
	return rawString;
    }

    string left_trim = regex_replace(rawString, regex("^\\s+\\b"), "");
    string right_trim = regex_replace(left_trim, regex("\\b\\s+$"), "");

    return right_trim;
}

bool EquationParser::isInteger(string input){
    regex re ("^\\d+$");
    if (regex_match(input, re)) return true;
    else return false;
}

bool EquationParser::containsOperator(string input){
    regex re ("^.*\\++.*$");
    if (regex_match(input, re)) return true;
    else return false;
}

string EquationParser::resolveVariable(string query){
    string result = left_hash[query];
    return result;
}

string EquationParser::compute(string input){
    int result = 0;
    vector<string> expanded_string;

    if (isInteger(input)){
        return input;
    } else if (containsOperator(input)){
	expanded_string = splitOnChar(input, '+');
	for (auto item: expanded_string){
	    if (isInteger(item)){
		result += stoi(item);
	    } else {
		string resolved_variable = resolveVariable(item);
		result += stoi(compute(resolveVariable(item)));
	    }
	    
	}
    } else {
	string resolved_variable = resolveVariable(input);
	result += stoi(compute(resolveVariable(input)));
    }
    return to_string(result);
}

string EquationParser::evaluate(){
    vector<string> return_value;
    vector<string> operation_array;
    stringstream formatted_return;

    for (auto item: left_hash){
	int result = 0;
	stringstream return_line;
	operation_array = splitOnChar(item.second, '+');
	for(auto operand: operation_array){
	    result += stoi(compute(operand));
	}
	updateMap(item.first, to_string(result));
	return_line << item.first << " = " << result << endl;
	formatted_return << return_line.str();
    }
    return formatted_return.str();
}

int main(int argc, char *argv[]) {
    string line;
    vector<string> lines;

    if (argc < 2) {
    	cerr << "Usage: EquationParser <path_to_input_file>" << endl;
	return 1;
    }

    fstream inputFile;
    try {
	    inputFile.open(argv[1], ios::in);
	    while(getline(inputFile, line)){
		lines.push_back(line);
	    }
    }
    catch (exception &e){
	cerr << "Error: " << e.what() << endl;
	return 1;
    }

    if (lines.size() == 0){
	cerr << "Error: empty file" << endl;
	return 1;
    }

    EquationParser equation_parser(lines);
    cout << equation_parser.evaluate();
}