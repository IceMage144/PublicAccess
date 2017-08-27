import math

def tMergeSort(v, b, e):
    if (e-b > 2):
        aux = (e-b)/3
        a1 = b+math.ceil(aux)
        a2 = b+math.ceil(2*aux)
        tMergeSort(v, b, a1)
        tMergeSort(v, a1, a2)
        tMergeSort(v, a2, e)
        intercala(v, b, a1, a2)
        intercala(v, b, a2, e)
    elif (e-b == 2 and v[b] > v[b+1]):
        v[b], v[b+1] = v[b+1], v[b]

def intercala(v, b, m, e):
    aux = [(v[b+i] if (i < m-b) else v[e-i+m-b-1]) for i in range(e-b)]
    count = 0
    i, j = 0, e-b-1
    for count in range(b, e):
        if (aux[i] <= aux[j]):
            v[count] = aux[i]
            i += 1
        else:
            v[count] = aux[j]
            j -= 1


def main():
    n = int(input())
    aux = input().split()
    v = [int(i) for i in aux]
    print(v)
    tMergeSort(v, 0, n)
    print(v)

if __name__ == "__main__":
    main()
