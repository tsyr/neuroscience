import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D

x=[]
y=[]

f=open('../t.txt','r')
for i in f.readlines():
    x.append(float(i))
f.close()
f=open('../h.txt','r')
for i in f.readlines():
    y.append(float(i))
f.close()

fig = plt.figure()
ax = Axes3D(fig)

def update(n):
    xx = np.array([n])
    yy = np.array([n])
    zz = np.array([n])
    ax.clear()
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_xlim(-100,100)
    ax.set_ylim(-100,100)
    ax.set_zlim(-100,100)
    ax.scatter(xx,yy,zz, c='r')
    plt.title("particle")

ani = animation.FuncAnimation(fig, update, np.arange(0, 100), interval=10, blit=False)
plt.show()
