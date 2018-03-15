#deckData.py

# general helper functions for creating and manipulating conway shuffle data

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

import os
import subprocess32 as subprocess
import pandas as pd
import numpy as np

MAXDECKSIZE = 255

def endpoints(n): 
	return [factorial(i) for i in xrange(n+2)]

def factorial(n):
	if n <= 1: return 1
	return n * factorial(n-1)

def userDeckSize():
	gotNum = False
	while (1):
		s = raw_input("Enter maximum deck size:")
		try: 
			n = int(s)
		except ValueError:
			print "enter an integer (base 10)"
			continue

		if 1 <= n <= MAXDECKSIZE:
			break
		else:
			print "number must be between 1 and {} (inclusive)".format(MAXDECKSIZE)
	return n

def findGenData(n, filename, autoClobber = False, options = 'v'):
	if os.access(filename, os.R_OK):
		print "precalculated dataset available"
		if autoClobber: 
			print "clobber mode on, the csv will be overwritten."
		else:
			print "using precalculated data"
			return 0
	elif os.access(filename, os.F_OK):
		print "file exists but no read permissions, check os permissions"
		return -1

	print "writing datafile to {}\n (this may take some time, especially for n > 10)".format(filename)
	command = "../bin/oneThruN {} -n | ../bin/perm -b{} | ../bin/shuffle -v".format(n, options)
	print command
	try:
		ofile = open(filename, 'w')
		retval = subprocess.call(command, stdout = ofile, shell = True)
		if retval != 0: print "error with command"
	except:
		print "error creating datafile"
		retval = -1

	return retval

def loadHDF5(n, options = None, clobberh5 = None, clobberCSV = None): 
	if options == None:
		options = getOptions()

	filename = "../data/out{}{}".format(n, options)
	h5filename = filename + '.h5'
	
	store = None
	if os.access(h5filename, os.R_OK):
		if clobberh5 == None:
			clobberh5 = not yesNo("use existing hdf5 datastore?")
		if clobberh5 == False:
			store = pd.HDFStore(h5filename)

	if store == None:
		store = pd.HDFStore(h5filename)
		csvfilename = filename + '.csv'

		if clobberCSV == None:
			clobberCSV = noYes("Force recalculate csv?")
		findGenData(n, csvfilename, clobberCSV, options)

		store.put(	'df', 
					pd.DataFrame(columns=['n', 'shuffleCount', 'perm', 'best']), 
					format = 'table',
					data_columns = True,

				)
		reader = pd.read_csv(csvfilename, 
							 index_col = 'n', 
							 chunksize = 1000000, 
							 dtype = {	'n' : np.int64, 
							 			'shuffleCount' : np.int32, 
							 			'best' : np.object
							 		 }
						)
		for chunk in reader:
			store.append('df', chunk)
		h5loaded = True
	return store

def hd5All(n, options = None, clobberh5 = None, clobberCSV = None):
	stores = [None] * (n + 1)
	if options == None: options = getOptions()
	if clobberCSV == None:
		clobberCSV = noYes("Force recalculate csv files?")
	if clobberh5 == None:
		clobberh5 = noYes("Force recalculate hdf5 files?")
	for i in range(1, n+1):
		stores[i] = loadHDF5(i, options, clobberh5, clobberCSV)
	return stores

def yesNo(question):
	question += " Y/n: "
	userStr = raw_input(question)
	return userStr == '' or userStr not in "NonoNO"

def noYes(question):
	question += " y/N: "
	userStr = raw_input(question)
	return userStr != '' and userStr in 'yesYesYES'

def getOptions():
	options = ''
	if noYes("use lexographic sorting?"):
		options += 's'

	if noYes("use reverse mode?"):
		options += 'r'

	return options