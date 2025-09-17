# -*- coding: utf-8 -*-

from matrix import Matrix
from setting import Setting
from move import Move
import time

def main():
	matrix = Matrix()
	matrix.set_array(Setting.num_particles)
	cell = Move(matrix)
	angle = 0

	for n in range(360):
		for _ in range(4):
			print(angle)
			cell.move(angle)
			matrix.shift()
			matrix.show()
			time.sleep(0.02)
		angle += 2

if __name__ == "__main__":
	main()
