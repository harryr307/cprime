#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8 
#define MAX_NUM 1000000000

typedef struct {
  int start;
  int end;
  int* primes;
  int count;
} thread_data;

int test(int rhs)
{
  if (rhs<2) return 0;
  if (rhs==2) return 1;
  if (rhs%2==0) return 0;
  for (int i=3;i*i<=rhs;i+=2)
    if (rhs%i==0)
      return 0;
  return 1;
}

void* thread_func(void* arg)
{
  thread_data* data = (thread_data*)arg;
  int curnum = data->start;

  data->count = 0;
  data->primes = malloc(sizeof(int)*(data->end - data->start + 1));

  while (curnum <= data->end)
  {
    if (test(curnum)==1)
      data->primes[data->count++] = curnum;

    curnum += 2;
  }

  return NULL;
}

int main()
{
  pthread_t threads[NUM_THREADS];
  thread_data tdata[NUM_THREADS];

  printf("2\n");

  int chunk = (MAX_NUM-3)/NUM_THREADS;

  for (int i=0;i<NUM_THREADS;i++)
  {
    tdata[i].start = 3 + i*chunk;
    if (tdata[i].start % 2 == 0) tdata[i].start++;
    tdata[i].end = (i==NUM_THREADS-1) ? MAX_NUM : tdata[i].start + chunk - 1;
    pthread_create(&threads[i],NULL,thread_func,&tdata[i]);
  }

  for (int i=0;i<NUM_THREADS;i++)
    pthread_join(threads[i],NULL);

  /* Print in order */
  for (int i=0;i<NUM_THREADS;i++)
  {
    for (int j=0;j<tdata[i].count;j++)
      printf("%d\n", tdata[i].primes[j]);

    free(tdata[i].primes);
  }
}
