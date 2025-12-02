// Modulorithmic Dial Simulation
// 0-100 Circular Dial with Left and Right Turns


#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve1(const vector<string>& dials) {
    int H = dials.size();
    int W = dials[0].size();

    int position = 50;
    long long ans = 0;

    for(int r = 0; r < H; ++r) {
        char ch = dials[r][0];
        // Process each dial character
        // For example, if ch is 'L' or 'R', perform corresponding operations
        int number = stoi(dials[r].substr(1));

        if(ch == 'L') {
            position = ((position - number) % 100 + 100) % 100;
        } else if(ch == 'R') {
            position = (position + number) % 100;
        }

        if(position < 0) {
            position += 100;
        } else if(position >= 100) {
            position -= 100;
        }

        if(position == 0) {
            ans++;
        }
    }

    cout << ans << "\n";
}

void solve2(const vector<string>& dials) {
    int H = dials.size();
    int W = dials[0].size();

    int position = 50;
    long long ans = 0;

    for(int r = 0; r < H; ++r) {
        char ch = dials[r][0];
        int number = stoi(dials[r].substr(1));

        if(ch == 'L') {
            for(int i = 0; i < number; ++i) {
                position = ((position - 1) % 100 + 100) % 100;
                if(position == 0) {
                    ans++;
                }
            }
        } else if(ch == 'R') {
            for(int i = 0; i < number; ++i) {
                position = (position + 1) % 100;
                if(position == 0) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> dials;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        dials.push_back(line);
    }
    if (dials.empty()) return 0;

    solve1(dials);
    solve2(dials);
    return 0;
}