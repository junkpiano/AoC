#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long solve_part1(const vector<string>& input) {
    if (input.empty()) return 0;
    vector<string> lines = input;
    size_t sPos = lines[0].find('S');
    if (sPos == string::npos) return 0;
    long long ans = 0;

    auto beam =
        [&](auto&& self, size_t sPos, vector<string>& lines, int startRow, long long &ans) -> void{
            if (startRow >= static_cast<int>(lines.size())) return;

            for (size_t i = startRow; i < lines.size(); ++i) {
                if (lines[i][sPos] == '|') {
                    return; // Already visited, stop here
                }
                if (lines[i][sPos] == '^') {
                    // instead of breaking, we replace '.' with '|' at sPos -1, and sPos+1
                    if (sPos > 0 && lines[i][sPos - 1] == '.') {
                        lines[i][sPos - 1] = '|';
                    }
                    if (sPos + 1 < lines[i].size() && lines[i][sPos + 1] == '.') {
                        lines[i][sPos + 1] = '|';
                    }
                    if (sPos > 0) {
                        self(self, sPos - 1, lines, i + 1, ans);
                    }
                    if (sPos + 1 < lines[i].size()) {
                        self(self, sPos + 1, lines, i + 1, ans);
                    }
                    ans++;
                    break;
                }
                if (lines[i][sPos] == '.') {
                    lines[i][sPos] = '|';
                }
            }
        };

    beam(beam, sPos, lines, 1, ans);
    return ans;
}

unsigned long long solve_part2(const vector<string>& lines) {
    if (lines.empty()) return 0;
    const int rows = static_cast<int>(lines.size());
    const int cols = static_cast<int>(lines[0].size());

    int start_col = -1;
    for (int c = 0; c < cols; ++c) {
        if (lines[0][c] == 'S') {
            start_col = c;
            break;
        }
    }
    if (start_col == -1) return 0;

    vector<unsigned long long> dp(cols), next_dp(cols);
    unsigned long long timelines = 0;

    if (rows == 1) return 1;
    dp[start_col] = 1;

    for (int r = 1; r < rows; ++r) {
        fill(next_dp.begin(), next_dp.end(), 0);
        for (int c = 0; c < cols; ++c) {
            if (dp[c] == 0) continue;
            char cell = lines[r][c];

            auto add_timeline = [&](int next_r, int next_c, unsigned long long ways) {
                if (next_r >= rows || next_c < 0 || next_c >= cols) {
                    timelines += ways;
                } else {
                    next_dp[next_c] += ways;
                }
            };

            if (cell == '^') {
                add_timeline(r + 1, c - 1, dp[c]);
                add_timeline(r + 1, c + 1, dp[c]);
            } else {
                add_timeline(r + 1, c, dp[c]);
            }
        }
        dp.swap(next_dp);
    }

    return timelines;
}

int main() {
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

    long long part1 = solve_part1(lines);
    unsigned long long part2 = solve_part2(lines);
    cout << part1 << "\n" << part2 << "\n";

    return 0;
}
