#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    vector<pair<long long, long long>> ranges;
    vector<string> ingredients;

    while (getline(cin, line))
    {
        if (line.empty())
            break;

        size_t pos = line.find('-');
        long long st = stoll(line.substr(0, pos));
        long long en = stoll(line.substr(pos + 1));
        ranges.push_back({st, en});
    }

    while (getline(cin, line))
    {
        if (line.empty())
            break;
        ingredients.push_back(line);
    }

    long long ans = 0;

    for (const string &ingredient : ingredients)
    {
        for (const auto &range : ranges)
        {
            long long st = range.first;
            long long en = range.second;

            long long num = stoll(ingredient);
            if (st <= num && num <= en)
            {
                ans++;
                break;
            }
        }
    }
    cout << ans << "\n";

    // Sort ranges by start position
    sort(ranges.begin(), ranges.end());

    // Merge overlapping ranges and count total unique elements
    long long ans2 = 0;
    if (!ranges.empty())
    {
        long long currentStart = ranges[0].first;
        long long currentEnd = ranges[0].second;

        for (size_t i = 1; i < ranges.size(); ++i)
        {
            long long st = ranges[i].first;
            long long en = ranges[i].second;

            // If ranges overlap or are adjacent, merge them
            if (st <= currentEnd + 1)
            {
                currentEnd = max(currentEnd, en);
            }
            else
            {
                // No overlap, add current range to total
                ans2 += (currentEnd - currentStart + 1);
                currentStart = st;
                currentEnd = en;
            }
        }
        // Add the last range
        ans2 += (currentEnd - currentStart + 1);
    }

    cout << ans2 << "\n";
    return 0;
}