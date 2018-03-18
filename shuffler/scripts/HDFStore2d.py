# HDFStore2d.py

# (c) Brian Evans, 2018

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.

# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.

# * Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import pandas as pd


class HDFStore2d(pd.HDFStore)

	def __init__(self, filename, mode = ''):
		if mode = '': 
			mode = 'a' if os.access(filename, os.R_OK) else 'w'
		if mode == 'a':
			if os.access(filename, os.R_OK):
				super(HDFStore2d, self).__init__(filename)
			else:
				raise IOError("Not able to access {} for reading.".format(filename))

		pass

	def calcColumn(self, fun, colname, columns = [], scalars = []):
		""" Adds a calculated column to the hdfStore2d.
		for each row of data st[r][colname] will be calculated by
		calling fun(st[r][columns], scalars)
		"""





		pass

	def colsFromdf(self, df, columns = [])
		pass

	def colsFromHDFStore(self, store, key = [], columns = []):
		pass

