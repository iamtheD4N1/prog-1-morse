#include <stdio.h>
#include "filein.h"
#include "encode.h"
#include "decode.h"
#include "debugmalloc.h"

int main(int argc, char **argv){
    Adat *T = filein();
    if(argc != 2)
        printf("Hiba: A program nem kapott szükséges parancssori kapcsolót!\nHasználja az e (encode) vagy d (decode) kapcsolót a működéshez!\n");
    else{
        switch (*argv[1]){
            case 'e':
                doEncode(T);
                break;
            case 'd':
                doDecode(T);
                break;
            default:
                printf("Hiba: A program nem kapott szükséges parancssori kapcsolót!\nHasználja az e (encode) vagy d (decode) kapcsolót a működéshez!\n");
                break;
        }
    }
    felszabadit(T);

    return 0;
}