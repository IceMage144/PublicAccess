import math

def lMergeSort(v, b, e):
    if (e-b > 1):
        aux = math.floor((e+b)/2)
        A = lMergeSort(v, b, aux)
        B = lMergeSort(v, aux, e)
        return intercala(A, B)
    return v[b]

def intercala(A, B):
    aux = []
    for i in range(len(A)):
        aux.append(A[i])
    for j in range(len(B)-1, -1, -1):
        aux.append(B[j])
    R = [0 for i in range(len(A) + len(B))]
    count = 0
    i, j = 0, len(A) + len(B) - 1
    for count in range(len(A) + len(B)):
        if (aux[i] <= aux[j]):
            R[count] = aux[i]
            i += 1
        else:
            R[count] = aux[j]
            j -= 1
    return R


def main():
    v = [[7, 9, 10], [3, 4, 8], [1, 2, 5, 11], [0], [6, 12]]
    print(v)
    R = lMergeSort(v, 0, 5)
    print(R)

if __name__ == "__main__":
    main()
