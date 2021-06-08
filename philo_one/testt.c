#include <unistd.h> 
#include<stdio.h>
#include<pthread.h>
 
void* reader(void*);
pthread_mutex_t mut[5];
int n;
 
int main()
{
  pthread_t t1[5];
  int i,j = 0,k;
  n = 5;
  for(i = 0; i < n; i++)
    {
      j=i;
      pthread_create(&t1[i], NULL, reader, &j);
    }
  for(j = 0; j < n; j++)
    pthread_join(t1[j], NULL);
  return 1;
}
 
void *reader(void* arg)
{
  int val = *(int*)arg;
  pthread_mutex_lock(&mut[val % n]);
  pthread_mutex_lock(&mut[(val + 1) % n]);
  //printf("%d Eating\n", val + 1);
    printf("%d \n", val + 1);
  sleep(1);
  pthread_mutex_unlock(&mut[val % n]);
  pthread_mutex_unlock(&mut[(val + 1) % n]);
  //printf("%d Finished Eating\n",val + 1);
}