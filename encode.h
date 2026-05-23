#ifndef ENCODE_H
#define ENCODE_H
#include <stdbool.h>
#include "filein.h"

/// @brief Az enkódolásért felelős fuggvény
/// @param T Az adatokat tartalmazó láncolt lista pointere
/// @return Sikeres volt-e a enkódolás
bool doEncode(Adat *T);

#endif