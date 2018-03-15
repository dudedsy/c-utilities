# someplots.py

# recall stored data or generate data for conway shuffle
# plot in a variety of fashions

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

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os
import subprocess32 as subprocess
import math

import deckData as dd

def computeLayout(n):
	if n == 10:
		plotCols = 5
		plotRows = 2
	else:
		plotCols = int(math.sqrt(n))
		if math.sqrt(n) > plotCols: plotCols += 1
		plotRows = n/plotCols
		if plotRows * plotCols < n: plotRows += 1
	return plotRows, plotCols

def scatterAllDecks(n, stores):
	## scatter plot of all results
	plotRows, plotCols = computeLayout(n)
	for i in range(1, n + 1):
		plt.subplot(plotRows, plotCols, i)
		scatterDeck(stores[i])

def scatterDeck(store, style = 'b,'):
	plt.plot(store.df.index.values, store.df.shuffleCount.values, 'b,')

def histAllDecks(n, stores):
	## scatter plot of all results
	plotRows, plotCols = computeLayout(n)
	for i in range(1, n + 1):
		plt.subplot(plotRows, plotCols, i)	
		histDeck(stores[i])

def histDeck(store):
	maxSC = store.df.shuffleCount.max()	
	store.df.shuffleCount.plot(kind='hist', bins = maxSC+1)

def maxBins(store, bins=100):
	totalPoints = len(store.df.index)
	pointsPerBin = totalPoints / bins + 1

	maxdexes = []
	maxes = []

	for chunk in store.select('df', chunksize = pointsPerBin, columns = ['shuffleCount']):
		maxdex = chunk.shuffleCount.idxmax()
		maxdexes.append(maxdex)
		maxes.append(chunk.shuffleCount[maxdex])

	plt.plot(maxdexes, maxes, 'r.-')

def allMaxBins(n, stores, bins=100):
	plotRows, plotCols = computeLayout(n)
	for i in range(1, n+1):
		plt.subplot(plotRows,plotCols, i)
		maxBins(stores[i], bins)

def allHexBins(n, stores):
	plotRows, plotCols = computeLayout(n)
	for i in range(1, n+1):
		plt.subplot(plotRows, plotCols, i)
		hexBins(stores[i])

def hexBins(store, gridsize = 150):
	gridy = store.df.shuffleCount.max()/2 + 1
	plt.hexbin(store.df.index.values, store.df.shuffleCount.values, gridsize = (gridsize, gridy), mincnt = 1)

def main():
	n = dd.userDeckSize()
	endpoints = dd.endpoints(n)
	stores = dd.hd5All(n)

	plt.style.use('ggplot')

	if n < 11:
		plt.figure(1)
		scatterAllDecks(n, stores)

		plt.figure(2)
		histAllDecks(n, stores)

		plt.figure(3)
		allHexBins(n, stores)

	plt.figure(4)
	allMaxBins(n, stores)

	plt.show()

	return store

if __name__ == '__main__':
	store = main()