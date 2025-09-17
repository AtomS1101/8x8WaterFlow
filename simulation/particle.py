# -*- coding: utf-8 -*-
import random

class Particle:
	def __init__(self):
		self.x = random.randint(0, 255)
		self.y = random.randint(0, 255)
		self.vx = 0
		self.vy = 0

	def move(self, ax, ay):
		adjust_a = 0.1
		bounce = -0.5
		self.x += self.vx
		self.y += self.vy
		self.vx += ax * adjust_a
		self.vy += ay * adjust_a

		if self.x < 0:
			self.x = 0
			self.vx *= bounce
		elif self.x > 255:
			self.x = 255
			self.vx *= bounce
		if self.y < 0:
			self.y = 0
			self.vy *= bounce
		elif self.y > 255:
			self.y = 255
			self.vy *= bounce
