#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "encode.h"
#include "debugmalloc.h"

/// @brief Enkódoláshoz szükséges tömböt hozza létre a láncolt listából
/// @param T A láncolt lista pointere
/// @return A dekódoló tömb pointere
static char **buildEncodeArray(Adat *T){ //A tömb elemei stringekre mutató pointerek
    char **EncodeArray = (char**) calloc(__SCHAR_MAX__+1, sizeof(char*));
    while(T != NULL){
        if(EncodeArray[T->letter] != NULL){
            printf("Hiba: Kétszer szerepel a(z) '%c' betű!\n", T->letter);
            return NULL;
        }
        else{
            if(checkMorse(T->morse)){
                EncodeArray[T->letter] = T->morse; //sikeres értékadás
                //printf("%d indexnél %c: %s\n", T->letter, T->letter, T->morse);
            }
            else{
                printf("Hiba: '%c' betűnél hibás a %s morze kód!\n", T->letter, T->morse);
                return NULL;
            }
        }
        T = T->prev;
    }

    return EncodeArray;
}

/// @brief Az enkódolásért felelős fuggvény
/// @param T Az adatokat tartalmazó láncolt lista pointere
/// @return Sikeres volt-e a enkódolás
bool doEncode(Adat *T){
    char **A = buildEncodeArray(T);
    char buffer;
    while(scanf("%c", &buffer) != EOF){
        if(A[toupper(buffer)] != NULL)
            printf("%s ", A[toupper(buffer)]);
        else{
        switch (buffer){
            case ' ':
                printf("/ ");
                break;
            case '\n':
                printf("\n");
                break;
            default:
                printf("# ");
                break;
            }
        }
    }
    free(A);
    
    return true;
}