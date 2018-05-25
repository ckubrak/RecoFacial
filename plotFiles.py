import matplotlib.pyplot as plt
import glob, os
import numpy as np



def plotear(filename):
    variable = []
    dependiente = []
    with open(filename) as fp:
        for line in fp:
            data = line.split(" ")
            data[5] = data[5][:-1]
            variable.append(data[0])
            dependiente.append(data[5])

    # variable.reverse()
    # dependiente.reverse()
    # variable.sort()
    # dependiente = [x for _,x in sorted(zip(dependiente,variable))]
    vPlot = np.array(variable)
    dPlot = np.array(dependiente)
    plt.scatter(vPlot,dPlot)

    xLab = ('k')

    plt.xlabel(xLab)
    plt.xticks(variable, rotation='vertical')



    yLab = ('tiempo (millisec)')
    # yLab = ('accuracy')
    plt.ylabel(yLab)
    plt.xlim(xmin=0) 
    plt.savefig('graficos/'+filename+'_'+yLab+'.png')

    plt.cla()


os.chdir(".")
for file in glob.glob("*knn*"):
    plotear(file)