#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue; // 入力に空行がない前提ならここはあってもOK
        grid.push_back(line);
    }
    if (grid.empty()) return 0;

    int H = (int)grid.size();
    int W = (int)grid[0].size();

    // 探す: ガードの初期位置と向き
    int sr = -1, sc = -1;
    int initDir = 0; // 0: up, 1: right, 2: down, 3: left
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            char ch = grid[r][c];
            if (ch == '^' || ch == 'v' || ch == '<' || ch == '>') {
                sr = r;
                sc = c;
                if (ch == '^') initDir = 0;
                else if (ch == '>') initDir = 1;
                else if (ch == 'v') initDir = 2;
                else if (ch == '<') initDir = 3;
            }
        }
    }

    if (sr == -1) {
        return 0; // ガードが見つからないのはおかしいけど一応
    }

    // シミュレーション用に、初期位置は空きマス扱いにしておく
    grid[sr][sc] = '.';

    // 方角ベクトル: up, right, down, left
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    // -------- Part 1: 元のマップでの訪問マス数 --------
    {
        vector<vector<bool>> visited(H, vector<bool>(W, false));
        int r = sr, c = sc, dir = initDir;
        visited[r][c] = true;

        while (true) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];

            // マップ外に出たら終了
            if (nr < 0 || nr >= H || nc < 0 || nc >= W) {
                break;
            }

            if (grid[nr][nc] == '#') {
                // 障害物が正面 → 右に90度回頭
                dir = (dir + 1) % 4;
                continue;
            }

            // 1歩前進
            r = nr;
            c = nc;
            visited[r][c] = true;
        }

        long long ans1 = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (visited[i][j]) ++ans1;
            }
        }

        cout << ans1 << "\n";
    }

    // -------- Part 2: 1つだけ新しい障害物を置いてループを作るパターン数 --------
    // 状態 (r, c, dir) を再訪したらループ
    long long ans2 = 0;

    // 各マス・各方向に対する「どの試行で訪問したか」を記録するマーク配列
    static vector<vector<array<int,4>>> seen;
    seen.assign(H, vector<array<int,4>>(W));
    int mark = 1; // 各候補ごとにインクリメントする

    for (int br = 0; br < H; ++br) {
        for (int bc = 0; bc < W; ++bc) {
            // スタート位置はNG
            if (br == sr && bc == sc) continue;
            // もともと障害物のところには置けないのでスキップ
            if (grid[br][bc] != '.') continue;

            // 仮に障害物を置く
            grid[br][bc] = '#';

            int r = sr, c = sc, dir = initDir;
            bool loop = false;
            int curMark = mark++;

            while (true) {
                // この状態を以前この候補で訪れていたらループ
                if (seen[r][c][dir] == curMark) {
                    loop = true;
                    break;
                }
                seen[r][c][dir] = curMark;

                int nr = r + dr[dir];
                int nc = c + dc[dir];

                // マップ外に出たらループではない
                if (nr < 0 || nr >= H || nc < 0 || nc >= W) {
                    break;
                }

                if (grid[nr][nc] == '#') {
                    // 障害物が正面 → 右回頭
                    dir = (dir + 1) % 4;
                    continue;
                }

                // 1歩前進
                r = nr;
                c = nc;
            }

            if (loop) {
                ++ans2;
            }

            // 障害物を元に戻す
            grid[br][bc] = '.';
        }
    }

    cout << ans2 << "\n";

    return 0;
}
