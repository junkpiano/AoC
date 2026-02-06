# python 4.py < input.txt  0.24s user 0.02s system 90% cpu 0.284 total

import sys

def count_isolated_at_symbols(lines, H, W):
    ans = 0
    at_positions = []

    for r in range(H):
        for c in range(W):
            if lines[r][c] == '@':
                # Found an '@', count adjacent '@' symbols
                adjacent_at_counts = 0

                # Check all 8 adjacent cells
                for dr in range(-1, 2):
                    for dc in range(-1, 2):
                        if dr == 0 and dc == 0:
                            continue
                        nr = r + dr
                        nc = c + dc

                        if 0 <= nr < H and 0 <= nc < W:
                            if lines[nr][nc] == '@':
                                adjacent_at_counts += 1

                # If fewer than 4 adjacent '@' symbols, this is "isolated"
                if adjacent_at_counts < 4:
                    at_positions.append((r, c))
                    ans += 1

    # Remove the '@' symbols from the grid
    for r, c in at_positions:
        lines[r][c] = '.'

    return ans

def main():
    lines = []
    for line in sys.stdin:
        line = line.rstrip('\n')
        if line:
            lines.append(list(line))  # Convert to list for mutability

    if not lines:
        return

    H = len(lines)
    W = len(lines[0])

    ans = count_isolated_at_symbols(lines, H, W)

    print(ans)

    # Keep processing until no more isolated '@' symbols
    while True:
        new_ans = count_isolated_at_symbols(lines, H, W)
        if new_ans == 0:
            break
        ans += new_ans

    print(ans)

if __name__ == "__main__":
    main()
