#include <bcm2835.h>
#include <stdio.h>

#define GPIO_PINNO 13

int main(int argc, char *argv[])
{
    if (!bcm2835_init())
        return 1;
    bcm2835_gpio_fsel(GPIO_PINNO, BCM2835_GPIO_FSEL_OUTP);

    while(1) {
        bcm2835_gpio_write(GPIO_PINNO, HIGH);
        bcm2835_gpio_write(GPIO_PINNO, LOW);
    }
    bcm2835_close();
    return 0;
}

