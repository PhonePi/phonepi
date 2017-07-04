#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QApplication>
#include <QString>
#include <QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

struct Answer_struct{
    QString name;
    QMap<QString, QVariant> porp_map;
};
Q_DECLARE_METATYPE(Answer_struct)

class MainWindow : public QWidget{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showDialer();

public slots:
    void back();
    void erase();
    void dialNumber();

private:
    //QDBusConnection bus = QDBusConnection::systemBus();
    QString selected_modem;
	QString dialedNumber;
    QLabel *phoneNumber;
    std::string workingDir = "//home//arseny//Repos//KSPT//Phone//src//phone//qt//";
    QGridLayout *textLayout;
    QGridLayout *buttonLayout;
    QGridLayout *commonLayout;
    QWidget *mainWindow;
    QWidget *textField;
    QWidget *buttonField;
};
#endif // MAINWINDOW_H
