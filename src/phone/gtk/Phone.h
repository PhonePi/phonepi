#ifndef PHONE_H
#define PHONE_H

#include <gtkmm.h>
#include <vector>
#include <string>

class Phone : public Gtk::Window {
protected:
    Gtk::Label labelPhoneNumber;

    std::string captures [12] = {
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

    Gtk::Image numbers[12] = {
            Gtk::Image("../pics/numbers/1.png"),
            Gtk::Image("../pics/numbers/2.png"),
            Gtk::Image("../pics/numbers/3.png"),
            Gtk::Image("../pics/numbers/4.png"),
            Gtk::Image("../pics/numbers/5.png"),
            Gtk::Image("../pics/numbers/6.png"),
            Gtk::Image("../pics/numbers/7.png"),
            Gtk::Image("../pics/numbers/8.png"),
            Gtk::Image("../pics/numbers/9.png"),
            Gtk::Image("../pics/numbers/star.png"),
            Gtk::Image("../pics/numbers/0.png"),
            Gtk::Image("../pics/numbers/sharp.png"),
    };

    void buttonDialClicked(std::string phoneNumber);
    void buttonClearClicked();
    void buttonNumberClicked(std::string button);
    void buttonCreate(Gtk::Image* button_image, int row, int column,
                      Glib::SignalProxy0<void>::SlotType func);
    void dialingNumbers();
    void clearGrid(Gtk::Grid* grid);

public:
    Phone();
    ~Phone();
    Gtk::Grid numbersGrid;
    Gtk::Grid labelGrid;
    Gtk::Box gridBox;
};

#endif //PHONE_H