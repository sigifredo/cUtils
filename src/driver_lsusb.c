
#include <stdio.h>
#include <libusb-1.0/libusb.h>

#define IMANUFACTURER		1
#define ID_PRODUCT		0x0006
#define ID_VENDOR		0x0079

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
debug();
        if(verificarDispositivo(list[i]))
        {
debug();
            libusb_device_handle *handle;
debug();
            device = list[i];
debug();

            if(libusb_open(device, &handle))
                return 0;
            else
            {
debug();
                if(libusb_kernel_driver_active(handle, 0) == 1) // si el kernel lo tiene ligado a él
                {
debug();
                    if (libusb_detach_kernel_driver(handle, 0) == 0) // lo desligamos
                    {
debug();
                        // se desliga correctamente
                    }
                    else
                    {
debug();
                        // no se desliga correctamente
                    }
                }
debug();
                if(libusb_claim_interface(handle, 0) < 0)
                {
debug();
                    // no se pudo establecer
                }
                else
                {
debug();
                    // todo bien
                    printf("todo bien!!\n");
                }

debug();
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
        printf("lo encontramos\n");
return 1;
    }
else
return 0;

}

