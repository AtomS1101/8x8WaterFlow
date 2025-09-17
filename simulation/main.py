# -*- coding: utf-8 -*-

from matrix import Matrix
from setting import Setting
from refresh import Refresh
import time

def main():
	matrix = Matrix()
	matrix.set_array(Setting.num_particles)
	angle = 0

	for n in range(360):
		print(angle)
		Refresh(matrix, angle)
		matrix.show()
		angle += 2
		time.sleep(0.05)

if __name__ == "__main__":
	main()
