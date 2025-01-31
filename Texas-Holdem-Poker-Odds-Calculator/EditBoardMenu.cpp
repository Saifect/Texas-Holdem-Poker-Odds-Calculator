#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

void print_editBoardMenu(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    int choice;
    bool exit_editor = false;
    int num_cards;
    bool deal_cards = true;
    bool debugging_mode = false;

    while (!exit_editor) {
        printf("\n");
        printf("================================================\n");
        printf("             ������� ����������                 \n");
        printf("================================================\n");

        for (int i = 0; i < game->get_current_players(); i++) {
            // ���������, ���� �� ������� ����� ������
            const Card& card1 = game->get_player(i).get_hand().get_const_card(0);
            const Card& card2 = game->get_player(i).get_hand().get_const_card(1);

            if (card1.get_rank() != NONE_RANK && card2.get_rank() != NONE_RANK) {
                printf("����� ������ %d: %s %s � %s %s\n", i + 1,
                    card1.get_rank_name(),
                    card1.get_suit_name(),
                    card2.get_rank_name(),
                    card2.get_suit_name());
            }
            else {
                printf("����� ������ %d: �� ������\n", i + 1);
            }
        }

        if (strcmp(game->get_phase(), "preflop") == 0) {
            printf("����� �� �����: �����������\n");
        }
        else {
            game->get_board().print_board_cards();
        }

        printf("������� ������ ���� (�����): %s\n", game->get_phase());
        printf("================================================\n");
        printf("               �������� �����                   \n");
        printf("================================================\n");
        printf("1. ��������/�������� Flop (3 �����)\n");
        printf("2. ��������/�������� Turn (4-�� �����)\n");
        printf("3. ��������/�������� River (5-�� �����)\n");
        printf("4. ��������� Flop ���������� �������\n");
        printf("5. ��������� Turn ��������� ������\n");
        printf("6. ��������� River ��������� ������\n");
        printf("7. �������� Turn\n");
        printf("8. �������� River\n");
        printf("9. �������� ����\n");
        if (debugging_mode == false) {
            printf("10. �������� �������� �������\n");
        }
        else {
            printf("10. ������ �������� �������\n");
        }
        if (debugging_mode == true) {
            printf("11. �������� ���������� ���� �� ����� (�������)\n");
            printf("12. ������� ������ ������� ���� (�������)\n");
        }

        printf("-----------------------------------------------\n");
        printf("0. �����\n");
        printf("================================================\n");
        printf("�������� ��������: ");
        choice = (int)scanf_secure("int");

        handle_editBoardMenu_choice(choice, game, &exit_editor, used_cards, &deal_cards, &debugging_mode);
    }
}

void handle_editBoardMenu_choice(int choice, Game* game, bool* exit_editor, bool used_cards[NUM_RANKS][NUM_SUITS], bool* deal_cards, bool* debugging_mode) {
    int num_cards;

    switch (choice) {
    case 1:
        printf("-----------------------------------------------\n");
        printf("     �������������� Flop (1-3 ����� �����)     \n");
        printf("-----------------------------------------------\n");
        *deal_cards = deal_board_cards(game, used_cards, 0, 3);  // ���� ��� ���� �� ����

        if (*deal_cards == true) {
            game->set_phase("flop");
        }

        break;

    case 2:
        if (game->get_board().get_num_cards() < 3) {
            printf("������� ���������� �������� Flop!\n");
            press_any_key_to_continue();
        }
        else {
        
            printf("-----------------------------------------------\n");
            printf("     �������������� Turn (�������� �����)     \n");
            printf("-----------------------------------------------\n");
            *deal_cards = deal_board_cards(game, used_cards, 3, 1);
     
        }
        break;

    case 3:
        if (game->get_board().get_num_cards() < 4) {
            printf("������� ���������� �������� Turn!\n");
            press_any_key_to_continue();
        }
        else {
     
            printf("-----------------------------------------------\n");
            printf("      �������������� River (����� �����)       \n");
            printf("-----------------------------------------------\n");
            *deal_cards = deal_board_cards(game, used_cards, 4, 1);
            if (*deal_cards == true) {
                game->set_phase("river");
            }
        }
        break;

    case 4:
        if (game->get_board().get_num_cards() < 3) {
            printf("�������������� Flop (��������� 3 �����)\n");
            deal_board_random_cards(game, used_cards, 0, 3);
        }
        else {
            printf("���� ��� �����! ������� �������� ����.\n");
            press_any_key_to_continue();
        }
        break;

    case 5:
        if (game->get_board().get_num_cards() < 3) {
            printf("������� ���������� �������� Flop!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 4 || game->get_board().get_num_cards() == 5) {
            printf("���� ��� �����! ������� �������� ����.\n");
            press_any_key_to_continue();
        }
        else {
            printf("�������������� Turn (��������� 4-�� �����)\n");
            deal_board_random_cards(game, used_cards, 3, 1);
        }
        break;

    case 6:
        if (game->get_board().get_num_cards() < 4) {
            printf("������� ���������� �������� Turn!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 5) {
            printf("����� ��� �����! ������� �������� ����.\n");
            press_any_key_to_continue();
        }
        else {
            printf("�������������� River (��������� 5-�� �����)\n");
            deal_board_random_cards(game, used_cards, 4, 1);
        }
        break;

    case 7:
        if (game->get_board().get_num_cards() < 3) {
            printf("������� ���������� �������� flop � turn!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 3) {
            printf("������� ���������� �������� turn!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 5) {
            printf("������� ���������� �������� River\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 4) {
            clear_board_turn(game, used_cards);
            printf("Turn ������!\n");
            press_any_key_to_continue();
        }
        break;

    case 8:
        if (game->get_board().get_num_cards() < 3) {
            printf("������� ���������� �������� flop � turn � river!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 3) {
            printf("������� ���������� �������� turn � river!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 4) {
            printf("������� ���������� �������� river!\n");
            press_any_key_to_continue();
        }
        else if (game->get_board().get_num_cards() == 5) {
            clear_board_river(game, used_cards);
            printf("River ������!\n");
            press_any_key_to_continue();
        }
        break;

    case 9:
        clear_board(game, used_cards);
        printf("���� ������!\n");
        press_any_key_to_continue();
        break;

    case 10:
        *debugging_mode = !(*debugging_mode);
        break;

    case 11:
        num_cards = game->get_board().get_num_cards();
        if (num_cards > 4) {
            printf("�� ����� ������: %d ����\n", num_cards);
        }
        else {
            printf("�� ����� ������: %d �����\n", num_cards);
        }
        press_any_key_to_continue();
        break;

    case 12:
        print_used_cards(used_cards);
        press_any_key_to_continue();
        clearConsole();
        break;

    case 0:
        *exit_editor = true;
        break;

    default:
        break;
    }
    clearConsole();
}

bool deal_board_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int start_index, int num_cards) {
    int rank_choice, suit_choice;
    int initial_num_cards = game->get_board().get_num_cards(); // ������� ���������� ���� �� �����
    int current_num_cards = initial_num_cards;
    bool rewrite = false;

    if (start_index + num_cards > 5) {
        printf("������: ��������� ������������ ���������� ���� �� �����.\n");
        return false;
    }

    // ����������� �����, ������� ����� ������������
    for (int i = 0; i < num_cards; i++) {
        if (start_index + i < initial_num_cards) {
            // �������� ������� ����� �� �����
            Card old_card = game->get_board().get_card(start_index + i);
            // ����������� � � ������� used_cards
            used_cards[old_card.get_rank()][old_card.get_suit()] = false;
        }
    }

    for (int i = 0; i < num_cards; i++) {
        do {
            printf("(11 - �����, 12 - ����, 13 - ������, 14 - ���)\n");
            printf("������� ���� ����� %d (2-14) ��� 0 ��� ������: ", start_index + i + 1);
            rank_choice = (int)scanf_secure("int");
            if (rank_choice == 0) {
                clear_board(game, used_cards); // ������ ���������
                return false;
            }
            if (rank_choice < 2 || rank_choice > 14) {
                printf("�������� ���� �����! ���������� �����.\n");
                continue;
            }
            printf("(1 - �����, 2 - �����, 3 - �����, 4 - ����)\n");
            printf("������� ����� ����� %d ��� 0 ��� ������: ", start_index + i + 1);
            suit_choice = (int)scanf_secure("int");
            if (suit_choice == 0) {
                clear_board(game, used_cards); // ������ ���������
                return false;
            }
            if (suit_choice < 1 || suit_choice > 4) {
                printf("�������� ����� �����! ���������� �����.\n");
                continue;
            }

            if (used_cards[rank_choice - 2][suit_choice - 1]) {
                printf("��� ����� ��� ������������! ���������� ������ �����.\n");
            }
            else {
                Card new_card((Suit)(suit_choice - 1), (Rank)(rank_choice - 2));
                if (start_index + i < current_num_cards) {
                    // ���������� ������������ �����
                    game->get_board().set_card(start_index + i, new_card);
                    rewrite = true;
                }
                else {
                    // ���������� ����� �����
                    game->get_board().add_card(new_card, used_cards);
                    current_num_cards++;
                }
                used_cards[rank_choice - 2][suit_choice - 1] = true;
                if (i + 1 == num_cards) {
                    press_any_key_to_continue();
                }
                break;
            }
        } while (true);
    }

    // ���������� ���� ����
    if (!rewrite) {
        if (current_num_cards > initial_num_cards) {
            if (current_num_cards == 3) {
                game->set_phase("flop");
            }
            else if (current_num_cards == 4) {
                game->set_phase("turn");
            }
            else if (current_num_cards == 5) {
                game->set_phase("river");
            }
        }
    }

    return true;
}

void deal_board_random_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int start_index, int num_cards) {
    int rank_choice, suit_choice;

    Card temp_cards[MAX_BOARD_CARDS];
    int temp_card_count = 0;

    for (int i = 0; i < num_cards; i++) {
        do {
            // ��������� ���������� ����� (�� 0 �� 12)
            rank_choice = rand() % NUM_RANKS;
            // ��������� ��������� ����� (�� 0 �� 3)
            suit_choice = rand() % NUM_SUITS;

            if (!used_cards[rank_choice][suit_choice]) {
                temp_cards[i].init_card((Suit)suit_choice, (Rank)rank_choice, used_cards);
                used_cards[rank_choice][suit_choice] = true; // �������� ����� ��� ��������������
                temp_card_count++;
                break;
            }
        } while (true);
    }

    // ���������� �����
    printf("��������������� �����:\n");
    for (int i = 0; i < num_cards; i++) {
        temp_cards[i].print_card();
    }
    press_any_key_to_continue();

    // ��������� ����� �� �����
    if (temp_card_count == num_cards) {
        for (int i = 0; i < num_cards; i++) {

            game->get_board().set_card(start_index + i, temp_cards[i]);
        }

        // ��������� ���������� ���� �� �����
        game->get_board().set_num_cards(start_index + num_cards);

        // �������� ���� ����
        if (game->get_board().get_num_cards() == 3) {
            game->set_phase("flop");
        }
        else if (game->get_board().get_num_cards() == 4) {
            game->set_phase("turn");
        }
        else if (game->get_board().get_num_cards() == 5) {
            game->set_phase("river");
        }
    }
    else {
        printf("�� ������� ������ ��� �����, ��������� ��������.\n");
        press_any_key_to_continue();
        for (int i = 0; i < temp_card_count; i++) {
            Rank rank = temp_cards[i].get_rank();
            Suit suit = temp_cards[i].get_suit();
            if (rank != NONE_RANK && suit != NONE_SUIT) {
                used_cards[rank][suit] = false;
            }
        }

    }
}

void clear_board(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    for (int i = 0; i < game->get_board().get_num_cards(); i++) {
        Card card = game->get_board().get_card(i);
        if (card.get_rank() != NONE_RANK && card.get_suit() != NONE_SUIT) {
            used_cards[card.get_rank()][card.get_suit()] = false;
        }
        card.init_card(NONE_SUIT, NONE_RANK, used_cards);
    }

    game->set_phase("preflop");
    game->get_board().set_num_cards(0);  // �������� ���������� ���� �� �����
}

void clear_board_turn(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    // ������� ����� ����� (��������� ����� �� �����)
    Card card = game->get_board().get_card(3); // ������ 3 ������������� ��������� ����� (0-based index)
    if (card.get_rank() != NONE_RANK && card.get_suit() != NONE_SUIT) {
        used_cards[card.get_rank()][card.get_suit()] = false;
    }
    card.init_card(NONE_SUIT, NONE_RANK, used_cards);

    game->get_board().set_num_cards(3); // ������������� ���������� ���� �� ����� ������� � 3 (����)
    game->set_phase("flop");
}


void clear_board_river(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    // ������� ����� ������ (����� ����� �� �����)
    Card card = game->get_board().get_card(4); // ������ 4 ������������� ����� ����� (0-based index)
    if (card.get_rank() != NONE_RANK && card.get_suit() != NONE_SUIT) {
        used_cards[card.get_rank()][card.get_suit()] = false;
    }
    card.init_card(NONE_SUIT, NONE_RANK, used_cards);

    game->get_board().set_num_cards(4); // ������������� ���������� ���� �� ����� ������� � 4 (����� �����)
    game->set_phase("turn");
}

void print_board_cards(const Board* board) {
    board->print_board_cards();
}











