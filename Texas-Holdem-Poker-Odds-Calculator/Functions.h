#pragma once
#include "Classes.h"
#include "CommonFunctions.h"

// Инициализация игры
void initialize_game(Game* game, int num_players);

// Функции печати меню
void print_mainMenu(Game* game, Settings* settings, PokerCombination* result_player, int* choice);
void print_editPlayerMenu(Game* game, Settings* settings, bool used_cards[NUM_RANKS][NUM_SUITS]);
void print_editBoardMenu(Game* game, Settings* settings, bool used_cards[NUM_RANKS][NUM_SUITS]);
void print_calculatorMenu(Game* game, Settings* settings, PokerCombination* result_player);
void print_used_cards(bool used_cards[NUM_RANKS][NUM_SUITS]);

// Функции главного меню
void get_user_choice(int* choice);
void handle_mainMenu_choice(Game* game, Settings* settings, PokerCombination* result_player, int choice);
void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[NUM_RANKS][NUM_SUITS], Settings* settings);

// Функции обработки меню
void handle_calculatorMenu_choice(int choice, Game* game, Settings* settings, bool* exit, PokerCombination* result_player);
void handle_editPlayerMenu_choice(int choice, Game* game, Settings* settings, bool* back, bool used_cards[NUM_RANKS][NUM_SUITS]);
void handle_editBoardMenu_choice(int choice, Game* game, Settings* settings, bool* exit_editor, bool used_cards[NUM_RANKS][NUM_SUITS], bool* deal_cards, bool* debugging_mode);
void initialization_debug_settings(Settings* settings);

// Вспомогательные функции
void deal_random_cards_all(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS]);
void deal_cards(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS]);
void deal_random_cards(Player* player, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_player);
void clear_player_cards(Player* players, int current_players, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_player, bool mute_mode);
void clear_all_players_cards(Player* players, int current_players, bool used_cards[NUM_RANKS][NUM_SUITS], bool mute_mode);

// Функции для работы с доской
void clear_board(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void clear_board_turn(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
void clear_board_river(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS]);
bool deal_board_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int start_index, int num_cards);

// Функции для работы с колодой
void shuffle_deck(Card* deck, int size);
void create_deck(Card* deck, bool used_cards[NUM_RANKS][NUM_SUITS]);

// Функции логики игры
PokerCombination determine_hand(Hand& hand, const Board& board);
int compare_hands(const PokerCombination& hand1, const PokerCombination& hand2);
void print_hand(PokerCombination hand);
void print_board_cards(const Board* board);
void deal_board_random_cards(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int start_index, int num_cards);
void calculate_probabilities(Game* game, bool used_cards[NUM_RANKS][NUM_SUITS], int choice_numSimulations, Settings* settings);

// Прототипы функций, если они определены в другом месте или файле
void print_probabilityMenu(Game* game, Settings* settings, bool used_cards[NUM_RANKS][NUM_SUITS]);
void compare_all_hands(Game* game, PokerCombination hands[]);
void calculate_probabilities_debugging(Game* game, Settings* settings, Board simulated_board, PokerCombination* player_hands, int current_simulation, bool tie, int best_player);
void debug_board(const Board& board);

void handle_settingsMenu_choice(Settings* settings, int choice, bool* exit);
void print_settingsMenu(Settings* settings);
void configure_simulations(Settings* settings);
void update_progress_bar(int current_sim, int total_sims, double elapsed_seconds);
void flush_input_buffer();