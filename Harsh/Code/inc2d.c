#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int N=1024;
double A[1024][1024];
int main(){
double rtclock();

double clkbegin, clkend;
double t;

int i,j,k,it;


// Initialization; 
  for(i=0;i<N;i++)
   for(j=0;j<N;j++)
   { 
     A[i][j] = i+j;
   }

  clkbegin = rtclock();
  int T=1;
   for(it=0;it<T;it++)
    for(j=0;j<N;j++)
     for(i=0;i<N;i++) 
      A[i][j] +=1;
//
  clkend = rtclock();
  t = clkend-clkbegin;
  if (A[N/2][N/2]*A[N/2][N/2] < -100.0) printf("%f\n",A[N/2][N/2]);
  printf("Performance: Matrix Size = %d x %d; Niter = %d: %.2f GFLOPS; Time = %.3f sec\n", N,N,T,1e-9*N*N*T/t,t);
}

double rtclock()
{
  struct timezone Tzp;
  struct timeval Tp;
  int stat;
  stat = gettimeofday (&Tp, &Tzp);
  if (stat != 0) printf("Error return from gettimeofday: %d",stat);
  return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}

