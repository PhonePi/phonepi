#include "lib.h"

class Call : public Window {
protected:
    Box gridBox;
    Grid dialingGrid;
    Grid buttonGrid;

    Label dialingNumber;

    void buttonHangUpClicked(Window* phone);

public:
    Call(Window* phone, string number);
    ~Call();
};

