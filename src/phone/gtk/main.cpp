#include "Phone.h"

int main(int argc, char *argv[]) {
    Gtk::Main kit(argc, argv);
    Phone phone;
    Gtk::Main::run(phone);
    return 0;
}
