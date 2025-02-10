#define _CRT_SECURE_NO_WARNINGS
#include "Classes.h"
#include "CommonFunctions.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>

// Инициализация статического поля (оно объявлено в классе Card)
int Card::totalCardsCreated = 0;

////////////////////////////////////////
// Класс Card
////////////////////////////////////////

Card::Card() : suit(NONE_SUIT), rank(NONE_RANK), is_used(false) {
    totalCardsCreated++;  // увеличиваем счетчик при создании карты
}

Card::Card(Suit s, Rank r) : suit(s), rank(r), is_used(false) {
    totalCardsCreated++;  // увеличиваем счетчик при создании карты
}

Suit Card::get_suit() const { return suit; }
Rank Card::get_rank() const { return rank; }

void Card::set_suit(Suit s) { suit = s; }
void Card::set_rank(Rank r) { rank = r; }

std::string Card::get_rank_name_impl() const {
    switch (rank) {
    case TWO:   return "Двойка";
    case THREE: return "Тройка";
    case FOUR:  return "Четверка";
    case FIVE:  return "Пятерка";
    case SIX:   return "Шестерка";
    case SEVEN: return "Семерка";
    case EIGHT: return "Восьмерка";
    case NINE:  return "Девятка";
    case TEN:   return "Десятка";
    case JACK:  return "Валет";
    case QUEEN: return "Дама";
    case KING:  return "Король";
    case ACE:   return "Туз";
    default:    return "Неизвестно";
    }
}

std::string Card::get_suit_name_impl() const {
    switch (suit) {
    case HEARTS:   return "Черви";
    case DIAMONDS: return "Бубны";
    case CLUBS:    return "Трефы";
    case SPADES:   return "Пики";
    default:       return "Неизвестно";
    }
}

void Card::print_card() const {
    // Выводим информацию о карте (используем inline‑методы get_rank_name() и get_suit_name())
    printf("%s %s\n", get_rank_name(), get_suit_name());
}

void Card::release_card(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    if (is_used && suit != NONE_SUIT && rank != NONE_RANK) {
        used_cards[rank][suit] = false;
        is_used = false;
    }
    suit = NONE_SUIT;
    rank = NONE_RANK;
}

void Card::init_card(Suit s, Rank r, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    // Если карта уже используется, ничего не делаем
    if (used_cards[r][s])
        return;
    suit = s;
    rank = r;
    is_used = true;
}

bool Card::is_valid() const {
    return rank >= TWO && rank <= ACE && suit >= HEARTS && suit <= SPADES;
}

// Дружественная функция для оператора вывода (<<)
std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.get_rank_name() << " " << card.get_suit_name();
    return os;
}

// Перегрузка префиксного оператора ++
Card& Card::operator++() {
    // Используем явное обращение через this->, чтобы избежать конфликтов (например, с макросом rank)
    if (this->rank < ACE) {
        this->rank = static_cast<Rank>(this->rank + 1);
    }
    return *this;
}

// Перегрузка постфиксного оператора ++
Card Card::operator++(int) {
    Card temp = *this;
    ++(*this);
    return temp;
}

void Card::init_random_card(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    release_card(used_cards);
    int r, s;
    do {
        s = rand() % NUM_SUITS;
        r = rand() % NUM_RANKS;
    } while (used_cards[r][s]);
    suit = static_cast<Suit>(s);
    rank = static_cast<Rank>(r);
    used_cards[r][s] = true;
    is_used = true;
}

////////////////////////////////////////
// Класс Hand
////////////////////////////////////////

Hand::Hand() {
    card[0] = Card();
    card[1] = Card();
}

Hand::Hand(const Card& card1, const Card& card2) {
    card[0] = card1;
    card[1] = card2;
}

Card* Hand::get_card_ptr(int index) {
    if (index < 0 || index >= 2) {
        return nullptr;
    }
    return &card[index];
}

void Hand::set_card(int index, const Card& c) {
    if (index < 0 || index >= 2) {
        printf("Ошибка: индекс карты вне допустимого диапазона (0 или 1).\n");
        press_any_key_to_continue();
        return;
    }
    card[index] = c;
}

void Hand::init_hand(const Card& card1, const Card& card2) {
    card[0] = card1;
    card[1] = card2;
}

void Hand::clear_hand(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    card[0].release_card(used_cards);
    card[1].release_card(used_cards);
}

const Card& Hand::get_const_card(int index) const {
    return card[index];
}

Card& Hand::get_card(int index) {
    return card[index];
}

////////////////////////////////////////
// Класс Player
////////////////////////////////////////

Player::Player() : equity(0.0), wins(0), ties(0), losses(0) {}

Player& Player::set_equity(double e) {
    equity = e;
    return *this;
}

void Player::set_wins(int w) { wins = w; }
void Player::set_ties(int t) { ties = t; }
void Player::set_losses(int l) { losses = l; }

Hand& Player::get_hand() { return hand; }
const Hand& Player::get_hand() const { return hand; }

void Player::set_hand(const Hand& h, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    clear_player_cards(used_cards);
    hand = h;
    used_cards[hand.get_card(0).get_rank()][hand.get_card(0).get_suit()] = true;
    used_cards[hand.get_card(1).get_rank()][hand.get_card(1).get_suit()] = true;
}

void Player::init_player(const Hand& new_hand, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    set_hand(new_hand, used_cards);
    equity = 0.0;
}

void Player::clear_player_cards(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    Card& c1 = hand.get_card(0);
    Card& c2 = hand.get_card(1);
    if (c1.get_rank() != NONE_RANK && c1.get_suit() != NONE_SUIT)
        used_cards[c1.get_rank()][c1.get_suit()] = false;
    if (c2.get_rank() != NONE_RANK && c2.get_suit() != NONE_SUIT)
        used_cards[c2.get_rank()][c2.get_suit()] = false;
    hand.clear_hand(used_cards);
}

double Player::get_equity() const { return equity; }
int Player::get_wins() const { return wins; }
int Player::get_ties() const { return ties; }
int Player::get_losses() const { return losses; }

// Дружественная функция для оператора + (объявлена как friend в классе Player)
Player operator+(const Player& lhs, const Player& rhs) {
    Player result;
    // Можно использовать либо прямой доступ, так как функция является другом, либо геттеры:
    result.equity = (lhs.equity + rhs.equity) / 2.0;
    result.wins = lhs.wins + rhs.wins;
    result.ties = lhs.ties + rhs.ties;
    result.losses = lhs.losses + rhs.losses;
    return result;
}

////////////////////////////////////////
// Класс Board
////////////////////////////////////////

Board::Board() : num_cards(0) {}

Board::Board(const Card cards_array[5]) {
    num_cards = 0;
    for (int i = 0; i < 5; i++) {
        if (cards_array[i].is_valid()) {
            cards[num_cards++] = cards_array[i];
        }
    }
}

int Board::get_num_cards() const { return num_cards; }

const Card& Board::get_card(int index) const {
    if (index < 0 || index >= num_cards) {
        static const Card invalid_card;
        fprintf(stderr, "Ошибка: индекс карты %d вне допустимого диапазона (0-%d).\n", index, num_cards - 1);
        return invalid_card;
    }
    return cards[index];
}

void Board::debug_print_cards() const {
    printf("Отладочный вывод карт на столе:\n");
    for (int i = 0; i < 5; i++) {
        const Card& c = cards[i];
        if (c.is_valid())
            c.print_card();
        else
            printf("Карта %d: НЕИЗВЕСТНО (не задано)\n", i + 1);
    }
}

void Board::init_board() {
    clear_board(used_cards);
}

void Board::set_num_cards(int num) { num_cards = num; }

void Board::set_card(int index, const Card& c) {
    if (index >= 0 && index < 5)
        cards[index] = c;
}

void Board::set_used_cards(bool new_used_cards[NUM_RANKS][NUM_SUITS]) {
    for (int i = 0; i < NUM_RANKS; ++i)
        for (int j = 0; j < NUM_SUITS; ++j)
            used_cards[i][j] = new_used_cards[i][j];
}

void Board::update_used_cards() {
    for (int r = 0; r < NUM_RANKS; ++r)
        for (int s = 0; s < NUM_SUITS; ++s)
            used_cards[r][s] = false;
    for (int i = 0; i < 5; ++i) {
        const Card& c = cards[i];
        if (c.get_rank() != NONE_RANK && c.get_suit() != NONE_SUIT)
            used_cards[c.get_rank()][c.get_suit()] = true;
    }
}

void Board::print_board_cards() const {
    printf("Карты на столе:\n");
    for (int i = 0; i < num_cards; i++) {
        cards[i].print_card();
    }
}

void Board::add_card(const Card& c, bool used_cards[NUM_RANKS][NUM_SUITS]) {
    if (num_cards < 5) {
        if (used_cards[c.get_rank()][c.get_suit()]) {
            printf("Ошибка: Карта %s %s уже используется!\n", c.get_rank_name(), c.get_suit_name());
            return;
        }
        cards[num_cards] = c;
        printf("-----------------------------------------------\n");
        printf("Добавлена карта: %s %s на позицию %d\n", c.get_rank_name(), c.get_suit_name(), num_cards + 1);
        printf("-----------------------------------------------\n");
        used_cards[c.get_rank()][c.get_suit()] = true;
        num_cards++;
    }
    else {
        printf("Ошибка: На доске уже 5 карт!\n");
    }
}

void Board::clear_board(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    for (int i = 0; i < num_cards; i++) {
        if (cards[i].get_rank() != NONE_RANK && cards[i].get_suit() != NONE_SUIT)
            used_cards[cards[i].get_rank()][cards[i].get_suit()] = false;
        cards[i] = Card();
    }
    num_cards = 0;
}

////////////////////////////////////////
// Класс Game
////////////////////////////////////////

Game::Game() : num_players(0), current_players(0) {}

void Game::press_any_key_to_continue() {
    printf("Нажмите любую клавишу для продолжения...\n");
    _getch();
}

int Game::get_current_players() const { return current_players; }
void Game::set_current_players(int num) { current_players = num; }
Board& Game::get_board() { return board; }
char* Game::get_phase() { return phase; }
void Game::set_phase(const char* ph) { strcpy(phase, ph); }
int Game::get_num_players() const { return num_players; }
void Game::set_player(int index, const Player& player) {
    if (index >= 0 && index < 12)
        players[index] = player;
}
Player& Game::get_player(int index) { return players[index]; }
void Game::set_num_players(int num) { num_players = num; }
void Game::clear_all_players_cards(bool used_cards[NUM_RANKS][NUM_SUITS]) {
    for (int i = 0; i < current_players; i++) {
        players[i].clear_player_cards(used_cards);
        printf("Рука игрока %d успешно очищена!\n", i + 1);
    }
    printf("Операция завершена!\n");
    press_any_key_to_continue();
}
void Game::init_game(int num_players) {
    this->num_players = num_players;
    current_players = num_players;
    board.init_board();
}
void Game::add_player(const Player& player, int index) {
    if (index >= 0 && index < 12)
        players[index] = player;
}

////////////////////////////////////////
// Класс Settings
////////////////////////////////////////

Settings::Settings()
    : debugging_mode(false),
    ties_visible_mode(false),
    wins_visible_mode(false),
    simulations_visible_mode(false),
    tie(false),
    show(false),
    current_winner(-1),
    debug_player_index(-1),
    max_players(10),
    min_simulations(100),
    max_simulations(5000000),
    num_simulations(50000)
{}

bool Settings::get_debugging_mode() const { return debugging_mode; }
void Settings::set_debugging_mode(bool mode) { debugging_mode = mode; }
bool Settings::get_ties_visible_mode() const { return ties_visible_mode; }
void Settings::set_ties_visible_mode(bool mode) { ties_visible_mode = mode; }
bool Settings::get_wins_visible_mode() const { return wins_visible_mode; }
void Settings::set_wins_visible_mode(bool mode) { wins_visible_mode = mode; }
bool Settings::get_simulations_visible_mode() const { return simulations_visible_mode; }
void Settings::set_simulations_visible_mode(bool mode) { simulations_visible_mode = mode; }
bool Settings::get_tie() const { return tie; }
void Settings::set_tie(bool is_tie) { tie = is_tie; }
bool Settings::get_show() const { return show; }
void Settings::set_show(bool is_show) { show = is_show; }
int Settings::get_current_winner() const { return current_winner; }
void Settings::set_current_winner(int winner) { current_winner = winner; }
int Settings::get_debug_player_index() const { return debug_player_index; }
void Settings::set_debug_player_index(int index) { debug_player_index = index; }
int Settings::get_max_players() const { return max_players; }
void Settings::set_max_players(int max) { max_players = max; }
int Settings::get_min_simulations() const { return min_simulations; }
void Settings::set_min_simulations(int min) { min_simulations = min; }
int Settings::get_max_simulations() const { return max_simulations; }
void Settings::set_max_simulations(int max) { max_simulations = max; }
int Settings::get_num_simulations() const { return num_simulations; }
void Settings::set_num_simulations(int default_sim) { num_simulations = default_sim; }
void Settings::initialize() {
    debugging_mode = false;
    ties_visible_mode = false;
    wins_visible_mode = false;
    simulations_visible_mode = false;
    tie = false;
    show = false;
    current_winner = -1;
    debug_player_index = -1;
    max_players = 10;
    min_simulations = 100;
    max_simulations = 1000000;
    num_simulations = 50000;
}
