#include <iostream>
#include <clocale>

namespace {
    const int MINUTES_MAX = 60;
    const int HOURS_MAX = 24;

    const int BORDER_MORNING = 5;
    const int BORDER_DAY = 12;
    const int BORDER_EVENING = 18;

    const int HOUR_NOON = 12;
    const int MINUTE_NOON = 0;
    const int HOUR_MIDNIGHT = 0;
    const int MINUTE_MIDNIGHT = 0;

    const int REMAINDER_10 = 10;
    const int REMAINDER_100 = 100;

    const int DIGIT_ONE = 1;
    const int DIGIT_TWO = 2;
    const int DIGIT_FOUR = 4;
    const int TEEN_START = 11;
    const int TEEN_END = 14;

    const int HOUR_LAST = 23;
}

void displayHoursDeclension(int h) {
    int rem10 = h % REMAINDER_10;
    int rem100 = h % REMAINDER_100;

    if (rem100 >= TEEN_START && rem100 <= TEEN_END) {
        std::cout << h << " часов";
    }
    else if (rem10 == DIGIT_ONE) {
        std::cout << h << " час";
    }
    else if (rem10 >= DIGIT_TWO && rem10 <= DIGIT_FOUR) {
        std::cout << h << " часа";
    }
    else {
        std::cout << h << " часов";
    }
}

void displayMinutesDeclension(int m) {
    int rem10 = m % REMAINDER_10;
    int rem100 = m % REMAINDER_100;

    if (rem100 >= TEEN_START && rem100 <= TEEN_END) {
        std::cout << m << " минут";
    }
    else if (rem10 == DIGIT_ONE) {
        std::cout << m << " минута";
    }
    else if (rem10 >= DIGIT_TWO && rem10 <= DIGIT_FOUR) {
        std::cout << m << " минуты";
    }
    else {
        std::cout << m << " минут";
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    int inputHours, inputMinutes;

    std::cout << "Введите часы и минуты (например, 2 48): ";
    std::cin >> inputHours >> inputMinutes;

    if (inputHours < 0 || inputHours >= HOURS_MAX || inputMinutes < 0 || inputMinutes >= MINUTES_MAX) {
        std::cout << inputHours << " " << inputMinutes << " - введены недопустимые данные\n";
        return 1;
    }

    if (inputHours == HOUR_NOON && inputMinutes == MINUTE_NOON) {
        std::cout << inputHours << " " << inputMinutes << " - полдень\n";
        return 0;
    }

    if (inputHours == HOUR_MIDNIGHT && inputMinutes == MINUTE_MIDNIGHT) {
        std::cout << inputHours << " " << inputMinutes << " - полночь\n";
        return 0;
    }

    std::cout << inputHours << " " << inputMinutes << " - ";
    displayHoursDeclension(inputHours);
    std::cout << " ";
    displayMinutesDeclension(inputMinutes);
    std::cout << " ";

    if (inputHours >= BORDER_MORNING && inputHours < BORDER_DAY) {
        std::cout << "утра";
    }
    else if (inputHours >= BORDER_DAY && inputHours < BORDER_EVENING) {
        std::cout << "дня";
    }
    else if (inputHours >= BORDER_EVENING && inputHours <= HOUR_LAST) {
        std::cout << "вечера";
    }
    else {
        std::cout << "ночи";
    }

    std::cout << "\n";
    return 0;
}2