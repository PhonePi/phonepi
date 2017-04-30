/**
 * Phone GUI with gtkmm using
 *
 * GUI в рабочем состоянии. Однако, при вводе цифр есть несколько проблем.
 * Во-первых, при добавлении цифр в label, съезжают все цифры.
 * Одним из вариантов решения - разнести label и кнопки по разным сеткам (grid),
 * однако, в классе Window этого не сделать. Этот класс на рассчитан на несколько
 * виджетов. Можно попробовать класс Box. Когда я его пробовал, ничего не отображалось.
 * Вероятнее всего, как-то неправильно упаковывал
 * Во-вторых, при нажатии на какую-либо кнопку, отображается только ее нажатие.
 * Отжатие не работает. Т. е., выглядит так, что на кнопку не нажали, а зажали.
 * Чтобы ее отжать, необходимо нажать еще раз. Думаю, нужно смотреть свойства.
 */

#include "Phone.h"

Phone::Phone() {
    set_border_width(10);
    set_position(Gtk::WIN_POS_CENTER_ALWAYS);
    set_title("Phone");
    set_default_size(480,480);
    set_size_request(480,480);
    labelGrid.set_size_request(480,480);
    labelGrid.set_row_spacing(20);
    labelGrid.set_column_spacing(20);
    add(labelGrid);

    labelPhoneNumber.set_label("Enter phone number:");
    labelGrid.attach(labelPhoneNumber, -1, 0, 1, 1);
    labelPhoneNumber.show();

    int number = 0;
    for(int i = 1; i < 5; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            char buffer[32];
            sprintf(buffer, "%s", captures[number++]);
            auto pButton = Gtk::manage(new Gtk::ToggleButton(buffer));
            pButton -> signal_clicked().connect(
                            sigc::bind<Button*>(sigc::mem_fun
                                                              (
                                                                      *this,
                                                                      &Phone::buttonNumberClicked
                                                              ), pButton)
                    );
            pButton -> set_size_request(50, 50);
            labelGrid.attach(*pButton, j, i, 1, 1);
        }
    }

    auto clearButton = Gtk::manage(new Gtk::ToggleButton("Clear"));
    clearButton -> signal_clicked().connect(
            sigc::mem_fun
                    (
                            *this,
                            &Phone::buttonClearClicked
                    )
    );
    clearButton -> set_size_request(50, 50);
    labelGrid.attach(*clearButton, 0, 5, 1, 1);

    auto dialButton = Gtk::manage(new Gtk::ToggleButton("Dial"));
    dialButton -> signal_clicked().connect(
            sigc::mem_fun
                    (
                            *this,
                            &Phone::buttonDialClicked
                    )
    );
    dialButton -> set_size_request(50, 50);
    labelGrid.attach(*dialButton, 2, 5, 1, 1);

    show_all_children();
}

Phone::~Phone(){}

void Phone::buttonNumberClicked(Button* button){
    labelPhoneNumber.set_text(labelPhoneNumber.get_text() + button->get_label());
}

void Phone::buttonDialClicked() {
    labelPhoneNumber.set_text("Empty function. For a while");
}

void Phone::buttonClearClicked() {
    labelPhoneNumber.set_label("__");
}
