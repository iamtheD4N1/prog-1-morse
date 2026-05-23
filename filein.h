#ifndef FILEIN_H
#define FILEIN_H
#include <stdbool.h>

/// @brief A fileban szereplő adatok beolvasásához és láncolt listás tárolásához szükséges adattípus
typedef struct Adat{
    char letter;
    char *morse;
    struct Adat *prev;
} Adat;

/// @brief Megnyitja és beolvassa a morseabc.txt filet, amiben az abc található
/// @return A beolvasott adatok listájának pointere
Adat *filein();

/// @brief Felszabadítja a dinamikusan lefoglalt beolvasáshoz szükséges láncolt listát
/// @param t A láncolt lista pointere
/// @return Sikeres volt-e a felszabadítás
bool felszabadit(Adat *t);

/// @brief Megvizsgálja egy morze kódról hogy csak '.'-ból és '-'-ből áll
/// @param s A vizsgálandó morze kód pointere
/// @return Helyes-e a vizsgált morze kód
bool checkMorse(char *s);

#endif