// ./a.out < input.txt  0.04s user 0.00s system 85% cpu 0.046 total

#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long countIsolatedAtSymbols(const vector<string> &lines, int H, int W)
{
    long long ans = 0;
    vector<pair<int, int>> atPositions;

    for (int r = 0; r < H; ++r)
    {
        for (int c = 0; c < W; ++c)
        {
            if (lines[r][c] == '@')
            {
                // Found an '@', look for adjacent numbers
                long long adjacentAtCounts = 0;

                // Count adjacent @ to the current '@'
                // if fewer than 3, count this '@', otherwise skip them.

                for (int dr = -1; dr <= 1; ++dr)
                {
                    for (int dc = -1; dc <= 1; ++dc)
                    {
                        if (dr == 0 && dc == 0)
                            continue;
                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < H && nc >= 0 && nc < W)
                        {
                            if (lines[nr][nc] == '@')
                            {
                                adjacentAtCounts++;
                            }
                        }
                    }
                }

                if (adjacentAtCounts < 4)
                {
                    atPositions.push_back({r, c});
                    ans++;
                }
            }
        }
    }

    for(const auto &pos : atPositions) {
        int r = pos.first;
        int c = pos.second;
        // Remove the '@' from the grid
        // to avoid counting it again in subsequent calls
        const_cast<string&>(lines[r])[c] = '.'; 
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line))
    {
        if (line.empty())
            continue;
        lines.push_back(line);
    }
    if (lines.empty())
        return 0;

    int H = lines.size();
    int W = lines[0].size();

    long long ans = countIsolatedAtSymbols(lines, H, W);

    cout << ans << "\n";

    while(true) {
        long long newAns = countIsolatedAtSymbols(lines, H, W);
        if(newAns == 0) {
            break;
        }
        ans += newAns;
    }

    cout << ans << "\n";
    return 0;
}