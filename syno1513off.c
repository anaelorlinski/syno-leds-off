#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>

// synobios extracted from Synology GPL kernel archive
#include "synobios.h"

// extracted from Synology GPL archive
// file : source/libsynosdk/gpl/synosdk/external.h
#define UART2_CMD_LED_POWER_ON              0x34
#define UART2_CMD_LED_POWER_BLINK           0x35
#define UART2_CMD_LED_POWER_OFF             0x36

#define UART2_CMD_LED_HD_OFF                0x37
#define UART2_CMD_LED_HD_GS                 0x38
#define UART2_CMD_LED_HD_GB                 0x39
#define UART2_CMD_LED_HD_AS                 0x3A
#define UART2_CMD_LED_HD_AB                 0x3B

#define UART2_CMD_LED_USB_ON                0x40
#define UART2_CMD_LED_USB_BLINK             0x41
#define UART2_CMD_LED_USB_OFF               0x42

int main()
{
    int synobios = open("/dev/synobios", O_RDONLY, 0);
    if (synobios == -1) {
        printf("cannot open /dev/synobios\n");
        return 1;
    }

    int i;
    
    // turn on
    for(i=1; i<=5; i++)
    {
        DISKLEDSTATUS s;
        s.status=DISK_LED_ORANGE_SOLID;
        s.diskno=i;
        ioctl(synobios, SYNOIO_SET_DISK_LED, &s);
    }
    
    SYNO_LED off = SYNO_LED_OFF;
    ioctl(synobios, SYNOIO_SET_PWR_LED, &off);	

    char c;
    

    c = UART2_CMD_LED_POWER_ON;   ioctl(synobios, SYNOIO_SET_UART2, &c);
    c = UART2_CMD_LED_HD_GS;      ioctl(synobios, SYNOIO_SET_UART2, &c);
    c = UART2_CMD_LED_USB_ON;     ioctl(synobios, SYNOIO_SET_UART2, &c);

    sleep(1);    

    // turn off
    for(i=1; i<=5; i++)
    {
        DISKLEDSTATUS s;
        s.status=DISK_LED_OFF;
        s.diskno=i;
        ioctl(synobios, SYNOIO_SET_DISK_LED, &s);
    }
    
    c = UART2_CMD_LED_POWER_OFF;   ioctl(synobios, SYNOIO_SET_UART2, &c);
    c = UART2_CMD_LED_HD_OFF;      ioctl(synobios, SYNOIO_SET_UART2, &c);
    c = UART2_CMD_LED_USB_OFF;     ioctl(synobios, SYNOIO_SET_UART2, &c);
 
    close(synobios);
    return 0;
}



