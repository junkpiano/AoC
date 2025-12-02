// Repeated Pattern ID Validator

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve1(const string& idRanges) {
    // split string by commas
    vector<string> idList;
    size_t start = 0;
    size_t end = idRanges.find(',');
    while (end != string::npos) {
        idList.push_back(idRanges.substr(start, end - start));
        start = end + 1;
        end = idRanges.find(',', start);
    }
    idList.push_back(idRanges.substr(start));
    int H = idList.size();

    // idRange is formatted as [numeric]-[numeric]
    // it shows range of IDs.
    // if the ID length is even and it's concatenated of 2 same halves, it's valid.

    // answer is sum of the all valid IDs in the ranges.
    long long ans = 0;

    for (int r = 0; r < H; ++r) {
        string idRange = idList[r];
        size_t dashPos = idRange.find('-');
        long long startID = stoll(idRange.substr(0, dashPos));
        long long endID = stoll(idRange.substr(dashPos + 1));

        for (long long id = startID; id <= endID; ++id) {
            string idStr = to_string(id);
            int len = idStr.length();
            if (len % 2 == 0) {
                string firstHalf = idStr.substr(0, len / 2);
                string secondHalf = idStr.substr(len / 2);
                if (firstHalf == secondHalf) {
                    ans += id;
                }
            }
        }
    }

    cout << ans << "\n";
}

void solve2(const string& idRanges) {
    // split string by commas
    vector<string> idList;
    size_t start = 0;
    size_t end = idRanges.find(',');
    while (end != string::npos) {
        idList.push_back(idRanges.substr(start, end - start));
        start = end + 1;
        end = idRanges.find(',', start);
    }
    idList.push_back(idRanges.substr(start));
    int H = idList.size();

    // idRange is formatted as [numeric]-[numeric]
    // it shows range of IDs.
    // if the ID length is even and it's concatenated of 2 same halves, it's valid.

    // answer is sum of the all valid IDs in the ranges.
    long long ans = 0;

    for (int r = 0; r < H; ++r) {
        string idRange = idList[r];
        size_t dashPos = idRange.find('-');
        long long startID = stoll(idRange.substr(0, dashPos));
        long long endID = stoll(idRange.substr(dashPos + 1));

        for (long long id = startID; id <= endID; ++id) {
            string idStr = to_string(id);
            int len = idStr.length();

            // here you can check more than twice.
            // from 2 to len
            // if all chunks are same, then it's valid.

            bool valid = false;
            // Try all possible number of chunks from 2 to len
            for (int numChunks = 2; numChunks <= len && !valid; ++numChunks) {
                if (len % numChunks == 0) {
                    int chunkSize = len / numChunks;
                    bool allSame = true;
                    string firstChunk = idStr.substr(0, chunkSize);

                    for (int i = 1; i < numChunks; ++i) {
                        string chunk = idStr.substr(i * chunkSize, chunkSize);
                        if (chunk != firstChunk) {
                            allSame = false;
                            break;
                        }
                    }

                    if (allSame) {
                        valid = true;
                    }
                }
            }

            if (valid) {
                ans += id;
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    cin >> line;

    solve1(line);
    solve2(line);
    return 0;
}