#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <cstdlib>

using namespace std;

// mac の旧 clang でも動く gcd 実装
int gcdll(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

using P = pair<int,int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        grid.push_back(line);
    }
    if (grid.empty()) return 0;

    int H = grid.size();
    int W = grid[0].size();

    unordered_map<char, vector<P>> freq;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            char ch = grid[r][c];
            if (ch != '.') {
                freq[ch].push_back({r, c});
            }
        }
    }

    vector<vector<bool>> anti1(H, vector<bool>(W, false));
    vector<vector<bool>> anti2(H, vector<bool>(W, false));

    for (const auto& kv : freq) {
        const vector<P>& pts = kv.second;
        int n = pts.size();
        if (n < 2) continue;

        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                int r1 = pts[i].first;
                int c1 = pts[i].second;
                int r2 = pts[j].first;
                int c2 = pts[j].second;

                // Part 1
                {
                    int ar = 2*r1 - r2;
                    int ac = 2*c1 - c2;
                    if (0 <= ar && ar < H && 0 <= ac && ac < W)
                        anti1[ar][ac] = true;

                    int br = 2*r2 - r1;
                    int bc = 2*c2 - c1;
                    if (0 <= br && br < H && 0 <= bc && bc < W)
                        anti1[br][bc] = true;
                }

                // Part 2
                int dr = r2 - r1;
                int dc = c2 - c1;
                int g = gcdll(dr, dc);
                int sr = dr / g;
                int sc = dc / g;

                // backward from p1
                {
                    int rr = r1;
                    int cc = c1;
                    while (0 <= rr && rr < H && 0 <= cc && cc < W) {
                        anti2[rr][cc] = true;
                        rr -= sr;
                        cc -= sc;
                    }
                }

                // forward from p2
                {
                    int rr = r2;
                    int cc = c2;
                    while (0 <= rr && rr < H && 0 <= cc && cc < W) {
                        anti2[rr][cc] = true;
                        rr += sr;
                        cc += sc;
                    }
                }
            }
        }
    }

    long long count1 = 0, count2 = 0;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (anti1[r][c]) ++count1;
            if (anti2[r][c]) ++count2;
        }
    }

    cout << "Part1 antinodes: " << count1 << "\n";
    cout << "Part2 antinodes: " << count2 << "\n";

    return 0;
}
