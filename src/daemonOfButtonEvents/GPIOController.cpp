#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include "GPIOController.h"

using namespace std;

// constructor creates and registers new GPIO with number "gpioNum" to system
GPIOController::GPIOController(int gpioNum, string direction) {
    // Instatiate GPIOController object for GPIO with current gpioNum number
    this->gpioNum = to_string(gpioNum);

    // open export file for adding new GPIO
    ofstream gpioExport("/sys/class/gpio/export");
    if (!gpioExport.is_open()){
        cout << " OPERATION FAILED: Unable to export GPIO"
             << this->gpioNum << ";" << endl;
        this->gpioNum = to_string(-1);
        return;
    }

    // add new GPIO to configuration
    gpioExport << this->gpioNum ;
    gpioExport.close();
    
    // set dicrection for gpioNum
    if (setDirection(direction) < 0) {
        //~GPIOController();
        return;
    }
}

// destructor unregisters and delete GPIO with number "this->gpioNum" from the system
GPIOController::~GPIOController() {
    // open unExport file for removing GPIO
    ofstream gpioUnExport("/sys/class/gpio/unexport");
    if (!gpioUnExport.is_open()){
        cout << " OPERATION FAILED: Unable to unexport GPIO"
             << this->gpioNum << ";" << endl;
        return;
    }

    // remove gpioNum from GPIO configuration
    gpioUnExport << this->gpioNum ;
    gpioUnExport.close();
    this->gpioNum = -1;
}

// function setDirection sets direction of GPIO work: "in" or "out" mode
int GPIOController::setDirection(string dir) {
    // open direction file for GPIO
    string gpioDirPath ="/sys/class/gpio/gpio" + this->gpioNum + "/direction";
    ofstream gpioDirFile(gpioDirPath.c_str());
    if (!gpioDirFile.is_open()){
        cout << " OPERATION FAILED: Unable to set direction of GPIO"
             << this->gpioNum << ";" << endl;
        return -1;
    }

    // write the direction to direction file (gpioDirPath)
    gpioDirFile << dir; 
    gpioDirFile.close();
    this->direction = dir;
    return 0;
}

// function setEvent sets type of event  (none, both, rising or falling)
int GPIOController::setEvent(string event) {
    // check mode of GPIO: function only for input gpio
    if (strcmp(this->direction.c_str(), "in") != 0) {
        cout << " OPERATION FAILED: Function \"setValue\" works only with IN GPIO"
             << this->gpioNum << ";" << endl;
        return -1;
    }

    // open file, which contain event of GPIO (0 or 1)
    string gpioeventPath = "/sys/class/gpio/gpio" + this->gpioNum + "/edge";
    ofstream gpioeventFile(gpioeventPath.c_str()); // open event file for current gpio
    if (!gpioeventFile.is_open()) {
        cout << " OPERATION FAILED: Unable to set the event of GPIO"
             << this->gpioNum << ";" << endl;
        return -2;
    }

    // set event into gpioeventPath
    gpioeventFile << event;
    gpioeventFile.close();
    this->event = event;
    return 0;
}

// function setValue sets value only for output GPIO
int GPIOController::setValue(int value) {
    // check mode of GPIO: function only for output gpio
    if (strcmp(this->direction.c_str(), "out") != 0) {
        cout << " OPERATION FAILED: Function \"setValue\" works only with OUT GPIO"
             << this->gpioNum << ";" << endl;
        return -1;
    }
    
    // open file, which contain value of GPIO (0 or 1)
    string gpioValuePath = "/sys/class/gpio/gpio" + this->gpioNum + "/value";
    ofstream gpioValueFile(gpioValuePath.c_str()); // open value file for gpio
    if (!gpioValueFile.is_open()){
        cout << " OPERATION FAILED: Unable to set the value of GPIO"
             << this->gpioNum << ";" << endl;
        return -2;
    }

    // set value into gpioValueFile
    gpioValueFile << value;
    gpioValueFile.close();
    return 0;
}

// function getValue gets value, only for input GPIO
int GPIOController::getValue() {
    // check mode of GPIO: function only for input gpio
    if (strcmp(this->direction.c_str(), "in") != 0) {
        cout << " OPERATION FAILED: Function \"getValue\" works only with IN GPIO"
             << this->gpioNum << ";" << endl;
        return -1;
    }
    
    // open file, which contain value of GPIO (0 or 1)
    string gpioValuePath = "/sys/class/gpio/gpio" + this->gpioNum + "/value";
    ifstream gpioValueFile(gpioValuePath.c_str());
    if (!gpioValueFile.is_open()){
        cout << " OPERATION FAILED: Unable to get the value from GPIO"
             << this->gpioNum << ";" << endl;
        return -2;
    }

    // read GPIO
    string tmp;
    gpioValueFile >> tmp ;
    gpioValueFile.close();
    
    return strcmp(tmp.c_str(), "0") == 0 ? 0 : 1;
}

// function getValue gets value on the event (look function setEvent), only for input GPIO
int GPIOController::getValueOnEvent(int timeOut) {
    // check mode of GPIO: function only for input gpio
    if (strcmp(this->direction.c_str(), "in") != 0) {
        cout << " OPERATION FAILED: Function \"getValue\" works only with IN GPIO"
             << this->gpioNum << ";" << endl;
        return -1;
    }
    
    // check type of event
    if (strcmp(this->event.c_str(), "both") != 0
        && strcmp(this->event.c_str(), "rising") != 0
        && strcmp(this->event.c_str(), "falling") != 0) {
        // reset default type of event
        if (setEvent("rising") < 0) return -2;
        cout << "Warning. Type of event is not defined. Default value (rising) is choisen." << endl;
    }
    
    char gpioValueFile[PATH_MAX];
    int fd;
    char c;
    int err;
    struct pollfd pollfd[1];

    // polling the line
    snprintf(gpioValueFile, sizeof(gpioValueFile), "/sys/class/gpio/gpio%d/value", this->gpioNum);
    fd = open(gpioValueFile, O_RDONLY);
    if (fd < 0) {
        cout << " OPERATION FAILED: Unable to open file with the value of GPIO"
             << this->gpioNum << ";" << endl;
        return -3;
    }
    read(fd, &c, sizeof(c));

    pollfd[0].fd = fd;
    pollfd[0].events = POLLPRI | POLLERR;
    pollfd[0].revents = 0;

    // waiting of event
    err =  poll(pollfd, 1, timeOut);
    if(err != 1) {
        cout << " OPERATION FAILED: Unable to POLL file with the value of GPIO"
             << this->gpioNum << ";" << endl;
        return -4;
    }

    // backing to start of value`s file
    lseek(fd, 0, SEEK_SET);
    read(fd, &c, sizeof(c));

    return c - '0';
}

// get number of current GPIO
int GPIOController::getGpioNum() {
    return stoi(this->gpioNum);
}
// get direction of current GPIO
string GPIOController::getGpioDirection() {
    return this->direction;
}
// get type of event of current GPIO
string GPIOController::getGpioEvent() {
    return this->event;
}