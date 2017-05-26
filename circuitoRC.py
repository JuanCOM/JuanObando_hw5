

import numpy as np
import matplotlib.pyplot as plt




crc = np.genfromtxt("CircuitoRC.txt")

t = crc[:,0]
q_obs = crc[:,1]
N=10000

V_o = 10




def my_model(R, C, t):
    return C*V_o*(1-np.exp(-t/(R*C)))

def likelihood(obs, model):
    return np.exp(-0.5*np.sum(((model - obs)/2000)**2))





R_walk = [2]
C_walk = [2]
l_walk = [likelihood(q_obs, my_model(R_walk[0], C_walk[0], t))]


for i in range( N):
    R_prime = np.random.normal(R_walk[i], 0.1)
    C_prime = np.random.normal(C_walk[i], 0.1)
    l_prime = likelihood(q_obs, my_model(R_prime, C_prime, t))

    Alpha = l_prime/l_walk[i]
    if(Alpha>=1):
        R_walk = np.append(R_walk, R_prime)
        C_walk = np.append(C_walk, C_prime)
        l_walk = np.append(l_walk, l_prime)
    else:
        R_walk = np.append(R_walk, R_walk[i])
        C_walk = np.append(C_walk, C_walk[i])
        l_walk = np.append(l_walk, l_walk[i])

max_likelihood_id = np.argmax(l_walk)
best_R = R_walk[max_likelihood_id]
best_C = C_walk[max_likelihood_id]

Q_max =  V_o*best_C

print (best_R)
print (best_C)
print (Q_max)




#fig, ax = plt.subplots(figsize = (5,5))
#ax.plot(crc[:,0], crc[:,1], label = r"Datos observados")
#ax.plot(crc[:,0], my_model(best_R, best_C, crc[:,0]),label = "Datos para $R = %f$ y $C = %f$" % #(best_R, best_C))#
#ax.set_xlabel(r"$t$")
#ax.set_ylabel(r"$q$")
#ax.set_title("Fit Circuito $RC$")
#ax.legend()
#plt.show()

fig = plt.figure(figsize=(8,10))


ax1 = fig.add_subplot(221)
ax1.plot(crc[:,0], crc[:,1], label = "crc_obs", color="black")
ax1.plot(crc[:,0], my_model(best_R, best_C, crc[:,0]),label = "$R = %f$ y $C = %f$" % (best_R, best_C), color="yellow")
ax1.set_title("$Cir_RC Obs-Model$")
ax1.set_xlabel("$t$")
ax1.set_ylabel("$q$")
ax1.legend()


#fig, ax = plt.subplots(1, 2, figsize = (5,5), sharey = True)
#ax[0].scatter(R_walk, -np.log(l_walk), alpha = 0.1)
#ax[1].scatter(C_walk, -np.log(l_walk), alpha = 0.1)
#ax[0].set_xlabel("$R$")
#ax[1].set_xlabel("$C$")
#ax[0].set_ylabel("$-\ln(L)$")
#plt.tight_layout()
#plt.show()

ax2 = fig.add_subplot(222)
ax2.scatter(R_walk, -np.log(l_walk), alpha = 0.1, label = "R_walk", color="red")
ax2.scatter(C_walk, -np.log(l_walk), alpha = 0.1, label = "C_walk", color ="green")
ax2.set_xlabel("$R y C$")
ax2.legend()



#fig, ax = plt.subplots(1, 2, figsize = (5,5), sharey = True)
#ax[0].hist(R_walk, 20, normed = True)
#ax[1].hist(C_walk, 20, normed = True)
#ax[0].set_xlabel(r"$R$")
#ax[1].set_xlabel(r"$C$")
#ax[0].set_ylabel(r"Frecuencia normalizada")
#plt.tight_layout()
#plt.show()


ax3 = fig.add_subplot(223)
ax3.set_title("histog_R")
count, bins, ignored =ax3.hist(R_walk, 20, normed = True, color="red" )
ax3.set_xlabel("$R$")

ax4 = fig.add_subplot(224)
ax4.set_title("histog_C")
count, bins, ignored =ax4.hist(C_walk, 20, normed = True, color = "red")
ax4.set_xlabel("$C$")


plt.tight_layout()
fig = plt.gcf()

plt.show()








