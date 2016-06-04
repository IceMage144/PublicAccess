#.n João Gabriel Basi
#.u 9793801

from random import *
from math import *
import matplotlib.pyplot as plt
import numpy as np

#Preenche a lista U com zeros
def zeroList(U, n):
	i = 0
	if len(U) == 0:
		while i < n:
			U.append(0)
			i += 1
	elif len(U) < n:
		while i < len(U):
			U[i] = 0
			i += 1
		while i < n:
			U.append(0)
			i += 1
	else:
		while i < n:
			U[i] = 0
			i += 1


#Preenche a lista U com valores aleatórios
def randomList(U, n):
	i = 0
	if len(U) == 0:
		while i < n:
			U.append(random())
			i += 1
	elif len(U) < n:
		while i < len(U):
			U[i] = random()
			i += 1
		while i < n:
			U.append(random())
			i += 1
	else:
		while i < n:
			U[i] = random()
			i += 1

#Acha o teto do valor máximo de U
def maxVal(U, n):
	i = 0
	maximo = 0
	while i < n:
		if U[i] > maximo:
			maximo = ceil(U[i])
		i += 1
	return maximo

#acha o chão do valor mínimo de U
def minVal(U, n):
	i = 0
	minimo = 0
	while i < n:
		if U[i] < minimo:
			minimo = floor(U[i])
		i += 1
	return minimo

#Transforma uma lista de valores aleatórios entre 0 e 1 em uma com valores entre a e b+1
def transformacaoEscala(U, V, n, a, b):
	i = 0
	zeroList(V, n)
	while i < n:
		V[i] = a+U[i]*(b-a+1)
		i += 1

#Soma dois vetores
def somaVetores(U1, U2, U, n):
	i = 0
	zeroList(U, n)
	while i < n:
		U[i] = U1[i] + U2[i]
		i += 1

#Acha a raiz de todos os números do vetor
def raizVetor(U, n):
	i = 0
	while i < n:
		U[i] = sqrt(U[i])
		i += 1

#Transforma uma distribuição aleatória em 2D em uma distribuição normal
def normalTransform(U1, U2, Z1, Z2, n):
	i = 0
	zeroList(Z1, n)
	zeroList(Z2, n)
	while i < n:
		Z1[i] = cos(2*pi*U2[i])*sqrt(-2*log(U1[i]))
		Z2[i] = sin(2*pi*U2[i])*sqrt(-2*log(U1[i]))
		i += 1

#Retorna a quantidade de valores de U que estão em cada intervalo de tamanho m
def histogram(U, n, H, m):
	maximo = maxVal(U, n)
	minimo = minVal(U, n)
	zeroList(H, m)
	i = 0
	#Acha a diferença de valores entre os intervalos
	x = (maximo-minimo)/m
	while i < n:
		j = 0
		while U[i] > x*(j+1)+minimo:
			j += 1
		H[j] += 1
		i += 1

#Testa as funções acima
def main(n, a, b):
	L = []
	M = []
	E = []
	S = []
	N1 = []
	N2 = []
	H = []
	inter = 20
	randomList(L, n)
	randomList(M, n)
	transformacaoEscala(L, E, n, a, b)
	somaVetores(L, M, S, n)
	normalTransform(L, M, N1, N2, n)

	#Produz o gráfico da transformacaoEscala
	histogram(E, n, H, inter)
	minimo = minVal(E, n)
	maximo = maxVal(E, n)
	step = (maximo-minimo)/inter
	plt.figure(figsize=(6, 6), dpi=80)
	index = np.arange(minimo, maximo, step)
	#define as barras
	rects1 = plt.bar(index, H, step, alpha=0.8, color='g')
	#etiqueta os eixos do gráfco
	plt.xlabel('Intervalos')
	plt.ylabel('Número de pontos')
	plt.title('Histograma da transformacaoEscala')

	plt.tight_layout()
	plt.savefig('hist_escala_translacao.png')

	#Produz o gráfico da somaVetores
	histogram(S, n, H, inter)
	minimo = minVal(S, n)
	maximo = maxVal(S, n)
	step = (maximo-minimo)/inter
	plt.figure(figsize=(6, 6), dpi=80)
	index = np.arange(minimo, maximo, step)
	#define as barras
	rects1 = plt.bar(index, H, step, alpha=0.8, color='g')
	#etiqueta os eixos do gráfco
	plt.xlabel('Intervalos')
	plt.ylabel('Número de pontos')
	plt.title('Histograma da somaVetores')

	plt.tight_layout()
	plt.savefig('hist_soma.png')

	#Produz o gráfico da normalTransform
	histogram(N1, n, H, inter)
	minimo = minVal(N1, n)
	maximo = maxVal(N2, n)
	step = (maximo-minimo)/inter
	plt.figure(figsize=(6, 6), dpi=80)
	index = np.arange(minimo, maximo, step)
	#define as barras
	rects1 = plt.bar(index, H, step, alpha=0.8, color='g')
	#etiqueta os eixos do gráfco
	plt.xlabel('Intervalos')
	plt.ylabel('Número de pontos')
	plt.title('Histograma do Z1 da normalTransform')

	plt.tight_layout()
	plt.savefig('hist_normal_Z1.png')

	histogram(N2, n, H, inter)
	minimo = minVal(N2, n)
	maximo = maxVal(N2, n)
	step = (maximo-minimo)/inter
	plt.figure(figsize=(6, 6), dpi=80)
	index = np.arange(minimo, maximo, step)
	#define as barras
	rects1 = plt.bar(index, H, step, alpha=0.8, color='g')
	#etiqueta os eixos do gráfco
	plt.xlabel('Intervalos')
	plt.ylabel('Número de pontos')
	plt.title('Histograma do Z2 da normalTransform')

	plt.tight_layout()
	plt.savefig('hist_normal_Z2.png')

	#Produz o gráfico da raizVetor
	raizVetor(L, n)
	histogram(L, n, H, inter)
	minimo = minVal(L, n)
	maximo = maxVal(L, n)
	step = (maximo-minimo)/inter
	plt.figure(figsize=(6, 6), dpi=80)
	index = np.arange(minimo, maximo, step)
	#define as barras
	rects1 = plt.bar(index, H, step, alpha=0.8, color='g')
	#etiqueta os eixos do gráfco
	plt.xlabel('Intervalos')
	plt.ylabel('Número de pontos')
	plt.title('Histograma da raizVetor')

	plt.tight_layout()
	plt.savefig('hist_raiz.png')

if __name__ == "__main__":
	n = int(input("Número de testes: "))
	a = float(input("Valor mínimo para a transformacaoEscala: "))
	b = float(input("Valor máximo para a transformacaoEscala: "))
	main(n, a, b)