# -*- coding: utf-8 -*-

from particle import Particle
from setting import Setting

class Matrix:
	def __init__(self):
		# array[2][8][8]
		self.array = [[[False] * Setting.size for _ in range(Setting.size)] for _ in range(2)]

	def setArray(self):
		# Fill an array with particles
		yAxis = Setting.particles // 8
		xAxis = Setting.particles % 8
		for y in range(yAxis):
			self.array[0][y] = [True] * 8
		for x in range(xAxis):
			self.array[0][yAxis][x] = True

	def refresh(self, angle):
		particle = Particle(self.array, angle)
		for y in range(Setting.size):
			for x in range(Setting.size):
				if (self.array[0][y][x]):
					particle.move(x, y)

	def shift(self):
		self.array[0] = self.array[1]
		self.array[1] = [[False] * Setting.size for _ in range(Setting.size)]

	def show(self):
		text = ""
		for row in self.array[0]:
			for value in row:
				text += "  *" if value else "   "
			text += "\n"
		text += "-----"
		print(text)
