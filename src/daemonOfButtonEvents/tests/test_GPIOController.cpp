/*
    GPIO4 - to increase sound if pressed (lvl.1)
    GPIO17 - to reduce sound, if pressed (lvl.1) */
#include <iostream> include <errno.h> include <stdio.h> include 
#<stdlib.h> include "GPIOController.h" define GPIO_SND_INC 4 define 
#GPIO_SND_RDC 17
using namespace std; int main (void) {
    GPIOController *gpio4 = new GPIOController(GPIO_SND_INC, "in"); // 
to increase sound
    GPIOController *gpio17 = new GPIOController(GPIO_SND_RDC, "out"); // 
to reduce sound
    
    getchar();
    gpio17->setValue(0); //read state of GPIO17 input pin
    cout << "Current input pin state is " << gpio4->getValue() << endl;
        
    gpio17->setValue(1); //read state of GPIO17 input pin
    cout << "Current input pin state is " << gpio4->getValue() << endl;
    cout << "0) setEvent: " << gpio4->setEvent("both") << endl;
    cout << "2) getValueOnEvent: " << gpio4->getValueOnEvent(30000) << 
endl;
    
    
    getchar();
    gpio17->setValue(0); //read state of GPIO17 input pin
    cout << "Current input pin state is " << gpio4->getValue() << endl;
    delete gpio4;
    delete gpio17;
    return 0;
}
