# -*- coding: utf-8 -*-

from setting import Setting

class Matrix:
	def __init__(self):
		self.array = [[0 for _ in range(Setting.size)] for _ in range(Setting.size)]

	def show(self, particles):
		for i in particles:
			adjust = (Setting.size - 1) / 255
			x = int(i.x * adjust)
			y = int(i.y * adjust)
			# print("index", x, y)
			self.array[y][x] += 1

		text = ""
		for y in range(Setting.size):
			for x in range(Setting.size):
				text += "  *" if self.array[y][x] >= Setting.threshold else "   "
			text += "\n"
		print("-" * 10)
		print(text)
