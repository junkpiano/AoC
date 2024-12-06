#include <algorithm>
#include <iostream>
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

void part1(const vector<string> &lines,
           unordered_map<int, vector<int>> &rules) {}

void part2(const vector<string> &lines,
           unordered_map<int, vector<int>> &rules) {}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // For getting input from input.txt file
  freopen("input.txt", "r", stdin);

  vector<string> lines;
  int section = 1;
  int max_section = 1;

  while (1) {
    string s;
    getline(cin, s);
    if (s == "") {
      if (section == max_section)
        break;
      section++;
      continue;
    }
  }

  // part1(lines, rules);
  // part2(lines, rules);

  return 0;
}
