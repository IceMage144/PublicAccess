def bubble(array):
    m = 0
    i = 0
    while i != len(array):
        i = 0
        for temp in array:
            if temp != len(array):
                if array[temp] < array[temp+1] and temp != len(array):
                    m = array[temp]
                    array[temp] = array[temp+1]
                    array[temp+1] = m
                    print(m)
                else:
                    i += 1
def insertionSort(C):
	n = len(C)
	temp = 1
	i = 0
	while temp != n:
		i = 0
		while i < temp:
			if C[temp-i] < C[temp-i-1]:
				C[temp-i], C[temp-i-1] = C[temp-i-1], C[temp-i]
			i += 1
		temp +=1
if __name__ == "__main__":
    a = [0,0,0,0,0,0,0,0,0,0]
    t = 0
    while t < 10:
        a[t] = int(input("Escolha números: "))
        t += 1
    bubble(a)
    print(a)
