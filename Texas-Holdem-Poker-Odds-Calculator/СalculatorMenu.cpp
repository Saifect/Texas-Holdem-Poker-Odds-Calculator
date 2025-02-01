#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

void print_calculatorMenu(Game* game, Settings* settings, PokerCombination* result_player) {
    srand(time(NULL));

    game->set_current_players(2);  // Установка текущих игроков через сеттер
    int choice = -1;
    bool edit_mode = false;
    int edit_current_player = 0;
    bool exit = false;

    while (!exit) {
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        for (int i = 0; i < game->get_current_players(); i++) {
            const Hand& hand = game->get_player(i).get_hand();  // Получаем руку через геттер
            const Card& card1 = hand.get_const_card(0);
            const Card& card2 = hand.get_const_card(1);

            if (card1.get_rank() != NONE_RANK && card2.get_rank() != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    card1.get_rank_name(),
                    card1.get_suit_name(),
                    card2.get_rank_name(),
                    card2.get_suit_name());
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
        }

        if (strcmp(game->get_phase(), "preflop") == 0) {  // Используем геттер для фазы игры
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            print_board_cards(&game->get_board());
        }

        printf("Текущая стадия игры (улица): %s\n", game->get_phase());  // Используем геттер для фазы

        // Меню
        printf("================================================\n");
        printf("           Функционал калькулятора              \n");
        printf("================================================\n");
        printf("1. Редактор игроков\n");
        printf("2. Редактор стола и стадий игры\n");
        printf("3. Редактор вычисления вероятностей\n");
        printf("4. Проанализировать комбинации игроков\n");
        if (settings->get_debugging_mode() == true) {
            printf("5. Вывести массив учтённых карт (отладка)\n");
        }

        printf("-----------------------------------------------\n");
        printf("0. Выйти из покерного калькулятора\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        get_user_choice(&choice);
        handle_calculatorMenu_choice(choice, game, settings, &exit, result_player);
    }
}

void handle_calculatorMenu_choice(int choice, Game* game, Settings* settings, bool* exit, PokerCombination* result_player) {
    if (result_player == NULL) {
        printf("Ошибка: недостаточно памяти для вычисления комбинаций.\n");
        press_any_key_to_continue();
        return;
    }    

    // Обработка выбора пользователя
    switch (choice) {
    case -1:
        clearConsole();
        break;

    case 0:
        *exit = true;
        clearConsole();
        break;

    case 1:
        clearConsole();
        print_editPlayerMenu(game, settings, used_cards);
        break;

    case 2:
        clearConsole();
        print_editBoardMenu(game, settings, used_cards);
        break;

    case 3:
        clearConsole();
        print_probabilityMenu(game, settings, used_cards);
        break;

    case 4:
        for (int i = 0; i < game->get_current_players() && i < game->get_num_players(); i++) {
            if (game->get_player(i).get_hand().get_const_card(0).get_rank() != NONE_RANK &&
                game->get_player(i).get_hand().get_const_card(1).get_rank() != NONE_RANK) {
                if (i == 0) {
                    printf("-----------------------------------------------\n");
                }
                printf("Карты %d-го игрока:\n", i + 1);
                result_player[i] = determine_hand(game->get_player(i).get_hand(), game->get_board());
                print_hand(result_player[i]);
                printf("-----------------------------------------------\n");
            }
            else {
                printf("Карты %d-го игрока не заданы!\n", i + 1);
            }
        }

        press_any_key_to_continue();
        clearConsole();
        break;

    case 5:
        if (settings->get_debugging_mode() == true) {
            print_used_cards(used_cards);
            press_any_key_to_continue();
        }
        clearConsole();
        break;

    default:
        clearConsole();
        break;
    }
}
