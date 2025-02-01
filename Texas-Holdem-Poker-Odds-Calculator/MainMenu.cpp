#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

//Начальное меню//
void print_mainMenu(Game* game, Settings* settings, PokerCombination* result_player, int* choice) {
    printf("\n");
    printf("================================================\n");
    printf("               Добро пожаловать!                \n");
    printf("================================================\n");
    printf("Выберите действие:\n");
    printf("1. Покерный калькулятор\n");
    printf("2. Режим практики\n");
    printf("3. Настройки\n");
    printf("4. Прочее\n");
    printf("------------------------------------------------\n");
    printf("0. Выход из программы\n");
    printf("================================================\n");
    printf("Ваш выбор: ");
    get_user_choice(choice);
    handle_mainMenu_choice(game, settings, result_player, *choice);
}

//Получение выбора пользователя//
void get_user_choice(int* choice) {
    *choice = (int)scanf_secure("int");
}

//Обработка выбора пользователя в основном меню//
void handle_mainMenu_choice(Game* game, Settings* settings, PokerCombination* result_player, int choice) {
    switch (choice) {
    case 0:
        printf("Вы уверены?\n");
        printf("Y/yes - да\n");
        printf("N/no - нет\n");

        char str_choice[3];
        string_get_secure(str_choice, 3);

        for (int i = 0; str_choice[i]; i++) {
            str_choice[i] = tolower(str_choice[i]);
        }

        if (strcmp(str_choice, "y") == 0 || strcmp(str_choice, "yes") == 0) {
            exit(0);
        }
        else {
            printf("Операция отменена.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }
    
        break;
    case -1:
        clearConsole(); //Обработка неправильного ввода функции scanf_secure (фича)
        break;

    case 1:
        clearConsole();
        print_calculatorMenu(game, settings, result_player);
        break;

    case 2:
        printf("Не реализовано\n");
        press_any_key_to_continue();
        clearConsole();
        break;

    case 3:
        clearConsole();
        print_settingsMenu(settings);
        break;
    case 4:
        printf("Status: Stable\n");
        printf("Version program: 3.2.2\n");
        printf("Author: Saifect@mail.ru\n");
        press_any_key_to_continue();
        break;

    default:
        break;
    }
}

