#include <algorithm>
#include <iostream>
#include <string>
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

long countElement(const vector<int> &v, int x) {
  long cnt = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == x)
      cnt++;
  }
  return cnt;
}

long long solveP1(const vector<int> &l, const vector<int> &r) {
  long long ans = 0;

  for (int i = 0; i < l.size(); i++) {
    ans += abs(l[i] - r[i]);
  }

  return ans;
}

long long solveP2(const vector<int> &l, const vector<int> &r) {
  long long ans = 0;
  unordered_map<int, int> mp;

  for (int i = 0; i < l.size(); i++) {
    if (mp[l[i]] == 0) {
      mp[l[i]] = countElement(r, l[i]);
    }

    if (mp[l[i]] > 0) {
      ans += l[i] * mp[l[i]];
    } else {
      mp[l[i]] = -1;
    }
  }

  return ans;
}

int main() {
  vector<int> l, r;

  while (1) {
    string s;
    getline(cin, s);
    if (s == "")
      break;

    vector<string> v = split(s, " ");
    l.push_back(stoi(v[0]));
    r.push_back(stoi(v[1]));
  }

  sort(l.begin(), l.end());
  sort(r.begin(), r.end());

  long long ans = 0;
  ans = solveP2(l, r);
  cout << ans << endl;
  return 0;
}
