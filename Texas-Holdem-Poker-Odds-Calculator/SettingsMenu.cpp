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
    int choice;
    int value;
    bool exit = false;
    while (!exit) {
        printf("\n");
        printf("================================================\n");
        printf("         Настройка количества симуляций         \n");
        printf("================================================\n");
        printf("Выберите параметр для изменения:\n");
        printf("1. Максимальное количество игроков (текущее: %d)\n", settings->get_max_players());
        printf("2. Минимальное количество симуляций (текущее: %d)\n", settings->get_min_simulations());
        printf("3. Максимальное количество симуляций (текущее: %d)\n", settings->get_max_simulations());
        printf("4. Количество симуляций по умолчанию (текущее: %d)\n", settings->get_num_simulations());
        printf("------------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");
        get_user_choice(&choice);

        if (choice == 0) {
            exit = true; // Возврат в предыдущее меню
        }
        else {
            printf("Введите новое значение: ");
            get_user_choice(&value);
        }

        switch (choice) {
        case 1:
            settings->set_max_players(value);
            break;

        case 2:
            settings->set_min_simulations(value);
            break;

        case 3:
            settings->set_max_simulations(value);
            break;

        case 4:
            settings->set_num_simulations(value);
            break;

        default:
            clearConsole();
            break;
        }

        if (choice != 0) {
            printf("Параметр успешно изменен.\n");
            press_any_key_to_continue();
            clearConsole();
        }
    }
}