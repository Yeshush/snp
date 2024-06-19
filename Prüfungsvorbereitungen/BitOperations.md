# Bitoperationen

### AND
Kann benutzt werden um Bits zu löschen


### OR
Kann benutz werden um Bitz zu setzen.

### XOR
Kann benutzt werden um Bits zu toggeln oder Werte zu tauschen

## Bit löschen / setzen
Manipulationen von einzelnen Bits gehören zu den Basis Operationen und dienen als Grundlagen um weitere komplexere Konstrukte zu schaffen. 

Verfollständigen sie folgendes Beispiel mit den drei Basis Operationen. Dabei gibt die Variable `bit` an, welches Bit manipuliert werden soll (Denken sie daran, dass die Bit-Positionen bei 0 beginnen. Bit 3 ist also das vierte Bit von rechts). Bei den gefragten Manipulationen, soll nur das angegebene `bit` geändert werden und der Rest soll unverändert bleiben:

- Bit 3 setzen: `0011 => 1011`
- Bit 1 löschen: `1011 => 1001`
- Bit 0 flippen: `1001 => 1000`

```c
#include <stdlib.h>
#include <stdio.h>

int main() {
  unsigned int number = 0x75;
  unsigned int bit = 3; // bit at position 3

  unsigned int shiftedBit = 0x01<<bit
  // Setting a bit
  number = number | shiftedBit;
  
  // Clearing a bit
  bit = 1;
  number = number & ~0x01<<bit;
  
  // Toggling a bit
  bit = 0;
  number = number ^ 0x01<<bit;

  printf("number = 0x%02X\n", number);
  
  return EXIT_SUCCESS;
}
```

## Werte tauschen
Werte werden durch allein durch Bitoperationen vertauscht ohne Hilfsvariable.

```c
#include <stdlib.h>
#include <stdio.h>


int main(){
  int a = 3;
  int b = 4;
  printf("a: %d; b: %d\n", a, b);
  
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;

  printf("a: %d; b: %d\n", a, b);
  return EXIT_SUCCESS;
}
```

## 4. Prüfen auf 2-er Potenz
Um eine gegebene Zahl zu prüfen ob sie eine 2er Potenz ist, können wir folgende Bit-Muster vergleichen:

Beispiel mit der Zahl 8: `1000 & 0111 == 0`. Wir prüfen also, ob die gegebene Zahl 8 (`1000`) nur ein Bit auf `1` hat und den Rest auf `0`.

Überlegen Sie sich einen Algorithmus um dies für beliebige positive Zahlen zu prüfen. Das Bitmuster, dass für die `&` Operation gebraucht wird, kann mittel Subtraktion von 1 berechnet werden (`1000 - 1 = 0111`):
```c
#include <stdio.h>
#include <stdlib.h>

int main(){
  int a = 32; // any positive number

  if(a > 0 && ((a & (a-1)) == 0) ){
    printf("%d is a power of 2", a);
  }
  return EXIT_SUCCESS;
}
```