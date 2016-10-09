using namespace std;

class EquationParser {
public:
    explicit EquationParser(vector<string> lines);

    string evaluate();

    void dumpMap();

private:
    map<string, string> left_hash;

    static bool containsOperator(string);
    static bool isInteger(string);

    static string trim(string);
    string resolveVariable(string);
    string compute(string);

    static vector<string> splitOnChar(string, char);

    void updateMap(string, string);
};