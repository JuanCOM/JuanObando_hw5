import numpy as np
import matplotlib.pyplot as plt



c0=np.genfromtxt("Canal_ionico.txt")
c1=np.genfromtxt("Canal_ionico1.txt")
cc=np.genfromtxt("impreso.txt")
cc1=np.genfromtxt("impreso1.txt")

x0=c0[:,0]
y0=c0[:,1]

x1=c1[:,0]
y1=c1[:,1]

xc=cc[:,0]
yc=cc[:,1]
lc=cc[:,2]

xc1=cc1[:,0]
yc1=cc1[:,1]
lc1=cc1[:,2]


max_likelihood_id = np.argmax(lc)
best_x=xc[max_likelihood_id]
best_y=yc[max_likelihood_id]
radio_max=lc[max_likelihood_id]

max_likelihood_id1 = np.argmax(lc1)
best_x1=xc1[max_likelihood_id1]
best_y1=yc1[max_likelihood_id1]
radio_max1=lc1[max_likelihood_id1]

fig = plt.figure(figsize=(5.5,15))

ang = np.linspace(0, 2*np.pi, 100)
c_x = (radio_max-0.5)*np.cos(ang) +best_x
c_y = (radio_max-0.5)*np.sin(ang) +best_y
ax1 = fig.add_subplot(421)
ax1.set_title("Parametros:,$x=%f$,$y=%f$,$r=%f$"%(best_x, best_y,radio_max))
ax1.scatter(x0,y0,s = 8, color ="black")
ax1.scatter(best_x,best_y, color="red", s =8)
ax1.plot(c_x, c_y, 'r-')

ax2 = fig.add_subplot(422)
ax2.scatter(xc, yc, s=0.1, color="black")

ax3 = fig.add_subplot(423)
count, bins, ignored =ax3.hist(xc, 20, normed=True)

ax4 = fig.add_subplot(424)
count, bins, ignored =ax4.hist(yc, 20, normed=True)

ang1 = np.linspace(0, 2*np.pi, 100)
c_x1 = (radio_max1-0.5)*np.cos(ang1) +best_x1
c_y1 = (radio_max1-0.5)*np.sin(ang1) +best_y1
ax5 = fig.add_subplot(425)
ax5.set_title("Parametros:,$x=%f$,$y=%f$,$r=%f$"%(best_x1, best_y1,radio_max1))
ax5.scatter(x1,y1,s = 8, color ="black")
ax5.scatter(best_x1,best_y1, color="red", s =8)
ax5.plot(c_x1, c_y1, 'r-')

ax6 = fig.add_subplot(426)
ax6.scatter(xc1, yc1, s=0.1, color="black")

ax7 = fig.add_subplot(427)
Count, bins, ignored =ax7.hist(xc1, 20, normed=True)

ax8 = fig.add_subplot(428)
count, bins, ignored =ax8.hist(yc1, 20, normed=True)


plt.tight_layout()
fig = plt.gcf()

plt.show()
