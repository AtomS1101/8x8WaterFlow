# -*- coding: utf-8 -*-
from setting import Setting
import math

class Move:
	def __init__(self, matrix, angle):
		self.matrix = matrix
		self.angle = angle

	def get_direction(self, x, y):
		angle_deg = math.radians(self.angle)
		dx = math.sin(angle_deg)
		dy = math.cos(angle_deg)
		direction = [round(dx), round(dy)]
		next = [x + direction[0], y + direction[1]]
		is_over_x = next[0] < 0 or next[0] >= Setting.size_x
		is_over_y = next[1] < 0 or next[1] >= Setting.size_y
		if is_over_x:
			direction[0] = 0
		if is_over_y:
			direction[1] = 0
		if self.matrix.array[y + direction[1]][x + direction[0]]:
			direction = [0, 0]
		return direction

	def move(self, x, y):
		direction = self.get_direction(x, y)
		self.matrix.degital_write(x, y, False)
		self.matrix.degital_write(x + direction[0], y + direction[1], True)
