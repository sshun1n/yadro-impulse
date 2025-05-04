#!/bin/bash

PROGRAM="./program"
TEST_DIR="tests"
TMP_DIR="${TEST_DIR}/tmp"
PASS=0
FAIL=0

# Создаем временную папку
mkdir -p "$TMP_DIR"

# Проверка наличия программы
if [ ! -f "$PROGRAM" ]; then
    echo "Ошибка: исполняемый файл $PROGRAM не найден!"
    echo "Соберите проект с помощью make перед запуском тестов"
    exit 1
fi

# Функция для запуска одного теста
run_test() {
    local test_num=$1
    local input="${TEST_DIR}/test${test_num}.txt"
    local expected="${TEST_DIR}/expected_test${test_num}.txt"
    local actual="${TMP_DIR}/actual_test${test_num}.txt"
    
    # Проверка наличия файлов
    if [ ! -f "$input" ]; then echo "Тест $test_num: отсутствует $input"; return 1; fi
    if [ ! -f "$expected" ]; then echo "Тест $test_num: отсутствует $expected"; return 1; fi

    # Запуск теста
    $PROGRAM "$input" > "$actual" 2>&1

    # Проверка результата
    if diff -wB "$actual" "$expected" > /dev/null; then
        echo -e "Тест $test_num: \033[32mПРОЙДЕН\033[0m"
        ((PASS++))
        return 0
    else
        echo -e "Тест $test_num: \033[31mПРОВАЛЕН\033[0m"
        echo "Различия:"
        diff -wB --color "$actual" "$expected"
        ((FAIL++))
        return 1
    fi
}

# Запуск всех тестов (1-5)
for test_num in {1..5}; do
    run_test "$test_num"
done

# Статистика
echo "--------------------------------"
echo "Всего тестов: $((PASS + FAIL))"
echo -e "Пройдено: \033[32m$PASS\033[0m"
echo -e "Провалено: \033[31m$FAIL\033[0m"

# Удаление временных файлов (раскомментируйте при необходимости)
# rm -rf "$TMP_DIR"

# Возвращаем код ошибки, если есть проваленные тесты
if [ $FAIL -ne 0 ]; then
    exit 1
else
    exit 0
fi