# -*- coding: utf-8 -*-
# v0.0.6

from setting import Setting
from random import randint

class Particle:
	def __init__(self, matrix, angle):
		self.matrix = matrix
		self.angle = angle

	def checkVacant(self, x, y, index):
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
		for i in range(len(step) - 1):
			if (self.angle >= step[i] and self.angle < step[i + 1]):
				flag = True
				isVacant, newX, newY = self.checkVacant(x, y, i)
				if (isVacant): # Simply move if it's vacnt
					self.matrix[1][newY][newX] = True
				else:
					rand = randint(0, 1)
					randDirect1 = -1 if (rand == 0) else 1
					randDirect2 = 1 if (rand == 0) else -1
					isVacant1, newX1, newY1 = self.checkVacant(x, y, i+randDirect1)
					isVacant2, newX2, newY2 = self.checkVacant(x, y, i+randDirect2)
					if (isVacant1):
						self.matrix[1][newY1][newX1] = True
					elif (isVacant2):
						self.matrix[1][newY2][newX2] = True
					else:
						self.matrix[1][y][x] = True # Stay there
				break

		if (not flag):
			isVacant, newX, newY = self.checkVacant(x, y, 7)
			if (isVacant): # Simply move if it's vacnt
				self.matrix[1][newY][newX] = True
			else:
				rand = randint(0, 1)
				randDirect1 = -1 if (rand == 0) else 1
				randDirect2 = 1 if (rand == 0) else -1
				isVacant1, newX1, newY1 = self.checkVacant(x, y, 7+randDirect1)
				isVacant2, newX2, newY2 = self.checkVacant(x, y, 7+randDirect2)
				if (isVacant1):
					self.matrix[1][newY1][newX1] = True
				elif (isVacant2):
					self.matrix[1][newY2][newX2] = True
				else:
					self.matrix[1][y][x] = True # Stay there

if __name__ == "__main__":
	matrix = [[[False] * Setting.size for _ in range(Setting.size)] for _ in range(2)]
	particle = Particle(matrix, 45)
	particle.move(0, 0)
	print(matrix)
