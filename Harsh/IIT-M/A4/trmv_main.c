#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#define N 8192
#define threshold 0.0000001

double A[N][N], x[N],y[N],yy[N];
int main(){
double rtclock();
void trmv(int n, double A[][n], double x[n], double y[n]);
void trmv_opt(int n, double A[][n], double x[n], double y[n]);
void compare(int n, double wref[n], double w[n]);

double clkbegin, clkend;
double t;
double rtclock();

int i,j,ii,jj;

  for(i=0;i<N;i++)
   { 
     x[i] = i; 
     y[i]= 0; 
     yy[i]= 0; 
     for(j=0;j<N;j++) A[i][j] = (i+2.0*j)/(2.0*N);
   }

  clkbegin = rtclock();
  trmv(N,A,x,y);
  clkend = rtclock();
  t = clkend-clkbegin;
  if (y[N/2]*y[N/2] < -100.0) printf("%f\n",y[N/2]);
  printf("Reference Triangular MV: Matrix Size = %d; %.2f GFLOPS; Time = %.3f sec; \n",
          N,2.0*1e-9*N*N/t,t);

  clkbegin = rtclock();
  trmv_opt(N,A,x,yy);
  clkend = rtclock();
  t = clkend-clkbegin;
  if (y[N/2]*y[N/2] < -100.0) printf("%f\n",y[N/2]);
  printf("Optimized Triangular MV: Matrix Size = %d; %.2f GFLOPS; Time = %.3f sec; \n",
          N,2.0*1e-9*N*N/t,t);
  compare(N,y,yy);

}

void trmv(int n, double A[][n], double x[n], double y[n])
{
  int i,j;
  for(j=0;j<n;j++)
    for(i=j;i<n;i++)
    {
      y[j] = y[j] + A[i][j]*x[i];
    }
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

void compare(int n, double wref[n], double w[n])
{
double maxdiff,this_diff;
int numdiffs;
int i;
  numdiffs = 0;
  maxdiff = 0;
  for (i=0;i<n;i++)
    {
     this_diff = wref[i]-w[i];
     if (this_diff < 0) this_diff = -1.0*this_diff;
     if (this_diff>threshold)
      { numdiffs++;
        if (this_diff > maxdiff) maxdiff=this_diff;
      }
    }
   if (numdiffs > 0)
      printf("%d Diffs found over threshold %f; Max Diff = %f\n",
               numdiffs,threshold,maxdiff);
   else
      printf("No differences found between base and test versions\n");
}
