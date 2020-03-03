#include <stdio.h>
#include <time.h>
#include <pthread.h>
#define numThreads 16

long cantidadIntervalos = 1000000000;
double baseIntervalo;

double acum = 0;

double baseIntervalo;

double cantIntPorThread;

struct timespec start, end;
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;
void *piFunc(void *pArg)
{
    double* threadNum = (double*)pArg;
    double fdx;
    double x;
    long i;
    double acum2 = 0;

    x = cantIntPorThread * baseIntervalo * (*threadNum);

    for (i = 0; i < cantIntPorThread; i++) {
        fdx = 4 / (1 + x * x);
        acum2 = acum2 + (fdx * baseIntervalo);
        x = x + baseIntervalo;
    }
	pthread_mutex_lock(&mutexsum);
	acum = acum + acum2;
	pthread_mutex_unlock (&mutexsum);


    return 0;
}

void main() {
	double elapsed =0;

    long i;
    double tNum[numThreads];
    pthread_t hThread[numThreads];

    baseIntervalo = 1.0 / cantidadIntervalos;
    cantIntPorThread = cantidadIntervalos / numThreads;
 //   InitializeCriticalSection(&cs);
    clock_gettime(CLOCK_MONOTONIC,&start);
    for (i = 0; i < numThreads; i++) {

        tNum[i] = i;
         pthread_create(&hThread[i],NULL,piFunc,&tNum[i]);

    }
	for (int i =0; i<numThreads;i++){
		pthread_join(hThread[i],NULL);
	}
    
   // DeleteCriticalSection(&cs);
    clock_gettime(CLOCK_MONOTONIC,&end);
	if((end.tv_nsec - start.tv_nsec)<0)
	{
		elapsed = 1000000000.0+ end.tv_nsec - start.tv_nsec;
	}
	else{
		elapsed = end.tv_nsec -start.tv_nsec;
	}
    printf("Resultado = %20.18lf (%lf)\n", acum, (elapsed/1000000000.0));
}

