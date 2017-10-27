//
// This exercise involves the computation of y = (A^T)Ax, i.e., (A-transposed)Ax 
// A is a dense nxn matrix and x in a vector of n elements. Since the
// product (AT)A takes O(N^3)operations to compute, it is not explicitly
// formed, but a sequence of two matrix-vector products is computed:
// 1) temp = Ax, followed by y = (AT)temp. The baseline code is a direct
// translation of teh above two step sequence into a sequenc eof two
// matrix-vector products. But it does not vectorize and has low performance
// Create a higher performance version in atax_opt.

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#define threshold 0.0000001
#define N 8192

double A[N][N], x[N],y[N],yy[N],temp[N];
int main(){
double rtclock();
void atax(int n, double A[][n], double x[n], double y[n]);
void atax_opt(int n, double A[][n], double x[n], double y[n]);
void compare(int n, double wref[n], double w[n]);

double clkbegin, clkend;
double t;
double rtclock();

int i,j,it;

  for(i=0;i<N;i++)
   { 
     x[i] = i/N; 
     y[i]= 0; 
     yy[i]= 0; 
     for(j=0;j<N;j++) A[i][j] = (i+2.0*j)/(2.0*N);
   }

  clkbegin = rtclock();
  atax(N,A,x,y);
  clkend = rtclock();
  t = clkend-clkbegin;
  if (y[N/2]*y[N/2] < -100.0) printf("%f\n",y[N/2]);
  printf("Reference A^TAx: Matrix Size = %d; %.2f GFLOPS; Time = %.3f sec; \n",
          N,2.0*1e-9*N*N/t,t);

  clkbegin = rtclock();
  atax_opt(N,A,x,yy);
  clkend = rtclock();
  t = clkend-clkbegin;
  if (yy[N/2]*yy[N/2] < -100.0) printf("%f\n",yy[N/2]);
  printf("Optimized A^TAx: Matrix Size = %d; %.2f GFLOPS; Time = %.3f sec; \n",
          N,2.0*1e-9*N*N/t,t);
  compare(N,y,yy);

}

void atax(int n, double A[][n], double x[n], double y[n])
{ int i,j;
  double temp[N];
// First form temp = Ax
  for(i=0;i<n;i++) temp[i] = 0;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    {
      temp[i] += A[i][j]*x[j];
    }
// Next compute y = (A^T)temp
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    {
      y[i] += A[j][i]*temp[j];
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
