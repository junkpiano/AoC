#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using i128 = __int128_t;

bool dfs(const vector<ull>& nums, int idx, ull cur, ull target) {
    // 途中で target を超えたらこれ以上どうやっても届かない
    if (cur > target) return false;

    if (idx == (int)nums.size()) {
        return cur == target;
    }

    ull next = nums[idx];

    // 1) 足し算
    {
        i128 tmp = (i128)cur + (i128)next;
        if (tmp <= (i128)target) {
            if (dfs(nums, idx + 1, (ull)tmp, target)) return true;
        }
    }

    // 2) 掛け算
    {
        i128 tmp = (i128)cur * (i128)next;
        if (tmp <= (i128)target) {
            if (dfs(nums, idx + 1, (ull)tmp, target)) return true;
        }
    }

    // 3) 連結（ || ）
    {
        ull p10 = 1;
        ull t = next;
        // next の桁数ぶん 10 を掛ける
        // next が 0 のときも 1 桁として扱うので do-while にする
        do {
            p10 *= 10;
            t /= 10;
        } while (t > 0);

        i128 tmp = (i128)cur * (i128)p10 + (i128)next;
        if (tmp <= (i128)target) {
            if (dfs(nums, idx + 1, (ull)tmp, target)) return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    ull answer = 0;

    while (std::getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);

        // 左側の "target:" を読む
        string token;
        ss >> token;
        if (token.back() == ':') token.pop_back();

        ull target = stoull(token);

        // 右側の数列
        vector<ull> nums;
        ull x;
        while (ss >> x) {
            nums.push_back(x);
        }

        if (nums.empty()) continue;

        // 最初の値を初期値にして DFS 開始
        if (dfs(nums, 1, nums[0], target)) {
            answer += target;
        }
    }

    cout << answer << '\n';
    return 0;
}
