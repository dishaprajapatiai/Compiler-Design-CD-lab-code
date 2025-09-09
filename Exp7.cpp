#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Grammar rules:
// E → E + T | T
// T → T * F | F
// F → id

string reduce(string s) {
    if (s == "id") return "F";   // F → id
    if (s == "F") return "T";    // T → F
    if (s == "T*F") return "T";  // T → T * F
    if (s == "T") return "E";    // E → T
    if (s == "E+T") return "E";  // E → E + T
    return "";
}

// Tokenizer: converts string into {"id", "+", "id", "*", "id"}
vector<string> tokenize(string input) {
    vector<string> tokens;
    for (int i = 0; i < input.size();) {
        if (input.substr(i, 2) == "id") {
            tokens.push_back("id");
            i += 2;
        } else {
            string t(1, input[i]);
            tokens.push_back(t);
            i++;
        }
    }
    tokens.push_back("$"); // End marker
    return tokens;
}

int main() {
    string input;
    cout << "Enter input string (use 'id' for identifiers): ";
    cin >> input;

    vector<string> tokens = tokenize(input);
    stack<string> st;

    cout << "\nSHIFT-REDUCE PARSER STEPS\n";
    cout << "---------------------------------------\n";

    for (int i = 0; i < tokens.size(); i++) {
        string tk = tokens[i];

        // SHIFT
        cout << "Shift: " << tk << endl;
        st.push(tk);

        // Try reductions after every shift
        bool reduced = true;
        while (reduced) {
            reduced = false;

            for (int len = 3; len >= 1; len--) {
                if (st.size() >= len) {
                    vector<string> temp;
                    string s = "";
                    for (int j = 0; j < len; j++) {
                        temp.push_back(st.top());
                        st.pop();
                    }
                    for (int j = len - 1; j >= 0; j--) s += temp[j];

                    string lhs = reduce(s);
                    if (lhs != "") {
                        cout << "Reduce: " << s << " -> " << lhs << endl;
                        st.push(lhs);
                        reduced = true;
                        break;
                    } else {
                        for (int j = len - 1; j >= 0; j--) st.push(temp[j]);
                    }
                }
            }
        }
    }

    // Final check
    if (st.size() == 2 && st.top() == "$") {
        st.pop();
        if (st.top() == "E") {
            cout << "\n String Accepted!\n";
            return 0;
        }
    }

    cout << "\n String Rejected!\n";
    return 0;
}