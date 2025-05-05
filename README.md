# Система управления компьютерным клубом
### Структура проекта
* `main.cpp`: Точка входа, обработка аргументов.
* `club.h/cpp`: Управление клубом, обработка событий.
* `event.h/cpp`: Парсинг и обработка событий.
* `table.h/cpp`: Управление состоянием столов.
* `utils.h/cpp`: Утилиты для работы со временем.
* `tests/`: Примеры входных данных.
* `tests.sh`: Скрипт для автотестов (Linux).

### Требования
<p>Компилятор: GCC или Clang (Linux), MinGW/Cygwin (Windows).<p>
<p>Стандарт: C++14 и выше.<p>

### Сборка
```bash
# Ubuntu/Debian
sudo apt install build-essential
```
```bash
# Сборка
make
```
### Запуск
```bash
# Запуск программы
./program <input_file>
```
### Тестирование
```bash
# Linux
chmod +x tests.sh
bash tests.sh
```
