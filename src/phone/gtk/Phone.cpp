/**
 * Phone GUI with gtkmm using
 *
 * GUI в рабочем состоянии. Однако, при вводе цифр есть несколько проблем.
 * Во-первых, при добавлении цифр в label, съезжают все цифры.
 * Одним из вариантов решения - разнести label и кнопки по разным сеткам (grid),
 * однако, в классе Window этого не сделать. Этот класс на рассчитан на несколько
 * виджетов. Можно попробовать класс Box. Когда я его пробовал, ничего не отображалось.
 * Вероятнее всего, как-то неправильно упаковывал. (ИСПРАВЛЕНО!!!!)
 * Во-вторых, при нажатии на какую-либо кнопку, отображается только ее нажатие.
 * Отжатие не работает. Т. е., выглядит так, что на кнопку не нажали, а зажали.
 * Чтобы ее отжать, необходимо нажать еще раз. Думаю, нужно смотреть свойства. 
 * (МОЖНО СЧИТАТЬ, ЧТО ИСПРАВЛЕНО. КОСТЫЛЬНО, ПРАВДА)
 *
 * Окно вызова теперь открывается не вторым окном, а вместо окна набора номера.
 * Однако, после того, как трубку повесили - не получается скрыть окно вызова и вернуть окно
 * набора номера. При скрытии окна вызова происходит выход из приложения.
 * Пока что оставляю оба окна, что представляет из себя плохую идею.
 * Вместо кнопок Вызвать/Стереть/Положить трубку используются соответствующие иконки. 
 */

#include "Phone.h"
#include "QDBusCalls.h"

Phone::Phone() {
    set_border_width(10);
    set_position(Gtk::WIN_POS_CENTER_ALWAYS);
    set_title("Phone");
    set_default_size(480,480);
    set_size_request(480,480);
    gridBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    gridBox.pack_start(labelGrid);
    gridBox.pack_end(numbersGrid);
    add(gridBox);

    labelPhoneNumber.set_label("");
    labelGrid.attach(labelPhoneNumber, -1, 0, 1, 1);
    labelPhoneNumber.show();
    labelPhoneNumber.set_text("89215773326");

    dialingNumbers();

    show_all_children();
}

Phone::~Phone(){}

void Phone::buttonNumberClicked(std::string button){
    labelPhoneNumber.set_text(labelPhoneNumber.get_text() + button);
}

void Phone::buttonDialClicked() {
    if(labelPhoneNumber.get_text().empty())
        return;

    clearGrid(&labelGrid);
    clearGrid(&numbersGrid);

    QDBusCalls* qdbs = new QDBusCalls();

    labelGrid.set_size_request(480, 200);
    labelGrid.override_background_color(Gdk::RGBA("blue"), Gtk::STATE_FLAG_NORMAL);
    labelGrid.override_color(Gdk::RGBA("white"), Gtk::STATE_FLAG_NORMAL);
    labelGrid.add(labelDialing);
    Gtk::Label timer;
    labelGrid.add(labelTimer);
    labelPhoneNumber.set_text("Dialing: " + labelPhoneNumber.get_text());


    buttonCreate(new Gtk::Image("../pics/buttons/hang_up.png"), 1, 1,
                 sigc::mem_fun
                         (
                                 *this,
                                 &Phone::buttonClearClicked
                         )
    );
    show_all_children();

    qdbs -> dialNumber(labelPhoneNumber.get_text().c_str());
}

void Phone::buttonClearClicked() {
    labelPhoneNumber.set_label(labelPhoneNumber.get_text()
                                       .substr(0, labelPhoneNumber.get_text().length() - 1));
}

void Phone::dialingNumbers(){

    int number = 0;
    for(int i = 1; i < 5; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            buttonCreate(&numbers[number], j, i,
                         sigc::bind<std::string>(sigc::mem_fun
                                                    (
                                                            *this,
                                                            &Phone::buttonNumberClicked
                                                    ), captures[number]));
            number++;
        }
    }

    buttonCreate(new Gtk::Image("../pics/buttons/erase.png"), 0, 5,
                 sigc::mem_fun
                         (
                                 *this,
                                 &Phone::buttonClearClicked
                         )
    );

    buttonCreate(new Gtk::Image("../pics/buttons/dial.png"), 2, 5,
                 sigc::mem_fun
                         (
                                 *this,
                                 &Phone::buttonDialClicked
                         )
    );
}

void Phone::buttonCreate(Gtk::Image* button_image, int row, int column,
                         Glib::SignalProxy0<void>::SlotType func){
    Gtk::Button* pButton = new Gtk::Button();
    pButton -> set_image(*button_image);
    pButton -> set_size_request(60, 60);
    pButton -> signal_clicked().connect(func);
    button_image -> show();
    numbersGrid.attach(*pButton, row, column, 1, 1);
}

void Phone::clearGrid(Gtk::Grid* grid){
    std::vector<Gtk::Widget*> label_children = grid -> get_children();
    for (Gtk::Widget* child : label_children)
        grid -> remove(*child);
}