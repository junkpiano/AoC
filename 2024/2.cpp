#include <algorithm>
#include <iostream>
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

int evaluate(const vector<int> &v) {
  bool increasing = true;
  if (v[0] > v[v.size() - 1]) {
    increasing = false;
  }

  int stop_index = -1;
  for (int i = 1; i < v.size(); i++) {
    if (increasing) {
      if (v[i] <= v[i - 1] || 1 > (v[i] - v[i - 1]) || 3 < (v[i] - v[i - 1])) {
        stop_index = i;
        break;
      }
    } else {
      if (v[i] >= v[i - 1] || 1 > (v[i - 1] - v[i]) || 3 < (v[i - 1] - v[i])) {
        stop_index = i;
        break;
      }
    }
  }

  return stop_index;
}

int main() {
  long long answer = 0;
  bool part2 = true;
  while (1) {
    string s;
    getline(cin, s);
    if (s == "")
      break;

    vector<int> v = int_split(s, " ");

    int stop_index = evaluate(v);
    if (stop_index == -1) {
      answer++;
      continue;
    }

    if (!part2) {
      continue;
    }

    vector<int> cp1 = v;
    vector<int> cp2 = v;
    cp1.erase(cp1.begin() + stop_index);
    cp2.erase(cp2.begin() + stop_index - 1);

    stop_index = evaluate(cp1);
    if (stop_index == -1) {
      answer++;
      continue;
    }

    stop_index = evaluate(cp2);
    if (stop_index == -1) {
      answer++;
      continue;
    }
  }

  cout << answer << endl;
  return 0;
}
