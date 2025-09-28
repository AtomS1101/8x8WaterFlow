# -*- coding: utf-8 -*-

from setting import Setting
from random import randint

class Particle:
	def __init__(self, matrix, angle):
		self.matrix = matrix
		self.angle = angle

	def isVacant(self, x, y, index):
		directionX = [1, 1,  1,  0, -1, -1, -1, 0]
		directionY = [1, 0, -1, -1, -1,  0,  1, 1]
		index = index - 8 if (index >= 8) else index
		newX = x + directionX[index]
		newY = y + directionY[index]
		newX = 0 if (newX < 0) else (Setting.size - 1) if (newX >= Setting.size) else newX
		newY = 0 if (newY < 0) else (Setting.size - 1) if (newY >= Setting.size) else newY
		isVacant = (not self.matrix[1][newY][newX]) and (not self.matrix[0][newY][newX])
		return isVacant, newX, newY

	def move(self, x, y):
		step = [int(45 * n + 22.5) for n in range(8)]
		flag = False
		# Calculate one by one for PIC optimization
		for i in range(len(step) - 1):
			if (self.angle >= step[i] and self.angle < step[i + 1]):
				flag = True
				# ===========================================
				isVacant, newX, newY = self.isVacant(x, y, i)
				if (isVacant): # Simply move if it's vacnt
					self.matrix[1][newY][newX] = True
					return
				# ===========================================
				randDirect = -1 if (randint(0, 1) == 0) else 1
				isVacant, newX, newY = self.isVacant(x, y, i+randDirect)
				if (isVacant):
					self.matrix[1][newY][newX] = True
					return
				# ===========================================
				r = randint(0, Setting.viscous)
				randDirect = -2 if (r == 0) else 2 if (r == 1) else 0
				isVacant, newX, newY = self.isVacant(x, y, i+randDirect)
				if (isVacant):
					self.matrix[1][newY][newX] = True
					return
				# ===========================================
				#　default
				self.matrix[1][y][x] = True # Stay there
				break

		if (not flag):
			# ===========================================
			isVacant, newX, newY = self.isVacant(x, y, 7)
			if (isVacant): # Simply move if it's vacnt
				self.matrix[1][newY][newX] = True
				return
			# ===========================================
			randDirect = -1 if (randint(0, 1) == 0) else 1
			isVacant, newX, newY = self.isVacant(x, y, 7+randDirect)
			if (isVacant):
				self.matrix[1][newY][newX] = True
				return
			# ===========================================
			r = randint(0, Setting.viscous)
			randDirect = -2 if (r == 0) else 2 if (r == 1) else 0
			isVacant, newX, newY = self.isVacant(x, y, 7+randDirect)
			if (isVacant):
				self.matrix[1][newY][newX] = True
				return
			# ===========================================
			# default
			self.matrix[1][y][x] = True # Stay there

if __name__ == "__main__":
	matrix = [[[False] * Setting.size for _ in range(Setting.size)] for _ in range(2)]
	particle = Particle(matrix, 45)
	particle.move(0, 0)
	print(matrix)
