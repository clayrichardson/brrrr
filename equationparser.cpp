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
    bool containsOperator(string);
    string trim(string);
    void dumpMap();

private:
    map<string, string> left_hash;
    vector<string> splitOnChar(string, char);
    bool isInteger(string);
    string resolveVariable(string);
    string compute(string);
    void updateMap(string, string);
};

EquationParser::EquationParser(vector<string> lines){
    for (auto line: lines){
	vector<string> split_equation = splitOnChar(line, '=');
	left_hash[split_equation[0]] = split_equation[1];
    }
    //dumpMap();
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
    //cout << "splitOnChar(" << line << ", " << character << ")" << endl;
    stringstream output;
    output << "[";
    for (auto item: seglist){
	output << item << ",";
    }
    //cout << "returning: " << output.str() << "]" << endl;
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
    //cout << "getting key: " << query << endl;
    string result = left_hash[query];
    //cout << "value is: " << result << endl;
    return result;
}

string EquationParser::compute(string input){
    //cout << "receiving: " << input << "." << endl;
    int result = 0;
    vector<string> expanded_string;

    if (isInteger(input)){
	//cout << "input is integer: " << input << endl;
        return input;
    } else if (containsOperator(input)){
	//cout << "input contains operator: " << input << endl;
	expanded_string = splitOnChar(input, '+');
	for (auto item: expanded_string){
	    if (isInteger(item)){
		//cout << "item is integer: " << item << endl;
		result += stoi(item);
	    } else {
		//cout << "else item is not integer: " << item << endl;
		string resolved_variable = resolveVariable(item);
		//cout << "calling resolveVariable with item: " << item << "." << endl;
		//cout << "calling compute with resolved variable: " << resolved_variable << endl;
		result += stoi(compute(resolveVariable(item)));
	    }
	    
	}
    } else {
	//cout << "calling resolveVariable with input: " << input << "." << endl;
	string resolved_variable = resolveVariable(input);
	//cout << "calling compute with input: " << resolved_variable << endl;
	//dumpMap();
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
	//cout << "resolving left_hash[" << item.first << "] => " << item.second << endl;
	operation_array = splitOnChar(item.second, '+');
	for(auto operand: operation_array){
	    //cout << "calling compute with operand: " << operand << endl;
	    result += stoi(compute(operand));
	}
	//cout << "setting left_hash[" << item.first << "] => " << result << endl;
	updateMap(item.first, to_string(result));
	//left_hash[item.first] = result;
	//cout << "value is now: " << "left_hash[" << item.first << "] => " << result << endl;
	//dumpMap();
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
    //cout << "containsOperator result: " << equation_parser.containsOperator("2 + 2") << endl;
    //cout << "trim operation: |" << equation_parser.trim(" left") << "|" << endl;
    //cout << "trim operation: |" << equation_parser.trim("right ") << "|" << endl;
    //cout << "trim operation: |" << equation_parser.trim(" both ") << "|" << endl;
    //cout << "trim operation: |" << equation_parser.trim("	left tab") << "|" << endl;
    //cout << "trim operation: |" << equation_parser.trim("right tab	") << "|" << endl;
    //cout << "trim operation: |" << equation_parser.trim("	both tab	") << "|" << endl;
    cout << equation_parser.evaluate();
}