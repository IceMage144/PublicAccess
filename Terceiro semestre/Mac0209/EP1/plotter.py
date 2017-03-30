import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys

matplotlib.style.use('ggplot')

def main():
    legend = ['gFx', 'gFy', 'gFz', 'TgF']
    times = []
    matrix = []
    args = sys.argv
    f = open(args[1], mode="r")
    for line in f:
        nums = line.split(";")
        nums[4] = nums[4].replace("\n", "")
        for i in range(5):
            nums[i] = nums[i].replace(",", ".")
            nums[i] = float(nums[i])
        matrix.append(np.array(nums[1:]))
        times.append(nums[0])
    f.close()
    matrix = np.array(matrix)
    #print(matrix)
    df = pd.DataFrame(matrix, columns=legend, index=times)
    df.plot()
    plt.show()


main()
