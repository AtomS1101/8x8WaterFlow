# -*- coding: utf-8 -*-
from setting import Setting

class Matrix:
	def __init__(self):
		self.array = [[[False] * Setting.size_x for _ in range(Setting.size_y)] for _ in range(2)]

	def set_array(self, particle):
		count = 0
		for y in range(Setting.size_x):
			for x in range(Setting.size_y):
				self.array[0][y][x] = True
				if (count >= particle - 1):
					return
				count += 1

	def degital_write(self, x, y, bool):
		self.array[1][y][x] = bool

	def shift(self):
		self.array[0] = self.array[1]
		self.array[1] = [[False] * Setting.size_x for _ in range(Setting.size_y)]

	def show(self):
		text = ""
		for row in self.array[0]:
			for value in row:
				text += "  *" if value else "   "
			text += "\n"
		text += "-----"
		print(text)
