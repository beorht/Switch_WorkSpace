#include <QApplication>
#include <QWidget>
#include "gui.h" // ваш UI-файл

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    Ui::Form ui;
    ui.setupUi(&window); // инициализация UI внутри виджета window

    window.show();
    return a.exec();
}
