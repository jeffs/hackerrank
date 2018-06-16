from sys import stdin

n, k = [int(s) for s in stdin.readline().split()]
height = max(int(s) for s in stdin.readline().split())
print(max(height - k, 0))
