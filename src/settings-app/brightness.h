//
// Created by kivi on 31.05.17.
//

#ifndef SETTINGS_APP_BRIGHTNESS_H
#define SETTINGS_APP_BRIGHTNESS_H

void startUpBrightnessThread();
void readBrightness(int newVal);
void* brightnessThread(void* arg);
void setBrightness(char val);

#endif //SETTINGS_APP_BRIGHTNESS_H
