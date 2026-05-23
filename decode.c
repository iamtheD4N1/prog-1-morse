#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "debugmalloc.h"

/// @brief Megkeresi egy string morze helyen lévő Fa pointert a bináris fában (rekurzív)
/// @param T Eredetileg a Dekódoló fánk gyökere, újrahivásnál annak gyerekei
/// @param morse A stringként megaadott morze kód, újrahívásnál a string következő eleme
/// @return A megadott morze kódhoz tartózó eleme a fának
static Fa *search(Fa *F, char *morse){
    Fa *value;
    switch (*morse)
    {
    case '.':
        if(F->pointchild == NULL)
            F->pointchild = (Fa*) calloc(1, sizeof(Fa));
        value = search(F->pointchild, morse+1);
        break;
    case '-':
        if(F->linechild == NULL)
            F->linechild = (Fa*) calloc(1, sizeof(Fa));
        value = search(F->linechild, morse+1);
        break;
    default: //peldaul '\0'
        return F;
    }
    return value;
}

/// @brief Hozzáad egy új betű és morze kód párt a Dekódoló fához
/// @param F A Dekódoló fa gyökerének pointere
/// @param letter A hozzáadandó karakter
/// @param morse A hozzáadandó morze kód
/// @return Sikeres volt-e a hozzáadás
static bool add(Fa *F, char letter, char *morse){
    Fa *elem = search(F, morse);
    if(elem->letter){
        printf("Hiba: %s morzekódhoz már van egy társított karakter. Meglévő: %c Új: %c\n", morse, elem->letter, letter);
        return 0;
    }
    elem->letter = letter;
    return true;
}

/// @brief Létrehozza a Dekódoló fát
/// @param T Az adatokat tartalmazó láncolt lista
/// @return A Dekóloló fa gyökerének pointere
static Fa *buildDecodeTree(Adat *T){
    Fa *root = calloc(1, sizeof(Fa));
    while(T != NULL){
        if(!add(root, T->letter, T->morse)){
            printf("Hiba %c karakternél és %s morze kodnál!.\n", T->letter, T->morse);
            return NULL;
        }
        T = T->prev;
    }
    
    return root;
}

/// @brief Ez a Dekódoló fa felszabadításáért felelős rekurzív függvény
/// @param F A Dekódoló fa gyökerének pointere
/// @return Sikeres volt-e a felszabadítás
static bool freeTree(Fa *F){
    if(F == NULL){
        return true;
    }
    else{
        freeTree(F->pointchild);
        freeTree(F->linechild);
        free(F);
        return true;
    }
}

/// @brief Megadja a már beolvasott fileból a leghosszabb morzekód hosszát,
/// @param T A láncolt lista pointere
/// @return A leghosszabb morzekód hossza a láncolt listából
static int getMaxLen(Adat *T){
    int maxlen = 0;
    while(T != NULL){
        if(maxlen < strlen(T->morse))
            maxlen = strlen(T->morse);
        T = T->prev;
    }
    return maxlen;
}

/// @brief A dekódolásért felelős függvény
/// @param T Az adatokat tartalmazó láncolt lista pointere
/// @return Sikeres volt-e a dekódolás
bool doDecode(Adat *T){
    Fa *F = buildDecodeTree(T), *bufferfa;
    if(F != NULL){
        char buffermorse[getMaxLen(T)];
        char enter;
        while(scanf("%s", buffermorse) != EOF){
            switch (buffermorse[0])
            {
            case '/':
                printf(" ");
                break;
            default:
                bufferfa = search(F, buffermorse);
                if(bufferfa->letter == 0)
                    printf("#");
                else
                    printf("%c", bufferfa->letter);
                break;
            }
            scanf("%c", &enter);
            if(enter == '\n')
                printf("\n");
        }
    }
    return freeTree(F);
}