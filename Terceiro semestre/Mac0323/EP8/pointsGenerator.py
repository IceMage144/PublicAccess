from random import random

def main():
    n = int(input("Number of points to generate:\n"))
    f = open("inp.txt", "w")
    for i in range(n):
        x = random()
        y = random()
        f.write(f"{x:.6} {y:.6}\n")
    f.close()

if __name__ == "__main__":
    main()
