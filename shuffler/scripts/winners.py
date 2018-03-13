# winners.py

# uses shuffle c pipeline to generate csv datafile of permutation shuffle data
# reads in csv and creates a pickled version of some highlights

# Copyright 2018 Brian G. Evans

# Licensed under the Apache License, Version 2.0 (the "License"); 
# you may not use this file except in compliance with the License. 
# You may obtain a copy of the License at 

#     http://www.apache.org/licenses/LICENSE-2.0 

# Unless required by applicable law or agreed to in writing, software 
# distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
# See the License for the specific language governing permissions and 
# limitations under the License. 

import csv
import cPickle
import os
import deckData as dd

class Winners(object):

	def __init__(self, n, filename, around = 20):

		self.endpoints = dd.endpoints(n)
		## maxes stores (number of moves, permutation number) tuples
		self.maxes = [{'shuffleCount':-1} for _ in xrange(n+1)]
		self.bestSoFar = []
		self.n = n
		self.around = around
		self.aroundEnds = [[] for _ in xrange(n+1)]
		self.aroundMaxes = [[] for _ in xrange(n+1)]

		# first pass, find all bests
		print "first pass"
		self._rowMap(filename, self._firstPass)

		# second pass, find the arounds
		print "second pass"
		self._rowMap(filename, self._secondPass)
		
	def _firstPass(self, row, decksize):
		if row['best'] == '*': 
			self.bestSoFar.append(row)
		if row['shuffleCount'] > self.maxes[decksize]['shuffleCount']:
			self.maxes[decksize] = row

	def _secondPass(self, row, decksize):
		if self.endpoints[decksize] - row['n'] < self.around:
			self.aroundEnds[decksize].append(row)
		if row['n'] - self.endpoints[decksize - 1] < self.around:
			self.aroundEnds[decksize - 1].append(row) 
		if -self.around < row['n'] - self.maxes[decksize]['n'] < self.around:
			self.aroundMaxes[decksize].append(row)


	def pickleIt(self, filename = ''):
		print "pickling winner data"
		if filename == '': 
			filename = "../data/winners{}.pkl".format(self.n)
		print "filename = {}".format(filename)
		with open(filename, 'w') as pfile:
			print "{} open for writing".format(filename)
			cPickle.dump(self, pfile)
		return 0


	def _rowMap(self, filename, fcn):
		with open(filename, 'r') as f:
			re = csv.DictReader(f, delimiter=',')
			decksize = 0
			for row in re:
				row['n'] = int(row['n'])
				row['shuffleCount'] = int(row['shuffleCount'])
				if row['n'] > self.endpoints[decksize]: 
					decksize += 1
					print "starting decksize {}".format(decksize)
				fcn(row, decksize)

def main():
	n = dd.userDeckSize()

	filename = '../data/out{}v.csv'.format(n)

	check = dd.findGenData(n, filename, True)
	if check != 0:
		return None, check
	
	print "finding winners"
	winners = Winners(n, filename)

	check = winners.pickleIt()
	return winners, check

if __name__ == '__main__':
	winners, status = main()
	if status != 0: 
		print "an error occured"
	else: 
		print "winner processing complete"
