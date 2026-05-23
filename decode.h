#ifndef DECODE_H
#define DECODE_H
#include <stdbool.h>
#include "filein.h"

/// @brief Egy bináris fát reprezentáló struktúra, 
///        áll az elem 2 gyerekének a pointeréből, és egy karakterből, ami a dekódolás eredménye
typedef struct Fa{
    char letter;
    struct Fa *pointchild, *linechild;
} Fa;

/// @brief A dekódolásért felelős függvény
/// @param T Az adatokat tartalmazó láncolt lista pointere
/// @return Sikeres volt-e a dekódolás
bool doDecode(Adat *T);

#endif