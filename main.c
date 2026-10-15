#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    //nonno
    printf("Nonno: PID: %d\n", getpid());

    pid = fork(); //padre

    if (pid < 0) {
        perror("Errore durante la fork del nonno");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        //pid padre

        printf("Padre: PID: %d, PPID: %d\n", getpid(), getppid());

        pid_t pid_nipote = fork(); //nipote

        if (pid_nipote < 0) {
            perror("Errore durante la fork del padre");
            exit(EXIT_FAILURE);
        }
        else if (pid_nipote == 0) {
            //pid nipote
            printf("Nipote: PID: %d, PPID: %d\n", getpid(), getppid());


            sleep(1);

            printf("Nipote Terminazione PID: %d\n", getpid());
            exit(EXIT_SUCCESS); // Il nipote esce
        }

        // Il Padre si mette in attesa della terminazione del suo unico figlio
        wait(NULL);

        printf("Padre Terminazione - PID: %d (Nipote concluso)\n", getpid());
        exit(EXIT_SUCCESS); // Il padre esce
    }

    // Il Nonno si mette in attesa della terminazione del suo unico figlio
    wait(NULL);

    printf("Nonno Terminazione - PID: %d. Tutta la catena e' conclusa.\n", getpid());

    return 0;
}