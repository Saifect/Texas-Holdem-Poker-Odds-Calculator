#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

void print_settingsMenu(Settings* settings) {
    int choice;
    bool exit = false; // Флаг для выхода из цикла

    while (!exit) {
        printf("\n");
        printf("================================================\n");
        printf("                   Настройки                    \n");
        printf("================================================\n");
        printf("Выберите действие:\n");
        printf("1. Настроить количество симуляций\n");

        // Проверка состояния режима отладки
        if (settings->get_debugging_mode()) {
            printf("2. Выключить режим отладки\n");
        }
        else {
            printf("2. Включить режим отладки\n");
        }

        printf("------------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");
        get_user_choice(&choice);

        // Обработка выбора пользователя
        handle_settingsMenu_choice(settings, choice, &exit);
    }
}

void handle_settingsMenu_choice(Settings* settings, int choice, bool* exit) {
    switch (choice) {
    case 1:
        // Настройка количества симуляций
        clearConsole();
        configure_simulations(settings);
        clearConsole();
        break;

    case 2:
        // Переключение режима отладки
        settings->set_debugging_mode(!settings->get_debugging_mode());
        clearConsole();
        break;

    case 0:
        // Выход из меню настроек
        *exit = true; // Устанавливаем флаг для выхода из цикла
        clearConsole();
        break;

    default:
        clearConsole();
        break;
    }
}

void configure_simulations(Settings* settings) {
    int choice = -1;
    int value = 0;

    while (true) {
        printf("\n");
        printf("================================================\n");
        printf("         Настройка количества симуляций         \n");
        printf("================================================\n");
        printf("1. Максимальное количество игроков (текущее: %d)\n", settings->get_max_players());
        printf("2. Минимальное количество симуляций (текущее: %d)\n", settings->get_min_simulations());
        printf("3. Максимальное количество симуляций (текущее: %d)\n", settings->get_max_simulations());
        printf("4. Количество симуляций по умолчанию (текущее: %d)\n", settings->get_num_simulations());
        printf("------------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        choice = scanf_secure("int");

        if (choice < 0 || choice > 4) {
            printf("Ошибка: Введите корректный номер пункта (0-4).\n");
            press_any_key_to_continue();
            clearConsole();
            continue;
        }

        if (choice == 0) {
            return;  // Выход из меню
        }

        printf("Введите новое значение: ");
        value = scanf_secure("int");

        switch (choice) {
        case 1:
            if (value > 12) {
                printf("Ошибка: Максимальное количество игроков — 12!\n");
            }
            else if (value < 0) {
                printf("Отрицательные игроки, да? Звучит интересно\n");
            }
            else  if (value < 2) {
                printf("Нужно хотя бы два игрока для вычисления вероятностей\n");
            }
            else {
                settings->set_max_players(value);
                printf("Максимальное количество игроков обновлено.\n");
            }
            break;

        case 2:
            if (value > 0) {
                settings->set_min_simulations(value);
                printf("Минимальное количество симуляций обновлено.\n");
            }
            break;

        case 3:
            if (value > 0) {
                settings->set_max_simulations(value);
                printf("Максимальное количество симуляций обновлено.\n");
            }
            break;

        case 4:
            if (value > 0) {
                settings->set_num_simulations(value);
                printf("Количество симуляций по умолчанию обновлено.\n");
            }
            break;
        }

        press_any_key_to_continue();
        clearConsole();
    }
}
