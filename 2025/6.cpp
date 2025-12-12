#include <iostream>
#include <string>
using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");

    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

int main() {
    // input: last line contains math operators
    // we calculate all numbers in the columns with the last character '*' or '+'.
    // 123 328  51 64   
    //  45 64  387 23
    //   6 98  215 314
    // *   +   *   +

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        if (line.empty())
            break;
        lines.push_back(line);
    }

    if (lines.empty())
        return 0;

    string lastLine = lines.back();
    lines.pop_back();

    // split lastline into characters by spaces, and delete empty entries
    vector<char> ops;
    vector<int> maxWidths;

    cout << "Debug: Last line operators: " << lastLine << "\n";

    // scan all characters in lastline
    int currentWidth = 0;
    for (int i = 0; i < lastLine.length(); ++i) {
        if (lastLine[i] != '+' && lastLine[i] != '*') {
            continue;
        } else {
            if(i - 2 - currentWidth >= 0) {
                maxWidths.push_back(i - 2 - currentWidth + 1);
            }
            ops.push_back(lastLine[i]);
            currentWidth = i;
        }
    }
    maxWidths.push_back(lastLine.length() - currentWidth);

    cout << "Debug: Operators and widths: " << maxWidths.size() << " columns\n";

    int n = ops.size();

    cout << "Debug: Number of columns: " << n << "\n";

    // Parse all lines into a 2D grid of numbers
    vector<vector<string>> grid;
    for(int j =0; j< lines.size(); ++j) {
        string ln_copy = lines[j];
        vector<string> row;
        size_t st = 0;
        for (int i = 0; i < n; ++i) {
            string token = ln_copy.substr(st, maxWidths[i]);
            if (!token.empty()) {
                row.push_back(token);
            }
            cout << token << " | ";
            st += maxWidths[i] + 1; // +1 for space
        }
        grid.push_back(row);
    }

    cout << "Debug: Parsed grid:\n";

    // Now process each column with its operator
    long long ans = 0;
    for (int col = 0; col < n; ++col) {
        char op = ops[col];

        if (op == '*') {
            long long result = 1;  // Initialize to 1 for multiplication
            for (const auto &row : grid) {
                if (col < row.size()) {
                    result *= stoll(trim(row[col]));
                }
            }
            ans += result;
        } else if (op == '+') {
            long long result = 0;
            for (const auto &row : grid) {
                if (col < row.size()) {
                    result += stoll(trim(row[col]));
                }
            }
            ans += result;
        }
    }

    cout << ans << "\n";

    // Part 2: Use same parsing approach as Part 1 with maxWidths
    // Now process each column (from right to left)
    long long ans2 = 0;

    for (int colIdx = 0; colIdx < n; ++colIdx) {
        char op = ops[colIdx];

        // Build number from column by reading character at position from right
    
        vector<string> verticalTokens(maxWidths[colIdx], "");

        for (const auto &tokens : grid) {
            string token = tokens[colIdx];

            for(int k=0; k<maxWidths[colIdx]; ++k) {
                if(token[k] != ' ') {
                    verticalTokens[k] += token[k];
                }
            }
        }

        cout << op << " | ";
        long long subTotal = (op == '*') ? 1 : 0;
        for(const auto &numStr : verticalTokens)
        {
            cout << numStr << " | ";
            if(numStr.empty()) continue;

            if (op == '*') {
                subTotal *= stoll(trim(numStr));
            } else if (op == '+') {
                subTotal += stoll(trim(numStr));
            }
        }
        cout << " Subtotal: " << subTotal << "\n";
        ans2 += subTotal;
    }

    cout << ans2 << "\n";
}