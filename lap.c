#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
/* square region */
#define XSIZE (10000)
#define YSIZE XSIZE
#define PI M_PI
double u[XSIZE][YSIZE], uu[XSIZE][YSIZE];
int num, niter;
static void lap_main(void);
static double verify(void);
int main(int argc, char* argv[]){
  int x, y;
  double dtime, value;
  num = 0;
  /* setting parameter */
  if(argc == 1) niter = 100;
  else niter = atoi(argv[1]);
  if(num == 0) {
    fprintf(stderr, "The number of iterations = %d\n", niter);
    fprintf(stderr, "Matrix Size = %d x %d\n", XSIZE, YSIZE);
  }
  /* initalize */
  for(x = 0; x < XSIZE; x++){
    for(y = 0; y < YSIZE; y++){
      u[x][y] = 0.0; uu[x][y] = 0.0;
    }
  }
  for(x = 1; x < XSIZE-1; x++)
    for(y = 1; y < YSIZE-1; y++)
      u[x][y] = sin((double)(x-1)/XSIZE*PI) + cos((double)(y-1)/YSIZE*PI);
  dtime = clock();
  lap_main();
  dtime = clock() - dtime;
  
  value = verify();
  if(num == 0){
    fprintf(stderr, "time = %.3f sec\n", dtime/CLOCKS_PER_SEC);
    fprintf(stderr, "Per. = %.3f GFlops\n", (double)niter*(XSIZE-2)*(YSIZE-2)*4/dtime/1000/1000/1000*CLOCKS_PER_SEC);
    fprintf(stderr, "Verification = %.3f \n", value);
  }
  return 0;
}
void lap_main(void){
  int x, y, k;
  /* Output intermediate the number of iterations */
  for(k = 0; k < niter; k++){
    if(k%(niter/10) == 0 && k != 0 && num == 0)
      fprintf(stderr, "iter = %d\n", k);
    /* old <- new */
    for(x = 1; x < XSIZE-1; x++)
      for(y = 1; y < YSIZE-1; y++)
  uu[x][y] = u[x][y];

    /* update */
    for(x = 1; x < XSIZE-1; x++)
      for(y = 1; y < YSIZE-1; y++)
  u[x][y] = (uu[x-1][y] + uu[x+1][y] + uu[x][y-1] + uu[x][y+1])/4.0;
  } // end of niter
}
double verify(){
  int x, y;
  double sum = 0.0;
  for(x = 1; x < XSIZE-1; x++)
    for(y = 1; y < YSIZE-1; y++)
      sum += (uu[x][y]-u[x][y]);
  return sum;
}
