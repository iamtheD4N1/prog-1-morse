#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filein.h"
#include "debugmalloc.h"

/// @brief Ez egy rekurzívan stringet beólvasó föggvény
/// @param n Első hiívásnál mindig 0. A karaktereket megszámoló változó, a függvény újrahívásához fontos
/// @param f A filera mutató pointer
/// @return A létrejött string pointere
static char *readmorse(int n, FILE *f){
    char input;
    char *s;
    if(fscanf(f, "%c", &input) != EOF && input != '\n')
        s = readmorse(n+1, f);
    else{
        s = (char*) malloc(n+1);
        input = '\0';
    }
    s[n] = input;
    return s;

}

/// @brief Létrehoz egy láncolt listát a .txt fileból beolvasva
/// @param f A filera mutató pointer
/// @return A láncolt lista vége (a láncolt lista fordított a filehoz képest)
static Adat *construct(FILE *f){
    Adat *prev = NULL;
    char bufferletter;
    while(fscanf(f, "%c ", &bufferletter) == 1){ //EOF-nál nem olvas tovább
        Adat *uj = (Adat*) malloc(sizeof(Adat));
        uj->letter = bufferletter;
        uj->morse = readmorse(0, f);
        uj->prev = prev;
        prev = uj;
    }
    return prev;
}

/// @brief Megnyitja és beolvassa a morseabc.txt filet, amiben az abc található
/// @return A beolvasott adatok listájának pointere
Adat *filein(){
    FILE *f = fopen("morseabc.txt","r");
    if(f == NULL) {
        printf("Nem sikerült a filet megnyitni.\n");
        return NULL;
    }
    else{
        Adat *T = construct(f);
        fclose(f);
        return T;
    }
}

/// @brief Felszabadítja a dinamikusan lefoglalt beolvasáshoz szükséges láncolt listát
/// @param t A láncolt lista pointere
/// @return Sikieres volt-e a felszabadítás
bool felszabadit(Adat *t){
    while(t != NULL){
        Adat *p = t;
        t = t->prev;
        free(p->morse);
        free(p);
    }
    free(t);
    return true;
}

/// @brief Megvizsgálha egy morze kódról hogy csak '.'-ból és '-'-ből áll
/// @param s A vizsgálandó morze kód pointere
/// @return Helyes-e a vizsgált morze kód
bool checkMorse(char *s){
    int i = 0;
    while(s[i] != '\0'){
        if(s[i] != '.' && s[i] != '-')
            return false;
        i++;
    }
    return true;
}