from sys import stdin

t = int(stdin.readline())   # number of text cases

for line in stdin:
    h = 1                   # height of tree
    n = int(line)           # number of cycles
    for i in range(n):
        if i % 2 == 0:
            h *= 2
        else:
            h += 1
    print(h)
