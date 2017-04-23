#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <string>
#include <signal.h>
#include <poll.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/limits.h>

using namespace std;

/* GPIOController  */
class GPIOController
{
public:
    // create a GPIO object that controls GPIO with number == gpioNum
    GPIOController(int gpioNum, string direction);
    ~GPIOController();              // no comments
    
    int setDirection(string dir);   // set GPIO Direction (input or output)
    int setEvent(string edge);      // set type of event - type of edge (none, both, rising or falling)
    int setValue(int value);        // set GPIO Value (only for output GPIO)

    int getValueOnEvent(int timeOut);   // get GPIO Value on the Event (only for input pin)
    
    int getValue();                 // get GPIO Value (only for input pin)
    int getGpioNum();               // return the GPIO number associated with the instance of an object
    string getGpioDirection();      // return direction of the GPIO
    string getGpioEvent();          // return event`s type of the GPIO

private:
    string gpioNum;     // GPIO number associated with the instance of an object
    string direction;   // GPIO direction
    string event;
};

#endif
