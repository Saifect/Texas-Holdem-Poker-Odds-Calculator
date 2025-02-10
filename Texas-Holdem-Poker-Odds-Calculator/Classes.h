#pragma once
#include "Globals.h"


// Масть карты
typedef enum {
    NONE_SUIT = -1,
    HEARTS,   // Черви
    DIAMONDS, // Бубны
    CLUBS,    // Трефы
    SPADES,   // Пики
} Suit;

// Ранк карты
typedef enum {
    NONE_RANK = -1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
} Rank;

// Класс Card
class Card {
private:
    Suit suit;
    Rank rank;
    bool is_used; // Флаг использования карты

    // Статическое поле для подсчёта созданных карт
    static int totalCardsCreated;

public:
    // Перегрузка операторов ++ (объявления)
    Card& operator++();      // префиксная версия
    Card operator++(int);    // постфиксная версия

    // Дружественная функция для оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    // Конструкторы, геттеры, сеттеры и т.д.
    Card();
    Card(Suit suit, Rank rank);
    Suit get_suit() const;
    Rank get_rank() const;
    void set_suit(Suit suit);
    void set_rank(Rank rank);
    bool is_valid() const;
    void set_used(bool used) { is_used = used; }

    // Служебные методы для формирования строк
    std::string get_rank_name_impl() const;
    std::string get_suit_name_impl() const;

    // Публичный интерфейс остаётся неизменным (возвращает const char*),
    // но реализован с использованием static thread_local переменных
    inline const char* get_rank_name() const {
        static thread_local std::string temp_rank;
        temp_rank = get_rank_name_impl();
        return temp_rank.c_str();
    }
    inline const char* get_suit_name() const {
        static thread_local std::string temp_suit;
        temp_suit = get_suit_name_impl();
        return temp_suit.c_str();
    }

    // Остальные методы:
    void print_card() const;
    void release_card(bool used_cards[NUM_RANKS][NUM_SUITS]);
    void init_card(Suit suit, Rank rank, bool used_cards[NUM_RANKS][NUM_SUITS]);
    void init_random_card(bool used_cards[NUM_RANKS][NUM_SUITS]);
};

class Hand {
private:
    Card card[2]; // Две карты руки

public:
    // Конструктор по умолчанию
    Hand();

    // Конструктор с параметрами
    Hand(const Card& card1, const Card& card2);

    Card* get_card_ptr(int index);

    // Установка карты
    void set_card(int index, const Card& card);

    // Инициализация руки
    void init_hand(const Card& card1, const Card& card2);

    // Очистка руки
    void clear_hand(bool used_cards[NUM_RANKS][NUM_SUITS]);

    // Геттер для карты
    const Card& get_const_card(int index) const;
    Card& get_card(int index);
};

// Класс Player – дружественный оператор + объявляем только здесь
class Player {
private:
    Hand hand;         // Рука игрока
    double equity;     // Вероятность победы
    int wins;          // Количество побед
    int ties;          // Количество ничьих
    int losses;        // Количество поражений
public:
    Player();
    // Сеттеры и геттеры
    Player& set_equity(double e);
    void set_wins(int w);
    void set_ties(int t);
    void set_losses(int l);
    Hand& get_hand();
    const Hand& get_hand() const;
    void set_hand(const Hand& h, bool used_cards[NUM_RANKS][NUM_SUITS]);
    void init_player(const Hand& new_hand, bool used_cards[NUM_RANKS][NUM_SUITS]);
    void clear_player_cards(bool used_cards[NUM_RANKS][NUM_SUITS]);
    double get_equity() const;
    int get_wins() const;
    int get_ties() const;
    int get_losses() const;

    // Дружественная функция для перегрузки оператора +
    friend Player operator+(const Player& lhs, const Player& rhs);
};


class Board {
private:
    Card cards[5]; // До 5 карт на столе
    int num_cards;

public:
    Board();
    Board(const Card cards_array[5]);
    void update_used_cards();
    void set_used_cards(bool new_used_cards[NUM_RANKS][NUM_SUITS]);
    int get_num_cards() const;
    const Card& get_card(int index) const;
    void init_board();
    void set_num_cards(int num);
    void set_card(int index, const Card& card);
    void print_board_cards() const;
    void add_card(const Card& card, bool used_cards[NUM_RANKS][NUM_SUITS]);
    void clear_board(bool used_cards[NUM_RANKS][NUM_SUITS]);
    void debug_print_cards() const;
};

class Game {
public:
    Game();

    void press_any_key_to_continue();
    int get_current_players() const;
    void set_current_players(int num);
    Board& get_board();
    char* get_phase();
    void set_phase(const char* ph);
    int get_num_players() const;
    void set_player(int index, const Player& player);
    Player& get_player(int index);
    void set_num_players(int num);
    void clear_all_players_cards(bool used_cards[NUM_RANKS][NUM_SUITS]);
    void init_game(int num_players);
    void add_player(const Player& player, int index);

private:
    Player players[12];   // Игроки
    int num_players;      // Общее количество игроков
    int current_players;  // Текущие игроки в игре
    Board board;          // Игровое поле
    char phase[10];       // Текущая фаза игры
};

// Покерные комбинации
typedef enum {
    HIGH_CARD,        // Старшая картаа
    ONE_PAIR,         // Пара
    TWO_PAIR,         // Две пары
    THREE_OF_A_KIND,  // Сет
    STRAIGHT,         // Стрит
    FLUSH,            // Флеш
    FULL_HOUSE,       // Фулл хаусее
    FOUR_OF_A_KIND,   // Каре
    STRAIGHT_FLUSH,   // Стрит флеш
    ROYAL_FLUSH
} PokerHandRank;

// Структура для покерной комбинации
typedef struct {
    PokerHandRank hand_rank;
    Rank high_card;
    Rank kicker[5];
} PokerCombination;

class Settings {
private:
    bool debugging_mode;
    bool ties_visible_mode;       // Отображение ничьих
    bool wins_visible_mode;       // Отображение побед
    bool simulations_visible_mode; // Отображение всех симуляций
    bool tie;                     // Флаг ничьей
    bool show;                    // Показывать ли элементы отладки
    int current_winner;           // Текущий победитель
    int debug_player_index;       // Индекс игрока для отладки

    int max_players;              // Максимальное количество игроков
    int min_simulations;          // Минимальное количество симуляций
    int max_simulations;          // Максимальное количество симуляций
    int num_simulations;      // Количество симуляций по умолчанию

public:
    // Конструктор по умолчанию
    Settings();

    // Геттеры и сеттеры для всех полей
    bool get_debugging_mode() const;
    void set_debugging_mode(bool mode);

    bool get_ties_visible_mode() const;
    void set_ties_visible_mode(bool mode);

    bool get_wins_visible_mode() const;
    void set_wins_visible_mode(bool mode);

    bool get_simulations_visible_mode() const;
    void set_simulations_visible_mode(bool mode);

    bool get_tie() const;
    void set_tie(bool is_tie);

    bool get_show() const;
    void set_show(bool is_show);

    int get_current_winner() const;
    void set_current_winner(int winner);

    int get_debug_player_index() const;
    void set_debug_player_index(int index);

    // Геттеры и сеттеры для новых полей
    int get_max_players() const;
    void set_max_players(int max);

    int get_min_simulations() const;
    void set_min_simulations(int min);

    int get_max_simulations() const;
    void set_max_simulations(int max);

    int get_num_simulations() const;
    void set_num_simulations(int default_sim);

    // Метод для инициализации настроек
    void initialize();
};
