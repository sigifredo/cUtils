
/**
 * Código para codificar una cadeba en base64. 
 *
 * @author Sigifredo Escobar Gómez <sigifredo89@gmail.com>
 * @version 2013-07-17
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void base64(char * str_in, char **str_out)
{
    int i, j, b;
    int len_i = strlen(str_in);
    int len_o;
    char * str_b;
    char ind_b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz"
                     "0123456789+/";

    if ((len_i%3) != 0)
        str_b = (char*) malloc((((len_i/3) + 1) * 4) + 1);
    else
        str_b = (char*) malloc(((len_i/3) * 4) + 1);

    if(str_b == NULL)
        return;

    for(i = 0, j = 0; i <= len_i-3; i+=3, j+=4)
    {
        b = (str_in[i] << 16) | (str_in[i+1] << 8) | str_in[i+2];

        str_b[j] = ind_b64[b >> 18 & 63];
        str_b[j+1] = ind_b64[b >> 12 & 63];
        str_b[j+2] = ind_b64[b >> 6 & 63];
        str_b[j+3] = ind_b64[b & 63];
    }

    if (i != len_i)
    {
        b = (str_in[i] << 16);

        if ((len_i - i) == 2)
        {
            b = b | (str_in[i+1] << 8);
            str_b[j+2] = ind_b64[b >> 6 & 63];
        }
        else
            str_b[j+2] = '=';

        str_b[j] = ind_b64[b >> 18 & 63];
        str_b[j+1] = ind_b64[b >> 12 & 63];
        str_b[j+3] = '=';
    }

    *str_out = str_b;
}

int main(int argc, char **argv)
{
    if (argc < 2) return;

    char str_in[] = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    char * str_out = NULL;

    base64(str_in, &str_out);

    printf("base64: %s\n", str_out);

    if (str_out)
        free(str_out);
}

