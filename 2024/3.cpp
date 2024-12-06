#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <cassert>
using namespace std;

vector<string> split(const string &str, const string &delimiter)
{
  vector<string> tokens;
  size_t pos = 0;
  string token;
  string s = str;
  while ((pos = s.find(delimiter)) != string::npos)
  {
    token = s.substr(0, pos);
    if (token != "")
      tokens.push_back(token);
    s = s.substr(pos + delimiter.length());
  }

  if (s != "")
    tokens.push_back(s);

  return tokens;
}

vector<int> int_split(const string &str, const string &delimiter)
{
  vector<string> tokens = split(str, delimiter);
  vector<int> int_tokens;
  for (int i = 0; i < tokens.size(); i++)
  {
    int_tokens.push_back(stoi(tokens[i]));
  }
  return int_tokens;
}

void part1(const string &input)
{
  long long answer = 0;
  regex re(R"(mul\((\d{1,3}),(\d{1,3})\))");
  smatch m;
  string::const_iterator searchStart(input.cbegin());

  while (regex_search(searchStart, input.cend(), m, re))
  {
    int a = stoi(m[1]);
    int b = stoi(m[2]);
    answer += a * b;
    searchStart = m.suffix().first;
  }

  cout << answer << endl;
}

void part2(const string &input)
{
  long long answer = 0;
  regex _do(R"(do\(\))");
  regex _dont(R"(don't\(\))");
  regex re(R"(mul\((\d{1,3}),(\d{1,3})\))");
  smatch m;
  string::const_iterator searchStart(input.cbegin());
  string doStr = "";

  bool active = true;
  while (true)
  {
    smatch m1, m2, m3;
    regex_search(searchStart, input.cend(), m1, re);
    regex_search(searchStart, input.cend(), m2, _do);
    regex_search(searchStart, input.cend(), m3, _dont);

    if (m1.empty() && m2.empty() && m3.empty())
      break;

    int minIdx = min(m1.position(), min(m2.position(), m3.position()));

    if (minIdx == m1.position())
    {
      if (active)
      {
        int a = stoi(m1[1]);
        int b = stoi(m1[2]);
        answer += a * b;

        cout << m1[0] << endl;
      }
      searchStart = m1.suffix().first;
    }
    else if (minIdx == m2.position())
    {
      active = true;
      cout << m2[0] << endl;
      searchStart = m2.suffix().first;
    }
    else if (minIdx == m3.position())
    {
      active = false;
      cout << m2[0] << endl;
      searchStart = m3.suffix().first;
    }
  }
  cout << answer << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // For getting input from input.txt file
  freopen("input.txt", "r", stdin);

  long long answer = 0;
  string input = "";
  while (1)
  {
    string s;
    getline(cin, s);
    if (s == "")
      break;

    input += s;
  }

  part1(input);
  part2(input);

  return 0;
}
