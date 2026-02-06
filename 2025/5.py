import sys

def main():
    ranges = []
    ingredients = []

    # Read ranges (format: "start-end")
    for line in sys.stdin:
        line = line.strip()
        if not line:
            break

        parts = line.split('-')
        st = int(parts[0])
        en = int(parts[1])
        ranges.append((st, en))

    # Read ingredients (individual numbers)
    for line in sys.stdin:
        line = line.strip()
        if not line:
            break
        ingredients.append(line)

    # Part 1: Count how many ingredients fall within any range
    ans = 0
    for ingredient in ingredients:
        num = int(ingredient)
        for st, en in ranges:
            if st <= num <= en:
                ans += 1
                break

    print(ans)

    # Part 2: Sort ranges by start position
    ranges.sort()

    # Merge overlapping ranges and count total unique elements
    ans2 = 0
    if ranges:
        current_start = ranges[0][0]
        current_end = ranges[0][1]

        for i in range(1, len(ranges)):
            st, en = ranges[i]

            # If ranges overlap or are adjacent, merge them
            if st <= current_end + 1:
                current_end = max(current_end, en)
            else:
                # No overlap, add current range to total
                ans2 += (current_end - current_start + 1)
                current_start = st
                current_end = en

        # Add the last range
        ans2 += (current_end - current_start + 1)

    print(ans2)

if __name__ == "__main__":
    main()
