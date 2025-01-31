#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

void print_editPlayerMenu(Game* game, bool used_cards[15][4]) {
    int choice;
    bool back = false;
    int choice_player;

    while (!back) {
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

        // ����� ���� �� �����
        if (strcmp(game->get_phase(), "preflop") == 0) {
            printf("����� �� �����: �����������\n");
        }
        else {
            game->get_board().print_board_cards();
        }

        printf("������� ������ ���� (�����): %s\n", game->get_phase());

        printf("================================================\n");
        printf("               �������� �������                 \n");
        printf("================================================\n");
        printf("1. ��������/�������� ����� ������\n");
        printf("2. ������������� ��������� ����� ������\n");
        printf("3. ������������� ��������� ����� ���� �������\n");
        printf("4. �������� ����� ������\n");
        printf("5. �������� ����� ���� �������\n");
        printf("6. ������ ���������� �������\n");
        printf("7. ������� ������ ������� ���� (�������)\n");
        printf("-----------------------------------------------\n");
        printf("0. �����\n");
        printf("================================================\n");
        printf("��� �����: ");

        // ��������� ������ ������������
        choice = (int)scanf_secure("int");

        handle_editPlayerMenu_choice(choice, game, &back, used_cards);
    }
}

void handle_editPlayerMenu_choice(int choice, Game* game, bool* back, bool used_cards[15][4]) {
    int choice_player;

    switch (choice) {
    case 0:
        *back = true;
        clearConsole();
        break;
    case 1:
        printf("������� ����� ������ ��� 0 ��� ������: ");
        choice_player = scanf_secure("int");
        if (choice_player == 0) {
            printf("������ ��������.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }

        if (choice_player < 0 || choice_player > game->get_current_players()) {
            printf("������ ��� ����� ������� �� ����������!\n");
            press_any_key_to_continue();
            clearConsole();
            return;
        }

        deal_cards(&game->get_player(choice_player - 1), used_cards);

        clearConsole();
        break;
    case 2:
        printf("������� ����� ������ ��� 0 ��� ������: ");
        choice_player = scanf_secure("int");
        if (choice_player == 0) {
            printf("������ ��������.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }
        deal_random_cards(&game->get_player(choice_player - 1), used_cards, choice_player);
        printf("���� ������ %d ������������� ��������!\n", choice_player);
        press_any_key_to_continue();
        clearConsole();
        break;

    case 3:
        for (int i = 0; game->get_current_players() > i; i++) {
            deal_random_cards(&game->get_player(i), used_cards, i);
        }

        printf("����� ��� ������� ������� �������������!\n");
        press_any_key_to_continue();
        clearConsole();
        break;

    case 4:
        printf("������� ����� ������ ��� 0 ��� ������: ");
        choice_player = scanf_secure("int");
        if (choice_player == 0) {
            printf("������ ��������.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }
        game->get_player(choice_player - 1).clear_player_cards(used_cards);
        printf("���� ������ %d ������� �������!\n", choice_player);
        press_any_key_to_continue();
        clearConsole();
        break;
    case 5:
        game->clear_all_players_cards(used_cards);
        clearConsole();
        break;
    case 6:
        printf("������� ���������� ������� (2-%d) ��� 0 ��� ������: ", game->get_num_players());
        choice_player = scanf_secure("int");

        if (choice_player == 0) {
            printf("������ ��������.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }

        if (choice_player == game->get_current_players()) {
            printf("� ��� ������� �� �������!\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }

        if (choice_player < 2 || choice_player > game->get_num_players()) {
            printf("�� ����� ����� ��� ���������!\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }

        if (choice_player < game->get_current_players()) {
            for (int i = choice_player; i < game->get_current_players(); i++) {
                game->get_player(i).clear_player_cards(used_cards);
            }
        }

        game->set_current_players(choice_player);
        printf("�� ������ %d ������� ��� ������������.\n", choice_player);
        press_any_key_to_continue();
        clearConsole();
        break;
    case 7:
        print_used_cards(used_cards);
        press_any_key_to_continue();
        clearConsole();
        break;
    default:
        clearConsole();
        break;
    }
}

void deal_cards(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    printf("------------------------------------------------\n");
    printf("          ���� ���� ��� ������\n");
    printf("------------------------------------------------\n");

    // ������� ������� ������� ����� ������
    player->clear_player_cards(used_cards);

    int rank_choice_card[2], suit_choice_card[2];

    for (int current_card = 0; current_card < 2; current_card++) {
        do {
            printf("������� ���� %d-�� ����� (2-14) ��� 0 ��� ������: ", current_card + 1);
            rank_choice_card[current_card] = (int)scanf_secure("int");
            if (rank_choice_card[current_card] == 0) {
                // ������ �����
                for (int j = 0; j < current_card; j++) {
                    player->get_hand().get_card(j).init_card(NONE_SUIT, NONE_RANK, used_cards);
                    used_cards[rank_choice_card[j] - 2][suit_choice_card[j] - 1] = false;
                }
                return;
            }
            if (rank_choice_card[current_card] < 2 || rank_choice_card[current_card] > 14) {
                printf("�������� ���� �����! ���������� �����.\n");
                continue;
            }

            printf("������� ����� %d-�� ����� (1 - �����, 2 - �����, 3 - �����, 4 - ����) ��� 0 ��� ������: ", current_card + 1);
            suit_choice_card[current_card] = (int)scanf_secure("int");
            if (suit_choice_card[current_card] == 0) {
                // ������ �����
                for (int j = 0; j < current_card; j++) {
                    player->get_hand().get_card(j).init_card(NONE_SUIT, NONE_RANK, used_cards);
                    used_cards[rank_choice_card[j] - 2][suit_choice_card[j] - 1] = false;
                }
                return;
            }
            if (suit_choice_card[current_card] < 1 || suit_choice_card[current_card] > 4) {
                printf("�������� ����� �����! ���������� �����.\n");
                continue;
            }

            // �������� �� ������������ �����
            if (used_cards[rank_choice_card[current_card] - 2][suit_choice_card[current_card] - 1]) {
                printf("��� ����� ��� ������������! ���������� ������ �����.\n");
            }
            else {
                // ������� �����
                Card new_card((Suit)(suit_choice_card[current_card] - 1), (Rank)(rank_choice_card[current_card] - 2));

                // ��������� ����� ������
                player->get_hand().set_card(current_card, new_card);

                // �������� ����� ��� ��������������
                used_cards[rank_choice_card[current_card] - 2][suit_choice_card[current_card] - 1] = true;

                // ���������� ����� ������� used_cards
                printf("����� ���������: %s %s\n",
                    new_card.get_rank_name(), new_card.get_suit_name());

                break;
            }
        } while (true);
    }
}


void deal_random_cards_all(Player* player, bool used_cards[15][4]) {
    // �������������� ������
    Card full_deck[52];
    create_deck(full_deck, used_cards);

    // ������ ��� ��������� ����
    Card* available_deck = (Card*)malloc(52 * sizeof(Card));
    int available_count = 0;

    // �������� ��������� �����
    for (int i = 0; i < 52; i++) {
        int rank = full_deck[i].get_rank();
        int suit = full_deck[i].get_suit() - 1;  // ����� ��������� �� 1 ��� ���������� ����������
        if (rank >= 2 && rank <= 14 && suit >= 0 && suit < 4) {
            if (!used_cards[rank][suit]) {
                available_deck[available_count++] = full_deck[i];
            }
        }
        else {
            printf("������: ������������ �������� rank = %d, suit = %d\n", rank, suit + 1);
        }
    }

    // ������������ ��������� �����
    shuffle_deck(available_deck, available_count);

    // ������������� ����� ����� ��� ������
    int old_rank1 = player->get_hand().get_card(0).get_rank();
    int old_suit1 = player->get_hand().get_card(0).get_suit() - 1;
    int old_rank2 = player->get_hand().get_card(1).get_rank();
    int old_suit2 = player->get_hand().get_card(1).get_suit() - 1;

    // ����������� ������ �����
    if (old_rank1 >= 2 && old_rank1 <= 14 && old_suit1 >= 0 && old_suit1 < 4) {
        used_cards[old_rank1][old_suit1] = false;
    }
    if (old_rank2 >= 2 && old_rank2 <= 14 && old_suit2 >= 0 && old_suit2 < 4) {
        used_cards[old_rank2][old_suit2] = false;
    }

    // ������ ����� �����
    player->get_hand().get_card(0) = available_deck[0];
    player->get_hand().get_card(1) = available_deck[1];

    int new_rank1 = player->get_hand().get_card(0).get_rank();
    int new_suit1 = player->get_hand().get_card(0).get_suit() - 1;
    int new_rank2 = player->get_hand().get_card(1).get_rank();
    int new_suit2 = player->get_hand().get_card(1).get_suit() - 1;

    // �������� ����� ����� ��� �������
    if (new_rank1 >= 2 && new_rank1 <= 14 && new_suit1 >= 0 && new_suit1 < 4) {
        used_cards[new_rank1][new_suit1] = true;
    }
    if (new_rank2 >= 2 && new_rank2 <= 14 && new_suit2 >= 0 && new_suit2 < 4) {
        used_cards[new_rank2][new_suit2] = true;
    }

    // ����������� ������
    free(available_deck);
}

void clear_player_cards(Player* players, int current_players, bool used_cards[15][4], int choice_player, bool mute_mode) {
    players[choice_player - 1].clear_player_cards(used_cards);
}

void clear_all_players_cards(Player* players, int current_players, bool used_cards[15][4], bool mute_mode) {
    for (int i = 0; i < current_players; i++) {
        players[i].clear_player_cards(used_cards);
        if (!mute_mode) {
            printf("���� ������ %d ������� �������!\n", i + 1);
        }
    }
    printf("�������� ���������!\n");
    press_any_key_to_continue();
}

void clear_player_hand(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    for (int i = 0; i < 2; i++) {
        if (player->get_hand().get_card(i).get_rank() != NONE_RANK && player->get_hand().get_card(i).get_suit() != NONE_SUIT) {
            used_cards[player->get_hand().get_card(i).get_rank()][player->get_hand().get_card(i).get_suit()] = false;
        }
        player->get_hand().get_card(i).set_rank(NONE_RANK);
        player->get_hand().get_card(i).set_suit(NONE_SUIT);
    }
}

void assign_random_card(Card* card, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    int rank, suit;
    do {
        rank = rand() % NUM_RANKS;
        suit = rand() % NUM_SUITS;
    } while (used_cards[rank][suit]);

    card->set_rank((Rank)rank);
    card->set_suit((Suit)suit);
    used_cards[rank][suit] = true;
}

void assign_random_hand(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    clear_player_hand(player, used_cards);
    for (int i = 0; i < 2; i++) {
        assign_random_card(&player->get_hand().get_card(i), used_cards);
    }
}

void deal_random_cards(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_player) {
    assign_random_hand(player, used_cards);
}