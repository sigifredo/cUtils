/*
 * gethwaddr.c
 *
 * Demonstrates retrieving hardware address of adapter using ioctl()
 *
 * Author: Ben Menking <bmenking@highstream.net>
 *
 */
/*
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>

int main( int argc, char *argv[] )
{
    int s;
    struct ifreq buffer;

    s = socket(PF_INET, SOCK_DGRAM, 0);

    memset(&buffer, '\0', sizeof(buffer));

    strcpy(buffer.ifr_name, "eth0");

    ioctl(s, SIOCGIFHWADDR, &buffer);

    close(s);

    for( s = 0; s < 6; s++ )
    {
        printf("%.2X ", (unsigned char)buffer.ifr_hwaddr.sa_data[s]);
    }

    printf("\n");

    return 0;
}
*/
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char hwadd[12];
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    strcpy(s.ifr_name, "eth0");
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s))
    {
        int i;

for (i = 0; i < 6; ++i)
{
printf(" %02x", (unsigned char) s.ifr_addr.sa_data[i]);
}

        puts("");

        return 0;
    }

    return 1;
}
