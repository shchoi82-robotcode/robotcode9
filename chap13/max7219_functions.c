#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "max7219_functions.h"

int fd;

int init_max7219()
{
	if((gpioInitialise()) < 0){
		fprintf(stderr, "gpioInitialise error\n");
		return 0;
	}

    if((fd = spiOpen(SPI_CHANNEL, SPI_BAUD, 0)) < 0){
        fprintf(stderr, "spi_open error\n");
        return 2;
    }

    spi_write_max7219(MAX7219_REG_DECODEMODE,0x00);
    spi_write_max7219(MAX7219_REG_SCANLIMIT,0x07);
    spi_write_max7219(MAX7219_REG_INTENSITY,0x01);
    spi_write_max7219(MAX7219_REG_SHUTDOWN,0x01);
    clear_max7219();
    return 0;
}

void release_max7219()
{
    spiClose(fd);
    gpioTerminate();
}

void spi_write_max7219(uint8_t reg, uint8_t val) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;
    spiWrite(fd, buf, 2);
    usleep(20);
}

void clear_max7219()
{
    uint8_t buf[2];
    for(int i = 0; i < 8; i++){
        buf[0] = i+1;
        buf[1] = 0;
        spi_write_max7219(buf[0], buf[1]);
    }
}

void dot_max7219(int row, int col)
{
    clear_max7219();
    uint8_t buf[2];
    buf[0] = row;
    buf[1] = 1 << (8-col);
    spi_write_max7219(buf[0], buf[1]);

}
