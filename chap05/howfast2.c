#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define GPIO_PINNO 13

int main(int argc, char *argv[])
{
    if (!bcm2835_init())
        return 1;
    bcm2835_gpio_fsel(GPIO_PINNO, BCM2835_GPIO_FSEL_OUTP);

    while(1) {
        bcm2835_gpio_write(GPIO_PINNO, HIGH);
        usleep(50);
        bcm2835_gpio_write(GPIO_PINNO, LOW);
        usleep(50);
    }
    bcm2835_close();
    return 0;
}

