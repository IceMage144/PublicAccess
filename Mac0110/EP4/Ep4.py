import matplotlib.pyplot as plt
from matplotlib.collections import RegularPolyCollection
import numpy as np

def leEntrada(nome):
    grade = 0
    vivas = []
    f = open(nome, mode="r")
    for linha in f:
        if linha == "H\n":
            grade = 1
        elif linha != "Q\n":
            vivas.append((int(linha[0]),int(linha[2])))
    return grade, vivas

def simulaQuadGenerica(n, m, lista, t, b, s):
    res = []
    tela = np.array([[0 for j in range(m)] for i in range(n)])
    for i in lista:
        tela[i[1]][i[0]] = 1
    prox = tela.copy()
    if type(b) != list:
        b = [b]
    if type(s) != list:
        s = [s]
    for k in range(t):
        tela = prox.copy()
        for i in range(n):
            for j in range(m):
                viz = 0
                for z in range(-1, 2):
                    if tela[(i+z)%n][(j+1)%m] == 1:
                        viz += 1
                    if tela[(i+z)%n][(j-1)%m] == 1:
                        viz += 1
                if tela[(i+1)%n][j] == 1:
                    viz += 1
                if tela[(i-1)%n][j] == 1:
                    viz += 1
                if tela[i][j] == 1:
                    if s.count(viz) == 0:
                        prox[i][j] = 0
                elif tela[i][j] == 0:
                    if b.count(viz) == 1:
                        prox[i][j] = 1
    for i in range(n):
        for j in range(m):
            if prox[i][j] == 1:
                res.append([i, j])
    return res

#######CONFIGURAR AS LINHAS IMPARES#############
def simulaHexGenerica(n, m, lista, t, b, s):
    res = []
    tela = np.array([[0 for j in range(m)] for i in range(n)])
    for i in lista:
        tela[i[1]][i[0]] = 1
    prox = tela.copy()
    if type(b) != list:
        b = [b]
    if type(s) != list:
        s = [s]
    for k in range(t):
        tela = prox.copy()
        for i in range(n):
            for j in range(m):
                viz = 0
                if tela[i][(j-1)%m] == 1:
                    viz += 1
                if tela[(i-1)%n][j] == 1:
                    viz += 1
                if tela[i][(j+1)%m] == 1:
                    viz += 1
                if tela[(i+1)%n][j] == 1:
                    viz += 1
                if j%2 != 0:
                    if tela[(i-1)%n][(j-1)%m] == 1:
                        viz += 1
                    if tela[(i-1)%n][(j+1)%m] == 1:
                        viz += 1
                else:
                    if tela[(i+1)%n][(j+1)%m] == 1:
                        viz += 1
                    if tela[(i+1)%n][(j-1)%m] == 1:
                        viz += 1
                if tela[i][j] == 1:
                    if s.count(viz) == 0:
                        prox[i][j] = 0
                elif tela[i][j] == 0:
                    if b.count(viz) == 1:
                        prox[i][j] = 1
    for i in range(n):
        for j in range(m):
            if prox[i][j] == 1:
                res.append([i, j])
    return res

def simulaQuad(n, m, lista, t):
    return simulaQuadGenerica(n, m, lista, t, 3, [2,3])

def simulaHex(n, m, lista, t):
    return simulaHexGenerica(n, m, lista, t, [3, 5], 2)

def desenhaQuad(n, m, lista, figura):
    tela = [[0 for j in range(m)] for i in range(n)]
    for i in lista:
        tela[i[0]][i[1]] = 1
    tela = np.array(tela)
    plt.figure(figsize=(5, 5), dpi=100)
    c = plt.pcolor(tela, edgecolors='k', linewidths=1, cmap="Blues")
    plt.xlim(xmin=-0.1, xmax=max(m, n)+0.1)
    plt.ylim(ymin=-0.1, ymax=max(m, n)+0.1)
    plt.axis('off')
    plt.savefig(figura)

def desenhaHex(n, m, lista, figura):
    tela = ["w" for i in range(m*n)]
    for i in lista:
        tela[i[0]+i[1]*n] = (0, 0, 0.5, 1)

    #calcula a altura e o lado dos hexagonos
    if m >= 2:
       ratio = ((2*n+1)*np.sqrt(3))/(3*m+1)
    else:
       ratio = (2*n*np.sqrt(3))/(3*m+1)
    if ratio > 1:
       h = 190/(2*n+1)
       l = h*np.sqrt(3)/3
    else:
       l = 190/(3*m+1)
       h = l*np.sqrt(3)

    #area do hexagono em pontos^2
    area = 3*np.sqrt(3)*(l*3.1)**2/2 #area = 3*np.sqrt(3)*(l*3.1)**2/6

    #calculando as coordenadas dos hexagonos (com alguns ajustes)
    x = np.array([(3*i/2+1)*l+2 for i in range(m)])
    y1 = np.array([(95*i/100+1)*h+2 for i in range(n)])
    y2 = y1 - (h-0.5)/2
    c = []

    for i in range(m):
        if (i+1)%2 != 0:
            c += [[x[i],y] for y in y1]
        else:
            c += [[x[i],y] for y in y2]
    c = np.array(c)

    #caso específico
    if m == 1 and n == 1:
       c = [50, 50]
       area = 56000

    #criando a figura
    fig = plt.figure(figsize=(5, 5), dpi=100)
    ax = fig.add_subplot(111)

    #plotando os hexagonos
    coll = RegularPolyCollection(
        numsides=6,
        sizes=(area,),
        rotation = np.pi/6,
        edgecolors = (0, 0, 0, 1),
        facecolors = tela,
        offsets = c,
        transOffset = ax.transData
    )
    ax.add_collection(coll)
    ax.set_xlim(xmin=0, xmax=100)
    ax.set_ylim(ymin=0, ymax=100)
    ax.axis('off')
    plt.savefig(figura)

def haRepeticoes(n, m, lista, t):
    a = 0
    temsim = False
    tela = np.array([[0 for j in range(m)] for i in range(n)])
    for i in lista:
        tela[i[1]][i[0]] = 1
    hist = [tela]
    prox = tela.copy()
    for k in range(t):
        tela = prox.copy()
        for i in range(n):
            for j in range(m):
                viz = 0
                for z in range(-1, 2):
                    if tela[(i+z)%n][(j+1)%m] == 1:
                        viz += 1
                    if tela[(i+z)%n][(j-1)%m] == 1:
                        viz += 1
                if tela[(i+1)%n][j] == 1:
                    viz += 1
                if tela[(i-1)%n][j] == 1:
                    viz += 1
                if tela[i][j] == 1:
                    if [2,3].count(viz) == 0:
                        prox[i][j] = 0
                elif tela[i][j] == 0:
                    if viz == 3:
                        prox[i][j] = 1
        hist.append(prox)
    while a < t-1 and temsim == False:
        b = a+1
        while b < t and temsim == False:
            idenlvl = 0
            for i in range(n):
                for j in range(m):
                    if hist[a][i][j] == hist[b][i][j]:
                        idemlvl += 1
            if idemlvl == m*n:
                temsim = True
    return temsim


if __name__ == "__main__":
    #nome = input("Digite o nome do arquivo a ser lido: ")
    grade, vivas = leEntrada("teste.txt")
    #n = int(input("n: "))
    #m = int(input("m: "))
    #t = int(input("t: "))
    #figura = input("Digite o nome da figura a ser salva: ")
    if grade == 0:
        res = simulaQuad(10, 9, vivas, 4)
        desenhaQuad(10, 9, res, "magicq4.png")
        haRepeticoes(10, 9, vivas, 4)
    else:
        res = simulaHex(9, 10, vivas, 2)
        desenhaHex(9, 10, res, "magich2.png")