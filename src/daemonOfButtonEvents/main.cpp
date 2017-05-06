/*
	sndInc  - to increase sound if pressed (lvl.1)
	sndRdc - to reduce sound, if pressed (lvl.1)
*/

#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
//#include <errno.h>
#include <signal.h>
#include <pthread.h>

#include "GPIOController.h"

#define GPIO_SND_INC		4
#define GPIO_SND_RDC		17
#define GPIO_DISP_IN		18
#define GPIO_DISP_OUT		27
#define ACTIV_LVL			0	// state for pressed button;
#define SENSITIVITY			10	// sensitivity of button`s press
								// 1 clikc will change soundLvl on 10%
#define MAX_FREQ_EVENT_SND	250	// max frequency of event (in ms) for sound daemon
#define MAX_FREQ_EVENT_DIS	600	// max frequency of event (in ms) for display daemon
#define SPEAKER_SCRIPT		"/home/alarm/gpioDaemon/set-speaker-volume"


using namespace std;


int soundLvl = 100;			// in percents
bool SIGTERM_event = false;

void SIGTEMT_handler(int sig) {
    write(0,"\nSIGTERM signal!\n",32);
    SIGTERM_event = true;
}


void *thrdSndCtrlFunction(void *arg);

int main (void)
{	
	struct sigaction sig_struct;
    sig_struct.sa_handler = SIGTEMT_handler;
    sig_struct.sa_flags = 0;
    sigemptyset(&sig_struct.sa_mask);

    if (sigaction(SIGINT, &sig_struct, NULL) == -1) {
        cout << "Problem with sigaction" << endl;
		cout << "Button Daemon Error#1: errno=" << errno << "; " << 
            "Could not set sigaction harder" << endl;
        exit(-1);
    }
	int soundChildPID = fork();

	// child #1 (sound daemon)
	if (soundChildPID == 0) {
		// thread env.
		int statusAddr;
		pthread_t thrdRdc;	// thread for reducing of Sound; Increasing occurs in main thread;

		// obj. sndInc serves for increasing of sound
		GPIOController *sndInc = new GPIOController(
			GPIO_SND_INC,	// number of GPIO
			"in",			// mode of work: input
			"falling"		// type of event: when input value falls from 1 to 0 (press of button)
		);
		// obj. sndRdc serves for reducing of sound
		GPIOController *sndRdc = new GPIOController(
			GPIO_SND_RDC,	// number of GPIO
			"in",			// mode of work: input
			"falling"		// type of event: when input value falls from 1 to 0 (press of button)
		);
		// set default state
		sndInc->setValue(1);
		sndRdc->setValue(1);
		
		// Reducing thread. Creation and start
		if (pthread_create(&thrdRdc, NULL, thrdSndCtrlFunction, (void*) sndRdc) != 0) {
			cout << "Sound Daemon Error#2: errno=" << errno << "; " << 
            "Could not create reducing threads;" << endl;
			exit(-2);  
		}

		// Increasing thread. Start in main
		thrdSndCtrlFunction(sndInc);	
		
		// wainting finish of all threads (increasing and reducing)
		pthread_join(thrdRdc, (void**)&statusAddr);
		
		delete sndInc;	// destruction of gpio objects
		delete sndRdc;
	// father (display daemon)
	} else {
		// obj. disBlockIn serves for blockin/unBlocking display
		GPIOController *disBlockIn = new GPIOController(
			GPIO_DISP_IN,	// number of GPIO
			"in",			// mode of work: input
			"falling"		// type of event: when input value falls from 1 to 0 (press of button)
		);
		GPIOController *disBlockOut = new GPIOController(
			GPIO_DISP_OUT,	// number of GPIO
			"out",			// mode of work: input
			"none"			// type of event: no event
		);
		int value;			// current value of GPIO
		int ignore = false;	// if user holds button
		bool block = false;	// status of display`s LED

		// set default state
		disBlockIn->setValue(1);
		disBlockOut->setValue(1);
		while (true) {
			// waiting the event (failing)
			value = disBlockIn->getValueOnEvent(2900); // timeOut 2.9 sec

			// checking the interruption
			if (SIGTERM_event) break;

			// checking: is event or timeOut?
			if (value != ACTIV_LVL) {
				ignore = false;
				continue;	  // it`s timeOut
			} 
			if (ignore) continue;	// it`s holing of button
			
			cout << "display block: " << disBlockOut->getValue() << endl;
			// it`s event
			disBlockOut->setValue(block ? 0 : 1);
			block = !block;
			ignore = true;

			// it`s regulate the max frequency of button`s event for display
			usleep(1000*MAX_FREQ_EVENT_DIS);			// usleep works with microSec;
		}

		delete disBlockIn;	// destruction of gpio objects
		delete disBlockOut;

		// stopping of work
		kill(soundChildPID, SIGTERM);	// send SIGTERM to soundChild
	}
	cout << "Succes" << endl;
    return 0;
}

// function for Increasing and Reducing of the sound lvl
void *thrdSndCtrlFunction(void *arg) {
	GPIOController *gpio = (GPIOController *)arg;
	int value;								  // current value of GPIO
	
	while (true) {
		// waiting the event (failing)
		value = gpio->getValueOnEvent(3000); // timeOut 3 sec

		// checking the interruption
		if (SIGTERM_event) break;

		// checking: is event or timeOut?
		if (value != ACTIV_LVL) continue;	  // it`s timeOut

		// it`s event
		if (gpio->getGpioNum() == GPIO_SND_INC) {
			//soundLvl + SENSITIVITY <= 100 ? soundLvl += SENSITIVITY : soundLvl = 100;
			soundLvl = 100;
			cout << "+soundLvl: " << soundLvl << endl;
		}
		else {
			soundLvl = 0;
			//soundLvl - SENSITIVITY > 0 ? soundLvl -= SENSITIVITY : soundLvl = 0;
			cout << "-soundLvl: " << soundLvl << endl;
		}

		// send through DBus;
		if (fork() == 0) {						// execl python script
			char soundLvlStr[4] = {0};
			sprintf(soundLvlStr, "%d", soundLvl);
			execl(SPEAKER_SCRIPT,				// name of program
					SPEAKER_SCRIPT,				// program`s agrs
					soundLvlStr,
					NULL
			);
			// if something went wrong
			cout << "set-speaker-volume: errno=" << errno << "; " << endl;
			exit(-1);
		}

		// it`s regulate the max frequency of button`s event
		usleep(1000*MAX_FREQ_EVENT_SND);			// usleep works with microSec;
	}
	cout << "Thrd is finished." << endl;
}






