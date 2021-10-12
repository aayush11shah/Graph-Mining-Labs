import numpy as np
import matplotlib.pyplot as plt

adjList_degreeFreq = []
adjList_degree = []
with open("adjList_degreeFreq.txt") as file:
    for line in file:
        k = line.split()
        if int(k[1])!=0:
            adjList_degree.append(int(k[0]))
            adjList_degreeFreq.append(int(k[1]))

CSR_degreeFreq = []
CSR_degree = []
with open("CSR_degreeFreq.txt") as file:
    for line in file:
        k = line.split()
        if int(k[1])!=0:
            CSR_degree.append(int(k[0]))
            CSR_degreeFreq.append(int(k[1]))

figure, axis = plt.subplots(2,1)
figure.suptitle("Degree Distribution Comparison for Graph Representations",  fontsize="x-large")

axis[0].set_title("Degree Distribution Curve using Adjacency Lists")
axis[0].scatter(adjList_degree, adjList_degreeFreq)
axis[0].set_xlabel("Degrees of vertices")
axis[0].set_ylabel("Frequencies of degrees")


axis[1].scatter(CSR_degree, CSR_degreeFreq, c="green")
axis[1].set_title("Degree Distribution Curve using CSR")
axis[1].set_xlabel("Degrees of vertices")
axis[1].set_ylabel("Frequencies of degrees")

figure.tight_layout()
plt.savefig("Degree_Comparison.png")
plt.show()
