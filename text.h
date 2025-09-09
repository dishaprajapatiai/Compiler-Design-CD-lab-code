// checkConstant.h
#ifndef CHECKCONSTANT_H
#define CHECKCONSTANT_H

#include <string>
#include <cctype>

bool isConstant(const std::string &s) {
    if (s.empty()) return false;   // empty string is not a constant

    for (char ch : s) {
        if (!isdigit(ch)) {
            return false;          // if any character is not a digit, return false
        }
    }
    return true;
}

#endif