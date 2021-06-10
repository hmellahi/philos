#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
        pid_t pid;
        int rv=0, i;
        pid_t child_pids[5];


        for (i=1; i<=5; i++){

                /* Multiple child forking */
                switch(pid = fork()){
                        case -1:
                                /* something went wrong */
                                /* parent exits */
                                perror("fork");
                                exit(1);

                        case 0:
                                /*Children process*/
                                child_pids[i] = getpid();
                                // printf(" CHILD: number (and return value): %d PID: %d PPID: %d \n", i, getpid(), getppid());
                                if (i != 5)
                                    sleep(3);
                                exit(i);
                                break;

                                /*Missing code for parent process - will be executed out of loop*/
                }
        }
        /*Parent process*/
        // if (pid!=0 && pid!=-1) {
                printf("PARENT: my PID is %d\n", getpid());

                for (i=1; i<=5; i++){
                        waitpid(child_pids[i], NULL, 0);
                        printf("PARENT: Child: %d returned value is: %d\n", i, WEXITSTATUS(child_pids[i]));
                }
        // }
}