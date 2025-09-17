# -*- coding: utf-8 -*-
from setting import Setting

class Matrix:
	def __init__(self):
		self.array = [[False] * Setting.size_x for _ in range(Setting.size_y)]

	def set_array(self, particle):
		count = 0
		for x in range(Setting.size_x):
			for y in range(Setting.size_y):
				self.array[y][x] = True
				if (count >= particle - 1):
					return
				count += 1

	def degital_write(self, x, y, bool):
		self.array[y][x] = bool

	def show(self):
		text = ""
		for row in self.array:
			for value in row:
				text += "  *" if value else "   "
			text += "\n"
		text += "\n-----"
		print(text)

if __name__ == "__main__":
	matrix = Matrix()
	matrix.degital_write(1, 1, True)
	matrix.show()
