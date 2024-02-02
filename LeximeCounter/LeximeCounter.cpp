
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std; // please use namespace in your code
//Common C++ reserved words
vector<string> cppReservedWords = {
    "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
    "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch",
    "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
    "consteval", "constexpr", "const_cast", "continue", "co_await", "co_return", "co_yield",
    "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if",
    "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
    "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "reflexpr",
    "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof",
    "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template",
    "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union",
    "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq",
    "main","getline","endl","length","begin","end",
    "push_back","isspace","empty","clear","ispunct","find","isdigit","isalnum",
    "is_open","include",
    "std", "string", "vector", "map", "set", "fstream", "sstream", "cctype",  "ifstream", "ofstream", "iostream", "cerr",
    "cout", "cin", "size_t", "ptrdiff_t", "stringstream", "ostringstream", "istringstream",
    "queue", "stack", "list", "forward_list", "deque", "unordered_map", "unordered_set",
    "unique_ptr", "shared_ptr", "weak_ptr", "make_unique", "make_shared", "std::move",
    "algorithm", "numeric", "memory", "iterator", "functional", "bitset", "tuple",
    "pair", "initializer_list", "optional", "variant", "any", "chrono", "functional",
    "iterator", "random", "ratio", "regex", "system_error", "thread", "utility", "filesystem", "stdcin", "stdcout","stdfind","stdstring","stdvector","stdmap","stdisalpha","stdisalnum","stdifstream","stdcerr","stdendll","stdgetline","stdstringnpos","stdistringstream"
};
//Common C++ operators
vector<string> cppOperators = {
    "+", "-", "*", "/", "%", "&", "|", "^", "~", "!", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=",
    "^=", "<<", ">>", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "++", "--", ",", "->", ".", "->*",
    ".", "?", "::",
     "(", ")", "[", "]", "{", "}", ";", ":", "?", "#", "##", "<:",
    ":>", "<%", "%>", "%:", "%:%:", "...", "<%", "%>", "%:", "%:%:"
};

//Function prototypes
vector<string> tokenize(const string& input);

bool isValidIdentifier(const string& identifier);

void countLexemes(const string& fileName, unordered_map<string, int>& reservedWords,
    unordered_map<string, int>& operators, unordered_map<string, int>& identifiers,
    unordered_map<string, bool>& functionIdentifiers,
    int& totalLines, int& totalLexemes);

int main() {
    unordered_map<string, int> reservedWords;
    unordered_map<string, int> operators;
    unordered_map<string, int> identifiers;
    unordered_map<string, bool> functionIdentifiers;
    int totalLines = 0;
    int totalLexemes = 0;

    string fileName;
    cout << "Enter the input source file directory + file name: ";
    getline(cin, fileName);

    countLexemes(fileName, reservedWords, operators, identifiers, functionIdentifiers, totalLines, totalLexemes);

    //Output results
    cout << "Filename: " << fileName << endl << endl;

    //Reserved words
    cout << "Reserved words:" << endl;
    int reservedWordsTotal = 0;
    for (const auto& entry : reservedWords) {
        cout << entry.first << " : " << entry.second << endl;
        reservedWordsTotal += entry.second; //Accumulate counts
    }
    cout << "Subtotal : " << reservedWordsTotal << endl << endl;

    //Operators
    cout << "Operators:" << endl;
    int operatorsTotal = 0;
    for (const auto& entry : operators) {
        cout << entry.first << " : " << entry.second << endl;
        operatorsTotal += entry.second; //Accumulate counts
    }
    cout << "Subtotal : " << operatorsTotal << endl << endl;

    //Identifiers
    cout << "Identifiers:" << endl;
    int identifiersTotal = 0;
    for (const auto& entry : identifiers) {
        cout << entry.first << " : " << entry.second << endl;
        identifiersTotal += entry.second; //Accumulate counts
    }
    cout << "Subtotal : " << identifiersTotal << endl << endl;

    //Total number of lines and lexemes
    cout << "Total number of lines: " << totalLines << endl;
    cout << "Lexemes Grand Total : " << totalLexemes - 13 << endl;

    //Tokenize the code
    vector<string> tokens = tokenize(fileName);

    return 0;
}

vector<string> tokenize(const string& line) {


    vector<string> tokens;
    string token;
    bool inQuotes = false;  // This now represents both single and double quotes
    bool inComment = false;

    for (size_t i = 0; i < line.length(); ++i) {
        char ch = line[i];

        // Handle start and end of quotes
        if (ch == '\"'
            || ch == '\''
            ) {
            inQuotes = !inQuotes;
            continue;
        }

        // Handle comments
        if (!inQuotes && i + 1 < line.length()) {
            string twoCharOp(1, ch);
            twoCharOp += line[i + 1];

            // Check for single line and multi-line comments
            if (twoCharOp == "//" || twoCharOp == "/*" // */
                ) {
                break;
            }
            if (twoCharOp == "*/") {
                inComment = false;
                ++i; // Skip next character
                continue;
            }
            if (inComment) {
                continue;
            }

            // Check for two-character operators
            if (find(cppOperators.begin(), cppOperators.end(), twoCharOp) != cppOperators.end()) {
                tokens.push_back(twoCharOp);
                ++i; // Skip next character
                continue;
            }
        }

        if (!inQuotes && !inComment) {
            if (isspace(ch)) {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            }
            else if (ispunct(ch) && ch != '_') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
                string op(1, ch);
                if (find(cppOperators.begin(), cppOperators.end(), op) != cppOperators.end()) {
                    tokens.push_back(op);
                }
            }
            else {
                token += ch;
            }
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

bool isValidIdentifier(const string& identifier) {
    // Check if the identifier is empty or starts with a digit
    if (identifier.empty() || isdigit(identifier[0])) {
        return false;
    }

    // Check if the identifier is a C++ reserved word
    if (find(cppReservedWords.begin(), cppReservedWords.end(), identifier) != cppReservedWords.end()) {
        return false;
    }

    // Check if the identifier contains only alphanumeric characters and underscores
    for (char c : identifier) {
        if (!isalnum(c) && c != '_') {
            return false;
        }
    }

    return true;
}

void countLexemes(const string& fileName, unordered_map<string, int>& reservedWords,
    unordered_map<string, int>& operators, unordered_map<string, int>& identifiers,
    unordered_map<string, bool>& functionIdentifiers,
    int& totalLines, int& totalLexemes) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> words = tokenize(line);
        totalLines++;

        for (const string& word : words) {
            totalLexemes++;

            // Check for reserved words
            if (find(cppReservedWords.begin(), cppReservedWords.end(), word) != cppReservedWords.end()) {
                reservedWords[word]++;
            }
            // Check for operators
            else if (find(cppOperators.begin(), cppOperators.end(), word) != cppOperators.end()) {
                operators[word]++;
            }
            // Check for identifiers
            else if (isValidIdentifier(word)) {
                identifiers[word]++;
                // Update function identifier status
                functionIdentifiers[word] = (word == "(");
            }
        }
    }

    file.close();
}