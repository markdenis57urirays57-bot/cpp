#ifndef LAB3_H
#define LAB3_H

namespace Lab3 {
    // Строгое требование: использование enum class для меню
    enum class TaskOption {
        ITERATION = 1,
        BISECTION = 2,
        NEWTON = 3,
        EXIT = 0
    };

    // Интерфейсные функции приложения
    void runApplication();

    [[nodiscard]] TaskOption getUserChoice();
}

#endif // LAB3_H