from random import *

def main(lin):
	f = open("teste.txt", mode="w")
	f.write("H\n")
	for i in range(lin):
		rand1 = int(19*random())
		rand2 = int(19*random())
		if i != lin-1:
			end = "\n"
		else:
			end = ""
		f.write(str(rand1)+","+str(rand2)+end)
	f.close()

if __name__ == "__main__":
	#lin = int(input("lin: "))
	main(150)