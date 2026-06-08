#include "stringmanip.hpp"
#include <cctype>
using std::string;


string trim(string s) {
    enum { Leading, Word, Trailing } state = Leading;
    int i = 0;
    for (char c : s) {
        if (std::isspace(c)) {
            if (state == Word)
                state = Trailing;
        }
        else {
            if (state == Trailing) {
                s[i++] = ' ';
            }
            s[i++] = c;
            state = Word;
        }
    }
    s.resize(i);
    return s;
}

string uppercase(string s) {
    for (auto& c : s) {
        c = std::toupper(c);
    }
    return s;
}

string lowercase(string s) {
    for (auto& c : s) {
        c = std::tolower(c);
    }
    return s;
}