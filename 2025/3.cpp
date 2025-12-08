#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Remove k digits to create the maximum integer (O(n) using monotonic stack)
string removeKDigits(string num, int k) {
    int n = num.size();
    if (k >= n) return "0";

    string stack = "";
    int toRemove = k;

    // Use monotonic decreasing stack
    for (int i = 0; i < n; i++) {
        // If current digit is larger than stack top,
        // remove smaller digits from stack while we can still remove
        while (!stack.empty() && stack.back() < num[i] && toRemove > 0) {
            stack.pop_back();
            toRemove--;
        }
        stack.push_back(num[i]);
    }

    // If we still need to remove digits (e.g., all increasing sequence)
    // remove from the end
    while (toRemove > 0) {
        stack.pop_back();
        toRemove--;
    }

    return stack;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;

    // Read all input lines
    while (getline(cin, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    long long solution1 = 0;
    long long solution2 = 0;

    // Process each line
    for (const string& num : lines) {
        int len = num.size();

        // Solution 1: Keep 2 digits (remove len-2 digits)
        string result1 = removeKDigits(num, len - 2);
        solution1 += stoll(result1);

        // Solution 2: Keep 12 digits (remove len-12 digits)
        string result2 = removeKDigits(num, len - 12);
        solution2 += stoll(result2);
    }

    cout << "Solution 1: " << solution1 << endl;
    cout << "Solution 2: " << solution2 << endl;

    return 0;
}
