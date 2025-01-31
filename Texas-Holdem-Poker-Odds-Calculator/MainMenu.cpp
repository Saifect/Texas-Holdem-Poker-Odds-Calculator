#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

//��������� ����//
void print_mainMenu(Game* game, Settings* settings, PokerCombination* result_player, int* choice) {
    printf("\n");
    printf("================================================\n");
    printf("               ����� ����������!                \n");
    printf("================================================\n");
    printf("�������� ��������:\n");
    printf("1. �������� �����������\n");
    printf("2. ����� ��������\n");
    printf("3. ���������\n");
    printf("4. ������\n");
    printf("------------------------------------------------\n");
    printf("0. ����� �� ���������\n");
    printf("================================================\n");
    printf("��� �����: ");
    get_user_choice(choice);
    handle_mainMenu_choice(game, settings, result_player, *choice);
}

//��������� ������ ������������//
void get_user_choice(int* choice) {
    *choice = (int)scanf_secure("int");
}

//��������� ������ ������������ � �������� ����//
void handle_mainMenu_choice(Game* game, Settings* settings, PokerCombination* result_player, int choice) {
    switch (choice) {
    case 0:
        exit(0);
        break;
    case -1:
        clearConsole(); //��������� ������������� ����� ������� scanf_secure (����)
        break;

    case 1:
        clearConsole();
        print_calculatorMenu(game, settings, result_player);
        break;
    case 2:
        printf("�� �����������\n");
        press_any_key_to_continue();
        clearConsole();
        break;
    case 3:
        clearConsole();
        print_settingsMenu(settings);
        break;
    case 4:
        printf("Status: Stable\n");
        printf("Version program: 3.0");
        printf("Author: Saifect@mail.ru\n");
        press_any_key_to_continue();
        break;

    default:
        break;
    }
}

