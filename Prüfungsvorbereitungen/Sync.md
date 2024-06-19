Sync / Semaphores und Signals werden verwendet um Zugriff auf geteilte Ressourcen zu koordinieren. Zudem können damit Threads aufeinander warten.

Syncs werden notwendig, wenn ein Thread auf einen anderen warten **muss**.
- z.B. wenn eine Resource im einten geöffnet ist, dann darf der andere diese erst öffnen, sobald der erste durch ist.
- Oder in einer kritischen Funktion, die **IMMER** ganz durchlaufen werden muss.

```c
// Mit dem volatile keyword wird klargestellt,
// dass diese Resource von mehreren Threads verwendet wird.
volatile int iAmShared = 0;
```

# Mutex - Mutual Exclusion
- Resourcen werden gegenseitig ausgeschlossen, ein Task blockiert den Eintritt für andere Tasks in die Crititcal Section

## Probleme
- Runtime Kosten (locks dauern)
- Rekursion
- Kein Unlock (Bei early return)
- Deadlock

```c
#include <sys/types.h>
#incldue <phtread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

const int N = 100000000;

// shared value
volatile int value = 0;

pthread_mutx_t mutex;

void * thread_method(void * arg)
{
	int delta = *(int*) arg;

	for (int i = 0; i < N; i++)
	{
		if (pthread_mutex_lock(&mutex) != 0)
		{
			perror("Mutex konnte nicht besetzt werden");
			exit(EXIT_FAILURE);
		}

		// Gemeinsame Variable auslesen
		int a = value;

		// Modifiziern
		a += delta;

		// Variable wieder setzen
		value = a;


		// Mutex wieder freigeben
		if (pthread_mutex_unlock(&mutex) != 0)
		{
			perror("Mutex konnte nicht freigegeben werden");
			exit(EXIT_FAILURE);
		}
	}
	return NULL;
}

int main (void)
{
	if (phtread_mutex_init(&mutex, NULL) != 0)
	{
		perror("Mutex konnte nicht initialisiert werden");
		exit(EXIT_FAILURE);
	}

	pthread_t th_inc;
	pthread_t th_dec;


	int inc = +1;
	int dec = -1;
	if (pthread_create(&th_inc, NULL, count, &inc) != 0)
	{
		perror("Thread konnte nicht erstellt werden");
		exit(EXIT_FAILURE);
	}
	
	if (pthread_create(&th_dec, NULL, count, &dec) != 0)
	{
		perror("Thread konnte nicht erstellt werden");
		exit(EXIT_FAILURE);
	}

	// noch auf threads waretn
	if (pthread_join(th_inc, NULL) != 0)
	{
		perror("Thread konnte nicht beendet werden");
		exit(EXIT_FAILURE);
	}
	if (pthread_join(th_dec, NULL) != 0)
	{
		perror("Thread konnte nicht beendet werden");
		exit(EXIT_FAILURE);
	}

}
```

# Semaphore
Tasks können über Semaphoren Synchronisationspunkte vereinbaren

## Probleme
- Synchronisation kostet Zeit
- Wenn ein wait zu viel, bzwh. ein signal zu wenig
- Deadlocks, System kann komplett blockiert werden

```c
// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

void* thread(void* arg)
{
	//wait
	sem_wait(&mutex);
	printf("\nEntered..\n");

	//critical section
	sleep(4);
	
	//signal
	printf("\nJust Exiting...\n");
	sem_post(&mutex);
}


int main()
{

	// 1 -> Initial value
	// unbedingt auf das achten
	sem_init(&mutex, 0, 1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,thread,NULL);
	sleep(2);
	pthread_create(&t2,NULL,thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&mutex);
	return 0;
}

```

## Rekusion
Mutex Lock-Unlock Paare immer nur im selben Task erlaubt
- es ist ein Fehler, wenn ein Unlock einer Mutex in einer anderen Task als 
jener gemacht wird, in der das entsprechende Lock gemacht wurde
- ein Mutex muss wissen, in welchem Task der Lock passierte und 
entsprechendes Fehlerhandling machen
 Verschachtelte Lock-Unlock Paare, ohne Selbst-Deadlock
- dieses Wissen über die aktuell blockierende Task kann genutzt werden, 
um verschachtelte (rekursive) Lock-Unlock Paare sinnvoll zu meistern
- i.A. ist die Unterstützung für rekursive Mutexes explizit zu setzten

Lösung 1 :
```c
Mutex = {allow_recursion}; // Pseudo code
Container shared_container = {...};
void get_length(Container c)
{
    lock(mutex);
    int len = count(c.data);
    unlock(mutex);
    return len;
}
void append(Container c, Element e)
{
    lock(mutex);
    // get_length() locks and unlocks again in the same thread as the outer lock-unlock pair
    if (get_length(c) < c.capacity)
    {
        push_back(c.data, e);
    }
    unlock(mutex);
}

```

Lösung 2: 
```c
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define FATAL(M) do { perror(M); exit(EXIT_FAILURE); } while(0)
#define N 10000000
#define MUTEXATTR PTHREAD_MUTEX_RECURSIVE
pthread_mutexattr_t mutex_attr;
pthread_mutex_t mutex;
int value = 0;
void calc(int step)
{
    if (pthread_mutex_lock(&mutex) != 0)
        FATAL("inner lock");
    value += step;
    if (pthread_mutex_unlock(&mutex) != 0)
        FATAL("inner unlock");
}
void *count(void *p)
{
    for (int i = 0; i < N; i++)
    {
        if (pthread_mutex_lock(&mutex) != 0)
            FATAL("lock");
        calc(*(int *)p);
        if (pthread_mutex_unlock(&mutex) != 0)
            FATAL("unlock");
    }
}
int main(void)
{
    if (pthread_mutexattr_init(&mutex_attr) != 0)
        FATAL("mutexattr_init");
    if (pthread_mutexattr_settype(&mutex_attr, MUTEXATTR) != 0)
        FATAL("mutexattr_set");
    if (pthread_mutex_init(&mutex, &mutex_attr) != 0)
        FATAL("mutex_init");
    pthread_t th_inc;
    pthread_t th_dec;
    int inc = +1;
    int dec = -1;
    if (pthread_create(&th_inc, NULL, count, &inc) != 0)
        FATAL("create");
    if (pthread_create(&th_dec, NULL, count, &dec) != 0)
        FATAL("create");
    if (pthread_join(th_inc, NULL) != 0)
        FATAL("join");
    if (pthread_join(th_dec, NULL) != 0)
        FATAL("join");
    if (value != 0)
        fprintf(stderr, "ERROR: exp=%d, act=%d\n", 0, value);
}
```

## Deadlock

Gegeben
- zwei Massenspeicher A und B
- Zugriff auf die individuellen Massenspeicher ist exklusiv, d.h. nur eine Task aufs mal kann auf A oder B zugreifen

Situation:
```c
// Task 1
void copyAtoB(File fileX)
{
	lock(A);
		lock(B);
			copy(«A/fileX», «B/fileX»);
		unlock(B);
	unlock(A);
}

// Task 2
void copyBtoA(File fileY)
{
	lock(B);
		lock(A);
			copy(«A/fileY», «B/fileY»);
		unlock(A);
	unlock(B);
}

```