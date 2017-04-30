//
// Created by valeriya on 29.04.17.
//
#include "lib.h"

class Phone : public Window {
protected:
    Label labelPhoneNumber;

    char* captures [12] = {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "*",
            "0",
            "#",
    };

    Grid labelGrid;
    Grid numbersGrid;

    void buttonDialClicked();
    void buttonClearClicked();
    void buttonNumberClicked(Button* button);

public:
    Phone();
    ~Phone();
};