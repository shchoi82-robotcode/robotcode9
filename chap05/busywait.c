#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define GPIO_PINNO 13

int main(int argc, char *argv[])
{
    volatile int i;
    int n;
    if (!bcm2835_init())
        return 1;
    bcm2835_gpio_fsel(GPIO_PINNO, BCM2835_GPIO_FSEL_OUTP);

    n = 755555;
    for(;;) {
        for(i = 0 ; i < n ; i++) {};
        bcm2835_gpio_write(GPIO_PINNO, HIGH);
        for(i = 0 ; i < n ; i++) {};
        bcm2835_gpio_write(GPIO_PINNO, LOW);
    }
    bcm2835_close();
    return 0;
}

