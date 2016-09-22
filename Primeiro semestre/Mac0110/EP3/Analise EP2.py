#.n João Gabriel Basi
#.u 9793801

from random import *
from math import *
import matplotlib.pyplot as plt
import numpy as np

#Determina os pontos médios das cordas a partir de seus extremos
def determinaPontosMedios(listaExtremos):
	n = len(listaExtremos)
	i = 0
	T = []
	while i < n:
		xm = (listaExtremos[i][0][0] + listaExtremos[i][1][0])/2
		ym = (listaExtremos[i][0][1] + listaExtremos[i][1][1])/2
		T.append((xm, ym))
		i +=1
	return T

#Determina os pontos extremos das cordas a partir de seus pontos médios
def determinaPontosExtremos(r, listaPontosMedios):
    n = len(listaPontosMedios)
    i = 0
    T = []
    while i < n:
        OM = sqrt(listaPontosMedios[i][0]**2+listaPontosMedios[i][1]**2)
        #Acha as cordenadas dos extremos como se o ângulo entre OM e o eixo x fosse zero
        Ao = (OM, sqrt(r**2-OM**2))
        Bo = (OM, -sqrt(r**2-OM**2))
        #Acha o cosseno e o seno do ângulo entre OM e o eixo x
        C = listaPontosMedios[i][0]/OM
        S = listaPontosMedios[i][1]/OM
        #Rotaciona as cordenadas achadas multiplicando-as por uma matriz de rotação e as coloca em tuplas
        A = (Ao[0]*C-Ao[1]*S, Ao[0]*S+Ao[1]*C)
        B = (Bo[0]*C-Bo[1]*S, Bo[0]*S+Bo[1]*C)
        T.append((A, B))
        i += 1
    return T

#Acha uma lista de cordas para o método 1
def listaCordasM1(r, n):
	i = 0
	T = []
	while i < n:
		angA = 2*pi*random()
		angB = 2*pi*random()
		A = (r*cos(angA), r*sin(angA))
		B = (r*cos(angB), r*sin(angB))
		T.append((A, B))
		i += 1
	return T

#Acha uma lista de cordas para o método 2
def listaCordasM2(r, n):
	i = 0
	T = []
	while i < n:
		C = 2*pi*random()
		OM = r*random()
		#Acha as cordenadas dos extremos como se o ângulo de C fosse zero
		Ao = (OM, sqrt(r**2-OM**2))
		Bo = (OM, -sqrt(r**2-OM**2))
		#Rotaciona, pelo ângulo de C, as cordenadas achadas multiplicando-as por uma matriz
		#de rotação e as coloca em tuplas
		A = (Ao[0]*cos(C)-Ao[1]*sin(C), Ao[0]*sin(C)+Ao[1]*cos(C))
		B = (Bo[0]*cos(C)-Bo[1]*sin(C), Bo[0]*sin(C)+Bo[1]*cos(C))
		T.append((A, B))
		i += 1
	return T

#acha uma lista de cordas para o método 3
def listaCordasM3(r, n):
    i = 0
    T = []
    while i < n:
        #gera um ponto aleatório em um quadrado de 2*r de lado e localizado entre -r e r
        Mx = r*(random()*2-1)
        My = r*(random()*2-1)
        #verifica se o ponto está dentro do círculo. Se não, gera outro ponto
        while My**2 + Mx**2 > r**2:
            Mx = r*(random()*2-1)
            My = r*(random()*2-1)
        T.append((Mx, My))
        i += 1
    return determinaPontosExtremos(r, T)

#Separa os pontos da borda em 8 categorias e imprime os pontos e o histograma da frequência de cada categoria
def distribuicaoBorda(r, listaCordas):
	n = len(listaCordas)
	i = 0
	H = [[],[],[],[],[],[],[],[]]
	Col = ['g', 'r', 'y', 'b', 'k', 'm', 'w', 'c']
	Sff = sin(pi/4)
	while i < n:
		j = 0
		while j < 2:
			if listaCordas[i][j][0] < r and listaCordas[i][j][0] >= r*Sff and listaCordas[i][j][1] <= r*Sff and listaCordas[i][j][1] > 0:
				H[0].append(listaCordas[i][j])
			elif listaCordas[i][j][0] < r*Sff and listaCordas[i][j][0] >= 0 and listaCordas[i][j][1] <= r and listaCordas[i][j][1] > r*Sff:
				H[1].append(listaCordas[i][j])
			elif listaCordas[i][j][0] < 0 and listaCordas[i][j][0] >= -r*Sff and listaCordas[i][j][1] < r and listaCordas[i][j][1] >= r*Sff:
				H[2].append(listaCordas[i][j])
			elif listaCordas[i][j][0] < -r*Sff and listaCordas[i][j][0] >= -r and listaCordas[i][j][1] < r*Sff and listaCordas[i][j][1] >= 0:
				H[3].append(listaCordas[i][j])
			elif listaCordas[i][j][0] <= -r*Sff and listaCordas[i][j][0] > -r and listaCordas[i][j][1] < 0 and listaCordas[i][j][1] >= -r*Sff:
				H[4].append(listaCordas[i][j])
			elif listaCordas[i][j][0] <= 0 and listaCordas[i][j][0] > -r*Sff and listaCordas[i][j][1] < -r*Sff and listaCordas[i][j][1] >= -r:
				H[5].append(listaCordas[i][j])
			elif listaCordas[i][j][0] <= r*Sff and listaCordas[i][j][0] > 0 and listaCordas[i][j][1] <= -r*Sff and listaCordas[i][j][1] > -r:
				H[6].append(listaCordas[i][j])
			elif listaCordas[i][j][0] <= r and listaCordas[i][j][0] > r*Sff and listaCordas[i][j][1] <= 0 and listaCordas[i][j][1] > -r*Sff:
				H[7].append(listaCordas[i][j])
			j += 1
		i += 1
	# especifica o tamanho da imagem e a resolucao
	plt.figure(figsize=(12, 6), dpi=80)
	# trabalhando no primeiro gráfico (lado esquerdo da figura)
	plt.subplot(121)
	# desenhando um círculo de raio r
	thetas=np.arange(0,2*np.pi,0.01)
	plt.plot(r*np.cos(thetas), r*np.sin(thetas), 'b-')
	# adicionando os pontos extremos dentro do círculo
	i = 0
	while i < 8:
		n = len(H[i])
		j = 0
		while j < n:
			plt.plot(H[i][j][0], H[i][j][1], Col[i]+'o')
			j += 1
		i += 1

	#Especifica os intervalos dos eixos com [xmin, xmax, ymin, ymax]
	plt.axis([-4/3*r, 4/3*r, -4/3*r, 4/3*r])
	plt.title('Pontos categorizados')
	# trabalhando no segundo grafico (lado direito da figura)
	plt.subplot(122)
	grupos = (len(H[0]), len(H[1]), len(H[2]), len(H[3]), len(H[4]), len(H[5]), len(H[6]), len(H[7]))
	index = np.arange(8)
	#define o tamanho das barras
	rects1 = plt.bar(index, grupos, 0.7, alpha=0.8, color=Col)

	plt.xlabel('Cor')
	plt.ylabel('Número de pontos')
	plt.title('Histograma por cor')
	plt.xticks(index+0.35, ('Green', 'Red', 'Yellow', 'Blue', 'Black', 'Magenta', 'White', 'Cyan'))

	plt.tight_layout()
	plt.savefig('distribuicao_borda.png')

#Separa os pontos médios em 8 categorias de acordo com sua distância do centro e imprime os pontos e o histograma da frequência de cada categoria
def distribuicaoRadial(r, listaCordas):
	T = determinaPontosMedios(listaCordas)
	n = len(T)
	i = 0
	H = [[],[],[],[],[],[],[],[]]
	Col = ['g', 'r', 'y', 'b', 'k', 'm', 'w', 'c']
	rf = r/8
	while i < n:
		#Distância do centro até o ponto médios
		OM = sqrt(T[i][0]**2+T[i][1]**2)
		if OM < rf:
			H[0].append(T[i])
		elif OM >= rf and OM < 2*rf:
			H[1].append(T[i])
		elif OM >= 2*rf and OM < 3*rf:
			H[2].append(T[i])
		elif OM >= 3*rf and OM < 4*rf:
			H[3].append(T[i])
		elif OM >= 4*rf and OM < 5*rf:
			H[4].append(T[i])
		elif OM >= 5*rf and OM < 6*rf:
			H[5].append(T[i])
		elif OM >= 6*rf and OM < 7*rf:
			H[6].append(T[i])
		else:
			H[7].append(T[i])
		i += 1
	# especifica o tamanho da imagem e a resolucao
	plt.figure(figsize=(12, 6), dpi=80)
	# trabalhando no primeiro gráfico (lado esquerdo da figura)
	plt.subplot(121)
	# desenhando um círculo de raio r
	thetas=np.arange(0,2*np.pi,0.01)
	plt.plot(r*np.cos(thetas), r*np.sin(thetas), 'b-')
	# adicionando os pontos médios dentro do círculo
	i = 0
	while i < 8:
		n = len(H[i])
		j = 0
		while j < n:
			plt.plot(H[i][j][0], H[i][j][1], Col[i]+'o')
			j += 1
		i += 1

	#Especifica os intervalos dos eixos com [xmin, xmax, ymin, ymax]
	plt.axis([-4/3*r, 4/3*r, -4/3*r, 4/3*r])
	plt.title('Pontos categorizados')
	# trabalhando no segundo grafico (lado direito da figura)
	plt.subplot(122)
	grupos = (len(H[0]), len(H[1]), len(H[2]), len(H[3]), len(H[4]), len(H[5]), len(H[6]), len(H[7]))
	index = np.arange(8)
	#define o tamanho das barras
	plt.bar(index, grupos, 0.7, alpha=0.8, color=Col)

	plt.xlabel('Cor')
	plt.ylabel('Número de pontos')
	plt.title('Histograma por cor')
	plt.xticks(index+0.35, ('Green', 'Red', 'Yellow', 'Blue', 'Black', 'Magenta', 'White', 'Cyan'))

	plt.tight_layout()
	plt.savefig('distribuicaoRadial.png')

#Separa os pontos médios em 8 categorias de acordo com a área do círculo e imprime os pontos e o histograma da frequência de cada categoria
def distribuicaoArea(r, listaCordas):
	T = determinaPontosMedios(listaCordas)
	n = len(T)
	i = 0
	H = [[],[],[],[],[],[],[],[]]
	Col = ['g', 'r', 'y', 'b', 'k', 'm', 'w', 'c']
	#Alturas que dividem o círculo em partes iguais
	h1 = 0.634705*r
	h2 = 0.403973*r
	h3 = 0.197646*r
	while i < n:
		if T[i][1] > h1:
			H[0].append(T[i])
		elif T[i][1] > h2:
			H[1].append(T[i])
		elif T[i][1] > h3:
			H[2].append(T[i])
		elif T[i][1] > 0:
			H[3].append(T[i])
		elif T[i][1] > -h3:
			H[4].append(T[i])
		elif T[i][1] > -h2:
			H[5].append(T[i])
		elif T[i][1] > -h1:
			H[6].append(T[i])
		else:
			H[7].append(T[i])
		i += 1
	# especifica o tamanho da imagem e a resolucao
	plt.figure(figsize=(12, 6), dpi=80)
	# trabalhando no primeiro gráfico (lado esquerdo da figura)
	plt.subplot(121)
	# desenhando um círculo de raio r
	thetas=np.arange(0,2*np.pi,0.01)
	plt.plot(r*np.cos(thetas), r*np.sin(thetas), 'b-')
	# adicionando os pontos médios dentro do círculo
	i = 0
	while i < 8:
		n = len(H[i])
		j = 0
		while j < n:
			plt.plot(H[i][j][0], H[i][j][1], Col[i]+'o')
			j += 1
		i += 1

	#Especifica os intervalos dos eixos com [xmin, xmax, ymin, ymax]
	plt.axis([-4/3*r, 4/3*r, -4/3*r, 4/3*r])
	plt.title('Pontos categorizados')
	# trabalhando no segundo grafico (lado direito da figura)
	plt.subplot(122)
	grupos = (len(H[0]), len(H[1]), len(H[2]), len(H[3]), len(H[4]), len(H[5]), len(H[6]), len(H[7]))
	index = np.arange(8)
	#define o tamanho das barras
	plt.bar(index, grupos, 0.7, alpha=0.8, color=Col)

	plt.xlabel('Cor')
	plt.ylabel('Número de pontos')
	plt.title('Histograma por cor')
	plt.xticks(index+0.35, ('Green', 'Red', 'Yellow', 'Blue', 'Black', 'Magenta', 'White', 'Cyan'))

	plt.tight_layout()
	plt.savefig('distribuicao_area.png')

#Imprime as cordas
def distribuicaoCordas(r, listaCordas):
	T = listaCordas
	n = len(T)
	i = 0
	# especifica o tamanho da imagem e a resolucao
	plt.figure(figsize=(6.25, 6), dpi=80)
	# desenhando um círculo de raio r = 10
	thetas=np.arange(0,2*np.pi,0.01)
	plt.plot(r*np.cos(thetas), r*np.sin(thetas), 'b-')
	while i < n:
		plt.plot([T[i][0][0], T[i][1][0]], [T[i][0][1], T[i][1][1]], 'g-')
		i += 1
	plt.axis([-4/3*r, 4/3*r, -4/3*r, 4/3*r])
	plt.title('Pontos categorizados')

	plt.tight_layout()
	plt.savefig('distribuicao_cordas.png')


def main():
	n = int(input("Número de testes: "))
	r = float(input("Raio do círculo: "))

	#método 1
	L = listaCordasM1(r, n)
	print('Bordas M1:')
	distribuicaoBorda(r, L)
	print('OK')
	print('Radial M1:')
	distribuicaoRadial(r, L)
	print('OK')
	print('Area M1:')
	distribuicaoArea(r, L)
	print('OK')
	print('Cordas M1:')
	distribuicaoCordas(r, L)
	print('OK')

	#método 2
	M = listaCordasM2(r, n)
	print('Bordas M2:')
	distribuicaoBorda(r, M)
	print('OK')
	print('Radial M2:')
	distribuicaoRadial(r, M)
	print('OK')
	print('Area M2:')
	distribuicaoArea(r, M)
	print('OK')
	print('Cordas M2:')
	distribuicaoCordas(r, M)
	print('OK')

	#método 3
	N = listaCordasM3(r, n)
	print('Bordas M3:')
	distribuicaoBorda(r, N)
	print('OK')
	print('Radial M3:')
	distribuicaoRadial(r, N)
	print('OK')
	print('Area M3:')
	distribuicaoArea(r, N)
	print('OK')
	print('Cordas M3:')
	distribuicaoCordas(r, N)
	print('OK')

if __name__ == "__main__":
	main()
