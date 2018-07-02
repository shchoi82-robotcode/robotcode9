#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#pragma GCC diagnostic ignored "-Wint-conversion"

#define BUFFER_MAX 50
#define GPIO_PINNO 13

FILE *fd[32] = {};

int openGPIO(int pin, int direction);
int writeGPIO(int gpio, int value);
int readGPIO(int gpio);

int main(int argc, char** argv) 
{
    openGPIO(GPIO_PINNO, 1);
    for (;;) {
        writeGPIO(GPIO_PINNO, 1);
        sleep(1);
        writeGPIO(GPIO_PINNO, 0);
        sleep(1);
    }
    return 0;
}

int writeGPIO(int gpio, int b) 
{
    if (b == 0) {
        write(fd[gpio], "0", 1);
    } else {
        write(fd[gpio], "1", 1);
    }

    lseek(fd[gpio], 0, SEEK_SET);
    return 0;
}

int readGPIO(int gpio) 
{
    char value_str[3];
    int c = read(fd[gpio], value_str, 3);
    lseek(fd[gpio], 0, SEEK_SET);

    if (value_str[0] == '0') {
        return 0;
    } else {
        return 1;
    }
}

int openGPIO(int gpio, int direction) 
{
    if (gpio < 0 || gpio > 31) return -1;
    if (direction < 0 || direction > 1)return -2;

    int len;
    char buf[BUFFER_MAX];

    if (fd[gpio] != NULL) {
        close(fd[gpio]);
        fd[gpio] = open("/sys/class/gpio/unexport", O_WRONLY);
        len = snprintf(buf, BUFFER_MAX, "%d", gpio);
        write(fd[gpio], buf, len);
        close(fd[gpio]);
    }
    fd[gpio] = open("/sys/class/gpio/export", O_WRONLY);
    len = snprintf(buf, BUFFER_MAX, "%d", gpio);
    write(fd[gpio], buf, len);
    close(fd[gpio]);

    len = snprintf(buf, BUFFER_MAX, "/sys/class/gpio/gpio%d/direction", gpio);
    fd[gpio] = open(buf, O_WRONLY);
    if (direction == 1) {
        write(fd[gpio], "out", 4);
        close(fd[gpio]);
        len = snprintf(buf, BUFFER_MAX, "/sys/class/gpio/gpio%d/value", gpio);
        fd[gpio] = open(buf, O_WRONLY);

    } else {
        write(fd[gpio], "in", 3);
        close(fd[gpio]);
        len = snprintf(buf, BUFFER_MAX, "/sys/class/gpio/gpio%d/value", gpio);
        fd[gpio] = open(buf, O_RDONLY);
    }
    return 0;
}
