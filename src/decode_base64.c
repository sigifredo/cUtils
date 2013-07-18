
/**
 * Código para decodificar una cadena en base64.
 *
 * @author Sigifredo Escobar Gómez <sigifredo89@gmail.com>
 * @version 2013-07-17
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ctoi(int c)
{
    if (c == '=')
        return 0;
    if (c <= '9')
        return c + 4;
    else if (c <= 'Z')
        return c - 65;
    else
        return c - 71;
}

void decode_base64(char * str_in, char **str_out)
{
    int i, j, b;
    int len_i = (strlen(str_in));

    char * str_t = (char *) malloc((len_i*4)/3);
    char * str_in_cp = (char *) malloc(len_i);

    strcpy(str_in_cp, str_in);

    for(i = 0; i < len_i; i++)
        str_in_cp[i] = ctoi(str_in_cp[i]);

    for(i = 0, j = 0; i < len_i; i+=4, j+=3)
    {
        b = (str_in_cp[i] << 18) | (str_in_cp[i+1] << 12) | (str_in_cp[i+2] << 6) | str_in_cp[i+3];
        str_t[j] = b >> 16 & 0xff;
        str_t[j+1] = b >> 8 & 0xff;
        str_t[j+2] = b & 0xff;
    }

    free(str_in_cp);
    *str_out = str_t;
}

int main(int argc, char **argv)
{
    if (argc < 2) return;

    char * str_out = NULL;

    decode_base64(argv[1], &str_out);

    printf("base64: %s\n", str_out);

    if (str_out)
        free(str_out);
}

