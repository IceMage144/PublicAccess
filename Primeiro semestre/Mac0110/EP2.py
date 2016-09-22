#.n João Gabriel Basi
#.u 9793801

from random import *
from math import *
def metodo1(r,n):
    cont = 0
    i = n
    #l é o lado do triângulo
    l = r*sqrt(3)
    while i > 0:
        #não é preciso achar um valor para A já que ao rotacionar o triângulo
        #o ponto A acaba se tornando o ângulo zero e deixa de ser aleatório
        #pois ele estará sempre no mesmo lugar em relação ao triângulo
        B = 2*pi*random()
        #Acha a corda por meio da base do triângulo ABO
        AB = 2*sin(B/2)*r
        if AB > l :
            cont += 1
        i -= 1
    return cont/n
def metodo2(r,n):
    cont = 0
    i = n
    l = r*sqrt(3)
    while i > 0:
        #Não é necessário achar um valor para C, já que C não é usado para
        #calcular a corda, só o raio, que é definido pelo usuário
        OC = r*random()
        corda = 2*sqrt(r**2-OC**2)
        if corda > l:
            cont += 1
        i -= 1
    return cont/n
def metodo3(r,n):
    cont = 0
    i = n
    l = r*sqrt(3)
    while i > 0:
        #gera um ponto aleatório em um quadrado de 2*r de lado
        x = r*(random()*2-1)
        y = r*(random()*2-1)
        #verifica se o ponto está dentro do círculo. Se não, gera outro ponto
        while y**2 + x**2 > r**2:
            x = r*(random()*2-1)
            y = r*(random()*2-1)
        #calcula a distância do ponto até a origem
        dist = sqrt(x**2+y**2)
        corda = 2*sqrt(r**2-dist**2)
        if corda > l:
            cont +=1
        i -= 1
    return cont/n
def main():
    r = int(input("Digite um raio para o circulo: "))
    n = int(input("Digite o numero de vezes que voce quer testar as probabilidades: "))
    print ("Probabilidade do metodo 1: ", metodo1(r,n))
    print ("Probabilidade do metodo 2: ", metodo2(r,n))
    print ("Probabilidade do metodo 3: ", metodo3(r,n))

if __name__ == '__main__':
    main()