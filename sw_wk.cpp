//g++ sw_wk.cpp -o get_ws -lX11 && ./get_ws
//g++ sw_wk.cpp -std=c++17 -lX11 -lftxui-component -lftxui-dom -lftxui-screen -o sw_wk && ./sw_wk

#include <cstddef>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp> 

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp" // Подключаем библиотеку nlohmann/json

#include <cstdio>
#include <memory>
#include <array>
#include <regex>

// Для удобства используем псевдоним nlohmann::json
using json = nlohmann::json;
using namespace ftxui;

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
}

int main() 
{
    // std::string cmd = "i3-msg focus mode_toggle";
    // system(cmd.c_str());

    std::string activeWorkSpace = get_current_workspace_name();
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();


    int selected = std::stoi(activeWorkSpace) - 1;

    std::vector<std::string> items = 
    {
        "Workspace: 1",
        "Workspace: 2",
        "Workspace: 3",
        "Workspace: 4",
        "Workspace: 5",
        "Workspace: 6",
        "Workspace: 7",
        "Workspace: 8",
        "Workspace: 9",
        "Workspace: 10",
    };

    // MenuOption option;
    // option.on_enter = [&] {
    //     std::string cmd = "i3-msg move container to workspace " + std::to_string(selected+1);
    //     system(cmd.c_str());

    //     cmd = "i3-msg workspace " + std::to_string(selected + 1);
    //     system(cmd.c_str());
    // };

    // Component menu = Menu(&items, &selected, option);

    // Component renderer = Renderer(menu, [&] {
    //     return vbox({
    //         text("Workspace List:") | bold,
    //         separator(),
    //         menu->Render(),
    //         separator(),
    //         text("Active: " + items[selected]) | color(Color::Green)
    //     }) | border;
    // });

    // ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    // screen.Loop(renderer);


    //👇 создаём опции с on_change
    // MenuOption option;
    // option.on_change = [&] 
    // {

    //     std::string cmd = "i3-msg move container to workspace " + std::to_string(selected+1);
    //     system(cmd.c_str());
        
    //     // Пример: переключить рабочее пространство i3
    //     cmd = "i3-msg workspace " + std::to_string(selected + 1);
    //     system(cmd.c_str());
    // };

    // Component menu = Menu(&items, &selected, option);

    // Component renderer = Renderer(menu, [&] 
    // {
    //     return vbox({
    //         text("Workspace List:") | bold,
    //         separator(),
    //         menu->Render() | color(Color::GrayLight) | bold | color(Color::GrayLight),
    //         separator(),
    //         text("Active: " + items[selected]) | color(Color::Green)
    //     }); //| frame | border | size(HEIGHT, LESS_THAN, 100);
    // });

    // ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    // screen.Loop(renderer);

    // Создаём свой Menu вручную
    Component menu = Renderer([&] {
        Elements entries;
        for (int i = 0; i < items.size(); ++i) {
            bool is_selected = (i == selected);
            auto style = is_selected 
                ? color(Color::Black) | bgcolor(Color::Cyan) | bold | frame // Без рамки
                : color(Color::GrayLight);
            entries.push_back(text(items[i]) | style);
        }

        return vbox(std::move(entries));
    });

    // Обработка клавиш
    menu = CatchEvent(menu, [&](Event event) {
        if (event == Event::Character('q') || event == Event::Character('Q') || event == Event::Character('й') || event == Event::Character('Й')) {
            screen.Exit(); // Завершаем приложение
            return 1;   // Событие обработано
        }
        if (event == Event::ArrowUp && selected > 0) {
            selected--;

            std::string cmd = "i3-msg move container to workspace " + std::to_string(selected+1);
            system(cmd.c_str());

            cmd = "i3-msg workspace " + std::to_string(selected+1);
            system(cmd.c_str());

            return 1;
        }
        if (event == Event::ArrowDown && selected < (int)items.size() - 1) {
            selected++;

            std::string cmd = "i3-msg move container to workspace " + std::to_string(selected+1);
            system(cmd.c_str());

            cmd = "i3-msg workspace " + std::to_string(selected+1);
            system(cmd.c_str());

            return 1;
        }
        return 0;

    });

    Component renderer = Renderer(menu, [&] 
    {
        return vbox({
            text("Workspace List:") | bold | color(Color::MagentaLight) | size(HEIGHT, LESS_THAN, 100) ,
            separator(),
            menu->Render() | bold | color(Color::GrayLight),
            separator(),
            text("Active: " + items[selected]) | color(Color::GreenLight)
        }) | frame | border | size(HEIGHT, LESS_THAN, 100);
    });

    screen.Loop(renderer);
}