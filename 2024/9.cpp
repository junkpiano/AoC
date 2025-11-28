#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

// Compute checksum given a disk of block IDs (-1 = free)
long long compute_checksum(const vector<int> &disk) {
    long long ans = 0;
    for (long long i = 0; i < (long long)disk.size(); ++i) {
        if (disk[i] >= 0) {
            ans += i * (long long)disk[i];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) {
        return 0;
    }

    // Parse dense format into lengths
    vector<int> lens;
    lens.reserve(s.size());
    for (char ch : s) {
        lens.push_back(ch - '0');
    }

    // Build initial disk layout and record file lengths
    vector<int> disk;
    disk.reserve(1000000); // just a rough reserve
    vector<int> fileLen;

    int fileId = 0;
    for (size_t i = 0; i < lens.size(); ++i) {
        int len = lens[i];
        if ((i % 2) == 0) {
            // file segment
            fileLen.push_back(len);
            for (int k = 0; k < len; ++k) {
                disk.push_back(fileId);
            }
            fileId++;
        } else {
            // free segment
            for (int k = 0; k < len; ++k) {
                disk.push_back(-1);
            }
        }
    }
    int numFiles = fileId;

    // -------- Part 1: move individual blocks from rightmost file blocks --------
    vector<int> disk1 = disk;

    {
        long long left = 0;
        long long right = (long long)disk1.size() - 1;

        while (true) {
            while (left < (long long)disk1.size() && disk1[left] != -1) {
                ++left;
            }
            while (right >= 0 && disk1[right] == -1) {
                --right;
            }
            if (left >= right || left >= (long long)disk1.size() || right < 0) {
                break;
            }
            // Move a block from right to left
            disk1[left] = disk1[right];
            disk1[right] = -1;
            ++left;
            --right;
        }
    }

    long long part1 = compute_checksum(disk1);
    cout << part1 << "\n";

    // -------- Part 2: move whole files from highest ID downwards --------
    vector<int> disk2 = disk;

    for (int fid = numFiles - 1; fid >= 0; --fid) {
        int len = fileLen[fid];
        if (len == 0) continue; // zero-length file, nothing to move

        // Find current position of this file (first occurrence)
        long long pos = -1;
        for (long long i = 0; i < (long long)disk2.size(); ++i) {
            if (disk2[i] == fid) {
                pos = i;
                break;
            }
        }
        if (pos == -1) {
            // should not happen for len>0, but be safe
            continue;
        }

        // Find leftmost free span [start, start+len) with start+len-1 < pos
        long long bestStart = -1;
        long long i = 0;

        while (i < pos) {
            if (disk2[i] != -1) {
                ++i;
                continue;
            }
            long long j = i;
            while (j < pos && disk2[j] == -1) {
                ++j;
            }
            long long spanLen = j - i;
            if (spanLen >= len) {
                bestStart = i;
                break; // leftmost such span
            }
            i = j;
        }

        if (bestStart == -1) {
            // No suitable span to the left; file does not move.
            continue;
        }

        // Move the whole file of length len from pos to bestStart
        for (int k = 0; k < len; ++k) {
            disk2[bestStart + k] = fid;
            disk2[pos + k] = -1;
        }
    }

    long long part2 = compute_checksum(disk2);
    cout << part2 << "\n";

    return 0;
}
