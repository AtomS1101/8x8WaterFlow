# -*- coding: utf-8 -*-

from move import Move
from setting import Setting

def Refresh(matrix, angle):
	x, y = 0, 0
	cell = Move(matrix, angle)
	for y in range(Setting.size_y):
		for x in range(Setting.size_x):
			if (matrix.array[y][x]):
				cell.move(x, y)
