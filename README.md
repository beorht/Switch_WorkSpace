

# 🖥️ Switch_WorkSpace

Интерактивное графическое приложение на **Qt 6 + C++**, позволяющее просматривать и управлять рабочими пространствами оконного менеджера **i3wm**.  
Также реализован анализ JSON-ответа от `i3-msg`.

---

## 📦 Возможности

- ✅ Получение списка рабочих пространств (через `i3-msg`)
- ✅ Отображение текущего активного рабочего пространства
- ✅ Перемещение активного окна в выбранное workspace
- ✅ Красивый графический интерфейс (Qt6, QWidgets)
- ✅ Обработка JSON (через `nlohmann/json`)
- ✅ Управление с клавиатуры (напр. клавиша `Q` — выход)

---

## 🧰 Используемые технологии

- Qt 6 (Widgets)
- C++17
- [nlohmann/json](https://github.com/nlohmann/json)
- i3 window manager (`i3-msg` API)
- Linux/Unix среда

---

## 🚀 Установка и сборка

### 🔧 Зависимости

Убедитесь, что у вас установлены:

- `g++` (или `clang++`)
- `qt6-base-dev`
- `pkg-config`
- `libnlohmann-json-dev` (или локальная `json.hpp`)
- установленный `i3` и утилита `i3-msg`

### 🛠️ Сборка

```bash
git clone https://github.com/beorht/Switch_WorkSpace.git
cd Switch_WorkSpace
g++ gui.cpp -o Switch_WorkSpace -I. -fPIC $(pkg-config --cflags --libs Qt6Widgets)
````

### ▶️ Запуск

```bash
./Switch_WorkSpace
```

> Программа автоматически определит активное рабочее пространство и отобразит его в GUI.

---

## 💡 Структура проекта

```bash
.
├── gui.cpp          # Главный файл приложения
├── gui.h            # UI-интерфейс (Qt Designer, .ui → .h)
├── json.hpp         # Заголовок JSON-парсера (nlohmann/json)
├── designer.ui      # Исходный .ui-файл (если есть)
└── README.md        # Документация
```

---

## ⌨️ Горячие клавиши

* `↑ / ↓` — выбор workspace
* `Q` — выход из программы

---

## 🧠 Примечания

* Подходит для использования в i3wm и других *tiling window managers*.
* JSON-ответ парсится из команды:

  ```bash
  i3-msg -t get_workspaces
  ```

---

## 🧑‍💻 Автор

Разработчик: [beorht](https://github.com/beorht)
