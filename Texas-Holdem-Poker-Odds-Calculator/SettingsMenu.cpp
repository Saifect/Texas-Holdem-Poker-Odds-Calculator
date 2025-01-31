#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

void print_settingsMenu(Settings* settings) {
    int choice;
    bool exit = false; // ���� ��� ������ �� �����

    while (!exit) {
        printf("\n");
        printf("================================================\n");
        printf("                   ���������                    \n");
        printf("================================================\n");
        printf("�������� ��������:\n");
        printf("1. ��������� ���������� ���������\n");

        // �������� ��������� ������ �������
        if (settings->get_debugging_mode()) {
            printf("2. ��������� ����� �������\n");
        }
        else {
            printf("2. �������� ����� �������\n");
        }

        printf("------------------------------------------------\n");
        printf("0. �����\n");
        printf("================================================\n");
        printf("��� �����: ");
        get_user_choice(&choice);

        // ��������� ������ ������������
        handle_settingsMenu_choice(settings, choice, &exit);
    }
}

void handle_settingsMenu_choice(Settings* settings, int choice, bool* exit) {
    switch (choice) {
    case 1:
        // ��������� ���������� ���������
        clearConsole();
        configure_simulations(settings);
        clearConsole();
        break;

    case 2:
        // ������������ ������ �������
        settings->set_debugging_mode(!settings->get_debugging_mode());
        clearConsole();
        break;

    case 0:
        // ����� �� ���� ��������
        *exit = true; // ������������� ���� ��� ������ �� �����
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
        printf("         ��������� ���������� ���������         \n");
        printf("================================================\n");
        printf("�������� �������� ��� ���������:\n");
        printf("1. ������������ ���������� ������� (�������: %d)\n", settings->get_max_players());
        printf("2. ����������� ���������� ��������� (�������: %d)\n", settings->get_min_simulations());
        printf("3. ������������ ���������� ��������� (�������: %d)\n", settings->get_max_simulations());
        printf("4. ���������� ��������� �� ��������� (�������: %d)\n", settings->get_num_simulations());
        printf("------------------------------------------------\n");
        printf("0. �����\n");
        printf("================================================\n");
        printf("��� �����: ");
        get_user_choice(&choice);

        if (choice == 0) {
            exit = true; // ������� � ���������� ����
        }
        else {
            printf("������� ����� ��������: ");
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
            printf("�������� ������� �������.\n");
            press_any_key_to_continue();
            clearConsole();
        }
    }
}