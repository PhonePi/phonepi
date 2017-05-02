#include "Call.h"

Call::Call(Window* phone, string number) {
    set_border_width(10);
    set_position(Gtk::WIN_POS_CENTER_ALWAYS);
    set_title("Dialing");
    set_default_size(480, 480);
    set_size_request(480, 480);
    dialingGrid.set_size_request(480, 200);
    dialingGrid.add(dialingNumber);
    gridBox.set_orientation(ORIENTATION_VERTICAL);
    dialingGrid.override_background_color(Gdk::RGBA("blue"), Gtk::STATE_FLAG_NORMAL);
    dialingGrid.override_color(Gdk::RGBA("white"), STATE_FLAG_NORMAL);
    gridBox.pack_start(dialingGrid);
    gridBox.pack_end(buttonGrid);
    add(gridBox);

    dialingNumber.set_text("Dialing: " + number);

    Gtk::Image *hang_image=new Gtk::Image("../pics/buttons/hang_up.png"); 
    Button* hangUp = new Button();
    hangUp -> set_image(*hang_image);
    hangUp -> set_size_request(60, 60);
    hangUp -> signal_clicked().connect(
            sigc::bind<Window*>(sigc::mem_fun
                                        (
                                                *this,
                                                &Call::buttonHangUpClicked
                                        ), phone)
    );
    buttonGrid.attach(*hangUp, 0, 2, 1, 1);
    hang_image -> show();

    show_all_children();
}

Call::~Call(){}

void Call::buttonHangUpClicked(Window* phone){
    hide();
    phone -> show();
}