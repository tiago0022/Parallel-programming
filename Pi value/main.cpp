// #include <iostream>
#include <stdio.h>
#include <omp.h>

#define THREADS 4

using namespace std;

static long num_steps = 1000000;
double step;

int main ()
{
	  double x, pi, sum = 0.0;
		double threadSums[THREADS];
	  double start_time, run_time;

	  step = 1.0/(double) num_steps;
	  start_time = omp_get_wtime();

		omp_set_num_threads(THREADS);

		#pragma omp parallel
    {

      int threadSteps = num_steps / omp_get_num_threads();
      // cout << "is " << threadSteps << endl;
			int id = omp_get_thread_num();
      int start = id * threadSteps;
      int end = start + threadSteps;
			// printf("is %d in %d\n", end, omp_get_thread_num());
      double mySum = 0;
  	  for (int i = start; i <= end; i++){
  		  x = (i - 0.5) * step;
  		  mySum = mySum + 4.0/(1.0+x*x);
  	  }
			threadSums[id] = mySum;
    }

		for(int i = 0; i < THREADS; i++)
			sum += threadSums[i];

	  pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  // cout << endl << " pi with " << num_steps << " steps is " << pi << " in " << run_time << " seconds" << endl;
    printf("\n pi with %ld steps is %f in %f seconds ",num_steps,pi,run_time);
}
