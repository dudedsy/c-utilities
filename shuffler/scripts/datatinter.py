# datatinter.py

# simple datashader functionality
# operates on a pandas hdfstore object
# creates datashader style plots in matplotlib
# inspired by datashader, from datashader.org
# but meant to be a simple python install
# for use with pandas HDFStore
# and pyplot
# also includes a mode for tinting integer valued datasets.

import pandas as pd 
import numpy as np

class Canvas(object):
	def __init__(self, plot_width = 600, plot_height = 600, x_range = None, y_range = None, intmode = False):
		self.plotSize((plot_height, plot_width))
		self.xrange = None if x_range == None else tuple(x_range)
		self.yrange = None if y_range == None else tuple(y_range)
		self.intmode = int_mode

		self.bins = pd.DataFrame(np.zeros(self.plotSize))

class DataTinter(object):
	def __init__(self, df, )