

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define ADD_SIZE	18
#define INTERFACE_NAME	"eth0"

/**
 * \brief Obtenemos la dirección mac del equipo.
 *
 * @param szDir Dirección mac retornada. Es recomendable que el tamaño de este arreglo sea mínimo 18 caracteres.
 *
 * @return Si el proceso se completa de forma satisfactoria retorna 0, de lo contrario retorna -1.
 *
 */
int obtenerDireccionMac(char * szDir);

int main()
{
    char hwaddr[ADD_SIZE];

    if(obtenerDireccionMac(hwaddr) == 0)
        printf("hwaddr: %s\n", hwaddr);
    else
        printf("No se ha podido encontrar la dirección MAC del equipo.\n");

    return 0;
}

int obtenerDireccionMac(char * szDir)
{
    int ret = 0;
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strcpy(s.ifr_name, INTERFACE_NAME);

    if (0 == ioctl(fd, SIOCGIFHWADDR, &s))
    {
        int i;
        char * cpDir = szDir;

        for (i = 0; i < 6; ++i)
        {
            sprintf(cpDir, "%02x", s.ifr_addr.sa_data[i]);
            cpDir[2] = ':';
            cpDir += 3;
        }
        *(--cpDir) = '\0';
    }
    else
        ret = -1;

    close(fd);

    return ret;
}
