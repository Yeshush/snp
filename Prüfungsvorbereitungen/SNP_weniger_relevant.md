## Einführung

![](./assets/Übersicht_SNP.png)

![](./assets/Übersicht_Hardware.png)

### User-/Kernel-Mode

![](./assets/Übersicht_User_Kernel_Mode.png)

Ein Programm, das im User-Mode läuft, kann einen Syscall aufrufen, um auf Hardware zuzugreifen etc. Dabei geschieht potentiell ein Mode Switch zum Kernel-Mode (CPU pausiert Ausführung, switcht, führt speziellen Befehl aus, switcht zurück, macht weiter mit dem normalen Programm). Syscalls sind Betriebssystem-abhängig und nehmen als Argument einen `long` entgegen, der der passenden Funktion entspricht. Um unabhängig vom Betriebssystem zu programmieren, können Wrapper-Funktionen der System-Library aufgerufen werden. Diese wurde in _POSIX_ standardisiert.

#### Standard-IO:

-   **stdin**: Eingabe von Tastatur, filedeskriptor 0
-   **stdout**: Ausgabe von normalen Meldungen auf Terminal, filedeskriptor 1
-   **stderr**: Ausgabe von Fehlern auf Terminal, filedeskriptor 2

#### Umleitung:

-   `[…] < file`: **stdin** aus file
-   `[…] > file`: überschreibt file mit **stdout**
-   `[…] 1> file`: wie oben
-   `[…] >> file`: hängt **stdout** an file an
-   `[…] 2> file`: überschreibt file mit **stderr**
-   `[…] >& file`: kombiniert **stdout** und **stderr**
-   `[Kommando 1] | [Kommando 2]`: speist **stdin** eines Kommandos in **stdin** des nächsten

#### Verkettung:

-   `[Kommando 1]; [Kommando 2]`: sobald erstes Komando fertig ist, wird zweites gestartet
-   `[Kommando 1] && [Kommando 2]`: zweites Kommando wird nur gestartet, wenn erstes _exit code_ `0` hat
-   `[Kommando 1] || [Kommando 2]`: zweites Kommando wird nur gestartet, wenn erstes **nicht** _exit code_ `0` hat
-   `[Kommando] &`: führt Kommando im Hintergrund aus und kehrt sofort zurück

## C


### Präprozessor, Compiler, Linker

![](./assets/Ablauf_Kompilierung.png)

#### Präprozessor
Führt Text-Ersetzungen im Quellcode durch.
Aufgaben:

- Text aus anderen Dateien in den Quelltext einbinden (`#include`)
- Mit `#define` definierte Konstanten durch die entsprechenden Werte ersetzen.
- Nach Bedingungen Teile des Quellcodes ein-/ausschliessen (`#if`, `#elif`, `#else`, `#endif`, `#ifdef`, `#ifndef`)

Weitere Details:

- Befehle beginnen mit `#`
- `gcc -E` führt nur Präprozessor aus
- `#include`s:
	- `#include <filename>` für Headerdateien der Compiler Installation
	- `#include "filename"` für selbst generierte Headerdateien
- `#define` ersetzt alle Vorkommnisse der Konstanten mit dem Wert
- `#undef` macht Definition einer Konstante rückgängig

##### Include Guards
Verhindern mehrfache Definition von Typen durch indirekte `#include`s.

```c
#ifndef HEADER_KENNUNG
#define HEADER_KENNUNG
[Header-Inhalt]
#endif
```

#### Compiler
Wandelt Quellcode in Objektdateien um. Objektcode: Maschineninstruktionen mit offenen Aufrufen.

Aufgaben:

- Syntax-Check
- statische Typ-Prüfung
- Errors/Warnungen ausgeben
- wenn keine Errors auftreten: Objektcode erzeugen (macht aus `*.c` `*.o`)


##### Objektdateien
Objektdateien (`.o`) beinhalten:

- generierten Maschinencode
- Liste der externen/importierten Symbole, die noch gelinkt werden müssen
- weitere Informationen (Debug-Daten, Sektionsgrössen, etc.)
- potentiell offene Aufrufe
	- Funktionen, die in einer anderen Quellcodedatei definiert sind
	- globale Variablen einer anderen Quellcodedatei

#### Linker
Verbindet die noch offenen Aufrufe in Objektdateien und generiert ein ausführbares Programm.

Aufgaben:

- Überprüft, ob verwendete Funktionen in anderen Objektdateien oder Libraries wirklich vorhanden sind
- Überprüft, ob `extern` deklarierte Variablen definiert sind
- Verlinkt die offenen Aufrufe zu einem ausführbaren Programm


#### Sicheres Programmieren

![](./assets/Übersicht_Sicheres_Programmieren.png)



## Systemnahe Programmierung
### Syscall
- Programme laufen normalerweise im User-Mode.
- Gewisse Funktionalität kann nur aus Kernel-Mode geboten werden.
- `syscall(long number, ...)` führt Mode-Switch und Aufruf abhängig von der angegebenen Nummer aus.
- Alternativ gibt es dafür Wrapper-Funktionen
- `syscall` gibt im Fehlerfall `-1` zurück und setzt die globale Variable `errno` auf den zum Error passenden Wert. Wrapper-Funktionen geben i. d. R. denselben Wert wie `syscall` zurück.

### Isolation
- privater Speicher pro Applikation, kein Zugriff auf fremden Speicher
- Jeder Applikation wird vorgegaukelt, ihr Memory beginne mit Adresse `0`.
- Die *Memory Management Unit (MMU)*
	- übersetzt virtuelle Adressen in physikalische.
	- lagert Memory auf Massenspeicher aus, falls nötig (swap).
	- Enthält *Memory Protection Unit (MPU)*, die unerlaubte Speicherzugriffe überwacht.

### Standards
- C ist
	- *Source* kompatibel: Sprach-Elemente, C Standard Library (Teil des C-Standards)
	- *Binary* kompatibel: Binaries auf derselben Architektur austauschbar
- *POSIX*: definiert u. a. C API auf UNIX-ähnlichen Betriebssystemen
- *FHS*: definiert auf UNIX-ähnlichen Betriebssystemen die Filesystem-Hirarchie
- C-Standards
	- GCC kennt: C90 Standard, C99 Standard, C11 Standard, GNU C11 Dialekt
	- Meist rückwärtskompatibel, geringe Features hinzugefügt

![](./assets/Übersicht_Standards.png)



### Filesystem
- *FHS* definiert Struktur:
	- `/bin` – grundlegende Systembefehle (für alle Benutzer)
	- `/boot` – statische Dateien des Bootloaders
	- `/dev` – Gerätedateien
	- `/etc` – spezifische Konfigurationsdateien
	- `/home` – Benutzerverzeichnisse, optional
	- `/lib` – Kernel-Module und dynamische Bibliotheken
	- `/media` – Einhängepunkte für Wechseldatenträger
	- `/mnt` – temporäre Einhängepunkte für Dateisysteme
	- `/opt` – zusätzliche Softwarepakete
	- `/root` – Benutzerverzeichnis für Benutzer root, optional
	- `/run` - Daten für laufende Prozesse (ersetzt /var/run)
	- `/sbin` – wichtige Systembefehle
	- `/srv` – Daten, die von Diensten angeboten werden
	- `/tmp` – temporäre Dateien
	- `/usr` - bin, include, lib, local, sbin, share, games, src, ... (steht für *Unix System Resources*, nicht für *User*)
	- `/var` - cache, lib, local, lock, log, opt, run, spool, tmp, ...

#### Interaktion
- *Everything is a file* – Philosophie um auf alles zuzugreiffen: Mäuse, Tastaturen, etc.
- Um ein mit einem file zu interagieren:
	1. File öffnen
	1. File lesen/schreiben
	1. File schliessen
- Geöffnete Files werden anhand eines *file descriptor*s (häufig abgekürzt `fd`), einer ID (Format: `int`) verwaltet.
	- gültig, solange file geöffnet.
	- in system calls verwendet
- Wenn file geöffnet ist
	- byte-stream, kann gelesen oder geschrieben (überschrieben, einfügen nicht möglich) werden
	- globale file-position, die beliebig gesetzt werden kann (am Anfang: `0`)
	- file kann verlängert (mit `0` gefüllt) oder trunkiert werden
	- file kann erneut geöffnet werden -> neuer *file descriptor*
	- mehrere Prozesse können selben *file descriptor* haben

#### *Inode*
- Verwaltungseinheit eines files
- assoziiert mit *ino*-Nummer (eindeutig im filesystem)
- vom Kernel verwaltet
- beinhaltet Informationen über file
	- letzter Zugriff
	- owner
	- size
	- physikalischer Ort auf Datenträger
	- Anzahl Hardlinks
	- **nicht:** File-Name
- Directory: file mit Namen-zu-*ino*-Paaren
- Links
	- (Hard-)Link:
		- Name-zu-*ino*-Paar
		- Anzahl in *Inode* gespeichert
		- nur innerhalb eines filesystems
		- `ln file hard-link-name`
	- Sym(bolischer )link:
		- Spezielles file mit einem Pfad auf ein anderes File
		- Auch über verschiedene filesystems möglich
		- `ln -s file sym-link-name`

#### Spezielle Files
##### Device files
Die Device-Files liegen in `/dev`. Sie sind Kernel-Objekte, die in der Regel mit Hardware kommunizieren, z. B. Gerätetreiber etc.:

- Character Devices: Zugriff auf Sequenz von Bytes, z. B. Tastatur
- Block Devices: Zugriff in Arrays von Bytes, z. B. Massenspeicher

##### Filesysteme
Andere Filesysteme (USB-Sticks, etc.) können eingebunden werden, sie werden an einer leeren Directory "angebracht" (typischerweise `/mnt`, `/media`).

Virtuelle Filesysteme existieren nur im Memory und geben z. B. den Kernel Status wieder:
- `/proc` – prozessrelevante Daten
- `/sys` – nicht-prozessrelevante Daten des Kernels
- `/dev` – Hardware-bezogene device files (+ virtuelle files wie `/dev/null`)



#### POSIX Pipe
##### Anonymous pipe
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PERROR_AND_EXIT(M) do { perror(M); exit(EXIT_FAILURE); } while(0)
#define MESSAGE "blocking pipe example message...\n"
#define MSIZE 10

int main() {
  int fd[2];
  if (pipe(fd) == -1) PERROR_AND_EXIT("pipe");
  pid_t cpid = fork();
  if (cpid == -1) PERROR_AND_EXIT("fork");
  if (cpid > 0) { // still in parent process: read from pipe
    if (close(fd[1]) == -1) PERROR_AND_EXIT("close");
    int n;
    do {
      char msg[MSIZE];
      n = read(fd[0], msg, MSIZE);
      if (n == -1) PERROR_AND_EXIT("read");
      write(STDOUT_FILENO, msg, n);
    } while (n > 0);
    if (close(fd[0]) == -1) PERROR_AND_EXIT("close");
    if (wait(NULL) == -1) PERROR_AND_EXIT("wait");
  } else { // in child process: write to pipe
    if (close(fd[0]) == -1) PERROR_AND_EXIT("close");
    if (write(fd[1], MESSAGE, sizeof(MESSAGE)) == -1) PERROR_AND_EXIT("write");
  }
}
```

- `pipe()`
	- öffnet ein Paar von assoziierten *File Deskriptoren*
	- nur benutzbar, wenn nachher der Prozess geteilt wird
	- für bidirektionale Kommunikation sind zwei Pipes nötig
- `close()`
	- schliesst *File Deskriptoren*
- `read()`
	- liest (blockierend) von der Pipe
- `write()`
	- schreibt (blockierend) auf die Pipe

##### Named pipe
- Spezielles FIFO file

###### Von der Shell
- kreieren: `mkfifo pfad –m Zugriffsmodus`
- schreiben/lesen: normales file I/O, blockiert bis beidseitig geöffnet
- löschen: wie reguläres file

###### Aus dem Code
Kreieren:

```c
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
```

Zugriff: file I/O wie auf reguläres File, inkl. löschen (`unlink`)

#### POSIX Message Queue
- Abfragen des Zustandes möglich (leer? Asynchrone Benachrichtigung, sobald Message anliegt, anfordern)
- Maximale Kapazität: (max. Anzahl Nachrichten) \* (maximale Grösse einer Nachricht)
- Mehrere Leser/Schreiber
- Lesen entfernt Nachricht aus der Queue

```c
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define PERROR_AND_EXIT(M) do { perror(M); exit(EXIT_FAILURE); } while(0)
#define QNAME "/demo" // the name must start on a slash
#define MSIZE 10

int main() {
  int q = 0, cpid = 0, n = 0, wpid = 0;
  struct mq_attr a = { .mq_maxmsg = 10, .mq_msgsize = MSIZE };
  if ((q = mq_open(QNAME, O_CREAT|O_RDWR|O_NONBLOCK|O_EXCL, 0666, &a)) == -1) PERROR_AND_EXIT("mq_open");
  if ((cpid = fork()) == -1) PERROR_AND_EXIT("fork");
  if (cpid > 0) { // parent: shares queue descriptor with child
    if (mq_unlink(QNAME) == -1) PERROR_AND_EXIT("mq_unlink"); // remove it from the filesystem again
    char msg[MSIZE+1]; // buffer allows for final '\0' to allow interpretation as string
    while(wpid == 0) { // read messages while the child process has not yet terminated
      sleep(1); // poll interval for non-blocking mq_receive() and non-blocking waitpid()
      while ((n = mq_receive(q, msg, MSIZE, NULL)) > 0) { // read while there are messages
        msg[n] = '\0'; // prepare for printf
        printf("Message: '%s'\n", msg);
      }
      if (n == -1 && errno != EAGAIN) PERROR_AND_EXIT("mq_receive"); // non-blocking read handling
      if ((wpid = waitpid(cpid, NULL, WNOHANG)) == -1) PERROR_AND_EXIT("waitpid"); // non-blocking
    }
    if (mq_close(q) == -1) PERROR_AND_EXIT("mq_close"); // close when completed
  } else { // child: shares queue descriptor with parent
    if (mq_send(q, "Hello", sizeof("Hello"), 1) == -1) PERROR_AND_EXIT("mq_send");
    sleep(2);
    if (mq_send(q, "Queue", sizeof("Queue"), 1) == -1) PERROR_AND_EXIT("mq_send");
  }
}
```

- `mq_open()`
	- kreiert Message Queue mit gegebenen Dimensionen und Zugriffsrechten
	- Message Queue existiert auf virtuellem filesystem unter `/dev/mqueue`
	- **Linux**: Der *Queue Deskriptor* vom Typ `mqd_t` ist ein *File Deskriptor*
- `mq_close()`
	- teilt Kernel mit, dass Zugriffe abgeschlossen sind
- `mq_unlink()`
	- löscht die Queue auf dem filesystem
	- kann unmittelbar nach dem Öffnen aufgerufen werden, da der Kernel die geöffnete Queue bis zum Schliessen derselben im Memory aktiv behält
	- typischerweise im Zusammenhang mit «temporären» Queues und im Zusammenhang mit der `mq_open` Flag Maske `O_EXCL` (exklusiv)
- `mq_reeceive()`
	- liest eine Message von der Queue
	- `mq_open`-flags definieren ob blockierend oder nicht
- `mq_send()`
	- schreibt Message in die Queue
	- jede Message bekommt Priorität (hohe Zahl = hohe Priorität). Einreihung nach allen Messages mit hörerer/gleicher Priorität
- `mq_getattr()`
	- gibt Meta-Informationen zurück (z. B. Anzahl anliegender Nachrichten)
- `mq_notify()`
	- registriert, wie ein Prozess benachrichtigt werden will, sobald eine Message anliegt (nur bei non-blocking, nur ein Prozess kann sich registrieren)

#### POSIX Socket
- virtueller Stecker, definiert durch IP-Adresse plus Port-Nummer
- erlaubt Kommunikation über Netzwerk (TCP, UDP, etc.)
- auch zwischen Prozessen auf demselben Rechner möglich
- Ein *Socket Deskriptor* ist eine *File Deskriptor*

##### Verbindungsorientiert
- Client
	- Socketdefinition (`getaddrinfo()`, `socket()`)
	- Verbindungsanfrage an einen Server (`connect()`)
	- bidirektionales Lesen/Schreiben (`read()`, `write()`, `recv()`, `send()`)
	- danach Socket schliessen (`close()`)
- Server
	- Socketdefinition (`getaddrinfo()`, `socket()`, `bind()`)
	- abwarten von Verbindungsanfragen (`listen()`)
	- akzeptiert eine Anfrage (`accept()`)
	- bidirektionales Lesen/Schreiben (`read()`, `write()`, `recv()`, `send()`)
	- danach eventuell Socket schliessen (`close()`)

##### Verbindungslos
- Client
	- Socketdefinition (`getaddrinfo()`, `socket()`)
	- **keine** Verbindungsanfrage
	- bidirektionales Lesen/Schreiben (`recfrom()`, `sendto()`)
	- danach Socket schliessen (`close()`)
- Server
	- Socketdefinition (`getaddrinfo()`, `socket()`, `bind()`)
	- **kein** Abwarten und Akzeptieren von Verbindungsanfragen
	- bidirektionales Lesen/Schreiben (`recfrom()`, `sendto()`)
	- danach eventuell Socket schliessen (`close()`)

##### Beispiel
*defs.h*

```c
#ifndef _DEFS_H_
#define _DEFS_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define SRV_SOCK "/tmp/my-server-socket.sock" #define CLI_SOCK "/tmp/my-client-socket.sock" #define BUFFER_SIZE 8192
#define ERR() do { perror(""); exit(1); } while(0) #endif // _DEFS_H_
```

*server.c*

```c
#include "defs.h"
int main(int argc, const char* argv[])
{
  // server: connection-less UNIX socket
  int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (fd < 0) ERR();
  struct sockaddr_un a = { AF_UNIX, SRV_SOCK };
  unlink(SRV_SOCK);
  if (bind(fd, (void*)&a, sizeof(a)) < 0) ERR();
  while(1) {
    char buf[BUFFER_SIZE] = { 0 };
    struct sockaddr_un client = { 0 };
    socklen_t client_len = sizeof(client);
    int n = recvfrom(fd, buf, sizeof(buf), 0, (void*)&client, &client_len);
    if (n < 0) ERR();
    if (n > 0) printf("%s\n", buf);
  }
}
```

*client.c*

```c
#include "defs.h"
int main(int argc, const char* argv[])
{
  // client: connection-less UNIX socket
  int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (fd < 0) ERR();
  struct sockaddr_un a = { AF_UNIX, CLI_SOCK };
  unlink(CLI_SOCK);
  if (bind(fd, (void*)&a, sizeof(a)) < 0) ERR();
  for(int i = 1; i < argc; i++) {
    const char *p = argv[i];
    int len = strlen(p)+1;
    struct sockaddr_un s = { AF_UNIX, SRV_SOCK };
    int n = sendto(fd, p, len, 0, (void*)&s, sizeof(s));
    if (n < 0) ERR();
  }
  close(fd);
  unlink(CLIENT);
}
```
