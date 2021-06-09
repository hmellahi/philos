#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#define THREAD_NUM 4
#include <errno.h>
#include <stdio.h> 
#include <sys/stat.h>

sem_t *semaphore;

void* routine(void* args) {
    printf("(%d) Waiting in the login queue\n", *(int*)args);
    sem_wait(semaphore);
    printf("(%d) Logged in\n", *(int*)args);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n", *(int*)args);
    sem_post(semaphore);
    free(args);
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    // printf("%s", strerror(errno));
    // semaphore = sem_open("forks", 1);
    // printf("%s", strerror(errno));
    semaphore = sem_open("dsa", O_CREAT, S_IRWXU, 2); 
    if (semaphore == SEM_FAILED) { 
    perror("sem_open failed"); 
    exit(EXIT_FAILURE); 
  } 
    int i, sval;
    i = -1;
    // sem_post(semaphore);
    while (++i < 2)
        sem_post(semaphore);
    // sem_getvalue(semaphore, &sval);
    printf("%d\n", sval);
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    // sem_destroy(&semaphore);
    sem_close(semaphore);
    return 0;
}

// #include <stdio.h> 
// #include <stdlib.h> 
// #include <semaphore.h> 
// #include <fcntl.h> 
// #include <sys/stat.h> 
 
// int main(int argc, char**argv) { 
//   sem_t *sem; 
 
//   if (argc != 3) { 
//     fprintf(stderr, "USAGE = %s cle valeur\n", argv[0]); 
//     exit(EXIT_FAILURE); 
//   } 
 
//   char*cle=argv[1]; 
//   int valeur = atoi(argv[2]); 
 
// puts(cle);
//   /* Creation et initialisation du semaphore */ 
//   sem = sem_open(cle, O_CREAT, S_IRWXU, valeur); 
//   if (sem == SEM_FAILED) { 
//     perror("sem_open failed"); 
//     exit(EXIT_FAILURE); 
//   } 
 
//   printf("Initialisation OK\n"); 
//   int sval = -1; 
//   /* recupere le nombre de jetons */ 
//   if(sem_getvalue(sem, &sval) <0) { 
//     perror("sem_getvalue failed"); 
//     exit(EXIT_FAILURE); 
//   } 
//   printf("sval = %d\n", sval); 
 
//   return EXIT_SUCCESS; 
// }