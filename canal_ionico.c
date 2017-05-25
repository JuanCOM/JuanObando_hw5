#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define SEED 35791246



void imprime(double *x, double *y, double *likelihood);
void imprime1(double *x1, double *y1, double *likelihood1);
double Gaussiannumber(double mu, double sigma);
double likelihood(double x_random, double y_random, double *x0, double *y0);
void leerarchivo(FILE * fp, double *x, double *y);

int ite=10000;
int siz=42;




void leerarchivo(FILE * fp, double *x, double *y){
	
unsigned int i = 0;
if (fp != NULL){
  double x_act; 
  double y_act;
  while (!feof(fp)){
    fscanf(fp, "%lf %lf", &x_act, &y_act);
    x[i]=x_act;
    y[i]=y_act;
    i++;
  }
}

}

/*main*/
int main()
{

FILE * fp =fopen("Canal_ionico.txt", "r");
double *x0 = malloc(siz*sizeof(double));
double *y0 = malloc(siz*sizeof(double));
leerarchivo(fp, x0, y0);

FILE * fp1 =fopen("Canal_ionico1.txt", "r");
double *x1 = malloc(siz*sizeof(double));
double *y1 = malloc(siz*sizeof(double));
leerarchivo(fp1, x1, y1);



/*hacemos las caminatas para canal_ionico*/
double *x_walk = malloc(ite*sizeof(double));
double *y_walk = malloc(ite*sizeof(double));
double *l_walk = malloc(ite*sizeof(double));

double l_init = likelihood(3.1, 5.4, x0, y0);
x_walk[0]=3.1;
y_walk[0]=5.4;
l_walk[0]=l_init;

int j;
for(j=1; j<ite; j++){
  double x_prime = Gaussiannumber(x_walk[j-1], 0.1);
  double y_prime = Gaussiannumber(y_walk[j-1], 0.1);
  double l_init = likelihood(x_walk[j-1], y_walk[j-1], x0, y0);
  double l_prime = likelihood(x_prime, y_prime, x0, y0);

  double alpha= l_prime/l_init;
  if(alpha >=1.0){
    x_walk[j] = x_prime;
    y_walk[j] = y_prime;
    l_walk[j] = l_prime;
    }
  else{
    double beta=(double)rand()/RAND_MAX;
    if(beta<=alpha){
      x_walk[j] = x_prime;
      y_walk[j] = y_prime;
      l_walk[j] = l_prime;}
    else{
      x_walk[j] = x_walk[j-1];
      y_walk[j] = y_walk[j-1] ;
      l_walk[j] = l_walk[j-1];}
      }
    
}

/*hacemos las caminatas para canal_ionico1*/
double *x_walk1 = malloc(ite*sizeof(double));
double *y_walk1 = malloc(ite*sizeof(double));
double *l_walk1 = malloc(ite*sizeof(double));

double l_init1 = likelihood(7, 5, x1, y1);
x_walk1[0]=7;
y_walk1[0]=5;
l_walk1[0]=l_init1;

int k;
for(k=1; k<ite; k++){
  double x_prime1 = Gaussiannumber(x_walk1[k-1], 0.1);
  double y_prime1 = Gaussiannumber(y_walk1[k-1], 0.1);
  double l_init1 = likelihood(x_walk1[k-1], y_walk1[k-1], x1, y1);
  double l_prime1 = likelihood(x_prime1, y_prime1, x1, y1);

  double alpha1= l_prime1/l_init1;
  if(alpha1 >=1.0){
    x_walk1[k] = x_prime1;
    y_walk1[k] = y_prime1;
    l_walk1[k] = l_prime1;
    }
  else{
    double beta1=(double)rand()/RAND_MAX;
    if(beta1<=alpha1){
      x_walk1[k] = x_prime1;
      y_walk1[k] = y_prime1;
      l_walk1[k] = l_prime1;}
    else{
      x_walk1[k] = x_walk1[k-1];
      y_walk1[k] = y_walk1[k-1] ;
      l_walk1[k] = l_walk1[k-1];}
      }
    
}


imprime(x_walk, y_walk, l_walk);

imprime1(x_walk1, y_walk1, l_walk1);


}



/*Busco el radio mínimo*/
double likelihood(double x_random, double y_random, double *x0, double *y0)
{
  int i;
  double r_min = 500.0;
  for(i=0; i<siz; i++)
    {
     double radios=sqrt((x0[i]-x_random)*(x0[i]-x_random) + (y0[i]-y_random)*(y0[i]-y_random));
     if(radios < r_min){
       r_min=radios;
     }
     
    }
return r_min;
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
void imprime(double *x, double *y, double *likelihood){ 
  FILE *doc= fopen("impreso.txt", "w");
  int i;
  for(i=0; i<ite; i++){
  fprintf(doc, "%lf %lf %lf \n", x[i], y[i], likelihood[i]);
  }  
}

/*imprimir1*/
void imprime1(double *x1, double *y1, double *likelihood1)
{ 
  FILE *doc1= fopen("impreso1.txt", "w");
  int i;
  for(i=0; i<ite; i++){
  fprintf(doc1, "%lf %lf %lf \n", x1[i], y1[i], likelihood1[i]);
  }
    
}









