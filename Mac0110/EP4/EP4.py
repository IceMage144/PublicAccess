#.n João Gabriel Basi
#.u 9793801

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
from matplotlib.collections import PatchCollection

hist = []
def leEntrada(nome):
    grade = 0
    vivas = []
    #abre o arquivo e analisa
    f = open(nome, mode="r")
    for linha in f:
        if linha == "H\n":
            grade = 1
        elif linha != "Q\n":
            coord = linha.split(",")
            vivas.append((int(coord[0]),int(coord[1].rstrip())))
    return grade, vivas

def simulaQuadGenerica(n, m, lista, t, b, s):
    res = []
    tela = np.array([[0 for j in range(m)] for i in range(n)])
    for i in lista:
        tela[i[0]][i[1]] = 1
    prox = tela.copy()
    hist.append(tela.copy())
    #ajusta o tipo das variaveis b e s
    if type(b) != list:
        b = [b]
    if type(s) != list:
        s = [s]
    #faz as iteracoes
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
        hist.append(prox.copy())
    #volta a matriz para uma lista com as coordenadas das celulas vivas
    for i in range(n):
        for j in range(m):
            if prox[i][j] == 1:
                res.append([i, j])
    return res

def simulaHexGenerica(n, m, lista, t, b, s):
    if m%2 != 0:
        m += 1
    res = []
    tela = np.array([[0 for j in range(m)] for i in range(n)])
    for i in lista:
        tela[i[0]][i[1]] = 1
    prox = tela.copy()
    #ajusta o tipo das variaveis b e s
    if type(b) != list:
        b = [b]
    if type(s) != list:
        s = [s]
    #faz as iteracoes
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
    #volta a matriz para uma lista com as coordenadas das celulas vivas
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
    patches = []
    tela = [[1,1,1] for i in range(m*n)]
    for i in lista:
        tela[i[0]+i[1]*n] = [0,0,0.5]

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

    #calculando as coordenadas dos hexagonos (com alguns ajustes)
    x = np.array([(3*i/2+1)*l+2 for i in range(m)])
    y1 = np.array([(i+1)*h+2 for i in range(n)])
    y2 = y1 - (h-0.5)/2
    c = []

    for i in range(m):
        if (i+1)%2 != 0:
            for y in y1:
                polygon = mpatches.RegularPolygon((x[i],y), 6, l, np.pi/6, lw = 1.0, facecolor=tela[i*n+y1.searchsorted(y)])
                patches.append(polygon)
        else:
            for y in y2:
                polygon = mpatches.RegularPolygon((x[i],y), 6, l, np.pi/6, lw = 1.0, facecolor=tela[i*n+y2.searchsorted(y)])
                patches.append(polygon)

    #criando a figura
    fig = plt.figure(figsize=(5, 5), dpi=100)
    ax = fig.add_subplot(111)

    #plotando os hexagonos
    collection = PatchCollection(patches, match_original=True)
    ax.add_collection(collection)
    ax.set_xlim(xmin=0, xmax=100)
    ax.set_ylim(ymin=0, ymax=100)
    ax.axis('off')
    plt.savefig(figura)

def haRepeticoes(n, m, lista, t):
    a = 0
    temsim = False
    while a < t and temsim == False:
        b = a+1
        while b < t+1 and temsim == False:
            idenlvl = 0
            for i in range(n):
                for j in range(m):
                    if hist[a][i][j] == hist[b][i][j]:
                        idenlvl += 1
            if idenlvl == m*n:
                temsim = True
            b += 1
        a += 1
    return temsim