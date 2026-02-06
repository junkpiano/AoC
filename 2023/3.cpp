// AoC 2023 Day 3 Solutions in C++14

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
using namespace std;

void solve1(const vector<string>& lines) {
    // Implementation for solve1 goes here
    // each line is composed of numeric characters, and special chars .#*, etc.
    // . means ignorable value
    // if sequence of digits is found, check any special chars adjecent to it in all directions(including diagonals)
    // if special char found, add the numeric value to a running total

    // interate lines to find sequences of digits
    // for each sequence, check adjacent characters if special char found, add to total

    int H = lines.size();
    if (H == 0) return;
    int W = lines[0].size();

    long long ans = 0;

    for (int r = 0; r < H; ++r) {
        int c = 0;
        while (c < W) {
            if (isdigit(lines[r][c])) {
                // Found start of a number
                int startCol = c;
                int num = 0;
                while (c < W && isdigit(lines[r][c])) {
                    num = num * 10 + (lines[r][c] - '0');
                    c++;
                }
                int endCol = c - 1;

                // Check surrounding characters around the entire number
                bool hasSpecialChar = false;

                // Check row above, same row (left/right), and row below
                for (int checkRow = r - 1; checkRow <= r + 1 && !hasSpecialChar; ++checkRow) {
                    if (checkRow < 0 || checkRow >= H) continue;

                    for (int checkCol = startCol - 1; checkCol <= endCol + 1 && !hasSpecialChar; ++checkCol) {
                        if (checkCol < 0 || checkCol >= W) continue;

                        // Skip the number itself
                        if (checkRow == r && checkCol >= startCol && checkCol <= endCol) continue;

                        char ch = lines[checkRow][checkCol];
                        if (!isdigit(ch) && ch != '.') {
                            hasSpecialChar = true;
                        }
                    }
                }

                if (hasSpecialChar) {
                    ans += num;
                }
            } else {
                c++;
            }
        }
    }

    cout << ans << "\n";
}

void solve2(const vector<string>& lines) {
    // first find *.
    // if found, please find the nearest digits adjacent to it in all 8 directions
    // if digits found, expand to left and right to get full number.
    // if the number of digits is exactly 2, multiplay them and add to total

    int H = lines.size();
    if (H == 0) return;
    int W = lines[0].size();

    long long ans = 0;

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (lines[r][c] == '*') {
                // Found a *, check all 8 adjacent positions
                set<pair<int, int>> numberStarts; // Store (row, startCol) to avoid duplicates
                vector<int> adjacentNumbers;

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) continue;
                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < H && nc >= 0 && nc < W && isdigit(lines[nr][nc])) {
                            // Found a digit, expand to get full number
                            // First, find the start of the number
                            int startCol = nc;
                            while (startCol > 0 && isdigit(lines[nr][startCol - 1])) {
                                startCol--;
                            }

                            // Check if we've already processed this number
                            if (numberStarts.find({nr, startCol}) != numberStarts.end()) {
                                continue;
                            }
                            numberStarts.insert({nr, startCol});

                            // Now extract the full number
                            int num = 0;
                            int col = startCol;
                            while (col < W && isdigit(lines[nr][col])) {
                                num = num * 10 + (lines[nr][col] - '0');
                                col++;
                            }
                            adjacentNumbers.push_back(num);
                        }
                    }
                }

                // If exactly 2 numbers adjacent, multiply them
                if (adjacentNumbers.size() == 2) {
                    ans += (long long)adjacentNumbers[0] * adjacentNumbers[1];
                }
            }
        }
    }

    cout << ans << "\n";


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }
    if (lines.empty()) return 0;

    solve1(lines);
    solve2(lines);
    return 0;
}