# -*- coding: utf-8 -*-
from setting import Setting

class Particle:
	def __init__(self, matrix, angle):
		self.matrix = matrix
		self.angle = angle

	def checkVacant(self, x, y):
		return (not self.matrix[1][y][x]) and (not self.matrix[0][y][x])

	def provisionalNext(self, x, y, dx, dy):
		newX = x + dx
		newY = y + dy
		newX = 0 if (newX < 0) else (Setting.size - 1) if (newX >= Setting.size) else newX
		newY = 0 if (newY < 0) else (Setting.size - 1) if (newY >= Setting.size) else newY
		return newX, newY

	def move(self, x, y):
		directionX = [0, 1, 1, 1, 1,  1,  1,  0,  0, -1, -1, -1, -1, -1, -1, 0]
		directionY = [1, 1, 1, 0, 0, -1, -1, -1, -1, -1, -1,  0,  0,  1,  1, 1]
		step = [int(22.5 * n) for n in range(17)]
		for i in range(len(step) - 1):
			if (self.angle >= step[i] and self.angle < step[i + 1]):
				newX, newY = self.provisionalNext(x, y, directionX[i], directionY[i])
				if (self.checkVacant(newX, newY)): # Simply move if it's vacnt
					self.matrix[1][newY][newX] = True
				elif (i%2 == 0): # Start is multiple of 45
					newX, newY = self.provisionalNext(x, y, directionX[i+1], directionY[i+1])
					if (self.checkVacant(newX, newY)):
						self.matrix[1][newY][newX] = True
					else:
						self.matrix[1][y][x] = True # Stay there
				elif ((i+1)%2 == 0): # End is multiple of 45
					newX, newY = self.provisionalNext(x, y, directionX[i-1], directionY[i-1])
					if (self.checkVacant(newX, newY)):
						self.matrix[1][newY][newX] = True
					else:
						self.matrix[1][y][x] = True # Stay there
				else: # No valid direction
					self.matrix[1][y][x] = True # Stay there
				break

if __name__ == "__main__":
	matrix = [[[False] * Setting.size for _ in range(Setting.size)] for _ in range(2)]
	particle = Particle(matrix, 45)
	particle.move(0, 0)
	print(matrix)
