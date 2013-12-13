#!/usr/bin/python

import sys
import subprocess
import os
import shutil

bits = [32, 64, 128]
trials = [100, 1000, 10000]
modulus = [2**32, 2**64, 2**128]

lines = []
for b in bits:
	for t in trials:
		# mod mult
		p = subprocess.Popen('./mod_test 0 ' + str(b) + ' ' + str(t), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
		for l in p.stdout.readlines():
			l = l.strip()
			lines.append("mod_mult_prime," + str(b) + "," + l) 
		for m in modulus:
			p = subprocess.Popen('./mod_test 0 ' + str(b) + ' ' + str(m) + ' ' + str(t), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
			for l in p.stdout.readlines():
				l = l.strip()
				lines.append("mod_mult_2power," + str(m) + "," + l) 

		# mod add
		p = subprocess.Popen('./mod_test 1 ' + str(b) + ' ' + str(t), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
		for l in p.stdout.readlines():
			l = l.strip()
			lines.append("mod_add_prime," + str(b) + "," + l) 
		for m in modulus:
			p = subprocess.Popen('./mod_test 1 ' + str(b) + ' ' + str(m) + ' ' + str(t), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
			for l in p.stdout.readlines():
				l = l.strip()
				lines.append("mod_add_2power," + str(m) + "," + l) 

for t in trials:
	# SHA1
	p = subprocess.Popen('./sha_test ' + str(t), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	for l in p.stdout.readlines():
		l = l.strip()
		lines.append("sha_160," + str(b) + "," + l) 
for l in lines:
	print(l)
