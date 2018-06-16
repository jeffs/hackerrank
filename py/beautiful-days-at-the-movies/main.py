from sys import stdin

def reverse(n):
    return int(str(n)[::-1])

def is_beautiful(n, k):
    return abs(n - reverse(n)) % k == 0

def main():
    i, j, k = [int(s) for s in stdin.readline().split()]
    r = 0
    for h in range(i, j + 1): 
        if is_beautiful(h, k):
            r += 1
    print(r)

main()
