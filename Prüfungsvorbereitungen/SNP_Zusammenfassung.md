# Zusammenfassung SNP

### Elemente

#### Datentypen

```c
signed char                 1 Byte    -128 bis 127
unsigned char               1 Byte    0 bis 255
[signed] short [int]        2 Bytes   -32768 bis 32767
unsigned short [int]        2 Bytes   0 bis 65535
[signed] int                4 Bytes   -2^31 bis 2^31 -1
unsigned [int]              4 Bytes   0 bis 2^32 -1
[signed] long [int]         8 Bytes   -2^63 bis 2^63 -1
unsigned long [int]         8 Bytes   0 bis 264-1
[signed] long long [int]    8 Bytes   -2^63 bis 2^63 -1
unsigned long long [int]    8 Bytes   0 bis 2^64 -1
long double                 10 Bytes  -1.2 * 10^4932 bis 1.2* 10^4932

```
Zusatz-Typen:

-   aus `stdint.h` (fixe Grössen):
    		\- `int8_t`, `uint8_t`	- `int16_t`, `uint16_t`	- `int32_t`, `uint32_t`	- `int64_t`, `uint64_t`
    		\- aus `stddef.h`:
    		\- `size_t` für `sizeof`, array indices
    		\- `ptrdiff_t` für Pointer-Subtraktionen
-   Booleans:
    		\- `0` = `false`
    		\- in `stdbool.h` Datentyp `bool`

##### Auswahl

-   Beginnt mit `1..9`: Dezimal, `signed int` (wenn zu gross: `signed long`)
-   Beginnt mit `0`: Oktal, `unsigned int`
-   Beginnt mit `0x`: Hexadezimal, `unsigned int`
-   Mit einfachen Anführungszeichen umschlossen (`'`): Als ASCII Code Zahl (`'A'` = `65`), `signed int` (`unsigned char` in C++)
-   Endet mit `l` oder `L`: `long`
-   Endet mit `ll` oder `LL`: `long long`
-   Ended mit `u` oder `U`: `unsigned`
-   Enthält Dezimalpunkt: `double`
-   Enthält Exponent (z. B. `1e-2`): `double`
-   Endet mit `f` oder `F`: `float`
-   Endet mit `l` oder `L` und enthält Dezimalpunkt: `long double`


<div style="page-break-after: always;"></div>

#### ASCII table

äquivalent:

```c
int a = 'A' = '\101' = '\0x41' = 65
```

![](./assets/ASCII_Table.png)

#### Operatoren

<img src="./assets/Reihenfolge_Operatoren.png" alt="Operatoren" width="600"/>



Wenn nur numerische Typen in einem Ausdruck vorkommen, werden sie in den grössten vorhandenen Typ gewandelt.

#### enum

```c
enum wochentage {Montag, Dienstag, Mittwoch, Donnerstag, Freitag, Samstag, Sonntag};
```

weisst die Zahlen `0..6` zu.

```c
enum frucht {Apfel = 5, Birne = 10, Zitrone = 15};
enum frucht {Apfel = 5, Birne, Zitrone}; /* Birne = 6, Zitrone = 7 */
enum frucht {Apfel, Birne = -1, Zitrone}; /* Apfel = 0, Birne = -1, Zitrone = 0; Werte müssen nicht unterschiedlich sein */
```

Wertebereich wird nicht erzwungen (`enum wochentage w1 = 99;` ist zulässig)

#### struct

Definition, Usage:

```c
struct point3D {
  double x;
  double y;
  double z;
};

struct point3D point = { 2.0, 4.0, 6.0 };

struct point3D point2 = point /* Komplette Struktur kopiert */
point.x /* Zugriff auf Komponenten */
```

#### typedef

```c
typedef struct {
  double x;
  double y;
  double z;
} Point3D;

typedef enum {Montag, Dienstag, Mittwoch, Donnerstag, Freitag, Samstag, Sonntag} Wochentage;

Point3D point = { 2.0, 4.0, 6.0 };
Wochentage tag = Montag;
```

#### Funktionen

-   Erlaubte Parameter: Basis-Datentypen, `struct`s, `enum`s, Arrays, Pointer
-   Erlaubte Rückgabewerte: Basis-Datentypen, `struct`s, `enum`s, Pointer (Achtung! Keine Pointer auf lokale Variablen! `malloc` benutzen!)
-   Wenn `void` als Parameter deklariert wird (`void useme(void)`), gibt es keine Parameter. Wenn keine Parameter deklariert werden (`void useme()`), wird die Typenüberprüfung ausgehebelt.

Wenn ein Array als Parameter übergeben werden soll, wird ein Pointer auf ein Element übergeben (`void a(int *b)` bzw. `void a(const int *b)`, Schreibweise `void a(int b[])` auch möglich und äquivalent). Innerhalb der Funktion ist nicht unterscheidbar, ob der Pointer auf ein Array oder nur ein Element zeigt. Die Grösse bei der Übergabe von Arrays bei den höheren Dimensionen muss angegeben werden wegen der Pointer-Arithmetik für die Zugriffe in der ersten Dimension.

#### Print

Zahl zwischen `%` und Konvertierungs-Operator gibt minimale Länge und potentiell Anzahl Dezimalstellen aus:

```c
int a = 3;
double b = 4.0;
printf("%3i", a); // "  3"
printf("%10.2f", b); // "      4.00"
printf("%.2f", b); // "4.00"
```

#### Sichtbarkeit

| Ort                       | keywords | Sichtbarkeit                                                         |
| ------------------------- | -------- | -------------------------------------------------------------------- |
| innerhalb einer Funktion  | -        | nur in der Funktion                                                  |
| ausserhalb einer Funktion | -        | in allen Files des Programms                                         |
| innerhalb einer Funktion  | `static` | nur in der Funktion (Wert bleibt über verschiedene Aufrufe bestehen) |
| ausserhalb einer Funktion | `static` | nur im aktuellen File                                                |

### Initialisierung

![](./assets/var_init.png)

### Arrays und Pointer

#### sizeof

-   Wird zur Kompilierzeit ausgewertet

#### Array

> Ein Array in C ist eine Sequenz von Elementen vom selben Typ, in einem zusammenhängenden Speicherbereich abgelegt.

![](./assets/Übersicht_Arrays_als_Parameter.png)

In C gibt es keine Out-of-Bounds-Checks. Lokale Arrays werden nicht auf default-Werte gesetzt, globale und statische auf `0`. Bei der Deklaration wird angegeben:

-   Name
-   Datentyp
-   Anzahl Elemente

Werte können direkt bei der Deklaration zugewiesen werden:

```c
int a[5] = {4,7,12,77,2}; /* Alle 5 Elemente werden initialisiert */
int b[] = {4,7,12,77,2}; /* Länge wird implizit auf 5 gesetzt */
int c[5] = {4,3,88,5}; /* OK, letztes Element erhält Wert 0 */
int d[5] = {4,3,88,5,3,6}; /* Kompilierfehler */
int e[2][3] = {{1,2,3},{4,5,6}};
```

Wenn ein Array konstant ist (Deklaration mit `const`), können die Elemente nicht mehr verändert werden.

##### Strings

-   doppelte Anführungszeichen!
-   `char`-Array, mit `\0` terminiert
-   Braucht n + 1 bytes Speicher bei n Zeichen

```c
char ca0[] = "Hello World!"; /* Korrekter String => Hello World!\0*/
char ca1[20]; /* char-Array für 20 chars, hat noch nichts mit einem String zu tun! */
char ca2[]; /* Kompilierfehler */
ca1 = "hello, world"; /* Kompilierfehler */

ca1[0] = 'h';
ca1[1] = 'e';
[…]
ca1[11] = 'd';
ca1[12] = '\0';
/* Jetzt kann man sagen, in ca1 ist ein String abgelegt! */
```

String-Funktionen der Standard Library (`string.h`):

| Funktion                                        | Beschreibung                                                                                            |
| ----------------------------------------------- | ------------------------------------------------------------------------------------------------------- |
| `int strlen(const char s[])`                    | Zählt Zeichen ohne abschliessendes `\0`.                                                                |
| `int strcmp(const char s1[], const char s2[]`   | Vergleicht zwei Strings (_s1_ > _s2_ &rarr; >0, _s1_ == _s2_ &rarr; 0)                                          |
| `char* strcpy(char dest[], const char source[]` | Kopiert String von _source_ nach _dest_. _dest_ muss genügend gross sein! Rückgabe: Pointer auf _dest_. |
| `char* strcat(char s1[], const char s2[])`      | Hängt _s2_ an _s1_ an. _s1_ muss genügend gross sein! Rückgabe: Pointer auf _s1_.                       |

##### Jagged Arrays

-   eindimensionale Arrays von Pointern
-   innerhalb derselben Dimension unterschiedlich viele Elemente
-   brauchen nur so viel Platz auf dem Stack wie wirklich nötig

```c
char *jagged[] = {"One", "Two", "Three"};
// jagged[2] ist "Three";
// jagged[2][2] ist 'r';
```

#### Pointer

Ein Pointer ist eine Zahl, die eine Adresse im Speicher des Rechners referenziert. Sie zeigt immer auf das tiefste Byte eines Wertes.

##### Deklaration

```c
int* p; // Pointer auf int
int *p; // dasselbe

char *d[20]; // Array von 20 Pointern auf char

double (*d)[20]; // Pointer auf Array mit 20 doubles
double dd[20] = { 2,3,4,5 };
d = &dd; // print: d[0][0] oder (*d)[1]

char **ppc; // Pointer auf Pointer auf char
sizeof(int*)     // 4 bytes auf 32bit-System, 8 bytes auf 64bit-System
sizeof(char*)    // 4 bytes auf 32bit-System, 8 bytes auf 64bit-System
sizeof(double*)  // 4 bytes auf 32bit-System, 8 bytes auf 64bit-System

int *p, q = 3; // p: Pointer auf int. q: int = 3.
p = &q;
*p = 5; // q = 5
```

##### Pointer-Arithmetik:

Ein Pointer kann mit einer beliebigen Ganzzahl verschoben werden. <br>
Multiplikation und Division von Pointer ist *nicht erlaubt*. <br>
Pointer - Pointer ergibt den Offset (Abstand) zwischen einander.


```c
char c[] = "SEPFS16"; // size = 8 (7 char + 1 '\0' )
char *p = c;
printf("%c", p[0]);     // S
printf("%d", p[0] - p[2]); // 3 // keine Arithmetik
printf("%s", p + p[0] - p[2]); //FS16. pointer verschieben und dann bis '\0' printen, // Arithmetik
printf("\n%s", p);
```

##### `void`-Pointer:

-   nackte Adresse
-   kann auf beliebiges Objekt zeigen
-   kann ohne Cast einem beliebigen Pointer zugewiesen werden
-   verwendet, um ein Block nicht näher spezifizierter Daten zu referenzieren.

```c
double    d = 1.0;
double *dp1 = &d;
void    *vp = dp1;
double *dp2 = vp;
```

##### Pointer und `const`

Pointer kann konstant sein, auf ein konstantes Objekt zeigen oder beides.

```c
int i = 15;
int * const ip = &1; // Konstanter Pointer
*ip = 20; // erlaubt
ip = NULL; // verboten

const int j = 15;
const int * jp = &j; // Pointer auf konstante Variable
*jp = 20; // verboten
jp = NULL; // erlaubt

const int k = 14;
const int *const kp = &k; // Konstanter Pointer auf konstante Variable
*kp = 20 // verboten
kp = NULL; // verboten
```

Pointer auf konstante Werte sind wichtig als Parameter (`void a(const int *b)`, `void a(const struct t *p)`).

##### Pointer und `NULL`

-   Die Adresse `0` ist nie gültig
-   Wird für ungültige/nicht initialisierte Pointer verwendet
-   `stdio.h` definiert `NULL` als `0`
-   `NULL` als return-value => Funktion fehlgeschlagen (Konvention)

##### Pointer und Strukturen

Wenn ein Pointer auf eine Struktur zeigt, gibt es eine abgekürzte Schreibweise, um auf Elemente zuzugreifen.

```c
struct foo {int a; int *b;};
struct foo f;

f.a = 3;
int c = 5;
f.b = &c;

struct foo *fp = &f;

// dereferenzieren
printf("%d", (*fp).a);     besser: printf("%d", fp->a);
printf("%d", (*(*fp).b));  besser: printf("%d", *fp->b);
```

##### Pointer und Funktionen

```c
void logger(char *msg); // Deklaration einer Logging Funktion
void (*out)(char *); // Definition der Variable out als Pointer auf eine Funktion mit einem char *s Parameter und void Return Typ
out = &logger; // out enthält die Adresse auf die logger Funktion
out =  logger; // abgekürzte, übliche Schreibweise, ohne Address-of-Operator

(*out)("Hello"); // Dereferenzieren von out (=logger) und die Funktion aufrufen
  out ("Hello"); // abgekürzte, übliche Schreibweise, ohne Dereferenz-Operator

typedef void (*log_fp_t)(char *); // log_fp_t ist ein Alias auf void (*)(char *)
log_fp_t f = logger; // f ist vom Typ void (*)(char *)
f("Hello"); // Aufruf über die Funktionspointer Variable f
```

#### Arrays und Pointer

-   Zugriffe auf Arrays werden vom Compiler automatisch über die passenden Pointer getätigt.
-   Die Startadresse ist dabei unveränderlich. (Bei Arrayschreibweise `char a[] = "Hello World!";`, nicht aber bei Pointerschreibweise `char *pa = "Hello World!";`)
-   Vergleiche zwischen Array-Variablen sind Vergleiche zwischen den Speicherorten (und nicht des Inhalts).
-   Wenn `p` ein Pointer auf das erste Element des Arrays ist, zeigt `p + 1` auf das zweite Element, unabhängig von deren Grösse. (Wird vom Compiler in `(p + i * sizeof([Element]))` gewandelt.)
-   Zugriffe auf Arrays (`a[n]`) werden vom Compiler in Pointerschreibweise umgewandelt (`* (a + n)`).
-   Das passiert auch bei mehrdimensionalen Arrays (`a[b][c]` entspricht `*(*(a + b) + c)`.

![](./assets/Arrays_vs_Pointer.png)

### Dynamische Allozierung

![](./assets/Übersicht_Speicher.png)

#### Stack

> Mit jedem Funktionsaufruf wird auf dem Stack automatisch Platz für lokale automatische Variablen reserviert

-   Stack-Speicherbedarf ändert sich ständig (mit Funktionsaufrufen)
-   Stack kann überlaufen (grosse Datenmengen nicht auf dem Stack allozieren, Vorsicht bei rekursiven Aufrufen)

#### Heap

-   Für dynamisch allozierten Speicher.
-   Muss händisch genau ein mal mit `free(void *ptr)` freigegeben werden.
-   Nach der Allozierung mit `ptr == NULL` überprüfen, ob Allozierung fehlgeschlagen ist.

```c
// aus stdlib.h
// alloziert "size" Bytes vom Heap und gibt die Start Adresse zurück
void *malloc(size_t size);
// alloziert "nitems" mal "size" Bytes, setzt sie auf 0, und gibt die Adresse zurück
void *calloc(size_t nitems, size_t size);
// vergrössert (oder verkleinert) einen vorgängig angeforderten Speicherbereich
void *realloc(void *ptr, size_t size);
// gibt einen oben angeforderten Speicherbereich frei
void free(void *ptr);
```

Der Zugriff erfolgt über Blöcke der Grösse 2ⁿ (üblich: 2⁹ = 512 bytes). Blöcke sind reine Abstraktion, haben nichts mit Hardware zu tun.

##### `<stdio.h>` (laut C11 Standard)

![](./assets/Übersicht_stdio.png)

##### IO system calls

![](./assets/Übersicht_IO_System_Call.png)

#### Buffering

-   _unbuffered_
    		\- ankommende Daten direkt verschicken
-   _fully-buffered_
    		\- gesammelt, bis Buffer voll ist, dann verschickt
-   _line-buffered_
    		\- gesammelt, bis Buffer voll oder Zeilenende, dann verschickt

##### Standard-Streams

| Stream   | C Standard Library | Kommentar                                                                 |
| -------- | ------------------ | ------------------------------------------------------------------------- |
| `stdin`  | _fully-buffered_   | falls mit interaktivem Device verbunden (z. B. Terminal): _line-buffered_ |
| `stdout` | _fully-buffered_   | falls mit interaktivem Device verbunden (z. B. Terminal): _line-buffered_ |
| `stderr` | _unbuffered_       | auf Linux-System: _unbuffered_                                            |

##### Blocking I/O

Blocking Funktionen (z. B. `getchar()` wartet, bis Input kommt. Wenn das nicht gewünscht ist, wird eine nicht-blocking Funktion aufgerufen und falls kein Wert anliegt, wird `-1` zurückgegeben und `errno` auf `EAGAIN` gesetzt.

### Parallele Programmierung

#### Prozesse vs. Threads – Übersicht

|                                                            | Prozess       | Thread                            |
| ---------------------------------------------------------- | ------------- | --------------------------------- |
| Kontrollfluss/Stack                                        | einer         | separat innerhalb eines Prozesses |
| virtuelles Memory                                          | separat       | geteilt mit Eltern-Prozess        |
| weitere Resourcen (z. B. files)                            | separat       | geteilt mit Eltern-Prozess        |
| Context switch                                             | nötig (teuer) | nicht nötig (billig)              |
| Schutz gegen unautorisierte Memory- und Resourcen-Zugriffe | gegeben       | nicht gegeben                     |
| Erzeugen mit                                               | `fork()`      | `pthread_create()`                |
| Warten auf Kinds-Element                                   | `wait(pid)`   | `pthread_join()`                  |

#### Prozesse

##### Lebenszyklus

![](./assets/Lebenszyklus_Prozess.png)

Spezielle Zustände:

-   `wait()` im Elternprozess bevor Kindsprozess terminiert: Elternprozess blockiert, bis Kindsprozess fertig ist
-   `wait()` im Elternprozess nachdem Kindsprozess terminiert: Kindsprozess bleibt bestehen (als sogenannter _Zombie-Prozess_, Zustand _terminiert_), bis erlöst durch `wait()`
-   Elternprozess terminiert, ohne auf Kindsprozess zu warten: Kindsprozess _verwaist_, wird vom init-Prozess adoptiert und bei der ersten Gelegenheit erlöst durch `wait()`

##### Befehle

-   `fork()`
    		\- dupliziert Elternprozess inkl. allen Ressourcen
    		\- return:
    			\- `< 0`: error, siehe `errno`
    			\- `== 0`: im Kindsprozess
    			\- `> 0`: im Elternprozess, _pid_ des Kindsprozess
-   `exit()`
    		\- terminiert Prozess
    		\- gibt exit-code an `wait()` von Elternprozess
-   `waitpid()`
    		\- nimmt exit-code entgegen (blockierend oder nicht)
-   `wexitstatus()`
    		\- extrahiert exit-code aus return-value von `wait()`
-   `exec()`-Familie
    		\- ersetzt aktuelles Programm komplett durch neues Programm
    		\- `execv(pathToExecutable, [argv])`
-   `system(pathToExecutable)`
    		\- ruft `fork()`, `execv()` und `waitpid()` auf – convenience-Funktion
-   `popen()`
    		\- wie `system()`, erlaubt aber Zugriff auf virtuelles file (named pipe), das den `stdout` des aufgerufenen Prozesses emuliert
    		\- mit `pclose()` wieder schliessen

##### Beispiel

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PERROR_AND_EXIT(M) do { perror(M); exit(EXIT_FAILURE); } while(0)

int main()
{
  pid_t cpid = fork();
  if (cpid == -1) PERROR_AND_EXIT("fork");
  if (cpid > 0) {
    // still in parent process
    printf("Parent: %d forked child %d\n", getpid(), cpid);
    int wstatus;
    pid_t wpid = waitpid(cpid, &wstatus, 0); // wait blocking for child to terminate
    if (wpid == -1) PERROR_AND_EXIT("waitpid");
    printf("Parent: child %d exited with %d (status=0x%x)\n", cpid, WEXITSTATUS(wstatus), wstatus);
    exit(EXIT_SUCCESS);
  } else {
    // in child process
    printf("Child: %d forked by parent %d\n", getpid(), getppid());
    sleep(3);
    exit(123);
  }
}
```

#### Prozessbaum
Beispiele

<table>
<tr>
<td>

```c
int main(void){
  fork();
  fork();
  fork();
  fork();
}
```
</td>
<td>

```c
int main(void){
  fork();
  fork();
  fork();
  pid_t pid = fork();
  if (pid == 0){
    fork();
  }
}
```
</td>
</tr>
<tr>
<td>

```
ProcA3.e─┬─ProcA3.e─┬─ProcA3.e─┬─ProcA3.e───ProcA3.e
         │          │          └─ProcA3.e
         │          ├─ProcA3.e───ProcA3.e
         │          └─ProcA3.e
         ├─ProcA3.e─┬─ProcA3.e───ProcA3.e
         │          └─ProcA3.e
         ├─ProcA3.e───ProcA3.e
         └─ProcA3.e
```
</td>
<td>

```
ProcA3.e─┬─ProcA3.e─┬─ProcA3.e─┬─ProcA3.e───ProcA3.e───ProcA3.e
         │          │          └─ProcA3.e───ProcA3.e
         │          ├─ProcA3.e───ProcA3.e───ProcA3.e
         │          └─ProcA3.e───ProcA3.e
         ├─ProcA3.e─┬─ProcA3.e───ProcA3.e───ProcA3.e
         │          └─ProcA3.e───ProcA3.e
         ├─ProcA3.e───ProcA3.e───ProcA3.e
         └─ProcA3.e───ProcA3.e
```
</td>
</tr>
</table>

#### Threads

##### Lebenszyklus mit join

![](./assets/Lebenszyklus_Thread_join.png)

##### Lebenszyklus mit detach
![](./assets/Lebenszyklus_Thread_detach.png)

##### Befehle

-   `pthread_create()`
    		\- erzeugt Thread
-   `pthread_join()`
    		\- wartet, bis angegebener Thread terminiert
    		\- gibt danach dessen Ressourcen frei
-   `pthread_detach()`
    		\- danach gibt der Thread seine Ressourcen direkt frei, nachdem er fertig gelaufen ist
    		\- kein `pthread_join()` mehr nötig oder möglich
    		\- kein return-value

##### Beispiel

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define PERROR_AND_EXIT(M) do { perror(M); exit(EXIT_FAILURE); } while(0)
#define CHECKED_PTHREAD(C) do { int ret = (C); if (ret) { errno = ret; PERROR_AND_EXIT(#C); } } while(0)

void *worker(void *arg)
{
  printf("worker\n");
  sleep(3);
  static int ret_value = 123;
  return &ret_value;
}

int main() {
  pthread_t thread;
  CHECKED_PTHREAD(pthread_create(&thread, NULL, worker, NULL));
  printf("main\n");
  static void *retval;
  CHECKED_PTHREAD(pthread_join(thread, &retval));
  printf("worker retval = %d\n", *((int*)retval));
  exit(EXIT_SUCCESS);
}
```

### Synchronisation
- Sperren: zeitlcih exklusive Ressourcen garantieren
- Signalisieren: zeitliche Abfolge Warten
- Exklusiver Zugriff: -Entry: wenn gesperrt &rarr; warten, -Exit: freigeben &rarr; nächster Prozess starten
- Problem: Daten werden unkontrolliert bearbeitet: Kontrext-Wechsel kann nicht beeinflusst werden

#### MUTEX
Mutual exclusion
![](/assets/mutex_ablauf.png)
Wann: um verschiedene Zugriffe über crit-sec auf gemeinsamen Daten/Ressourcen zu schützen
Wie:
<br>- init: Verhalten festlegen
<br>- lock: Bereich sperren, sonst in die Warteschlange
<br>- unlock: Bereich freigeben, falls etwas am Warten &rarr; freigeben. Nur im *gleichen* Thread!

#####Problem
- Kostet Zeit und Ressourcen
- Lock-Unlock-Parr fehlerhaft: Unlock durch Fehler nicht ausgeführt oder im falschen Thread
- Rekursion: nur ok im gleichen Threads
- Deadlocks


#### Semaphore
Mutex können auch als Semaphore abgebildet werden.

![](/assets/semaphore_ablauf.png)
Wann: Task über Sync-Punkt vereinbaren
Wie:
<br>- init: Zähler = n, n-Anzahl Tasks passieren zu Beginn.
<br>- wait: Zähler == 0 &rarr; warten, sonst Zähler > 0&rarr; -1 und weiterlaufen
<br>- post: Falls Task am Warten &rarr; freigeben, sonst Zähler + 1

#####Problem
- schlechtere Performance
- Falsche Anwendung
- Rekursion nicht möglich
- Deadlocks

#### Deadlocks
Gegenseitige Blockade von voneinader abhängigen Tasks, sodass keiner mehr was ausführt.
![](/assets/deadlock.png)

##### Livelock
Das System ist nicht im Sinne eines Deadlock blockiert, sondern die Tasks sind so beschäftigt "sich aus dem Weg zu gehen", dass sie keine produktive Arbeit mehr leisten.
##### Starvation
Eine blockierte Task kommt nie an die Reihe, weil andere Tasks sich "vordrängen".
##### Priority Inversion
Eine Task mit tiefer Priorität blocker eine Task mit höherer Priorität.

##### Verhindern
- Vorbeugen und Vermeiden:
	- alle Locks auf Mal und nur wenn alle gleichzeitig erfolgreich
	- globale fixe Lock Reihenfolge einzuhalten
	- Freigabe von Vorgänger-Locks wenn nicht alle Locks erfolgreich
- erkennen und lösen:
	- nur mit OS-Support
	- forcierter Abbruch/Auflösen
- sorgfältige Analyse und Design ist notwendig.


### Inter-Prozess-Kommunikation

#### Struktur

-   unstrukturiert/byte-basiert
    		\- Pipe, Socket, Shared Memory, Shared File
    		\- _everything is a file_ – ein file ist nur ein byte-stream, keine Struktur
-   strukturiert
    		\- Message Queue
    		\- Nur ganze messages

#### Synchronisation

-   implizit synchronisiert
    		\- Message Queue, Pipe, Socket
-   nicht implizit synchronisiert
    		\- Shared Memory, Shared File

#### Blockierend

-   blockierend
    		\- wartet, bis Daten verfügbar oder Zugriff erlaubt
-   nicht-blockierend
    		\- blockiert nicht, Handhabung komplizierter

#### POSIX Signals

-   Jeder Prozess kann jedem anderen Prozess ein Signal senden.
-   Ein Signal ist eine konstante Zahl mit systemweit definierter Bedeutung.
-   Jeder Prozess kann definieren, was bei einem Signal passieren soll:
    		\- Default (Verhalten nach von System vorgegebenem Verhalten
    		\- Ignore
    		\- Handler (custom-Funktion ausführen)

![](./assets/Übersicht_Signale.png)

`SIGKILL` und `SIGSTOP` sind nicht änderbar.

##### Befehle

-   `kill()`
    		\- Um Signal zu senden
-   `pause()`
    		\- warted blockierend, bis Signal empfangen wird
    		\- wenn ein Signal ankommt, passiert folgendes:
    			\- entweder terminiert der Prozess wegen dem Signal, d. h. der Code nach dem `pause()` Aufruf wird nicht mehr ausgeführt
    			\- oder das Signal wird ignoriert, d. h. es weckt den Prozess nicht auf und `pause()` blockiert weiter
    			\- oder der Aufruf gibt den Wert `-1` zurück (mit `errno == EINTR`) wenn die Aktion für das gegebene Signal definiert ist und zurück kommt (d.h. den Prozess nicht terminiert)
-   `WIFEXITED()`, `WEXITSTATUS()`
    		\- fragt den exit code von `wait()` ab
-   `WIFSIGNALED()`, `WTERMSIG()`
    		\- fragt den Signal Wert von `wait()` ab
-   `sigaction()`
    		\- registriert Handler-Funktion
    		\- registriert Signale, die während der Ausführung des Handlers blockiert werden.
    		\- Default-Handles:
    			\- `SIG_IGN`: ignorieren
    			\- `SIG_DFL`: default
    			\- custom handler
-   `sigfillset()`
    		\- als Teil von `struct sigaction` können die Signale angegeben werden, die während der Ausführung des registrierten Handlers blockiert werden
    		\- diese Funktion setzt alle Signale als blockiert
-   `raise()`
    		\- sendet dem eigenen Prozess ein Signal
    		\- entspricht `kill(getpid(), sig)`

##### Handler registrieren

###### Ignore signal
<table>
<tr>
<th>Ignore</th><th> Default action </th> <th> Custom hanlder </th>
</tr>
<tr>
<td>

```c
struct sigaction a = { 0 };
a.sa_flags = 0;
a.sa_handler = SIG_IGN;
sigfillset(&a.sa_mask);
sigaction(sig, &a, NULL);
```
</td>
<td>

```c
struct sigaction a = { 0 };
a.sa_flags = 0;
a.sa_handler = SIG_DFL;
sigfillset(&a.sa_mask);
sigaction(sig, &a, NULL);
```
</td>
<td>

```c
struct sigaction a = { 0 };
a.sa_flags = SA_SIGINFO;
a.sa_sigaction = handler;
sigfillset(&a.sa_mask);
sigaction(sig, &a, NULL);
```
</td>
</tr>
</table>

##### Beispiel

```c
#include <sys/types.h>
#include <signal.h>
...
// tell the child to gracefully terminate, e.g. save unsaved changes and then terminate
if (kill(child_pid, SIGTERM) == -1) PERROR_AND_EXIT("kill(SIGTERM)");
...
```

`kill()` wird für alle Signale verwendet (historisch gewachsen).

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define PERROR_AND_EXIT(M) do { perror(M); exit(EXIT_FAILURE); } while(0)

static pid_t start_child(int wait_for_signal) {
  pid_t cpid = fork();
  if (cpid == -1) PERROR_AND_EXIT("fork");
  if (cpid > 0) return cpid; // the parent returns the child pid
  if (wait_for_signal && pause() == -1) PERROR_AND_EXIT("pause"); // one child waits for a signal
  exit(123); // the child exits normally
}

static void wait_for_child() {
  int wsts;
  pid_t wpid = wait(&wsts); // wait blocking for any child to terminate
  if (wpid == -1) PERROR_AND_EXIT("wait");
  if (WIFEXITED(wsts)) printf("Child %d: exit=%d (status=0x%04X)\n", wpid, WEXITSTATUS(wsts), wsts);
  if (WIFSIGNALED(wsts)) printf("Child %d: signal=%d (status=0x%04X)\n", wpid, WTERMSIG(wsts), wsts);
}

int main() {
  pid_t cpid1 = start_child(0); // start child that exits with exit code
  pid_t cpid2 = start_child(1); // start child that waits for signal to terminate
  printf("Children started: %d (term with exit), %d (term with signal)\n", cpid1, cpid2);
  sleep(1); // let the children start so that both child processes exist
  if (kill(cpid2, SIGTERM) == -1) PERROR_AND_EXIT("kill"); // tell the child to terminate gracefully
  wait_for_child(); // waits blocking until some child terminates
  wait_for_child(); // waits blocking until some child terminates
}
```

---

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define PERROR_AND_EXIT(M) do { perror(M); exit(EXIT_FAILURE); } while(0)

static void handler(int sig, siginfo_t *siginfo, void *context) {
  printf("caught(%d): source=%d, this=%d\n", sig, siginfo->si_pid, getpid());
  raise(SIGTERM); // send SIGTERM to itself (identical to kill(getpid(), SIGTERM))
}

static void set_handler(int sig, void (*handler)(int, siginfo_t *, void *)) {
  struct sigaction a = { 0 };
  a.sa_flags = SA_SIGINFO; // handler variant with additional signal info signature
  a.sa_sigaction = handler; // the handler to be registered
  if (sigfillset(&a.sa_mask) == -1) PERROR_AND_EXIT("sigfillset"); // block all Signals
  if (sigaction(sig, &a, NULL) == -1) PERROR_AND_EXIT("sigaction"); // register handler
}

static pid_t start_child() {
  pid_t cpid = fork();
  if (cpid == -1) PERROR_AND_EXIT("fork");
  if (cpid > 0) return cpid; // parent returns cpid
  set_handler(SIGUSR1, handler); // child...
  if (pause() == -1) PERROR_AND_EXIT("pause");
  exit(EXIT_FAILURE);
}

int main() {
  pid_t cpid = start_child(); // start child that waits for signal to terminate
  printf("parent=%d, child=%d\n", getpid(), cpid);
  sleep(1); // give time to the child to start
  if (kill(cpid, SIGUSR1) == -1) PERROR_AND_EXIT("kill"); // send signal to child
  int ws;
  if (wait(&ws) == -1) PERROR_AND_EXIT("wait");
  if (WIFEXITED(ws)) printf("child exit=%d (status=0x%04X)\n", WEXITSTATUS(ws), ws);
  if (WIFSIGNALED(ws)) printf("child signal=%d (status=0x%04X)\n", WTERMSIG(ws), ws);
}
```
