#include <bcm2835.h>
#include <stdio.h>
#define PIN 17
int main(void)
{
	if (!bcm2835_init())
		return 1;
	
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
	
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);
	
    while (1)
	{
		// Read some data
		uint8_t value = bcm2835_gpio_lev(PIN);
		printf("read from pin 17: %d\n", value);

		// wait a bit
		delay(100);
	}
	bcm2835_close();
	return 0;
}
