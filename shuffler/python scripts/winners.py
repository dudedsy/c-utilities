#winners.py

import csv

def factorial(n):
	if n <= 1: return 1
	return n * factorial(n-1)

class Winners(object):

	def __init__(self, n, filename):

		self.endpoints = [factorial(i) for i in range(0,n+1)]
		## maxes stores (number of moves, permutation number) tuples
		self.maxes = [(0,0) for _ in range(0,n+1)]
		self.bestSoFar = []

		with open(filename, 'r')as f:
			re = csv.reader(f, delimiter=',')
			decksize = 0
			for i, row in enumerate(re):
				row = int(row[0]), int(row[1]), row[2], row[3]
				if row[0] > self.endpoints[decksize]: 
					decksize += 1
					print "starting decksize {}".format(decksize)
				if row[3] == '*': 
					self.bestSoFar.append(row)
				if row[1] > self.maxes[decksize][0]:
					self.maxes[decksize] = (row[1],i)



winners = Winners(12, 'out12v.csv')
