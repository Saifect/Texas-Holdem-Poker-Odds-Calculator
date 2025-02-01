#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

void print_probabilityMenu(Game* game, Settings* settings, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    
    int num_simulations = settings->get_num_simulations();
    int probabilityMenu_choice = 0;
    bool exit = false;

    while (exit == false) {

        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        for (int i = 0; i < game->get_current_players(); i++) {
            // Проверяем, были ли введены карты игрока
            const Card& card1 = game->get_player(i).get_hand().get_const_card(0);
            const Card& card2 = game->get_player(i).get_hand().get_const_card(1);

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

        // Карты на столе
        if (strcmp(game->get_phase(), "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            print_board_cards(&game->get_board());
        }
        printf("Текущая стадия игры (улица): %s\n", game->get_phase());

        double estimated_time;
        int current_players = game->get_current_players();
        // Получаем количество симуляций и текущее число игроков
        int num_simulations = settings->get_num_simulations();

        if (num_simulations == 250000 && current_players == 2) {
            estimated_time = 1.65;
        }
        else if (num_simulations == 50000 && current_players == 2) {
            estimated_time = 0.4;
        }
        else {
     
            // Для 2 игроков: 100000 симуляций занимают примерно 0.70 секунд
            double base_time_per_sim_2 = 0.67 / 100000.0; // сек/симуляция для 2 игроков
         
            // Показатель степени, полученный из измерений для 10 игроков:
            // (10/2)^k = 5^k = 1.78  -->  k ≈ 0.358
            const double EXPONENT = 0.358;

            // Вычисляем время на одну симуляцию с учётом текущего числа игроков
            double time_per_simulation = base_time_per_sim_2 * pow((double)current_players / 2.0, EXPONENT);

            // Итоговое оценочное время (в секундах)
            estimated_time = num_simulations * time_per_simulation;
        }

        printf("================================================\n");
        printf("             Настройка симуляций               \n");
        printf("================================================\n");
        printf("Текущее количество симуляций: %d\n", num_simulations);
        printf("Будет считаться примерно %.2f секунд(ы)\n", estimated_time); // Вывод времени
        if (settings->get_wins_visible_mode() == false && settings->get_ties_visible_mode() == false && settings->get_simulations_visible_mode() == false) {
            printf("Режим отладки для симмуляций: Выключен\n");
        }
        else {
            printf("Режим отладки для симмуляций: Включен\n");
        }
        printf("================================================\n");
        printf("       Редактор вычисления вероятностей         \n");
        printf("================================================\n");
        printf("1. Расчёт по методу симуляций Монте-Карло\n");
        printf("2. Изменить количество симуляций\n");
        if (settings->get_show() == true && settings->get_debugging_mode() == true) {
            printf("3. Скрыть элементы отладки\n");
            printf("4. %s отображение побед для игрока (отладка)\n",
                settings->get_wins_visible_mode() ? "Выключить" : "Включить");
            printf("5. %s отображение ничей (отладка)\n",
                settings->get_ties_visible_mode() ? "Выключить" : "Включить");
            printf("6. %s отображение всех симуляций (отладка)\n",
                settings->get_simulations_visible_mode() ? "Выключить" : "Включить");
            printf("7. Вывести массив учтённых карт (отладка)\n");
        }
        else if (settings->get_debugging_mode() == true) {
            printf("3. Показать элементы отладки\n");
        }
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        get_user_choice(&probabilityMenu_choice);
        handle_probabilityMenu_choice(probabilityMenu_choice, game, &exit, used_cards, settings);
    }
}

void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[NUM_RANKS][NUM_SUITS], Settings* settings) {

    int choice_user;
    char str_choice[4];
    int players_with_cards = 0;
    switch (choice) {
    case 0:
        *exit = true;
        clearConsole();
        break;

    case 1:
        for (int i = 0; i < game->get_current_players(); i++) {
            // Проверяем есть ли карты у игрока
            if (game->get_player(i).get_hand().get_const_card(0).get_rank() != NONE_RANK && game->get_player(i).get_hand().get_const_card(1).get_rank() != NONE_RANK) {
                players_with_cards++;
            }

            if (players_with_cards >= 2) {
                break;
            }
        }

        // Проверяем результат
        if (players_with_cards < 2) {
            printf("Карты для хотя-бы 2-x игроков не заданы.\n");
            press_any_key_to_continue();
            clearConsole();
        }
        else if (settings->get_num_simulations() >= settings->get_min_simulations() && settings->get_num_simulations() <= settings->get_max_simulations()) {

            if (settings->get_debugging_mode() == true && settings->get_num_simulations() > 5000) {
                if (settings->get_num_simulations() > 3000 && settings->get_num_simulations() < 10000) {
                    printf("Использовать режим отладки с количеством симуляций < 3000 не рекомендуется\nВы уверены?\n");
                }
                if (settings->get_num_simulations() > 10000 && settings->get_num_simulations() < 50000) {
                    printf("Оу, это будет долговато.\nДля режима отладки рекомендуется < 3000 симуляций, вы уверены?\n");
                }
                if (settings->get_num_simulations() > 50000 && settings->get_num_simulations() < 100000) {
                    printf("Это может быть очень долго.\nДля режима отладки рекомендуется < 3000 симуляций, вы уверены?\n");
                }
                else {
                    printf("Это будет в высшей степени долго.\nДля режима отладки рекомендуется < 3000 симуляций, вы уверены?\n");
                }
                printf("Y/yes - да\n");
                printf("N/no - нет\n");

                char str_choice[3];
                string_get_secure(str_choice, 3);

                // Приводим ввод к нижнему регистру //
                for (int i = 0; str_choice[i]; i++) {
                    str_choice[i] = tolower(str_choice[i]);
                }

                if (strcmp(str_choice, "y") == 0 || strcmp(str_choice, "yes") == 0) {

                    printf("Продолжаем выполнение в режиме отладки с %d симуляциями.\n", settings->get_num_simulations());

                }
                else {

                    printf("Операция отменена.\n");
                    press_any_key_to_continue();
                    clearConsole();
                    break;
                }

                press_any_key_to_continue();
                clearConsole();
            }
            printf("Зажмите 'Q' для выхода\n");
            printf("Загрузка...\n");
            calculate_probabilities(game, used_cards, settings->get_num_simulations(), settings);
            clearConsole();
        }
        break;

    case 2: {
   
        printf("-----------------------------------------------\n");
        printf("Введите количество симуляций\nДиапазон значений от %d до %d\n", settings->get_min_simulations(), settings->get_max_simulations());
        printf("Рекомендуется 100.000 - 300.000 симуляций\n");
        printf("Или введите 0 для отмены\n");
        printf("-----------------------------------------------\n");
        printf("Ваш выбор: ");
        int num_simulations_new = scanf_secure("int");

        if (num_simulations_new == 0) {
            printf("Операция отменена.\n");
            press_any_key_to_continue();
            clearConsole();
        }
        else if (num_simulations_new >= settings->get_min_simulations() && num_simulations_new <= settings->get_max_simulations()) {
            settings->set_num_simulations(num_simulations_new); // обновляем количество симуляций
            printf("Вы установили %d симуляций для метода Монте-Карло\n", num_simulations_new);
            if (settings->get_debugging_mode() == true) {
                printf("Текущее количество симуляций в settings: %d\n", settings->get_num_simulations()); // Отладочный вывод
            }
            press_any_key_to_continue();
            clearConsole();
        }
        else {
            printf("Вы ввели значение вне диапазона! Используем %d по умолчанию.\n", settings->get_num_simulations());
            settings->set_num_simulations(DEF_SIMULATIONS); // значение по умолчанию
            press_any_key_to_continue();
            clearConsole();
        }
        break;
    }

    case 3:
        if (settings->get_debugging_mode() == true) {
            settings->set_show(!settings->get_show());
        }
        clearConsole();
        break;

    case 4:
        if (settings->get_wins_visible_mode() == true && settings->get_debugging_mode() == true) {
            settings->set_wins_visible_mode(false);
            clearConsole();
        }
        else if (settings->get_debugging_mode() == true){
            printf("Введите номер игрока или 0 для отмены: ");
            choice_user = scanf_secure("int");
            if (choice_user == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }
            else if (choice_user < 1 || choice_user > game->get_num_players()) {
                printf("Вы ввели число вне диапазона!\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }
            else {
                settings->set_current_winner(choice_user);
                settings->set_wins_visible_mode(!settings->get_wins_visible_mode());
                if (settings->get_ties_visible_mode() == true) {
                    settings->set_ties_visible_mode(false);
                }
                clearConsole();
            }
        }
        clearConsole();
        break;

    case 5:
        if (settings->get_debugging_mode() == true) {
            settings->set_ties_visible_mode(!settings->get_ties_visible_mode());
            if (settings->get_wins_visible_mode() == true) {
                settings->set_wins_visible_mode(false);
            }
            if (settings->get_simulations_visible_mode() == true) {
                settings->set_simulations_visible_mode(false);
            }
        }
        clearConsole();
        break;

    case 6:
        if (settings->get_debugging_mode() == true) {
            settings->set_simulations_visible_mode(!settings->get_simulations_visible_mode());
            if (settings->get_wins_visible_mode() == true) {
                settings->set_wins_visible_mode(false);
            }
            if (settings->get_ties_visible_mode() == true) {
                settings->set_ties_visible_mode(false);
            }
        }
        clearConsole();
        break;

    case 7:
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


void flush_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
