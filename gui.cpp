// g++ gui.cpp -o my_app -I. -fPIC $(pkg-config --cflags --libs Qt6Widgets)

#include "json.hpp" // Подключаем библиотеку nlohmann/json

#include <QApplication>
#include <QWidget>
#include <QShortcut>
#include <QKeySequence>
#include <string>
#include "gui.h" // ваш UI-файл

#include <iostream>
#include <string>
#include <vector>

#include <cstddef>
#include <cstdio>
#include <memory>
#include <array>
#include <regex>

// Для удобства используем псевдоним nlohmann::json
using json = nlohmann::json;

// 1. Структура для вложенного объекта "rect"
struct Rect {
    int x;
    int y;
    int width;
    int height;
};

// 2. Структура для основного объекта рабочего пространства
struct Workspace {
    long long id; // Используем long long, т.к. ID очень большой
    int num;
    std::string name;
    bool visible;
    bool focused;
    Rect rect; // Вложенная структура
    std::string output;
    bool urgent;
};

// --- Функции для десериализации (преобразования JSON в C++ структуры) ---
// Эти функции позволяют nlohmann/json автоматически преобразовывать JSON-объекты
// в ваши C++ структуры. Их нужно определить в том же пространстве имен, что и json::parse
// или в глобальном.

void from_json(const json& j, Rect& r) 
{
    j.at("x").get_to(r.x);
    j.at("y").get_to(r.y);
    j.at("width").get_to(r.width);
    j.at("height").get_to(r.height);
}

void from_json(const json& j, Workspace& w) 
{
    j.at("id").get_to(w.id);
    j.at("num").get_to(w.num);
    j.at("name").get_to(w.name);
    j.at("visible").get_to(w.visible);
    j.at("focused").get_to(w.focused);
    j.at("rect").get_to(w.rect); // Это вызовет from_json для Rect
    j.at("output").get_to(w.output);
    j.at("urgent").get_to(w.urgent);
}

// Получение название активного WorkSpace i3
std::string get_current_workspace_name() 
{
    std::array<char, 4096> buffer;
    std::string result;

    FILE* pipe = popen("i3-msg -t get_workspaces", "r");
    if (!pipe) return "ERROR: popen failed";

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) 
    {
        result += buffer.data();
    }

    pclose(pipe);

    try 
    {
        // 1. Парсим строку в объект json
        json parsed_json = json::parse(result);

        // 2. Преобразуем JSON-массив в std::vector<Workspace>
        // Благодаря определенным функциям from_json, это происходит автоматически
        std::vector<Workspace> workspaces_array = parsed_json.get<std::vector<Workspace>>();

        // Теперь у вас есть массив (std::vector) объектов Workspace
        // std::cout << "Парсинг успешно выполнен. Количество рабочих пространств: " << workspaces_array.size() << std::endl;

        // Вывод для проверки
        for (const auto& ws : workspaces_array) 
        {
            if (ws.focused == true) 
            {
                // std::cout << "-----------------------------------" << std::endl;
                // std::cout << "ID: " << ws.id << std::endl;
                // std::cout << "Num: " << ws.num << std::endl;
                // std::cout << "Name: " << ws.name << std::endl;
                // std::cout << "Visible: " << (ws.visible ? "true" : "false") << std::endl;
                // std::cout << "Focused: " << (ws.focused ? "true" : "false") << std::endl;
                // std::cout << "Rect: {x=" << ws.rect.x << ", y=" << ws.rect.y
                //           << ", width=" << ws.rect.width << ", height=" << ws.rect.height << "}" << std::endl;
                // std::cout << "Output: " << ws.output << std::endl;
                // std::cout << "Urgent: " << (ws.urgent ? "true" : "false") << std::endl;

                return std::to_string(ws.num);
            }
        }

    } catch (const json::exception& e) 
    {
        // Обработка ошибок парсинга JSON
        std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
    } catch (const std::exception& e) 
    {
        // Прочие ошибки
        std::cerr << "Прочая ошибка: " << e.what() << std::endl;
    }

    return "NOT FOUND";
}

void move_active_window_to_workspace(int number) 
{
    std::string cmd = "i3-msg move container to workspace " + std::to_string(number);
    system(cmd.c_str());

    cmd = "i3-msg workspace " + std::to_string(number);
    system(cmd.c_str());

}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QWidget window;
    Ui::Form ui;
    ui.setupUi(&window); // инициализация UI внутри виджета window

    for (int i = 1; i <= 10; ++i)
    {
        /* code */
        ui.listWidget->addItem(":: Workspace ::: " + QString::number(i));
    }

    // Получение активного WorkSpace
    std::string activeWorkSpace = get_current_workspace_name();

    // Опеделение активного WorkSpace
    ui.listWidget->setCurrentRow( std::stoi(activeWorkSpace) - 1 );  // Выбирает 4-й элемент (нумерация с 0)
    qDebug() << activeWorkSpace;

    ui.label->setText("Active WorkSpace: " + QString::fromStdString(activeWorkSpace));

    // Событие переключения между объектами списка listView
    QObject::connect(ui.listWidget, &QListWidget::itemSelectionChanged, [&] () 
    {
        QList<QListWidgetItem *> selectedItems = ui.listWidget->selectedItems();

        if (!selectedItems.isEmpty()) 
        {
            QListWidgetItem *item = selectedItems.first();
            int index = ui.listWidget->row(item) + 1;  // 👈 получаем индекс
            qDebug() << "Выбрано:" << index;
            ui.label->setText("Active WorkSpace: " + QString::number(index));

            // Перемешение между Workspace
            move_active_window_to_workspace( index );

        } else 
        {
            qDebug() << "Ничего не выбрано.";
        }
    });

    // Закрытие приложения при нажатия Esc
    QShortcut *esc = new QShortcut(QKeySequence(Qt::Key_Escape), &window);
    QObject::connect(esc, &QShortcut::activated, []() {
        QApplication::quit();
    });

    window.show();
    return a.exec();
}
