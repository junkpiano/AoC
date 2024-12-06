#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string &str, const string &delimiter) {
  vector<string> tokens;
  size_t pos = 0;
  string token;
  string s = str;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    if (token != "")
      tokens.push_back(token);
    s = s.substr(pos + delimiter.length());
  }

  if (s != "")
    tokens.push_back(s);

  return tokens;
}

vector<int> int_split(const string &str, const string &delimiter) {
  vector<string> tokens = split(str, delimiter);
  vector<int> int_tokens;
  for (int i = 0; i < tokens.size(); i++) {
    int_tokens.push_back(stoi(tokens[i]));
  }
  return int_tokens;
}

void part1(const vector<string> &lines) {
  long long answer = 0;
  vector<vector<int>> directions = {
      {0, 1},  // right
      {1, 0},  // down
      {0, -1}, // left
      {-1, 0}, // up
      {1, 1},  // down-right
      {1, -1}, // down-left
      {-1, 1}, // up-right
      {-1, -1} // up-left
  };

  for (int i = 0; i < lines.size(); i++) {
    string line = lines[i];
    int x = 0;
    int y = 0;
    for (int j = 0; j < line.size(); j++) {
      if (line[j] == 'X') {
        x = i;
        y = j;

        for (int k = 0; k < directions.size(); k++) {
          int dx = directions[k][0];
          int dy = directions[k][1];
          int nx = x;
          int ny = y;
          string xmas = "";
          while (1) {
            if (xmas.size() < 4 && nx >= 0 && nx < line.size() && ny >= 0 &&
                ny < lines.size())
              xmas += lines[nx][ny];
            else
              break;

            nx += dx;
            ny += dy;
          }
          if (xmas == "XMAS") {
            answer++;
          }
        }
      }
    }
  }

  cout << answer << endl;
}

void part2(const vector<string> &lines) {
  long long answer = 0;
  for (int i = 0; i < lines.size() - 2; i++) {
    for (int j = 0; j < lines[i].size() - 2; j++) {
      string a = {lines[i][j], lines[i + 1][j + 1], lines[i + 2][j + 2]};
      string b = {lines[i][j + 2], lines[i + 1][j + 1], lines[i + 2][j]};
      if ((a == "MAS" || a == "SAM") && (b == "MAS" || b == "SAM")) {
        answer++;
      }
    }
  }
  cout << answer << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // For getting input from input.txt file
  freopen("input.txt", "r", stdin);

  long long answer = 0;
  vector<string> lines;
  while (1) {
    string s;
    getline(cin, s);
    if (s == "")
      break;
    lines.push_back(s);
  }

  part1(lines);
  part2(lines);

  return 0;
}
