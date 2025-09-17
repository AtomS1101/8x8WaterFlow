# -*- coding: utf-8 -*-
# v0.0.5

from matrix import Matrix
import time

def main():
	matrix = Matrix()
	# matrix.setArray()
	matrix.show()
	angle = 45

	while (True):
		for _ in range(2):
			print(angle)
			matrix.array[1][0][0] = True
			matrix.refresh(angle)
			matrix.shift()
			matrix.show()
			time.sleep(0.05)
		# angle += 3
		if angle >= 360:
			angle = 0

if __name__ == "__main__":
	main()
