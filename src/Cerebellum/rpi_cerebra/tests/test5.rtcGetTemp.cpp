#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define I2C_CMD_BATTERY     0xBB    // "Check battery status" (frequency == 60 sec.)
#define I2C_CMD_CHECK       0xCC    // "Check general status" (frequency == 1 sec.)
#define I2C_CMD_BRIGTH      0xDD    // "Set display brightness" (async.)
#define I2C_CMD_SHUT        0x88    // "RPi shut down" (async.)
#define I2C_CMD_TEMP        0x36    // "Get Temperature" (async.)
                                    // OTHER commands are invalid
#define BUFFER_SIZE 19 //0x00 to 0x13
// the time is in the registers in encoded decimal form

//char *socket_path = "./socket4242";
char *socket_path = "\0hidden";


int bcdToDec(char b) { return (b/16)*10 + (b%16); }
int main(){
    int file;
    printf("Starting the DS3231 test application\n");
    if((file=open("/dev/i2c-1", O_RDWR)) < 0){
        perror("failed to open the bus\n");
        return 1;
    }
    if(ioctl(file, I2C_SLAVE, 0x68) < 0){
        perror("Failed to connect to the sensor\n");
        return 1;
    }
    char writeBuffer[1] = {0x00};
    if(write(file, writeBuffer, 1)!=1){
        perror("Failed to reset the read address\n");
        return 1;
    }
    char buf[BUFFER_SIZE];
    if(read(file, buf, BUFFER_SIZE)!=BUFFER_SIZE){
        perror("Failed to read in the buffer\n");
        return 1;
    }
    printf("The RTC time is %02d:%02d:%02d\n", bcdToDec(buf[2]),
    bcdToDec(buf[1]), bcdToDec(buf[0]));
    // note that 0x11 = 17 decimal and 0x12 = 18 decimal
    float temperature = buf[0x11] + ((buf[0x12]>>6)*0.25);
    printf("The temperature is %f°C\n", temperature);
    close(file);
    return 0;
}