# -*- coding: utf-8 -*-
from setting import Setting
from direction import Direction
import math

class Move:
	def __init__(self, matrix):
		self.matrix = matrix
		self._angle = 0

	def get_direction(self, x, y):
		angle_deg = math.radians(self._angle)
		dx = round(math.sin(angle_deg))
		dy = round(math.cos(angle_deg))
		x_next = x + dx
		y_next = y + dy
		is_over_x = x_next < 0 or x_next >= Setting.size_x
		is_over_y = y_next < 0 or y_next >= Setting.size_y
		if is_over_x:
			dx = 0
		if is_over_y:
			dy = 0
		for buffer in range(2):
			if self.matrix.array[buffer][y + dy][x + dx]:
				dx, dy = Direction(dx, dy, self.matrix)
		return dx, dy

	def move(self, angle):
		x, y = 0, 0
		self._angle = angle
		for y in range(Setting.size_y):
			for x in range(Setting.size_x):
				if (self.matrix.array[0][y][x]):
					dx, dy = self.get_direction(x, y)
					self.matrix.degital_write(x + dx, y + dy, True)
