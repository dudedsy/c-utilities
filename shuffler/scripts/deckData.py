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

def findGenData(n, filename, autoClobber = False):
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
	command = "../bin/oneThruN {} -n | ../bin/perm -b | ../bin/shuffle -v".format(n)
	print command
	try:
		ofile = open(filename, 'w')
		retval = subprocess.call(command, stdout = ofile, shell = True)
		if retval != 0: print "error with command"
	except:
		print "error creating datafile"
		retval = -1

	return retval

def loadHDF5(n, h5filename = ''):
	if h5filename == '': 
		h5filename = "../data/out{}.h5".format(n)
	
	h5loaded = False

	if os.access(h5filename, os.R_OK):
		userStr = raw_input("use existing hdf5 datastore? Y/n:")
		if userStr == '' or userStr not in "NonoNO":
			store = pd.HDFStore(h5filename)
			h5loaded = True

	if h5loaded == False:
		store = pd.HDFStore(h5filename)

		
		csvfilename = "../data/out{}v.csv".format(n)
		userStr = raw_input("Force recalculate csv? y/N:")
		findGenData(n, csvfilename, userStr != '' and userStr in 'yesYesYES')

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