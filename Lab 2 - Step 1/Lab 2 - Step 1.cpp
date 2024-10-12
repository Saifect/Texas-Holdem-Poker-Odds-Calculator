#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#define NUM_RANKS 13
#define NUM_SUITS 4

//Масть карты//
typedef enum {
    NONE_SUIT,
    HEARTS,   // Черви
    DIAMONDS, // Бубны
    CLUBS,    // Трефы
    SPADES,   // Пики

}Suit;

//Ранк карты//
typedef enum {
    NONE_RANK, TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
} Rank;

class Card {
public:
    // Функция для получения имени масти (константная версия)
    const char* get_suit_name(Suit suit) const {
        switch (suit) {
        case NONE_SUIT: return "None";
        case HEARTS:    return "Hearts";
        case DIAMONDS:  return "Diamonds";
        case CLUBS:     return "Clubs";
        case SPADES:    return "Spades";
        default:        return "Unknown";
        }
    }

    // Функция для получения имени ранга (константная версия)
    const char* get_rank_name(Rank rank) const {
        switch (rank) {
        case NONE_RANK: return "None";
        case TWO:       return "Two";
        case THREE:     return "Three";
        case FOUR:      return "Four";
        case FIVE:      return "Five";
        case SIX:       return "Six";
        case SEVEN:     return "Seven";
        case EIGHT:     return "Eight";
        case NINE:      return "Nine";
        case TEN:       return "Ten";
        case JACK:      return "Jack";
        case QUEEN:     return "Queen";
        case KING:      return "King";
        case ACE:       return "Ace";
        default:        return "Unknown";
        }
    }

    // Конструктор по умолчанию
    Card() : suit(NONE_SUIT), rank(NONE_RANK) {};

    // Конструктор с параметрами
    Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

    // Инициализация карты
    void init_card(Suit suit, Rank rank) {
        this->suit = suit;
        this->rank = rank;
    }

    // Случайная инициализация карты
    void init_random_сard(Card* card) {
        card->suit = (Suit)(rand() % 4);
        card->rank = (Rank)(rand() % 13 + 2);
    }

    // Функция для отображения карты (константная версия)
    void print_card() const {
        printf("%s %s\n", get_rank_name(rank), get_suit_name(suit));
    }

    // Геттеры для приватных полей
    Suit get_suit() const {
        return suit;
    }

    Rank get_rank() const {
        return rank;
    }

    // Сеттер для масти
    void set_suit(Suit new_suit) {
        suit = new_suit;
    }

    // Сеттер для ранга
    void set_rank(Rank new_rank) {
        rank = new_rank;
    }

private:
    Suit suit;
    Rank rank;

};


class Hand {
public:
    Hand() {} // Конструктор по умолчанию

    Hand(const Card& card1, const Card& card2) { // Конструктор с параметрами
        card[0] = card1;
        card[1] = card2;
    }

    void set_card(int index, const Card& card) {
        if (index < 0 || index >= 2) {
            printf("Ошибка: индекс карты вне допустимого диапазона (0 или 1).\n");
            return;
        }
        this->card[index] = card; // Устанавливаем карту по индексу
        printf("Карта %d успешно установлена: %s %s\n", index + 1,
            card.get_rank_name(card.get_rank()),
            card.get_suit_name(card.get_suit()));
    }


    // Инициализация руки
    void init_hand(const Card& card1, const Card& card2) {
        card[0] = card1;
        card[1] = card2;
    }

    // Очистка руки
    void clear_hand() {
        card[0].init_card(NONE_SUIT, NONE_RANK);
        card[1].init_card(NONE_SUIT, NONE_RANK);
    }

    // Геттер для карты
    const Card& get_const_card(int index) const {
        return card[index];
    }

    Card& get_card(int index) {
        return card[index]; // Измените на неконстантную ссылку
    }


private:
    Card card[2]; // Две карты руки
};

class Player {
public:
    Player() : equity(0.0), wins(0), ties(0), losses(0) {}

    // Сеттеры для приватных полей
    void set_equity(double e) { equity = e; }
    void set_wins(int w) { wins = w; }
    void set_ties(int t) { ties = t; }
    void set_losses(int l) { losses = l; }

    // Геттер для доступа к руке
    Hand& get_hand() {  // Убрали const, чтобы разрешить изменение руки
        return hand;
    }

  
    void set_hand(const Hand& h) {
        hand = h;
    }

    // Инициализация игрока
    void init_player(const Hand& hand) {
        this->hand = hand;
        equity = 0.0;
    }

    // Очистка карт игрока
    void clear_player_cards(bool used_cards[15][5], bool mute_mode = false) {
        if (!mute_mode) {
            if (hand.get_card(0).get_rank() == NONE_RANK || hand.get_card(1).get_rank() == NONE_RANK) {
                printf("Рука игрока не задана, поэтому она не может быть очищена!\n");
                return;
            }
        }

        used_cards[hand.get_card(0).get_rank()][hand.get_card(0).get_suit()] = false;
        used_cards[hand.get_card(1).get_rank()][hand.get_card(1).get_suit()] = false;

        hand.clear_hand();
    }

    // Геттеры для получения статистики игрока
    double get_equity() const {
        return equity;
    }

    int get_wins() const {
        return wins;
    }

    int get_ties() const {
        return ties;
    }

    int get_losses() const {
        return losses;
    }

private:
    Hand hand;
    double equity;
    int wins;
    int ties;
    int losses;
};


class Board {
public:
    Board() : num_cards(0) {}

    int get_num_cards() const {
        return num_cards;
    }

    const Card& get_card(int index) const {
        return cards[index];
    }


    // Инициализация игрового поля
    void init_board() {
        num_cards = 0;
    }

    // Сеттер для количества карт
    void set_num_cards(int num) {
        num_cards = num;
    }

    // Геттеры, сеттеры и другие методы
    void set_card(int index, const Card& card) {
        if (index >= 0 && index < 5) {
            cards[index] = card;
        }
    }

    // Печать карт на столе
    void print_board_cards() const {
        printf("Карты на столе:\n");
        for (int i = 0; i < num_cards; i++) {
            cards[i].print_card(); // Вызов константного метода
        }
    }


    // Добавление карты на стол
    void add_card(const Card& card) {
        if (num_cards < 5) {
            cards[num_cards] = card;
            num_cards++;
        }
    }

private:
    Card cards[5]; // До 5 карт на столе
    int num_cards;
};

class Game {
public:
    Game() : num_players(0), current_players(0) {}

    void press_any_key_to_continue() {
        printf("Нажмите любую клавишу для продолжения...\n");
        _getch(); // Ожидание нажатия клавиши
    }

    // Геттер для количества игроков
    int get_current_players() const {
        return current_players;
    }

    // Сеттер для количества текущих игроков
    void set_current_players(int num) {
        current_players = num;
    }

    Board& get_board() {
        return board;
    }

    // Геттер для стадии игры
    const char* get_phase() const {
        return phase;
    }

    // Сеттер для фазы
    void set_phase(const char* ph) {
        strcpy(phase, ph);
    }

    // Геттер для количества игроков
    int get_num_players() const {
        return num_players;
    }

    void set_player(int index, const Player& player) {
        if (index >= 0 && index < 12) {
            players[index] = player;
        }
    }

    Player& get_player(int index) {
        return players[index];
    }

    // Сеттер для количества игроков
    void set_num_players(int num) {
        num_players = num;
    }

    // Очистка всех карт игроков
    void clear_all_players_cards(bool used_cards[15][5], bool mute_mode = false) {
        for (int i = 0; i < current_players; i++) {
            players[i].clear_player_cards(used_cards, mute_mode);
            if (!mute_mode) {
                printf("Рука игрока %d успешно очищена!\n", i + 1);
            }
        }
        printf("Операция завершена!\n");
        press_any_key_to_continue();
    }

    // Инициализация игры
    void init_game(int num_players) {
        this->num_players = num_players;
        current_players = num_players;
        board.init_board();
    }

    // Добавление игрока
    void add_player(const Player& player, int index) {
        if (index >= 0 && index < 12) {
            players[index] = player;
        }
    }

private:
    Player players[12];  // Игроки
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
    ROYAL_FLUSH       // Рояль (Нет блин пианино)
} PokerHandRank;

// Структура для покерной комбинации
typedef struct {
    PokerHandRank hand_rank;
    Rank high_card;
    Rank kicker[5];
} PokerCombination;

typedef struct {
    bool ties_mode;
    bool wins_mode;
    int current_winner;
}Settings_debugging_mode;



//=========PROTOTYPE_FUNCTIONS=========//
void initialize_game(Game* game, int num_players);

// Print Menu Functions
void print_mainMenu(Game* game, PokerCombination* result_player, int* choice);
void print_editPlayerMenu(Game* game, bool used_cards[15][5]);
void print_editBoardMenu(Game* game, bool used_cards[15][5]);
void print_calculatorMenu(Game* game, PokerCombination* result_player);

// Main Menu Functions
void get_user_choice(int* choice);
void handle_mainMenu_choice(Game* game, PokerCombination* result_player, int choice);
void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[15][5], int* num_simulations, Settings_debugging_mode* settings_debugging_mode);
void initialize_used_cards(Game* game, bool used_cards[15][5]);
// Initialization Functions
void init_card(Card* card, Suit suit, Rank rank);
void init_random_сard(Card* card);
void init_hand(Hand* hand, Card card1, Card card2);
void init_player(Player* players, Hand hand);
void init_board(Board* board);
void init_game(Game* game, Player player1, Player player2, Board board, const char* phase);

// Menu Handling Functions
void handle_calculatorMenu_choice(int choice, Game* game, bool* exit, PokerCombination* result_player);

// Utility Functions
void deal_cards(Player players[], int current_players, bool used_cards[15][5], int choice_player);
void deal_random_cards(Player players[], int current_players, bool used_cards[15][5], int choice_player);
void clear_player_cards(Player* players, int current_players, bool used_cards[15][5], int choice_player, bool mute_mode);
void clear_all_players_cards(Player* players, int current_players, bool used_cards[15][5], bool mute_mode);

// Useful Functions
double scanf_secure(const char* type);          // Функция для безопасного ввода различных типов данных
void clearConsole();                            // Функция для очистки консоли
void buffer_clear();                            // Функция для очистки буфера ввода
void line_remove(char* str);                    // Функция для удаления символа новой строки из строки
void string_get_secure(char* buffer, int size); // Функция для безопасного получения строки с защитой от переполнения буфера
void press_any_key_to_continue();               // Тут интуитивно понятно

// Board Functions
void clear_board(Game* game, bool used_cards[15][5]);
void clear_board_turn(Game* game, bool used_cards[15][5]);
void clear_board_river(Game* game, bool used_cards[15][5]);
void input_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards);

// Deck Functions
void shuffle_deck(Card* deck, int size);
void create_deck(Card* deck);


// Game Logic Functions
PokerCombination determine_hand(Hand hand, Board board);
int compare_hands(PokerCombination hand1, PokerCombination hand2);
void print_hand(PokerCombination hand);
void print_board_cards(const Board* board);
void randomize_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards);

// Прототип функции, если она определена в другом месте или файле
void calculate_probabilities(Game* game, bool used_cards[15][5], int choice_numSimulations, Settings_debugging_mode* settings);
void print_probabilityMenu(Game* game, bool used_cards[15][5]);
void compare_all_hands(Game* game, PokerCombination hands[]);

void calculate_probabilities_debugging(Game* game, Settings_debugging_mode* settings, Board simulated_board, PokerCombination* player_hands, int current_simulation, bool tie, int best_player);
//============MAIN_FUNCTION============//
int main() {

    /// Инициализация игры ///
    Game game;
    initialize_game(&game, 12);

    // Используем геттер для доступа к количеству игроков
    PokerCombination* result_player = (PokerCombination*)malloc(game.get_num_players() * sizeof(PokerCombination));

    /// Установка кодировок 
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Для православного языка
    setlocale(LC_ALL, "Rus");

    while (true) {
        int choice;
        print_mainMenu(&game, result_player, &choice);
        clearConsole();
    }

    free(result_player);
    return 0;
}


//======IMPLENTATION_OF_FUNCTIONS======//


void initialize_game(Game* game, int num_players) {
    if (num_players > 12) {
        num_players = 12; // Ограничение на 12 игроков
    }

    // Инициализируем игроков
    for (int i = 0; i < num_players; i++) {
        Card card1(NONE_SUIT, NONE_RANK);
        Card card2(NONE_SUIT, NONE_RANK);
        Hand hand(card1, card2);

        Player player;
        player.set_hand(hand);
        player.set_equity(0.0);
        player.set_wins(0);
        player.set_ties(0);
        player.set_losses(0);

        game->set_player(i, player); // Используем сеттер для игрока
    }

    // Инициализируем поле
    for (int i = 0; i < 5; i++) {
        game->get_board().set_card(i, Card(NONE_SUIT, NONE_RANK));
    }
    game->get_board().set_num_cards(0);

    // Устанавливаем фазу игры
    game->set_phase("preflop");

    // Устанавливаем количество игроков
    game->set_num_players(num_players); // Используем сеттер для количества игроков
}




const char* get_rank_name(Rank rank) {
    switch (rank) {
    case TWO: return "Двойка";
    case THREE: return "Тройка";
    case FOUR: return "Четверка";
    case FIVE: return "Пятерка";
    case SIX: return "Шестерка";
    case SEVEN: return "Семерка";
    case EIGHT: return "Восьмерка";
    case NINE: return "Девятка";
    case TEN: return "Десятка";
    case JACK: return "Валет";
    case QUEEN: return "Дама";
    case KING: return "Король";
    case ACE: return "Туз";
    default: return "Неизвестно";
    }
}

const char* get_suit_name(Suit suit) {
    switch (suit) {
    case HEARTS: return "Черви";
    case DIAMONDS: return "Бубны";
    case CLUBS: return "Трефы";
    case SPADES: return "Пики";
    default: return "Неизвестно";
    }
}

//Начальное меню//
void print_mainMenu(Game* game, PokerCombination* result_player, int* choice) {
    printf("\n");
    printf("================================================\n");
    printf("               Добро пожаловать!                \n");
    printf("================================================\n");
    printf("Выберите действие:\n");
    printf("1. Покерный калькулятор\n");
    printf("2. Режим практики\n");
    printf("3. Настройки\n");
    printf("4. Прочее\n");
    printf("------------------------------------------------\n");
    printf("0. Выход из программы\n");
    printf("================================================\n");
    printf("Ваш выбор: ");
    get_user_choice(choice);
    handle_mainMenu_choice(game, result_player, *choice);
}

//Получение выбора пользователя//
void get_user_choice(int* choice) {
    *choice = (int)scanf_secure("int");
}

//Обработка выбора пользователя в основном меню//
void handle_mainMenu_choice(Game* game, PokerCombination* result_player, int choice) {
    switch (choice) {
    case 0:
        printf("Выход из программы.\n");
        exit(0);
        break;
    case -1:
        clearConsole(); //Обработка неправильного ввода функции scanf_secure (фича)
        break;

    case 1:
        clearConsole();
        print_calculatorMenu(game, result_player);
        break;
    case 2:
        printf("Не реализовано\n");
        press_any_key_to_continue();
        clearConsole();

        break;
    case 3:
        printf("Не реализовано\n");
        press_any_key_to_continue();
        clearConsole();
        break;
    case 4:
        printf("Status: Stable\n");
        printf("Version program: 2.2\n");
        printf("Author: Saifect@mail.ru\n");
        press_any_key_to_continue();
        break;

    default:
        break;
    }
}


void print_calculatorMenu(Game* game, PokerCombination* result_player) {
    srand(time(NULL));

    game->set_phase("preflop");  // Установка стадии игры через сеттер
    game->set_current_players(2);  // Установка текущих игроков через сеттер
    int choice = -1;
    bool edit_mode = false;
    int edit_current_player = 0;
    bool exit = false;
    bool tracking_changes;


    game->get_player(0).get_hand().get_card(0).print_card();
    game->get_player(1).get_hand().get_card(1).print_card();

    while (exit == false) {
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        for (int i = 0; i < game->get_current_players(); i++) {
            const Hand& hand = game->get_player(i).get_hand();  // Получаем руку через геттер
            if (hand.get_const_card(0).get_rank() != NONE_RANK && hand.get_const_card(1).get_rank() != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(hand.get_const_card(0).get_rank()),
                    get_suit_name(hand.get_const_card(0).get_suit()),
                    get_rank_name(hand.get_const_card(1).get_rank()),
                    get_suit_name(hand.get_const_card(1).get_suit()));
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
        printf("-----------------------------------------------\n");
        printf("0. Выйти из покерного калькулятора\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        get_user_choice(&choice);
        handle_calculatorMenu_choice(choice, game, &exit, result_player);
    }
}




void handle_calculatorMenu_choice(int choice, Game* game, bool* exit, PokerCombination* result_player) {


    if (result_player == NULL) {
        printf("Ошибка: недостаточно памяти для вычисления комбинаций.\n");
        return;
    }

    // Массив для отслеживания занятых карт
    bool used_cards[15][5] = { false };

    // Помечаем карты игрока 1 как занятые
    const Hand& hand0 = game->get_player(0).get_hand();  // Получаем руку первого игрока
    used_cards[hand0.get_const_card(0).get_rank()][hand0.get_const_card(0).get_suit()] = true;
    used_cards[hand0.get_const_card(1).get_rank()][hand0.get_const_card(1).get_suit()] = true;

    // Помечаем карты игрока 2 как занятые
    const Hand& hand1 = game->get_player(1).get_hand();  // Получаем руку второго игрока
    used_cards[hand1.get_const_card(0).get_rank()][hand1.get_const_card(0).get_suit()] = true;
    used_cards[hand1.get_const_card(1).get_rank()][hand1.get_const_card(1).get_suit()] = true;

    // Помечаем карты на доске как занятые
    for (int i = 0; i < game->get_board().get_num_cards(); i++) {
        used_cards[game->get_board().get_card(i).get_rank()][game->get_board().get_card(i).get_suit()] = true;
    }

    switch (choice) {
    case -1:
        clearConsole();
        break;

    case 0:
        printf("Вы уверены? Введённые вами карты сбросятся\n");
        printf("Y/yes - да\n");
        printf("N/no - нет\n");

        char str_choice[3];
        string_get_secure(str_choice, 3);

        for (int i = 0; str_choice[i]; i++) {
            str_choice[i] = tolower(str_choice[i]);
        }

        if (strcmp(str_choice, "y") == 0 || strcmp(str_choice, "yes") == 0) {
            *exit = true;
        }
        else {
            printf("Операция отменена.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }
        clearConsole();
        break;

    case 1:
        clearConsole();
        print_editPlayerMenu(game, used_cards);
        break;

    case 2:
        clearConsole();
        print_editBoardMenu(game, used_cards);
        break;

    case 3:
        clearConsole();
        print_probabilityMenu(game, used_cards);
        break;

    case 4:
       for (int i = 0; i < game->get_current_players() && i < game->get_num_players(); i++) {
           if (game->get_player(i).get_hand().get_const_card(0).get_rank() != NONE_RANK && game->get_player(i).get_hand().get_const_card(1).get_rank() != NONE_RANK) {
                result_player[i] = determine_hand(game->get_player(i).get_hand(), game->get_board());
                print_hand(result_player[i]);
            }
            else {
                printf("Карты %d-го игрока не заданы, поэтому у него не может быть комбинации!\n", i + 1);
            }
        }

        press_any_key_to_continue();
        clearConsole();
        break;

    default:
        clearConsole();
        break;
    }


}

void print_hand(PokerCombination hand) {
    switch (hand.hand_rank) {
    case STRAIGHT_FLUSH:
        printf("Комбинация: Стрит-флеш\n");
        printf("Старшая карта: %d\n", hand.high_card);
        break;
    case FOUR_OF_A_KIND:
        printf("Комбинация: Каре %d\n", hand.high_card);
        printf("Кикер: %d\n", hand.kicker[0]);
        break;
    case FULL_HOUSE:
        printf("Комбинация: Фулл-хаус\n");
        printf("Тройка: %d\n", hand.high_card);
        printf("Пара: %d\n", hand.kicker[0]);
        break;
    case FLUSH:
        printf("Комбинация: Флеш\n");
        printf("Старшая карта: %d\n", hand.high_card);
        break;
    case STRAIGHT:
        printf("Комбинация: Стрит\n");
        printf("Старшая карта: %d\n", hand.high_card);
        break;
    case THREE_OF_A_KIND:
        if (hand.kicker[0] == NONE_RANK) {
            printf("Комбинация: Сет %d\n", hand.high_card);
        }
        else {
            printf("Комбинация: Трипс %d\n", hand.high_card);
            printf("Кикер: %d\n", hand.kicker[0]);
        }
        break;
    case TWO_PAIR:
        printf("Комбинация: Две пары\n");
        printf("Старшая пара: %d\n", hand.high_card);
        printf("Младшая пара: %d\n", hand.kicker[0]);
        break;
    case ONE_PAIR:
        if (hand.kicker[0] == NONE_RANK && hand.kicker[1] == NONE_RANK) {
            printf("Комбинация: Карманная пара %d\n", hand.high_card);
        }
        else {
            printf("Комбинация: Пара %d\n", hand.high_card);
            printf("Кикер: %d\n", hand.kicker[0]);
        }
        break;
    case HIGH_CARD:
        printf("Комбинация: Старшая карта %d\n", hand.high_card);
        printf("Кикер: %d\n", hand.kicker[0]);
        break;
    default:
        printf("Неизвестная комбинация\n");
        break;
    }
}


void print_probabilityMenu(Game* game, bool used_cards[15][5]) {
    int num_simulations = 250000;
    int probabilityMenu_choice = 0;
    bool exit = false;

    Settings_debugging_mode settings_debugging_mode;
    settings_debugging_mode.current_winner = -1;
    settings_debugging_mode.ties_mode = false;
    settings_debugging_mode.wins_mode = false;

    while (exit == false) {

        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        for (int i = 0; i < game->get_current_players(); i++) {
            // Проверяем были ли введены карты игрокаа
            if (game->get_player(i).get_hand().get_const_card(0).get_rank() != NONE_RANK && game->get_player(i).get_hand().get_const_card(1).get_rank() != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(game->get_player(i).get_hand().get_const_card(0).get_rank()),
                    get_suit_name(game->get_player(i).get_hand().get_const_card(0).get_suit()),
                    get_rank_name(game->get_player(i).get_hand().get_const_card(1).get_rank()),
                    get_suit_name(game->get_player(i).get_hand().get_const_card(1).get_suit()));
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

        printf("Текущяя стадия игры (улица): %s\n", game->get_phase());
        printf("Текущее количество симуляций: %d\n", num_simulations);
        if (settings_debugging_mode.wins_mode == false && settings_debugging_mode.ties_mode == false) {
            printf("Режим отладки: Выключен\n");
        }
        else {
            printf("Режим отладки: Включен\n");
        }
        printf("================================================\n");
        printf("       Редактор вычисления вероятностей         \n");
        printf("================================================\n");
        printf("1. Расчёт по методу симуляций Монте-Карло\n");
        printf("2. Изменить количество симуляций\n");
        if (settings_debugging_mode.wins_mode == false) {
            printf("3. Вкючить отображение побед для игрока\n");
        }
        if (settings_debugging_mode.wins_mode == true) {
            printf("3. Выключить отоброжение побед для игрока\n");
        }
        if (settings_debugging_mode.ties_mode == false) {
            printf("4. Включить отоброжение ничей\n");
        }
        if (settings_debugging_mode.ties_mode == true) {
            printf("4. Выключить отоброжение ничей\n");
        }
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        get_user_choice(&probabilityMenu_choice);
        handle_probabilityMenu_choice(probabilityMenu_choice, game, &exit, used_cards, &num_simulations, &settings_debugging_mode);
    }
}

void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[15][5], int* num_simulations, Settings_debugging_mode* settings_debugging_mode) {
    bool debugging_mode;
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
            printf("Нужно хотя бы 2 заданные руки для анализа вероятности.\n");
            press_any_key_to_continue();
            clearConsole();
        }
        else if (*num_simulations >= 10 && *num_simulations <= 20000000) {


            if (settings_debugging_mode->ties_mode == true || settings_debugging_mode->wins_mode == true) {
                debugging_mode = true;
            }
            else {
                debugging_mode = false;
            }
            if (debugging_mode == true && *num_simulations > 5000) {
                if (*num_simulations > 3000 && *num_simulations < 10000) {
                    printf("Использовать режим отладки с количеством симуляций < 3000 не рекомендуется\nВы уверены?\n");
                }
                if (*num_simulations > 10000 && *num_simulations < 50000) {
                    printf("Оу, это будет долговато.\nДля режима отладки рекомендуется < 3000 симуляций, вы уверены?\n");
                }
                if (*num_simulations > 50000 && *num_simulations < 100000) {
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

                    printf("Продолжаем выполнение в режиме отладки с %d симуляциями.\n", *num_simulations);

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
            printf("Не нажимайте ничего пока не загрузится результат \n");
            printf("Загрузка...\n");
            calculate_probabilities(game, used_cards, *num_simulations, settings_debugging_mode);

            press_any_key_to_continue();
            clearConsole();
        }
        break;

    case 2: {

        printf("-----------------------------------------------\n");
        printf("Введите количество симуляций\nДиапазон значений от 100 до 5.000.000\n");
        printf("Рекомендуется 100.000 - 300.000 симуляций\nЗначения >1.000.000 могут долго работать\n");
        printf("Или введите 0 для отмены\n");
        printf("-----------------------------------------------\n");
        printf("Ваш выбор: ");
        int num_simulations_new = scanf_secure("int");

        if (num_simulations_new == 0) {
            printf("Операция отменена.\n");
            press_any_key_to_continue();
            clearConsole();
        }
        else if (num_simulations_new >= 100 && num_simulations_new <= 5000000) {
            *num_simulations = num_simulations_new; // обновляем количество симуляцийй
            printf("Вы установили %d симуляций для метода Монте-Карло\n", *num_simulations);
            press_any_key_to_continue();
            clearConsole();
        }
        else {
            printf("Вы ввели значение вне диапазона! Используем 250000 по умолчанию.\n");
            *num_simulations = 250000; // значение по умолчанию
            press_any_key_to_continue();
            clearConsole();
        }
        break;
    }

    case 3:
        if (settings_debugging_mode->wins_mode == true) {
            settings_debugging_mode->wins_mode = !(settings_debugging_mode->wins_mode);
            clearConsole();
        }
        else {
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
                settings_debugging_mode->current_winner = choice_user;
                settings_debugging_mode->wins_mode = !(settings_debugging_mode->wins_mode);
                if (settings_debugging_mode->ties_mode == true) {
                    settings_debugging_mode->ties_mode = !(settings_debugging_mode->ties_mode);
                }
                clearConsole();
            }
        }
        break;

    case 4:

        settings_debugging_mode->ties_mode = !(settings_debugging_mode->ties_mode);
        if (settings_debugging_mode->wins_mode == true) {
            settings_debugging_mode->wins_mode = !(settings_debugging_mode->wins_mode);
        }

        clearConsole();

        break;
    default:
        clearConsole();
        break;
    }
}


void print_editPlayerMenu(Game* game, bool used_cards[15][5]) {
    int choice;
    bool back = false;
    int choice_player;




    while (!back) {

        game->get_player(0).get_hand().get_card(0).print_card();
        game->get_player(1).get_hand().get_card(1).print_card();
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        // Вывод информации о картах игроков
        for (int i = 0; i < game->get_current_players(); i++) {
            const Hand& hand = game->get_player(i).get_hand();
            const Card& card1 = hand.get_const_card(0);
            const Card& card2 = hand.get_const_card(1);

            // Проверяем, были ли введены карты для текущего игрока
            if (card1.get_rank() != NONE_RANK && card2.get_rank() != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    card1.get_rank_name(card1.get_rank()), card1.get_suit_name(card1.get_suit()),
                    card2.get_rank_name(card2.get_rank()), card2.get_suit_name(card2.get_suit()));
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
        }

        // Вывод карт на столе
        if (strcmp(game->get_phase(), "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            game->get_board().print_board_cards();
        }

        printf("Текущая стадия игры (улица): %s\n", game->get_phase());

        printf("================================================\n");
        printf("               Редактор игроков                 \n");
        printf("================================================\n");
        printf("1. Добавить/изменить карты игроку\n");
        printf("2. Сгенерировать случайные карты игроку\n");
        printf("3. Очистить карты игроку\n");
        printf("4. Очистить всех игроков\n");
        printf("5. Задать количество игроков\n");
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        // Получение выбора пользователя
        choice = (int)scanf_secure("int");

        switch (choice) {
        case 0:
            back = true;
            clearConsole();
            break;
        case 1:
            printf("Введите номер игрока или 0 для отмены: ");
            choice_player = scanf_secure("int");
            if (choice_player == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }
            deal_cards(&game->get_player(choice_player - 1), game->get_current_players(), used_cards, choice_player - 1);
            clearConsole();
            break;
        case 2:
            printf("Введите номер игрока или 0 для отмены: ");
            choice_player = scanf_secure("int");
            if (choice_player == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }
            deal_random_cards(&game->get_player(choice_player - 1), game->get_current_players(), used_cards, choice_player);
            printf("Рука игрока %d сгенерирована случайно!\n", choice_player);
            press_any_key_to_continue();
            clearConsole();
            break;
        case 3:
            printf("Введите номер игрока или 0 для отмены: ");
            choice_player = scanf_secure("int");
            if (choice_player == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }
            game->get_player(choice_player - 1).clear_player_cards(used_cards, false);
            printf("Рука игрока %d успешно очищена!\n", choice_player);
            press_any_key_to_continue();
            clearConsole();
            break;
        case 4:
            game->clear_all_players_cards(used_cards, false);
            clearConsole();
            break;
        case 5:
            printf("Введите количество игроков (2-%d) или 0 для отмены: ", game->get_num_players());
            choice_player = scanf_secure("int");

            if (choice_player == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }

            if (choice_player == game->get_current_players()) {
                printf("У вас столько же игроков!\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }

            if (choice_player < 2 || choice_player > game->get_num_players()) {
                printf("Вы ввели число вне диапазона!\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }

            // Если новое количество игроков меньше текущего
            if (choice_player < game->get_current_players()) {
                for (int i = choice_player; i < game->get_current_players(); i++) {
                    game->get_player(i).clear_player_cards(used_cards, true);
                }
            }

            game->set_current_players(choice_player);
            printf("Вы задали %d игроков для калькулятора.\n", choice_player);
            press_any_key_to_continue();
            clearConsole();
            break;

        default:
            clearConsole();
            break;
        }
    }
}


void print_editBoardMenu(Game* game, bool used_cards[15][5]) {
    int choice;
    bool exit_editor = false;

    while (!exit_editor) {
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        // были ли карты введены для 1-го игрока?
        for (int i = 0; i < game->get_current_players(); i++) {
            if (game->get_player(i).get_hand().get_const_card(0).get_rank() != NONE_RANK &&
                game->get_player(i).get_hand().get_const_card(1).get_rank() != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(game->get_player(i).get_hand().get_const_card(0).get_rank()),
                    get_suit_name(game->get_player(i).get_hand().get_const_card(0).get_suit()),
                    get_rank_name(game->get_player(i).get_hand().get_const_card(1).get_rank()),
                    get_suit_name(game->get_player(i).get_hand().get_const_card(1).get_suit()));
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
        }

        if (strcmp(game->get_phase(), "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            game->get_board().print_board_cards();
        }

        printf("Текущяя стадия игры (улица): %s\n", game->get_phase());
        printf("================================================\n");
        printf("               Редактор стола                   \n");
        printf("================================================\n");
        printf("1. Добавить/изменить Flop (3 карты)\n");
        printf("2. Добавить/изменить Turn (4-ая карта)\n");
        printf("3. Добавить/изменить River (5-ая карта)\n");
        printf("4. Заполнить Flop случайными картами\n");
        printf("5. Заполнить Turn случайными картами\n");
        printf("6. Заполнить River случайными картами\n");
        printf("7. Очистить Turn\n");
        printf("8. Очистить River\n");
        printf("9. Очистить стол\n");
        printf("------------------------------------------------\n");
        printf("0. Выйти\n");
        printf("================================================\n");
        printf("Выберите действие: ");
        choice = (int)scanf_secure("int");

        switch (choice) {
        case 1:
            printf("Редактирование Flop (первая, вторая и третья карты на столе)\n");
            input_board_cards(game, used_cards, 0, 3);  // Ввод трёх карт на флоп
            break;

        case 2:
            if (game->get_board().get_num_cards() < 3) {
                printf("Сначала необходимо добавить Flop!\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование Turn (четвёртая карта)\n");
                input_board_cards(game, used_cards, 3, 1);
            }
            break;

        case 3:
            if (game->get_board().get_num_cards() < 4) {
                printf("Сначала необходимо добавить Turn!\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование River (пятая карта)\n");
                input_board_cards(game, used_cards, 4, 1);
            }
            break;

        case 4:
            if (game->get_board().get_num_cards() < 3) {
                printf("Редактирование Flop (случайные 3 карты)\n");
                randomize_board_cards(game, used_cards, 0, 3);
            }
            else {
                printf("Флоп уже задан! Сначала очистите стол.\n");
                press_any_key_to_continue();
            }
            break;

        case 5:
            if (game->get_board().get_num_cards() < 3) {
                printf("Сначала необходимо добавить Flop!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 4 || game->get_board().get_num_cards() == 5) {
                printf("Терн уже задан! Сначала очистите стол.\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование Turn (случайная 4-ая карта)\n");
                randomize_board_cards(game, used_cards, 3, 1);
            }
            break;

        case 6:
            if (game->get_board().get_num_cards() < 4) {
                printf("Сначала необходимо добавить Turn!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 5) {
                printf("Ривер уже задан! Сначала очистите стол.\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование River (случайная 5-ая карта)\n");
                randomize_board_cards(game, used_cards, 4, 1);
            }
            break;

        case 7:
            if (game->get_board().get_num_cards() < 3) {
                printf("Сначала необходо добавить flop и turn!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 3) {
                printf("Сначала необходо добавить turn!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 5) {
                printf("Сначала необходимо очистить River\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 4) {
                clear_board_turn(game, used_cards);
                printf("Turn очищен!\n");
                press_any_key_to_continue();
            }
            break;

        case 8:
            if (game->get_board().get_num_cards() < 3) {
                printf("Сначала необходимо добавить flop и turn и river!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 3) {
                printf("Сначала необходимо добавить turn и river!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 4) {
                printf("Сначала необходимо добавить river!\n");
                press_any_key_to_continue();
            }
            else if (game->get_board().get_num_cards() == 5) {
                clear_board_river(game, used_cards);
                printf("River очищен!\n");
                press_any_key_to_continue();
            }
            break;

        case 9:
            clear_board(game, used_cards);
            printf("Стол очищен!\n");
            press_any_key_to_continue();
            break;

        case 0:
            exit_editor = true;
            break;

        default:
            break;
        }
        clearConsole();
    }
}

// Инициализация руки
void init_hand(Hand* hand, const Card& card1, const Card& card2) {
    hand->init_hand(card1, card2);
}

// Инициализация игрока
void init_player(Player* players, const Hand& hand) {
    players->init_player(hand);
}

// Инициализация игрового поля
void init_board(Board* board) {
    board->init_board();
}

void print_board_cards(const Board* board) {
    board->print_board_cards();
}

void clear_player_cards(Player* players, int current_players, bool used_cards[15][5], int choice_player, bool mute_mode) {
    players[choice_player - 1].clear_player_cards(used_cards, mute_mode);
}

void clear_all_players_cards(Player* players, int current_players, bool used_cards[15][5], bool mute_mode) {
    for (int i = 0; i < current_players; i++) {
        players[i].clear_player_cards(used_cards, mute_mode);
        if (!mute_mode) {
            printf("Рука игрока %d успешно очищена!\n", i + 1);
        }
    }
    printf("Операция завершена!\n");
    press_any_key_to_continue();
}


void deal_cards(Player players[], int current_players, bool used_cards[15][5], int choice_player) {
    if (choice_player < 0 || choice_player >= current_players) {
        printf("Игрока под таким номером не существует!\n");
        press_any_key_to_continue();
        clearConsole();
        return;
    }
    else {
        printf("------------------------------------------------\n");
        printf("          Ввод карт для игрока %d\n", choice_player + 1);
        printf("------------------------------------------------\n");

        // Ввод первой карты
        int rank_choice_card[2], suit_choice_card[2];

        for (int current_card = 0; current_card < 2; current_card++) {
            do {
                printf("Введите ранг %d-ой карты (2-14) или 0 для выхода: ", current_card + 1);
                rank_choice_card[current_card] = (int)scanf_secure("int");
                if (rank_choice_card[current_card] == 0) {
                    // Отменяем ввод
                    for (int j = 0; j < current_card; j++) {
                        players[choice_player].get_hand().get_card(j).init_card(NONE_SUIT, NONE_RANK);
                        used_cards[rank_choice_card[j]][suit_choice_card[j]] = false;
                    }
                    return;
                }
                if (rank_choice_card[current_card] < 2 || rank_choice_card[current_card] > 14) {
                    printf("Неверный ранг карты! Попробуйте снова.\n");
                    continue;
                }

                printf("Введите масть %d-ой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ", current_card + 1);
                suit_choice_card[current_card] = (int)scanf_secure("int");
                if (suit_choice_card[current_card] == 0) {
                    // Отменяем ввод
                    for (int j = 0; j < current_card; j++) {
                        players[choice_player].get_hand().get_card(j).init_card(NONE_SUIT, NONE_RANK);
                        used_cards[rank_choice_card[j]][suit_choice_card[j]] = false;
                    }
                    return;
                }
                if (suit_choice_card[current_card] < 1 || suit_choice_card[current_card] > 4) {
                    printf("Неверная масть карты! Попробуйте снова.\n");
                    continue;
                }

                // Проверка на уникальность
                if (used_cards[rank_choice_card[current_card]][suit_choice_card[current_card]]) {
                    printf("Эта карта уже используется! Попробуйте другую карту.\n");
                }
                else {
                    // Используем неконстантную ссылку для установки карты
                    players[choice_player].get_hand().set_card(current_card, Card((Suit)suit_choice_card[current_card], (Rank)rank_choice_card[current_card]));
                    used_cards[rank_choice_card[current_card]][suit_choice_card[current_card]] = true;

                    for (int r = 2; r <= 14; r++) {
                        for (int s = 1; s <= 4; s++) {
                            printf("used_cards[%d][%d] = %d\n", r, s, used_cards[r][s]);
                        }
                    }

                    printf("Выбрана карта: %s %s\n",
                        get_rank_name((Rank)rank_choice_card[current_card]),
                        get_suit_name((Suit)suit_choice_card[current_card]));



               

                    press_any_key_to_continue();

                    break;
                }
            } while (true);
        }
    }
}








//==========Useful_functions==========//
double scanf_secure(const char* type) {
    while (1) {
        if (strcmp(type, "int") == 0) {
            int num;
            if (scanf("%d", &num) == 1) {
                while (getchar() != '\n');
                return num;
            }
            else {
                printf("Ошибка ввода. Пожалуйста, введите целое число.\n");
                press_any_key_to_continue();
                buffer_clear();
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
                printf("Ошибка ввода. Пожалуйста, введите вещественное число: ");
                buffer_clear();
            }
        }
        else if (strcmp(type, "double") == 0) {
            double num;
            if (scanf("%lf", &num) == 1) {
                while (getchar() != '\n');
                return num;
            }
            else {
                printf("Ошибка ввода. Пожалуйста, введите вещественное число: ");
                buffer_clear();
            }
        }
        else if (strcmp(type, "bool") == 0) {
            char input[10];
            if (scanf("%9s", input) == 1) {
                if (strcmp(input, "true") == 0 || strcmp(input, "1") == 0) { //Оно подрчеркивает зеленым и я незнаю почему так
                    return 1;
                }
                else if (strcmp(input, "false") == 0 || strcmp(input, "0") == 0) {
                    return 0;
                }
                else {
                    printf("Ошибка ввода. Пожалуйста, введите 'true' или 'false': ");
                    buffer_clear();
                }
            }
            else {
                printf("Ошибка ввода. Пожалуйста, введите 'true' или 'false': ");
                buffer_clear();
            }
        }
        else {
            printf("Неизвестный тип данных.\n");
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


// Очистка буфераа
void buffer_clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Удаление строки
void line_remove(char* str) {

    str[strcspn(str, "\n")] = '\0';
}

// Получение строки с защитой от переполнения буфера
void string_get_secure(char* buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        line_remove(buffer);
    }
    else {
        buffer_clear();
    }
}

void press_any_key_to_continue() {
    printf("Нажмите любую клавишу для продолжения...\n");
    _getch(); // Ожидание нажатия клавиши
}

// Функция для перемешивания массива карт//
void shuffle_deck(Card* deck, int size) {
    for (int i = 0; i < size; i++) {
        int randomIndex = rand() % size;
        Card temp = deck[i];
        deck[i] = deck[randomIndex];
        deck[randomIndex] = temp;
    }
}

// Функция для создания полной колоды карт
void create_deck(Card* deck) {
    int index = 0;
    for (int suit = HEARTS; suit <= SPADES; suit++) {
        for (int rank = TWO; rank <= ACE; rank++) {
            deck[index].set_suit((Suit)suit);  // Используем сеттер
            deck[index].set_rank((Rank)rank);  // Используем сеттер
            index++;
        }
    }
}


// Функция раздачи случайных карт двум игрокам
void deal_random_cards(Player players[], int current_players, bool used_cards[15][5], int choice_player) {
    if (choice_player < 0 || choice_player > current_players) {
        printf("Игрока под таким номером не существует!\n");
        press_any_key_to_continue();
        clearConsole();
        return;
    }

    Card full_deck[52];
    create_deck(full_deck);
    Card available_deck[52];
    int available_count = 0;

    for (int i = 0; i < 52; i++) {
        if (!used_cards[full_deck[i].get_rank()][full_deck[i].get_suit()]) {
            available_deck[available_count++] = full_deck[i];
        }
    }

    // Перемешиваем
    shuffle_deck(available_deck, available_count);

    used_cards[players[choice_player - 1].get_hand().get_card(0).get_rank()][players[choice_player - 1].get_hand().get_card(0).get_suit()] = false;
    used_cards[players[choice_player - 1].get_hand().get_card(1).get_rank()][players[choice_player - 1].get_hand().get_card(1).get_suit()] = false;

    players[choice_player - 1].get_hand().get_card(0) = available_deck[0];
    players[choice_player - 1].get_hand().get_card(1) = available_deck[1];

    used_cards[players[choice_player - 1].get_hand().get_card(0).get_rank()][players[choice_player - 1].get_hand().get_card(0).get_suit()] = true;
    used_cards[players[choice_player - 1].get_hand().get_card(1).get_rank()][players[choice_player - 1].get_hand().get_card(1).get_suit()] = true;
}


// максимальный размер доски
#define MAX_BOARD_CARDS 5

void input_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards) {
    int rank_choice, suit_choice;

    for (int i = 0; i < num_cards; i++) {
        do {
            printf("Введите ранг карты %d (2-14) или 0 для выхода: ", start_index + i + 1);
            rank_choice = (int)scanf_secure("int");
            if (rank_choice == 0) {
                return;
            }
            if (rank_choice < 2 || rank_choice > 14) {
                printf("Неверный ранг карты! Попробуйте снова.\n");
                continue;
            }

            printf("Введите масть карты %d (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ", start_index + i + 1);
            suit_choice = (int)scanf_secure("int");
            if (suit_choice == 0) {
                return;
            }
            if (suit_choice < 1 || suit_choice > 4) {
                printf("Неверная масть карты! Попробуйте снова.\n");
                continue;
            }

            // Проверка на уникальность
            if (used_cards[rank_choice][suit_choice]) {
                printf("Эта карта уже используется! Попробуйте другую карту.\n");
            }
            else {
                Card new_card((Suit)suit_choice, (Rank)rank_choice);
                game->get_board().set_card(start_index + i, new_card);
                used_cards[rank_choice][suit_choice] = true;
                break;
            }
        } while (true);
    }
}


void randomize_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards) {
    int rank_choice, suit_choice;


    Card temp_cards[5];
    int temp_card_count = 0;

    for (int i = 0; i < num_cards; i++) {
        do {
            // генерация случайного ранга (от 2 до 14 где 14 = тузя)//
            rank_choice = rand() % 13 + 2;


            suit_choice = rand() % 4 + 1;


            if (!used_cards[rank_choice][suit_choice]) {

                temp_cards[i].set_rank((Rank)rank_choice);
                temp_cards[i].set_suit((Suit)suit_choice);

                temp_card_count++;
                used_cards[rank_choice][suit_choice] = true;
                break;
            }
        } while (1);
    }

    // Сохраняем карты на доске
    if (temp_card_count == num_cards) {
        for (int i = 0; i < num_cards; i++) {
            game->get_board().set_card(start_index + i, temp_cards[i]);


        }

        // Обновляем 
        game->get_board().set_num_cards(start_index + num_cards);


        // Изменяем фазу игры
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
        printf("Не удалось ввести все карты, изменения отменены.\n");
    }
}



void clear_board(Game* game, bool used_cards[15][5]) {
    for (int i = 0; i < game->get_board().get_num_cards(); i++) {
        Card card = game->get_board().get_card(i);
        used_cards[card.get_rank()][card.get_suit()] = false;
        card.init_card(NONE_SUIT, NONE_RANK);
    }
    game->get_board().set_num_cards(0);  // Обнуляем количество карт на столе
    printf("Игровое поле очищено!\n");
}


void clear_board_turn(Game* game, bool used_cards[15][5]) {

    for (int i = 0; i < 3; i++) { // Очистка карт флопа
        Card card = game->get_board().get_card(i);
        used_cards[card.get_rank()][card.get_suit()] = false;
        card.init_card(NONE_SUIT, NONE_RANK);
    }
    game->get_board().set_num_cards(3);  // Устанавливаем количество карт на столе

    game->set_phase("flop");

}

void clear_board_river(Game* game, bool used_cards[15][5]) {

    Card card = game->get_board().get_card(4); // Очистка карты ривера
    used_cards[card.get_rank()][card.get_suit()] = false;
    card.init_card(NONE_SUIT, NONE_RANK);
    game->get_board().set_num_cards(4); // Устанавливаем количество карт на столе

    game->set_phase("turn");

}

//Эта функция нигде не используется, но мне жалко ее удалять. По сути проверка была ли карта уже использована.
bool is_card_used(Card* board_cards, int num_cards, Card new_card) {
    for (int i = 0; i < num_cards; i++) {
        if (board_cards[i].get_rank() == new_card.get_rank() && board_cards[i].get_suit() == new_card.get_suit()) {
            return true;  // Карта уже использована
        }
    }
    return false;  // Карта не использована
}

// Функция для случайной генерации карты
Card generate_random_card(bool used_cards[15][5]) {
    Card card;
    Rank rank_choice;
    Suit suit_choice;

    do {
        rank_choice = (Rank)(rand() % NUM_RANKS + 2);  // Ранги от 2 до 14 (2-10, J, Q, K, A)
        suit_choice = (Suit)(rand() % NUM_SUITS + 1);  // Масти от 1 до 4
    } while (used_cards[rank_choice][suit_choice]);

    used_cards[rank_choice][suit_choice] = true;

    // Используем сеттеры для установки ранга и масти
    card.set_rank(rank_choice);
    card.set_suit(suit_choice);

    return card;
}


// Проверка на уникальность всех карт в массиве
bool is_unique_cards(Card* cards, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (cards[i].get_rank() == cards[j].get_rank() && cards[i].get_suit() == cards[j].get_suit()) {
                return false;
            }
        }
    }
    return true;
}



int compare_hands(PokerCombination hand1, PokerCombination hand2) {

    if (hand1.hand_rank > hand2.hand_rank) return 1;
    if (hand1.hand_rank < hand2.hand_rank) return -1;


    if (hand1.high_card > hand2.high_card) return 1;
    if (hand1.high_card < hand2.high_card) return -1;

    // сравниваем кикеры
    switch (hand1.hand_rank) {
    case STRAIGHT:
    case STRAIGHT_FLUSH:
        if (hand1.high_card == hand2.high_card) return 0;
        break;

    case FOUR_OF_A_KIND:
    case FULL_HOUSE:
        if (hand1.kicker[0] > hand2.kicker[0]) return 1;
        if (hand1.kicker[0] < hand2.kicker[0]) return -1;
        break;

    case THREE_OF_A_KIND:
        // у трипса только один кикер //
        for (int i = 0; i < 2; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case ONE_PAIR:
    case TWO_PAIR:
        // для пары и двух пар используются три кикера //
        for (int i = 0; i < 3; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case FLUSH:
        // у флеша все пять карт сравниваются по убыванию //
        for (int i = 0; i < 5; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case HIGH_CARD:
        // у старшей карты все пять карт сравниваются //
        for (int i = 0; i < 5; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    default:
        break;
    }

    return 0; // Ничья
}

PokerCombination determine_hand(Hand hand, Board board) {
    PokerCombination result;
    result.hand_rank = HIGH_CARD;
    result.high_card = NONE_RANK;
    for (int i = 0; i < 5; i++) {
        result.kicker[i] = NONE_RANK;
    }

    int card_count[15] = { 0 };
    int suit_count[5] = { 0 };
    Card all_cards[7];            // Массив всех карт (рука + борд) //

    // Собираем все карты (2 карты руки + карты на борде) //
    all_cards[0] = hand.get_card(0);
    all_cards[1] = hand.get_card(1);
    for (int i = 0; i < board.get_num_cards(); i++) {
        // Используем геттер для получения карты с доски
        all_cards[2 + i] = board.get_card(i);

    }

    // Подсчет количества карт по рангу и мастям //
    for (int i = 0; i < 2 + board.get_num_cards(); i++) {
        card_count[all_cards[i].get_rank()]++;
        suit_count[all_cards[i].get_suit()]++;
    }

    Rank top_pair = NONE_RANK, second_pair = NONE_RANK;
    Rank highest_rank = NONE_RANK;
    int flush_suit_index = -1;
    int three_of_a_kind = 0, second_three_of_a_kind = 0;
    int four_of_a_kind = 0;

    // Определение пар троек каре //
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] == 4) {
            four_of_a_kind = rank;
        }
        else if (card_count[rank] == 3) {
            if (three_of_a_kind == 0) {
                three_of_a_kind = rank;
            }
            else {
                second_three_of_a_kind = rank;
            }
        }
        else if (card_count[rank] == 2) {
            if (top_pair == NONE_RANK) {
                top_pair = static_cast<Rank>(rank);
            }
            else if (second_pair == NONE_RANK) {
                second_pair = static_cast<Rank>(rank);
            }
        }
        else if (card_count[rank] == 1 && rank > highest_rank) {
            highest_rank = static_cast<Rank>(rank);
        }
    }

    // Опредееление наличия флеша //
    for (int suit = 0; suit < 5; suit++) {
        if (suit_count[suit] >= 5) {
            flush_suit_index = suit;
            break;
        }
    }

    // Проверка на фулл-хаус //
    if (three_of_a_kind > 0 && (top_pair > 0 || second_three_of_a_kind > 0)) {
        result.hand_rank = FULL_HOUSE;
        result.high_card = static_cast<Rank>(three_of_a_kind); // Старший сет
        result.kicker[0] = static_cast<Rank>((top_pair > 0) ? top_pair : second_three_of_a_kind); // Пара

        return result;
    }

    // Проверка на стрит-флеш //
    if (flush_suit_index != -1) {
        Rank flush_cards[7];
        int flush_card_count = 0;

        // Собираем карты одной масти//
        for (int i = 0; i < 2 + board.get_num_cards(); i++) {
            if (all_cards[i].get_suit() == flush_suit_index) {
                flush_cards[flush_card_count++] = all_cards[i].get_rank();
            }
        }

        qsort(flush_cards, flush_card_count, sizeof(Rank), [](const void* a, const void* b) {
            return (*(Rank*)b - *(Rank*)a);
            });

        // Проверка на стрит-флеш //
        for (int i = 0; i < flush_card_count - 4; i++) {
            if (flush_cards[i] - flush_cards[i + 1] == 1 &&
                flush_cards[i + 1] - flush_cards[i + 2] == 1 &&
                flush_cards[i + 2] - flush_cards[i + 3] == 1 &&
                flush_cards[i + 3] - flush_cards[i + 4] == 1) {
                result.hand_rank = STRAIGHT_FLUSH;
                result.high_card = flush_cards[i];
                return result;
            }
        }

        // Определение флеша //
        result.hand_rank = FLUSH;
        result.high_card = flush_cards[0];
        for (int i = 1; i < 5; i++) {
            result.kicker[i - 1] = flush_cards[i];
        }
        return result;
    }

    // Проверка на стрит //
    int consecutive = 0;
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] > 0) {
            consecutive++;
            if (consecutive == 5) {
                result.hand_rank = STRAIGHT;
                result.high_card = static_cast<Rank>(rank + 4);
                return result;
            }
        }
        else {
            consecutive = 0;
        }
    }

    // Проверка на стрит A-2-3-4-5 //
    if (card_count[ACE] > 0 && card_count[TWO] > 0 && card_count[THREE] > 0 &&
        card_count[FOUR] > 0 && card_count[FIVE] > 0) {
        result.hand_rank = STRAIGHT;
        result.high_card = FIVE;
        return result;
    }

    // Проверка на каре //
    if (four_of_a_kind > 0) {
        result.hand_rank = FOUR_OF_A_KIND;
        result.high_card = static_cast<Rank>(four_of_a_kind);
        result.kicker[0] = highest_rank;
        return result;
    }

    // Проверка на тройку//
    if (three_of_a_kind > 0) {
        result.hand_rank = THREE_OF_A_KIND;
        result.high_card = static_cast<Rank>(three_of_a_kind);
        int kicker_index = 0;
        for (int rank = ACE; rank >= TWO && kicker_index < 2; rank--) {
            if (card_count[rank] == 1 && rank != three_of_a_kind) {
                result.kicker[kicker_index++] = static_cast<Rank>(rank);
            }
        }
        return result;
    }

    // Проверка на две пары//
    if (top_pair > 0 && second_pair > 0) {
        result.hand_rank = TWO_PAIR;
        result.high_card = top_pair;
        result.kicker[0] = second_pair;
        result.kicker[1] = highest_rank;
        return result;
    }

    // Проверка на пару//
    if (top_pair > 0) {
        result.hand_rank = ONE_PAIR;
        result.high_card = top_pair;
        int kicker_index = 0;
        for (int rank = ACE; rank >= TWO && kicker_index < 3; rank--) {
            if (card_count[rank] == 1 && rank != top_pair) {
                result.kicker[kicker_index++] = static_cast<Rank>(rank);
            }
        }
        return result;
    }

    // Если нет комбинаций то хай карта //
    result.hand_rank = HIGH_CARD;
    result.high_card = highest_rank;
    int kicker_index = 0;
    for (int rank = ACE; rank >= TWO && kicker_index < 4; rank--) {
        if (card_count[rank] == 1) {
            result.kicker[kicker_index++] = static_cast<Rank>(rank);
        }
    }

    return result;
}




void calculate_probabilities(Game* game, bool used_cards[15][5], int choice_numSimulations, Settings_debugging_mode* settings) {
    // победы, поражения и ничьи для каждого игрока
    for (int i = 0; i < game->get_current_players(); i++) {
        game->get_player(i).set_wins(0);
        game->get_player(i).set_ties(0);
        game->get_player(i).set_losses(0);
    }

    // (карты игроков и борда)
    initialize_used_cards(game, used_cards);

    for (int i = 0; i < choice_numSimulations; i++) {
        Card deck[52];
        int deck_index = 0;

        // Временно копируем used_cards для каждой simulation
        bool sim_used_cards[15][5];
        memcpy(sim_used_cards, used_cards, sizeof(sim_used_cards));

        // Заполняем колоду, исключая карты из массива used_cards
        for (int rank = 2; rank <= 14; rank++) {
            for (int suit = 1; suit <= 4; suit++) {
                if (!sim_used_cards[rank][suit]) {
                    deck[deck_index].init_card((Suit)suit, (Rank)rank);
                    deck_index++;
                }
            }
        }

        // Перемешиваем колоду
        for (int j = deck_index - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            Card temp = deck[j];
            deck[j] = deck[k];
            deck[k] = temp;
        }

        Card simulation_board[5];

        // Копируем уже известные карты на борд
        for (int j = 0; j < game->get_board().get_num_cards(); j++) {
            simulation_board[j] = game->get_board().get_card(j);
        }

        for (int j = game->get_board().get_num_cards(); j < 5; j++) {
            bool card_found = false;
            while (!card_found) {
                simulation_board[j] = deck[--deck_index]; // Берём карту здесь
                // Проверяем, что карта не использована нигде
                if (!sim_used_cards[simulation_board[j].get_rank()][simulation_board[j].get_suit()]) {
                    sim_used_cards[simulation_board[j].get_rank()][simulation_board[j].get_suit()] = true;
                    card_found = true;
                }
            }
        }

        Board simulated_board;
        simulated_board.set_num_cards(5);
        for (int j = 0; j < 5; j++) {
            simulated_board.set_card(j, simulation_board[j]);
        }

        // Массив для хранения комбинаций всех игроков
        PokerCombination* player_hands = (PokerCombination*)malloc(game->get_current_players() * sizeof(PokerCombination));

        // Оценка комбинаций для каждого игрока
        for (int j = 0; j < game->get_current_players(); j++) {
            player_hands[j] = determine_hand(game->get_player(j).get_hand(), simulated_board);
        }

        // Находим лучшую комбинацию и проверяем на ничью
        int best_player = 0;
        bool tie = false;
        int tie_count = 1;

        for (int j = 1; j < game->get_current_players(); j++) {
            int comparison = compare_hands(player_hands[j], player_hands[best_player]);
            if (comparison > 0) {
                best_player = j;
                tie = false;
                tie_count = 1;
            }
            else if (comparison == 0) {
                tie = true;
                tie_count++;
            }
        }

        // Обновляем статистику
        for (int j = 0; j < game->get_current_players(); j++) {
            if (tie && compare_hands(player_hands[j], player_hands[best_player]) == 0) {
                game->get_player(j).set_ties(game->get_player(j).get_ties() + 1);
            }
            else if (j == best_player) {
                game->get_player(j).set_wins(game->get_player(j).get_wins() + 1);
            }
            else {
                game->get_player(j).set_losses(game->get_player(j).get_losses() + 1);
            }
        }

        // TEST_MODE
        calculate_probabilities_debugging(game, settings, simulated_board, player_hands, i, tie, best_player);

        free(player_hands);
    }

    // Выводим вероятности
    double total_simulations = (double)choice_numSimulations;

    for (int i = 0; i < game->get_current_players(); i++) {
        printf("------------------\n   Игрок %d\n------------------\n", i + 1);
        printf("Победы: %.2f%%\n", (game->get_player(i).get_wins() / total_simulations) * 100);
        printf("Поражения: %.2f%%\n", (game->get_player(i).get_losses() / total_simulations) * 100);
        printf("Ничьи: %.2f%%\n", (game->get_player(i).get_ties() / total_simulations) * 100);
    }
}

void initialize_used_cards(Game* game, bool used_cards[15][5]) {
    for (int rank = 2; rank <= 14; rank++) {
        for (int suit = 1; suit <= 4; suit++) {
            used_cards[rank][suit] = false;
        }
    }

    for (int i = 0; i < game->get_current_players(); i++) {
        Card card1 = game->get_player(i).get_hand().get_card(0);
        Card card2 = game->get_player(i).get_hand().get_card(1);
        used_cards[card1.get_rank()][card1.get_suit()] = true;
        used_cards[card2.get_rank()][card2.get_suit()] = true;
    }

    for (int i = 0; i < game->get_board().get_num_cards(); i++) {
        Card board_card = game->get_board().get_card(i);
        used_cards[board_card.get_rank()][board_card.get_suit()] = true;
    }
}

void calculate_probabilities_debugging(Game* game, Settings_debugging_mode* settings, Board simulated_board, PokerCombination* player_hands, int current_simulation, bool tie, int best_player) {
    if (settings->wins_mode == true) {
        if (best_player + 1 == settings->current_winner) {
            printf("Симуляция %d:\n", current_simulation + 1);
            printf("Карты на столе: ");
            for (int j = 0; j < 5; j++) {
                printf("%d%c ", simulated_board.get_card(j).get_rank(), simulated_board.get_card(j).get_suit() == HEARTS ? 'Ч' :
                    simulated_board.get_card(j).get_suit() == DIAMONDS ? 'Б' :
                    simulated_board.get_card(j).get_suit() == CLUBS ? 'Т' :
                    simulated_board.get_card(j).get_suit() == SPADES ? 'П' : '?');
            }
            printf("\n");

            for (int j = 0; j < game->get_current_players(); j++) {
                printf("Игрок %d: комбинация %d, старшая карта: %d\n", j + 1, player_hands[j].hand_rank, player_hands[j].high_card);
            }

            printf("Игрок %d победил.\n", best_player + 1);
            printf("\n");
        }
    }
    else if (settings->ties_mode == true) {
        if (best_player + 1 == settings->current_winner && settings->current_winner != -1) {
            printf("Симуляция %d:\n", current_simulation + 1);
            printf("Карты на столе: ");
            for (int j = 0; j < 5; j++) {
                printf("%d%c ", simulated_board.get_card(j).get_rank(), simulated_board.get_card(j).get_suit() == HEARTS ? 'Ч' :
                    simulated_board.get_card(j).get_suit() == DIAMONDS ? 'Б' :
                    simulated_board.get_card(j).get_suit() == CLUBS ? 'Т' :
                    simulated_board.get_card(j).get_suit() == SPADES ? 'П' : '?');
            }
            printf("\n");

            if (tie) {
                printf("Ничья между игроками.\n");
            }

            printf("\n");
        }
    }
}

// Сравнивает комбинации всех игроков
void compare_all_hands(Game* game, PokerCombination hands[]) {
    for (int i = 0; i < game->get_current_players(); i++) {
        for (int j = i + 1; j < game->get_current_players(); j++) {
            int result = compare_hands(hands[i], hands[j]);

            if (result == 1) {
                // Игрок i побеждает игрока j
                game->get_player(i).set_wins(game->get_player(i).get_wins() + 1);
                game->get_player(j).set_losses(game->get_player(j).get_losses() + 1);
            }
            else if (result == -1) {
                // Игрок j побеждает игрока i
                game->get_player(j).set_wins(game->get_player(j).get_wins() + 1);
                game->get_player(i).set_losses(game->get_player(i).get_losses() + 1);
            }
            else {
                // Ничья
                game->get_player(i).set_ties(game->get_player(i).get_ties() + 1);
                game->get_player(j).set_ties(game->get_player(j).get_ties() + 1);
            }
        }
    }
}




void fillDeck(int deck[], int player1[], int player2[], int board[], int stage) {
    int cardCount = 0;

    for (int i = 0; i < 52; i++) {
        int card = i;


        int isExcluded = 0;
        for (int j = 0; j < 2; j++) {
            if (player1[j] == card || player2[j] == card) {
                isExcluded = 1;
                break;
            }
        }
        for (int j = 0; j < stage; j++) {
            if (board[j] == card) {
                isExcluded = 1;
                break;
            }
        }

        if (!isExcluded) {
            deck[cardCount++] = card;
        }
    }
}