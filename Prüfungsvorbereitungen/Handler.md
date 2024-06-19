# Signalhandler
Implementation eines Signalhandlers.
Ergänzen Sie den folgenden Code so, dass folgende Anforderungen erfüllt sind: 
Wenn ein Benutzer Ctrl-C drückt, dann soll 
- der Parent-Prozess den Text „User Interrupt“ ausgeben 
- der Child-Prozess diese Benutzer-Aktion ignorieren
- 
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define PERROR_AND_EXIT(M) do{perror(M);exit(EXIT_FAILURE);} while(0)

void do_work()
{
    for (;;)
    {
    }
}

int main(void)
{
    pid_t cpid = fork();
    if (cpid == -1)
    {
        PERROR_AND_EXIT("fork");
    }
	//parent =>  cpid == childID
    if (cpid > 0)
    {
        struct sigaction a = {0};

        a.sa_flags = SA_SIGINFO;
        a.sa_sigaction = handler;

        // blockt alle Signale
        if (sigfillset(&a.sa_mask) == -1)
        {
            PERROR_AND_EXIT("sigfillset");
        }
        // register handler für Signal: SIGINT
        if (sigaction(SIGINT, &a, NULL) == -1)
        {
            PERROR_AND_EXIT("sigaction");
        }
        do_work();
    }
	// child
    else
    {
        do_work();
    }
}

// snp/theorie/SNP_10_Sys_Inter_Prozess_Kommunikation/
// SNP_Sys_Inter_Prozess_Kommunikation.pdf page 18
static void handler(int sig, siginfo_t *siginfo, void *context)
{
    printf("User Interrupt\n");
}
```