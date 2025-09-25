# -*- coding: utf-8 -*-
#test


from matrix import Matrix
import time
from random import randint

def main():
	matrix = Matrix()
	matrix.setArray()
	matrix.show()
	angle = 45

	while (True):
		for _ in range(2):
			print(angle)
			# if randint(0, 10) == 1:
			# 	matrix.array[1][0][0] = True
			matrix.refresh(angle)
			matrix.shift()
			matrix.show()
			time.sleep(0.05)
			# time.sleep(0.07)
		angle += 2
		if angle >= 360:
			angle = 0

if __name__ == "__main__":
	main()
