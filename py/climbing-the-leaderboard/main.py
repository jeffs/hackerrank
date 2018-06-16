#!/usr/bin/env python3

from sys import stdin
from bisect import bisect_left

class SortedSet:

    def __init__(self, values=()):
        self.values = sorted(list(set(values)))

    def insert(self, value):
        index = bisect_left(self.values, value)
        if index < len(self.values) and self.values[index] == value:
            return False
        else:
            self.values.insert(index, value)
            return True

    def find(self, value):
        return bisect_left(self.values, value)

    def has(self, value):
        index = bisect_left(self.values, value)
        return index < len(self.values) and self.values[index] == value

    def size(self):
        return len(self.values)

if __name__ == '__main__':

    n = int(stdin.readline())
    scores = SortedSet(int(score) for score in stdin.readline().split())
    m = int(stdin.readline())
    alice = [int(score) for score in stdin.readline().split()]

    for a in alice:
        scores.insert(a)
        print(scores.size() - scores.find(a))

