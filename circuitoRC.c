#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define SEED 35791246


void imprime(double *R, double *C );
double likelihood(double *obs, double *model);
double Gaussiannumber(double mu, double sigma);
double  * my_model(double R, double C, double *t);
int siz = 299;
int V_0 = 10;
int ite = 10000;


int main(){

FILE * fp =fopen("CircuitoRC.txt", "r");

double *t = malloc(siz*sizeof(double));
double *q_obs = malloc(siz*sizeof(double));
	
unsigned int i = 0;
if (fp != NULL){
  double t_act; 
  double q_act;
  while (!feof(fp)){
    fscanf(fp, "%lf %lf", &t_act, &q_act);
    t[i]=t_act;
    q_obs[i]=q_act;
    i++;
   }
 }

fclose(fp);

/*hago la caminata*/
double *R_walk = malloc(ite*sizeof(double));
double *C_walk = malloc(ite*sizeof(double));
double *l_walk = malloc(ite*sizeof(double));



double l_init = likelihood(q_obs, my_model(R_walk[0], C_walk[0], t));
R_walk[0]=2;
C_walk[0]=2;
l_walk[0]=l_init;

int j;
double R_prime;
double C_prime;
double l_prime;
double alpha;
double beta;
for(j=1; j<ite; j++){
  R_prime = Gaussiannumber(R_walk[j-1], 0.1);
  C_prime = Gaussiannumber(C_walk[j-1], 0.1);
  l_prime = likelihood(q_obs, my_model(R_prime, C_prime, t));

  alpha= l_prime/l_walk[i];
  if(alpha >=1.0){
    R_walk[j] = R_prime;
    C_walk[j] = C_prime;
    l_walk[j] = l_prime;
    }
  else{
    beta=(double)rand()/RAND_MAX;
    if(beta<=alpha){
      R_walk[j] = R_prime;
      C_walk[j] = C_prime;
      l_walk[j] = l_prime;
        }
    else{
      R_walk[j] = R_walk[j-1];
      C_walk[j] = C_walk[j-1] ;
      l_walk[j] = l_walk[j-1];
        }
      }


imprime(R_walk, C_walk);

 }
}

/*likelihood*/
double likelihood(double *obs, double *model)
{
  int i;
  double sumatoria;
  for(i=0; i<siz; i++)
    {
    	sumatoria=exp(-0.5*((obs[i]-model[i])/2000))*exp(-0.5*((obs[i]-model[i])/2000)); 
     }
     
return sumatoria;
} 

/*my_model*/
double  * my_model(double R, double C, double *t)
{
  double *modelo = malloc(siz*sizeof(double));
  int i;
  for(i=0; i<siz; i++)
    {
     modelo[i]=V_0*C*(1-exp(-t[i]/(R*C)));
    }
     
return modelo;
} 


/*numeros random normalizados*/
double Gaussiannumber(double mu, double sigma)
{
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}

/*imprimir*/
void imprime(double *R, double *C )
{ 
  FILE *doc= fopen("imprecrc.txt", "w");
  
  int i;
  for(i=0; i<ite; i++){
  fprintf(doc, "%f %f \n", R[i], C[i]);
  }
    
}

