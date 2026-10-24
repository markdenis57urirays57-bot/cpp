#include "lab3.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

namespace Lab3 {

    // Анонимный неймспейс для вспомогательных математических функций (строгое требование)
    namespace {
        const int MAX_ITERATIONS = 100000;

        // Исходная функция f(x) = x - k*cos(x)
        [[nodiscard]] double f(double x, double k) {
            return x - k * std::cos(x);
        }

        // Производная f'(x) = 1 + k*sin(x)
        [[nodiscard]] double df(double x, double k) {
            return 1.0 + k * std::sin(x);
        }

        // Функция для метода итераций phi(x) = k*cos(x)
        [[nodiscard]] double phi(double x, double k) {
            return k * std::cos(x);
        }

        // Структура для возврата результата вычислений (корень и кол-во итераций)
        struct MathResult {
            double root;
            int iterations;
            bool success;
        };

        // 1. Метод итераций
        [[nodiscard]] MathResult solveIteration(double x0, double k, double epsilon) {
            double x = x0;
            double x_prev = x0;
            int iters = 0;
            do {
                x_prev = x;
                x = phi(x_prev, k);
                iters++;
                if (iters > MAX_ITERATIONS) return { x, iters, false };
            } while (std::abs(x - x_prev) >= epsilon);
            return { x, iters, true };
        }

        // 2. Метод половинного деления
        [[nodiscard]] MathResult solveBisection(double xL, double xR, double k, double epsilon) {
            if (f(xL, k) * f(xR, k) > 0) {
                return { 0.0, 0, false }; // Некорректный интервал
            }
            int iters = 0;
            double xM = xL;
            while (std::abs(xR - xL) >= epsilon) {
                xM = (xL + xR) / 2.0;
                double fM = f(xM, k);
                if (std::abs(fM) < 1e-15) break; // Точное совпадение

                if (f(xL, k) * fM < 0) {
                    xR = xM;
                }
                else {
                    xL = xM;
                }
                iters++;
                if (iters > MAX_ITERATIONS) return { xM, iters, false };
            }
            return { xM, iters, true };
        }

        // 3. Метод Ньютона
        [[nodiscard]] MathResult solveNewton(double x0, double k, double epsilon) {
            double x = x0;
            double x_prev = x0;
            int iters = 0;
            do {
                x_prev = x;
                double derivative = df(x_prev, k);
                if (std::abs(derivative) < 1e-12) {
                    return { x, iters, false }; // Защита от деления на ноль
                }
                x = x_prev - f(x_prev, k) / derivative;
                iters++;
                if (iters > MAX_ITERATIONS) return { x, iters, false };
            } while (std::abs(x - x_prev) >= epsilon);
            return { x, iters, true };
        }

        // Вспомогательная функция вывода (вычисления и вывод строго разделены)
        void printResult(const MathResult& res) {
            if (res.success) {
                std::cout << "--> Корень найден: " << std::setprecision(8) << res.root << "\n";
                std::cout << "--> Количество итераций: " << res.iterations << "\n";
            }
            else {
                std::cout << "--> Ошибка: корень не найден (превышено число итераций или некорректные данные).\n";
            }
        }
    } // конец анонимного неймспейса

    [[nodiscard]] TaskOption getUserChoice() {
        std::cout << "\n=== ИНТЕРАКТИВНОЕ МЕНЮ ===\n";
        std::cout << "1. Метод итераций\n";
        std::cout << "2. Метод половинного деления\n";
        std::cout << "3. Метод Ньютона\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;

        // Очистка потока в случае ввода символов вместо чисел
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }
        // Кастуем int к enum class как требуется
        return static_cast<TaskOption>(choice);
    }

    void handleIteration() {
        double x0, k, eps;
        std::cout << "Введите начальное приближение (x0): ";
        std::cin >> x0;
        std::cout << "Введите коэффициент при cos(x) (k): ";
        std::cin >> k;
        std::cout << "Введите погрешность (например, 1e-6): ";
        std::cin >> eps;
        printResult(solveIteration(x0, k, eps));
    }

    void handleBisection() {
        double xL, xR, k, eps;
        std::cout << "Введите начало интервала (xL): ";
        std::cin >> xL;
        std::cout << "Введите конец интервала (xR): ";
        std::cin >> xR;
        std::cout << "Введите коэффициент при cos(x) (k): ";
        std::cin >> k;
        std::cout << "Введите погрешность (например, 1e-6): ";
        std::cin >> eps;
        printResult(solveBisection(xL, xR, k, eps));
    }

    void handleNewton() {
        double x0, k, eps;
        std::cout << "Введите начальное приближение (x0): ";
        std::cin >> x0;
        std::cout << "Введите коэффициент при cos(x) (k): ";
        std::cin >> k;
        std::cout << "Введите погрешность (например, 1e-6): ";
        std::cin >> eps;
        printResult(solveNewton(x0, k, eps));
    }

    void runApplication() {
        bool running = true;
        while (running) {
            TaskOption option = getUserChoice();

            switch (option) {
            case TaskOption::ITERATION:
                handleIteration();
                break;
            case TaskOption::BISECTION:
                handleBisection();
                break;
            case TaskOption::NEWTON:
                handleNewton();
                break;
            case TaskOption::EXIT:
                running = false;
                std::cout << "Завершение программы.\n";
                break;
            default:
                std::cout << "Неверный ввод, попробуйте снова.\n";
                break;
            }
        }
    }
}