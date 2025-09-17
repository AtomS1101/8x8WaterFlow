# -*- coding: utf-8 -*-

from matrix import Matrix
import time

def main():
	matrix = Matrix()
	matrix.setArray()
	matrix.show()
	angle = 0

	while (True):
		for _ in range(4):
			print(angle)
			# matrix.array[1][0][0] = True
			matrix.refresh(angle)
			matrix.shift()
			matrix.show()
			time.sleep(0.02)
		angle += 11
		if angle >= 360:
			angle = 0

if __name__ == "__main__":
	main()
