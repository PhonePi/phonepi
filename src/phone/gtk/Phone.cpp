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

    int number = 0;
    for(int i = 1; i < 5; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            char buffer[32];
            //sprintf(buffer, "%s", captures[number++]);
            Gtk::Image* button_image = &numbers[number]; 
            Button* pButton = new Button();//Gtk::manage(new Gtk::ToggleButton(buffer));
            pButton -> set_image(*button_image);
            pButton -> set_size_request(60, 60);
            pButton -> signal_clicked().connect(
                            sigc::bind<string>(sigc::mem_fun
                                    (
                                           *this,
                                           &Phone::buttonNumberClicked
                                    ), captures[number])
                    );
            button_image -> show();
            numbersGrid.attach(*pButton, j, i, 1, 1);
            number++;
        }
    }

    Gtk::Image *clear_image=new Gtk::Image("../pics/buttons/erase.png"); 
    Button* clearButton = new Button();
    clearButton -> set_image(*clear_image);
    clearButton -> set_size_request(60, 60);
    clearButton -> signal_clicked().connect(
            sigc::mem_fun
                    (
                            *this,
                            &Phone::buttonClearClicked
                    )
    );
    numbersGrid.attach(*clearButton, 0, 5, 1, 1);
    clear_image -> show();

    Gtk::Image *dial_image=new Gtk::Image("../pics/buttons/dial.png"); 
    Button* dialButton = new Button();
    dialButton -> set_image(*dial_image);
    dialButton -> set_size_request(60, 60);
    dialButton -> signal_clicked().connect(
            sigc::mem_fun
                    (
                            *this,
                            &Phone::buttonDialClicked
                    )
    );
    numbersGrid.attach(*dialButton, 2, 5, 1, 1);
    dial_image -> show();

    show_all_children();
}

Phone::~Phone(){}

void Phone::buttonNumberClicked(string button){
    labelPhoneNumber.set_text(labelPhoneNumber.get_text() + button);

}

void Phone::buttonDialClicked() {
    if(labelPhoneNumber.get_text().empty())
        return;

    /*Передача номера по DBus. И отрисовка экрана звонка*/
    //labelPhoneNumber.set_text("It's a moc");
    hide();
    Call call(this, labelPhoneNumber.get_text());
    Main::run(call);
}

void Phone::buttonClearClicked() {
    labelPhoneNumber.set_label(labelPhoneNumber.get_text().substr(0, labelPhoneNumber.get_text().length() - 1));
}
