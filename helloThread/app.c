#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>




#define numThreads 4

void *Thread_routine(void *arg){
	int* threadNum = (int*)arg;
	printf("hello from thread %d\n",(*threadNum));
}
int main(){
	int tNum[numThreads];
	pthread_t threadID[numThreads];
	for (int i =0; i<numThreads;i++){
		tNum[i] =i;
		pthread_create(&threadID[i],NULL,Thread_routine,&tNum[i]);
	}	
	for(int i =0; i< numThreads; i++){
		pthread_join(threadID[i],NULL);
	}

	
	return 0;
}
