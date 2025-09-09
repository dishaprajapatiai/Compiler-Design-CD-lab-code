//LEFT RECURSION ELIMINATION
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// Helper function to split string by delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Main function to eliminate immediate left recursion
void eliminateLeftRecursion(const string& nonTerminal, const vector<string>& productions) {
    vector<string> alpha;  // Left-recursive parts: A -> Aα
    vector<string> beta;   // Non-left-recursive parts: A -> β

    for (const string& prod : productions) {
        if (prod.substr(0, nonTerminal.size()) == nonTerminal) {
            // Left recursion: A -> Aα
            alpha.push_back(prod.substr(nonTerminal.size()));
        } else {
            // Non-left recursion: A -> β
            beta.push_back(prod);
        }
    }

    if (alpha.empty()) {
        // No left recursion found
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); ++i) {
            cout << productions[i];
            if (i != productions.size() - 1) cout << " | ";
        }
        cout << endl;
    } else {
        string newNonTerminal = nonTerminal + "'";
        // Output the transformed grammar
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < beta.size(); ++i) {
            cout << beta[i] << newNonTerminal;
            if (i != beta.size() - 1) cout << " | ";
        }
        cout << endl;

        cout << newNonTerminal << " -> ";
        for (size_t i = 0; i < alpha.size(); ++i) {
            cout << alpha[i] << newNonTerminal << " | ";
        }
        cout << "ε" << endl;
    }
}

int main() {
    string input;
    cout << "Enter production (e.g., A -> Aa | b): ";
    getline(cin, input);

    // Parsing input
    size_t arrowPos = input.find("->");
    if (arrowPos == string::npos) {
        cerr << "Invalid production format." << endl;
        return 1;
    }

    string nonTerminal = input.substr(0, arrowPos);
    nonTerminal.erase(remove(nonTerminal.begin(), nonTerminal.end(), ' '), nonTerminal.end());

    string rightSide = input.substr(arrowPos + 2);
    vector<string> productions = split(rightSide, '|');

    // Remove whitespace
    for (string& prod : productions) {
        prod.erase(remove(prod.begin(), prod.end(), ' '), prod.end());
    }

    eliminateLeftRecursion(nonTerminal, productions);

    return 0;
}

