#include "lib.h"
#include "Call.h"

class Phone : public Window {
protected:
    Label labelPhoneNumber;

    string captures [12] = {
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

    Image numbers[12] = {
        Image("../pics/numbers/1.png"),
        Image("../pics/numbers/2.png"),
        Image("../pics/numbers/3.png"),
        Image("../pics/numbers/4.png"),
        Image("../pics/numbers/5.png"),
        Image("../pics/numbers/6.png"),
        Image("../pics/numbers/7.png"),
        Image("../pics/numbers/8.png"),
        Image("../pics/numbers/9.png"),
        Image("../pics/numbers/star.png"),
        Image("../pics/numbers/0.png"),
        Image("../pics/numbers/sharp.png"),
    };

    Box gridBox;
    Grid labelGrid;
    Grid numbersGrid;

    void buttonDialClicked();
    void buttonClearClicked();
    void buttonNumberClicked(string button);

public:
    Phone();
    ~Phone();
};