# -*- coding: utf-8 -*-

import time
import math
from particle import Particle
from matrix import Matrix
from setting import Setting

def main():
	particles = [Particle() for _ in range(Setting.num_particles)]

	t = 0
	for n in range(720):
		radian = math.radians(t)
		ax, ay = math.cos(radian), math.sin(radian)
		for p in particles:
			p.move(ax, ay)
		matrix = Matrix()
		print(t, ax, ay)
		matrix.show(particles)
		t += 1
		time.sleep(0.05)

if __name__ == "__main__":
	main()
