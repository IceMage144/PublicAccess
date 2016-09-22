from random import *
from math import *
import matplotlib.pyplot as plt
import numpy as np

def main():
	count = 1
	ma = 0
	plt.figure(figsize=(6, 6), dpi=80)
	f = open("listaCollatz.txt", mode="r")
	for linha in f:
		i = 0
		collatz = ""
		while linha[i] != '\n':
			collatz += linha[i]
			i += 1
		collatz = int(collatz)
		if count-1 > 0:
			ma = (ma*(count-1)+collatz)/count
		plt.plot(count, collatz, 'go')
		plt.plot(count, log(count), 'ro')
		plt.plot(count, sqrt(count), 'bo')
		plt.plot(count, ma, 'yo')
		count += 1
		if (count == 2500):
			print("25%")
		elif (count == 5000):
			print("50%")
		elif (count == 7500):
			print("75%")
		elif (count == 10000):
			print("99%")
	count = 1
	while (2**count < 10000):
		plt.plot([2**count,2**count], [0, 300], 'k-')
		count += 1
	print("100%")
	plt.tight_layout()
	plt.show()

if __name__ == '__main__':
	main()