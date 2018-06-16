from sys import stdin

letter_heights = tuple(int(s) for s in stdin.readline().split())
word = stdin.readline().strip()

word_height = max(letter_heights[ord(c) - ord('a')] for c in word)
print(word_height * len(word))
