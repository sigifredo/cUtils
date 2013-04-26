
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

#define IMANUFACTURER		0
// Keyboard
#define ID_PRODUCT		0x0103
#define ID_VENDOR		0x04f3
// Mouse
// #define ID_PRODUCT		0x6019
// #define ID_VENDOR		0x17ef
#define ENDPOINT_IN		0x81

#define debug()			printf("%d\n", __LINE__)

libusb_context *ctx = NULL; //a libusb session

ssize_t cnt = 0;
libusb_device **list;
libusb_device *device = NULL;

int verificarDispositivo(libusb_device *device);

int main()
{
    int i;
    int retVal = libusb_init(&ctx);
    cnt = libusb_get_device_list(ctx, &list);

    if(cnt < 0)
        return 0;

    for(i = 0; i < cnt; i++)
    {
        if(verificarDispositivo(list[i]))
        {
            libusb_device_handle *handle;
            device = list[i];

            if(libusb_open(device, &handle))
            {
                perror("No se ha podido abrir el dispositivo.");
                return 0;
            }
            else
            {
                if(libusb_kernel_driver_active(handle, 0) == 1) // si el kernel lo tiene ligado a él
                {
                    if (libusb_detach_kernel_driver(handle, 0) == 0) // lo desligamos
                    {
                        printf("Se desliga el dispositivo del kernel correctamente.\n");
                    }
                    else
                    {
                        perror("No se ha podido desligar el dispositivo del kernel.\n");
                    }
                }

                if(libusb_claim_interface(handle, 0) < 0)
                {
                    perror("No se ha podido ejercer control sobre el dispositivo.");
                }
                else
                {
                    printf("todo bien!!\n");
                    while(1)
                    {
                        int i;
                        int n = 8;
                        char c[n];
                        memset(c, '\0', n);
                        int actual_length;
                        // int r = libusb_interrupt_transfer(handle, ENDPOINT_IN, datos, 8, &actual_length, 0);
                        int r = libusb_bulk_transfer(handle, ENDPOINT_IN, c, n, &actual_length, 0);

                        if(r == LIBUSB_SUCCESS)
                        {
                            for(i = 0; i < 4; ++i)
                                printf("%d", c[i]);
                            puts("");
                            printf("Datos leidos: %s\nactual_length: %d\n\n", c, actual_length);
                        }
                        else
                        {
                            perror("No se han podido leer los datos.");
                            break;
                        }
                    }
                }

                libusb_close(handle);
                libusb_free_device_list(list, 1);
                libusb_exit(ctx);
            }

        }

    }

    return 0;
}


int verificarDispositivo(libusb_device *device)
{
    struct libusb_device_descriptor devDesc;
    libusb_get_device_descriptor(device, &devDesc);

    if(devDesc.iManufacturer == IMANUFACTURER && devDesc.idProduct == ID_PRODUCT && devDesc.idVendor == ID_VENDOR)
    {
        printf("Teclado encontrado.\n");

        return 1;
    }
    else
        return 0;

}

