#pragma once
#include "Classes.h"
#include "CommonFunctions.h"

// ������������� ����
void initialize_game(Game* game, int num_players);

// ������� ������ ����
void print_mainMenu(Game* game, PokerCombination* result_player, int* choice);
void print_editPlayerMenu(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void print_editBoardMenu(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void print_calculatorMenu(Game* game, PokerCombination* result_player);
void print_used_cards(bool used_cards[NUM_RANKS][NUM_SUITS]);

// ������� �������� ����
void get_user_choice(int* choice);
void handle_mainMenu_choice(Game* game, PokerCombination* result_player, int choice);
void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[NUM_RANKS][NUM_SUITS], int* num_simulations, Settings_debugging_mode* settings);

// ������� ��������� ����
void handle_calculatorMenu_choice(int choice, Game* game, bool* exit, PokerCombination* result_player);
void handle_editPlayerMenu_choice(int choice, Game* game, bool* back, bool used_cards[NUM_RANKS][NUM_SUITS]);
void handle_editBoardMenu_choice(int choice, Game* game, bool* exit_editor, bool used_cards[NUM_RANKS][NUM_SUITS], bool* deal_cards, bool* debugging_mode);

// ��������������� �������
void deal_random_cards_all(Player players[], bool used_cards[NUM_RANKS][NUM_SUITS]);
void deal_cards(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS]);
void deal_random_cards(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_player);
void clear_player_cards(Player* players, int current_players, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_player, bool mute_mode);
void clear_all_players_cards(Player* players, int current_players, bool used_cards[NUM_RANKS][NUM_SUITS], bool mute_mode);

// ������� ��� ������ � ������
void clear_board(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void clear_board_turn(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void clear_board_river(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
bool deal_board_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int start_index, int num_cards);

// ������� ��� ������ � �������
void shuffle_deck(Card* deck, int size);
void create_deck(Card* deck, bool used_cards[NUM_RANKS][NUM_SUITS]);

// ������� ������ ����
PokerCombination determine_hand(const Hand hand, const Board board);
int compare_hands(PokerCombination hand1, PokerCombination hand2);
void print_hand(PokerCombination hand);
void print_board_cards(const Board* board);
void deal_board_random_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int start_index, int num_cards);

// ��������� �������, ���� ��� ���������� � ������ ����� ��� �����
void initialize_board_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void calculate_probabilities(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_numSimulations, Settings_debugging_mode* settings);
void print_probabilityMenu(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void compare_all_hands(Game* game, PokerCombination hands[]);
void calculate_probabilities_debugging(Game* game, Settings_debugging_mode* settings, Board simulated_board, PokerCombination* player_hands, int current_simulation, bool tie, int best_player);

void print_player_cards(const Game* game);
void print_board_info(const Game* game);
void print_debug_menu(const Settings_debugging_mode* settings);
void print_menu_header(const char* title);
void toggle_debug_option(bool* option, const char* description);
bool confirm_debug_simulation(int num_simulations);

void debug_board(const Board& board);