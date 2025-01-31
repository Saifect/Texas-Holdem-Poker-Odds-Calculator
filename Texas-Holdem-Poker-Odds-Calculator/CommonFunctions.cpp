#define _CRT_SECURE_NO_WARNINGS
#include "CommonFunctions.h"           


double scanf_secure(const char* type) {
    while (1) {
        if (strcmp(type, "int") == 0) {
            int num;
            if (scanf("%d", &num) == 1) {
                while (getchar() != '\n');
                return num;
            }
            else {
                printf("������ �����. ����������, ������� ����� �����.\n");
                press_any_key_to_continue();
                clear_buffer();
                return -1;
            }
        }
        else if (strcmp(type, "float") == 0) {
            float num;
            if (scanf("%f", &num) == 1) {
                while (getchar() != '\n');
                return num;
            }
            else {
                printf("������ �����. ����������, ������� ������������ �����: ");
                clear_buffer();
            }
        }
        else if (strcmp(type, "double") == 0) {
            double num;
            if (scanf("%lf", &num) == 1) {
                while (getchar() != '\n');
                return num;
            }
            else {
                printf("������ �����. ����������, ������� ������������ �����: ");
                clear_buffer();
            }
        }
        else if (strcmp(type, "bool") == 0) {
            char input[10];
            if (scanf("%9s", input) == 1) {
                if (strcmp(input, "true") == 0 || strcmp(input, "1") == 0) { //��� ������������� ������� � � ������ ������ ���
                    return 1;
                }
                else if (strcmp(input, "false") == 0 || strcmp(input, "0") == 0) {
                    return 0;
                }
                else {
                    printf("������ �����. ����������, ������� 'true' ��� 'false': ");
                    clear_buffer();
                }
            }
            else {
                printf("������ �����. ����������, ������� 'true' ��� 'false': ");
                clear_buffer();
            }
        }
        else {
            printf("����������� ��� ������.\n");
            return 0;
        }
    }
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// ������� �������
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// �������� ������
void line_remove(char* str) {

    str[strcspn(str, "\n")] = '\0';
}

// ��������� ������ � ������� �� ������������ ������
void string_get_secure(char* buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        line_remove(buffer);
    }
    else {
        clear_buffer();
    }
}

void press_any_key_to_continue() {
    printf("������� ����� ������� ��� �����������...\n");
    _getch(); // �������� ������� �������
}

void print_used_cards(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    int count = 0;
    printf("�������������� �����:\n");
    printf("     �����  �����  �����  ����\n");

    // �������� �� ������ ����
    for (int rank = 0; rank < NUM_RANKS; rank++) { // ����� �� 0 �� 12
        printf("%2d: ", rank + 2); // ���������� ���� ��� 2..14

        // �������� �� ������ ����
        for (int suit = 0; suit < NUM_SUITS; suit++) { // ����� �� 0 �� 3
            if (used_cards[rank][suit]) {
                count++;
            }
            printf("%5s ", used_cards[rank][suit] ? "��" : "���");
        }

        printf("\n"); // ������� �� ����� ������ ����� ������ ������ ����/�����
    }

    printf("���������� ������� ����: %d\n", count);
}