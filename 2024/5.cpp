#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
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

bool isSafe(const string &line, unordered_map<int, vector<int>> &rules) {
  vector<int> nums = int_split(line, ",");
  bool safe = true;
  for (int i = nums.size() - 2; i >= 0; i--) {
    vector<int> rule = rules[nums[i]];
    int j = i + 1;
    while (j < nums.size()) {
      if (find(rule.begin(), rule.end(), nums[j]) == rule.end()) {
        safe = false;
        break;
      }
      j++;
    }
    if (!safe)
      break;
  }

  return safe;
}

void part1(const vector<string> &lines,
           unordered_map<int, vector<int>> &rules) {
  long long answer = 0;
  for (auto line : lines) {
    bool safe = isSafe(line, rules);
    if (safe) {
      answer += nums[nums.size() / 2];
    }
  }
  cout << answer << endl;
}

auto cmp = [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
  return lhs.second > rhs.second;
};

void part2(const vector<string> &lines,
           unordered_map<int, vector<int>> &rules) {
  long long answer = 0;
  for (auto line : lines) {
    bool safe = isSafe(line, rules);
    if (!safe) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(
          cmp);
      for (int i = 0; i < nums.size(); i++) {
        vector<int> rule = rules[nums[i]];
        int count = 0;
        for (int j = 0; j < nums.size(); j++) {
          if (find(rule.begin(), rule.end(), nums[j]) != rule.end()) {
            count++;
          }
        }

        pq.push(make_pair(nums[i], count));
      }

      int k = 0;
      while (pq.size() > 0) {
        pair<int, int> p = pq.top();
        pq.pop();
        if (k == nums.size() / 2) {
          answer += p.first;
          break;
        }
        k++;
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
  unordered_map<int, vector<int>> rules;
  int section = 1;
  int max_section = 2;
  while (1) {
    string s;
    getline(cin, s);
    if (s == "") {
      if (section == max_section)
        break;
      section++;
      continue;
    }
    if (section == 1) {
      vector<int> nums = int_split(s, "|");
      rules[nums[0]].push_back(nums[1]);
    } else {
      lines.push_back(s);
    }
  }

  part1(lines, rules);
  part2(lines, rules);

  return 0;
}
