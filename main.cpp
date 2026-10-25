#include "lab3.h"
#include <iostream>
#include <clocale>

int main() {
    // Включаем поддержку русского языка в консоли
    std::setlocale(LC_ALL, "Russian");

    // Запуск всего приложения
    Lab3::runApplication();

    return 0;
}