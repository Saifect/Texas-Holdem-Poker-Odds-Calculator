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

//Игральная карта//
typedef struct {
	Suit suit;
	Rank rank;
}Card;

//Игральная рука игрока (Техасский Холдем)//
typedef struct {
	Card card1; //Первая классная карта
	Card card2; //Вторая великолепная карта 
}Hand;

//Игрок//
typedef struct {
	Hand hand;     //Рука игрока
	double equity; //Вероятность забрать лавэ у соперника НЕ РЕАЛИЗОВАНО ПОКА но скоро будет 
    int wins;
    int ties;
    int losses;
}Player;

//Игровое поле//
typedef struct {
	Card cards[5]; //Карты на борде
	int num_cards; //Количество карт на борде
}Board;

//Структура для представления игры//
typedef struct {
	Player player1;   // Первый игрок
	Player player2;   // Второй игрок
	Board board;      // Игровое поле
	char phase[10];   // Фаза игры (например префлоп флоп терн ривер)
} Game;

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
    ROYAL_FLUSH       // Рояль (Нет бл пианино)
} PokerHandRank;

// Структура для покерной комбинации
typedef struct {
    PokerHandRank hand_rank; // Ранг комбинации
    Rank high_card;          // Старшая карта (стрит и флэш)
    Rank kicker[4];           // Кикеры макс 4
} PokerCombination;


//=========PROTOTYPE_FUNCTIONS=========//

// Print Menu Functions
void print_mainMenu(int* choice);
void print_editPlayerMenu(Game* game, bool used_cards[15][5]);
void print_editBoardMenu(Game* game, bool used_cards[15][5]);
void print_calculatorMenu();

// Main Menu Functions
void get_user_choice(int* choice);
void handle_mainMenu_choice(int choice);
void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[15][5]);


// Initialization Functions
void init_card(Card* card, Suit suit, Rank rank);
void init_randomCard(Card* card);
void init_hand(Hand* hand, Card card1, Card card2);
void init_player(Player* player, Hand hand);
void init_board(Board* board);
void init_game(Game* game, Player player1, Player player2, Board board, const char* phase);

// Menu Handling Functions
void handle_calculatorMenu_choice(int choice, Game* game, bool* exit);

// Utility Functions
const char* get_rank_name(Rank rank);
const char* get_suit_name(Suit suit);
void input_player_cards(Player* player, bool used_cards[15][5]);
void clear_player_cards(Player* player, bool used_cards[15][5], int current_player);

// Useful Functions
double scanf_secure(const char* type);          // Функция для безопасного ввода различных типов данных
void clearConsole();                            // Функция для очистки консоли
void buffer_clear();                            // Функция для очистки буфера ввода
void line_remove(char* str);                    // Функция для удаления символа новой строки из строки
void string_get_secure(char* buffer, int size); // Функция для безопасного получения строки с защитой от переполнения буфера
void press_any_key_to_continue();               // Тут интуитивно понятно

// Board Functions
void clear_board(Game* game, bool used_cards[15][5]);
void input_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards);

// Deck Functions
void shuffle_deck(Card* deck, int size);
void create_deck(Card* deck);
void deal_random_cards(Player* player1, Player* player2, short current_player);

// Game Logic Functions
PokerCombination determine_hand(Hand hand, Board board);
int compare_hands(PokerCombination hand1, PokerCombination hand2);
void print_hand(PokerCombination hand);
void display_board_cards(const Board* board);
void fill_board_with_random_cards(Game* game, const char* phase);
void randomize_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards);

// Прототип функции, если она определена в другом месте или файле
PokerCombination evaluate_hand(Hand player_hand, Card* board_cards);
void calculate_probabilities(Game* game, Player* player1, Player* player2, Board* board, bool used_cards[15][5], int choice_numSimulations);
void print_probabilityMenu(Game* game, bool used_cards[15][5]);

//============MAIN_FUNCTION============//
int main(){

    //Какая-то непонятная фигня//
    system("chcp 65001"); 
    clearConsole();
    /// Установка кодировок консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "Rus");
    ///Основная логика///
    while (true) {
        int choice;
        print_mainMenu(&choice);
        clearConsole();
    }
  
	return 0;
}

//======IMPLENTATION_OF_FUNCTIONS======//

//Начальное меню//
void print_mainMenu(int* choice) {
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
	printf("0. Выход\n");
    printf("================================================\n");
	printf("Ваш выбор: ");
    get_user_choice(choice);
    handle_mainMenu_choice(*choice);
}

//Получение выбора пользователя//
void get_user_choice(int *choice) {
    *choice = (int)scanf_secure("int"); 
}

//Обработка выбора пользователя в основном меню//
void handle_mainMenu_choice(int choice) {
    switch (choice) {
    case 0:
        printf("Выход из программы.\n");
        exit(0); 

        //ATTENTION НЕ КОСТЫЛЬ А ФИЧА
    case -1:
        clearConsole(); //Обработка неправильного ввода функции scanf_secure
        break;

    case 1:
        clearConsole();
        print_calculatorMenu();
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
        printf("Status: In developed\n");
        printf("Version program: ALPHA 1.2\n");
        printf("Author: Saifect@mail.ru\n");
        press_any_key_to_continue();
        break;

    default:
        printf("Неверный выбор! Попробуйте снова.\n");
        break;
    }
}


//Меню калькулятора вероятностей//
void print_calculatorMenu() {
    srand(time(NULL));

    /// Инициализация игры для калькултора ///
    Card card1 = { NONE_SUIT, NONE_RANK }; 
    Card card2 = { NONE_SUIT, NONE_RANK };
    Hand hand1 = { card1, card2 };
    Hand hand2 = { card1, card2 }; 
    Player player1 = { hand1 }; 
    Player player2 = { hand2 };
    Board board = { NONE_SUIT }; 
    Game game = { player1, player2, board }; 
    strcpy(game.phase, "preflop");


    int choice = -1;
    bool edit_mode = false;
    int edit_current_player = 0;
    bool exit = false;
    bool tracking_changes;

    while (exit == false)
    {
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        //были ли карты введены для 1-го игрока?
        if (game.player1.hand.card1.rank != NONE_RANK && game.player1.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 1: %s %s и %s %s\n", get_rank_name(game.player1.hand.card1.rank),
                get_suit_name(game.player1.hand.card1.suit),
                get_rank_name(game.player1.hand.card2.rank),
                get_suit_name(game.player1.hand.card2.suit));
        }
        else {
            printf("Карты игрока 1: не заданы\n");
        }

        //были ли карты введены для 2-го игрока?
        if (game.player2.hand.card1.rank != NONE_RANK && game.player2.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 2: %s %s и %s %s\n", get_rank_name(game.player2.hand.card1.rank),
                get_suit_name(game.player2.hand.card1.suit),
                get_rank_name(game.player2.hand.card2.rank),
                get_suit_name(game.player2.hand.card2.suit));
        }
        else {
            printf("Карты игрока 2: не заданы\n");
        }
  
        if (strcmp(game.phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            display_board_cards(&game.board);

        }

        printf("Текущяя стадия игры (улица): %s\n", game.phase);
        printf("================================================\n");
        printf("           Функционал калькулятора              \n");
        printf("================================================\n");
        printf("1. Редактор карт игроков\n");
        printf("2. Редактор стола и стадий игры\n");
        printf("3. Редактор вычисления вероятностей\n");
        printf("4. Проанализировать комбинациии игроков\n");
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");


        get_user_choice(&choice);
        handle_calculatorMenu_choice(choice, &game, &exit);
    }
}



void handle_calculatorMenu_choice(int choice, Game* game, bool* exit) {

    //Инициализация результата вычисления комбинаций //
    PokerCombination result_player1;
    PokerCombination result_player2;

    //массив для отслеживания занятых карт //
    bool used_cards[15][5] = { false };

    //Помечаем карты которые уже были выданы //
    used_cards[game->player1.hand.card1.rank][game->player1.hand.card1.suit] = true;
    used_cards[game->player1.hand.card2.rank][game->player1.hand.card2.suit] = true;
    used_cards[game->player2.hand.card1.rank][game->player2.hand.card1.suit] = true;
    used_cards[game->player2.hand.card2.rank][game->player2.hand.card2.suit] = true;

    //Помечаем карты на доске как занятые //
    for (int i = 0; i < game->board.num_cards; i++) {
        used_cards[game->board.cards[i].rank][game->board.cards[i].suit] = true;
    }

    switch (choice) {

    case -1:
        clearConsole(); //Обработка неправильного ввода функции scanf_secure 
        break;

    case 0:
        printf("Возврат в главное меню...\n");
        *exit = true;
        press_any_key_to_continue();
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
        if (game->player1.hand.card1.rank == NONE_RANK || game->player2.hand.card1.rank == NONE_RANK) {
            printf("У игроков должны быть заданы карты, для вычисления вероятности!\n");
            press_any_key_to_continue();
            clearConsole();
        }
        else {
            clearConsole();
            print_probabilityMenu(game, used_cards);
        }
       
        break;

    case 4:
        if (game->player1.hand.card1.rank != NONE_RANK && game->player1.hand.card2.rank != NONE_RANK) {
            printf("--------------\n");
            printf(" Первый игрок \n");
            printf("--------------\n");
            result_player1 = determine_hand(game->player1.hand, game->board);
            print_hand(result_player1);
           
        }
        else {
            printf("Карты 1-го игрока не заданы, поэтому у него не может быть комбинации!\n");
        }

        if (game->player2.hand.card1.rank != NONE_RANK && game->player2.hand.card2.rank != NONE_RANK) {
            printf("--------------\n");
            printf(" Второй игрок \n");
            printf("--------------\n");
            result_player2 = determine_hand(game->player2.hand, game->board);
            print_hand(result_player2);
          
        }
        else {
            printf("Карты 2-го игрока не заданы, поэтому у него не может быть комбинации!\n");
        }
        press_any_key_to_continue();
        clearConsole();
        break;

    default:
        printf("Неверный выбор! Попробуйте снова.\n");
        press_any_key_to_continue();
        clearConsole();
        break;
    }
}

void print_probabilityMenu(Game* game, bool used_cards[15][5]) {
   
    int probabilityMenu_choice = 0;
    bool exit = false;

    while (exit == false) {
        // Текущая информация всегда на экране
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        // Карты игрока 1
        if (game->player1.hand.card1.rank != NONE_RANK && game->player1.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 1: %s %s и %s %s\n",
                get_rank_name(game->player1.hand.card1.rank),
                get_suit_name(game->player1.hand.card1.suit),
                get_rank_name(game->player1.hand.card2.rank),
                get_suit_name(game->player1.hand.card2.suit));
        }
        else {
            printf("Карты игрока 1: не заданы\n");
        }

        // Карты игрока 2
        if (game->player2.hand.card1.rank != NONE_RANK && game->player2.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 2: %s %s и %s %s\n",
                get_rank_name(game->player2.hand.card1.rank),
                get_suit_name(game->player2.hand.card1.suit),
                get_rank_name(game->player2.hand.card2.rank),
                get_suit_name(game->player2.hand.card2.suit));
        }
        else {
            printf("Карты игрока 2: не заданы\n");
        }

        // Карты на столе
        if (strcmp(game->phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            display_board_cards(&game->board);
        }

        printf("Текущяя стадия игры (улица): %s\n", game->phase);
        printf("================================================\n");
        printf("       Редактор вычисления вероятностей         \n");
        printf("================================================\n");
        printf("1. Метод симуляций Монте-Карло\n");
        printf("2. Метод подсчёта количества аутов\n");
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        get_user_choice(&probabilityMenu_choice);
        handle_probabilityMenu_choice(probabilityMenu_choice, game, &exit, used_cards);
    }
}

void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[15][5]) {
    int choice_numSimulations;
    switch (choice) {
    case 0:
        *exit = true; // Изменяем значение через указатель
        clearConsole();
        break;

    case 1:
        // Очистка экрана перед меню с симуляциями
        printf("-----------------------------------------------\n");
        printf("Введите количество симуляций\nДиапазон значений от 10.000 до 2.000.000\n");
        printf("(Рекомендуется 250.000 симуляций)\n");
        printf("Или введите 0 для отмены\n");
        printf("-----------------------------------------------\n");
        printf("Ваш выбор: ");
        choice_numSimulations = scanf_secure("int");
   

        if (choice_numSimulations == 0) {
            printf("Операция отменена.\n");
            press_any_key_to_continue();
            clearConsole();
        }
        else if (choice_numSimulations >= 10000 && choice_numSimulations <= 2000000) {
            // Выполнение симуляций
            calculate_probabilities(game, &game->player1, &game->player2, &game->board, used_cards, choice_numSimulations); // Передаем количество симуляций
            press_any_key_to_continue();
            clearConsole();
        }
        else {
            printf("Вы ввели значение вне диапазона!\n");
            press_any_key_to_continue();
            clearConsole();
        }
        break;

    case 2:
        printf("Не реализовано\n");
        press_any_key_to_continue();
        clearConsole();
        break;

    default:
        printf("Неверный выбор! Попробуйте снова.\n");
        press_any_key_to_continue();
        clearConsole();
        break;
    }
}


void print_editPlayerMenu(Game* game, bool used_cards[15][5]) {
    int choice;
    bool back = false;

    while (!back) {
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");
        //были ли карты введены для 1-го игрока?
        if (game->player1.hand.card1.rank != NONE_RANK && game->player1.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 1: %s %s и %s %s\n", get_rank_name(game->player1.hand.card1.rank),
                get_suit_name(game->player1.hand.card1.suit),
                get_rank_name(game->player1.hand.card2.rank),
                get_suit_name(game->player1.hand.card2.suit));
        }
        else {
            printf("Карты игрока 1: не заданы\n");
        }

        //были ли карты введены для 2-го игрока?
        if (game->player2.hand.card1.rank != NONE_RANK && game->player2.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 2: %s %s и %s %s\n", get_rank_name(game->player2.hand.card1.rank),
                get_suit_name(game->player2.hand.card1.suit),
                get_rank_name(game->player2.hand.card2.rank),
                get_suit_name(game->player2.hand.card2.suit));
        }
        else {
            printf("Карты игрока 2: не заданы\n");
        }
        
        if (strcmp(game->phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            display_board_cards(&game->board);

        }

        printf("Текущяя стадия игры (улица): %s\n", game->phase);

        printf("================================================\n");
        printf("            Редактор карт игроков               \n");
        printf("================================================\n");
        printf("1. Добавить/Изменить карты 1-му игроку\n");
        printf("2. Добавить/Изменить карты 2-му игроку\n");
        printf("3. Добавить случайные карты 1-му игроку\n");
        printf("4. Добавить случайные карты 2-му игроку\n");
        printf("5. Очистить карты 1-му игроку\n");
        printf("6. Очистить карты 2-му игроку\n");
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        choice = (int)scanf_secure("int");

        switch (choice) {
        case 0:
            back = true;
            clearConsole();
            break;
        case 1:
            input_player_cards(&game->player1, used_cards);
            clearConsole();
            break;
        case 2:
            input_player_cards(&game->player2, used_cards);
            clearConsole();
            break;
        case 3:
            deal_random_cards(&game->player1, &game->player2, 1);
            clearConsole();
            break;
        case 4:
            deal_random_cards(&game->player1, &game->player2, 2);
            clearConsole();
            break;
        case 5:
            clear_player_cards(&game->player1, used_cards, 1);
            clearConsole();
            break;
        case 6:
            clear_player_cards(&game->player2, used_cards, 2);
            clearConsole();
            break;


        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            press_any_key_to_continue();
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
        if (game->player1.hand.card1.rank != NONE_RANK && game->player1.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 1: %s %s и %s %s\n",
                get_rank_name(game->player1.hand.card1.rank),
                get_suit_name(game->player1.hand.card1.suit),
                get_rank_name(game->player1.hand.card2.rank),
                get_suit_name(game->player1.hand.card2.suit));
        }
        else {
            printf("Карты игрока 1: не заданы\n");
        }

        // были ли карты введены для 2-го игрока?
        if (game->player2.hand.card1.rank != NONE_RANK && game->player2.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 2: %s %s и %s %s\n",
                get_rank_name(game->player2.hand.card1.rank),
                get_suit_name(game->player2.hand.card1.suit),
                get_rank_name(game->player2.hand.card2.rank),
                get_suit_name(game->player2.hand.card2.suit));
        }
        else {
            printf("Карты игрока 2: не заданы\n");
        }

        if (strcmp(game->phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            display_board_cards(&game->board);
        }

        printf("Текущяя стадия игры (улица): %s\n", game->phase);
        printf("================================================\n");
        printf("               Редактор стола                   \n");
        printf("================================================\n");
        printf("1. Добавить/изменить Flop (3 карты)\n");
        printf("2. Добавить/изменить Turn (4-ая карта)\n");
        printf("3. Добавить/изменить River (5-ая карта)\n");
        printf("4. Заполнить Flop случайными картами\n");
        printf("5. Заполнить Turn случайными картами\n");
        printf("6. Заполнить River случайными картами\n");
        printf("7. Очистить стол\n");
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
            if (game->board.num_cards < 3) {
                printf("Сначала необходимо добавить Flop!\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование Turn (четвёртая карта)\n");
                input_board_cards(game, used_cards, 3, 1);  // Ввод одной карты на тёрн
            }
            break;

        case 3:
            if (game->board.num_cards < 4) {
                printf("Сначала необходимо добавить Turn!\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование River (пятая карта)\n");
                input_board_cards(game, used_cards, 4, 1);  // Ввод одной карты на ривер
            }
            break;

        case 4:
            if (game->board.num_cards < 3) {
                printf("Редактирование Flop (случайные 3 карты)\n");
                randomize_board_cards(game, used_cards, 0, 3);  // Случайная раздача 3 карт на флоп
            }
            else {
                printf("Флоп уже задан! Сначала очистите стол.\n");
                press_any_key_to_continue();
            }
            break;

        case 5:
            if (game->board.num_cards < 3) {
                printf("Сначала необходимо добавить Flop!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 4 || game->board.num_cards == 5) {
                printf("Терн уже задан! Сначала очистите стол.\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование Turn (случайная 4-ая карта)\n");
                randomize_board_cards(game, used_cards, 3, 1);  // Случайная раздача 1 карты на тёрн
            }

            break;

        case 6:
            if (game->board.num_cards < 4) {
                printf("Сначала необходимо добавить Turn!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 5) {
                printf("Ривер уже задан! Сначала очистите стол.\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование River (случайная 5-ая карта)\n");
                randomize_board_cards(game, used_cards, 4, 1);  // Случайная раздача 1 карты на ривер
            }
            break;

        case 7:
            clear_board(game, used_cards);
            press_any_key_to_continue();
            break;

        case 0:
            exit_editor = true;
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            press_any_key_to_continue();
            break;
        }
        clearConsole();
    }
}



//Инициализация карты//
void init_card(Card* card, Suit suit, Rank rank){
	card->suit = suit;
	card->rank = rank;
}

//Случайная инициализация карты//
void init_randomCard(Card* card) {

    //Задаем вопрос карте "ты кто по масти?"
	card->suit = (Suit)(rand() % 4);


	card->rank = (Rank)(rand() % 13 + 2);
}


//Инициализация руки//
void init_hand(Hand* hand, Card card1, Card card2) {
	hand->card1 = card1;
	hand->card2 = card2;
}

//Инициализация игрока//
void init_player(Player* player, Hand hand) {
	player->hand = hand;
	player->equity = 0.0;  // Начальная вероятность выигрыша
}

//Инициализация игрового поля//
void init_board(Board* board) {
	board->num_cards = 0;  // В начале нет карт на столе 
}

//Инициализация игры//
void init_game(Game* game, Player player1, Player player2, Board board, const char* phase) {
	game->player1 = player1;
	game->player2 = player2;
	game->board = board;
	snprintf(game->phase, sizeof(game->phase), "%s", phase);  
}

//Вывод названий рангов//
const char* get_rank_name(Rank rank) {
    switch (rank){
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

//Вывод названий мастей//
const char* get_suit_name(Suit suit) {
    switch (suit) {
    case HEARTS: return "Черви";
    case DIAMONDS: return "Бубны";
    case CLUBS: return "Трефы";
    case SPADES: return "Пики";
    default: return "Неизвестно";
    }
}

// Функция для отображения карты//
void print_card(Card card) {
    printf("%s %s\n", get_rank_name(card.rank), get_suit_name(card.suit));
}


void display_board_cards(const Board* board) {
    printf("Карты на столе:\n");
    for (int i = 0; i < board->num_cards; i++) {
        print_card(board->cards[i]);
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

void clear_player_cards(Player* player, bool used_cards[15][5], int current_player){

    if (player->hand.card1.rank == NONE_RANK || player->hand.card2.rank == NONE_RANK) {
        printf("Рука игрока %d не задана, поэтому она не может быть очищена!\n", current_player);
        press_any_key_to_continue();
        clearConsole();

    }

    used_cards[player->hand.card1.rank][player->hand.card1.suit] = false;
    used_cards[player->hand.card2.rank][player->hand.card2.suit] = false;

    player->hand.card1.rank = NONE_RANK;
    player->hand.card1.suit = NONE_SUIT;

    player->hand.card2.rank = NONE_RANK;
    player->hand.card2.suit = NONE_SUIT;

    printf("Рука игрока %d успешно очищена!\n", current_player);

}




void input_player_cards(Player* player, bool used_cards[15][5]) {
    int rank_choice, suit_choice;

    // Ввод первой карты
    do {
        printf("Введите ранг 1-ой карты (2-14) или 0 для выхода: ");
        rank_choice = (int)scanf_secure("int");
        if (rank_choice == 0) {
            return;
        }
        if (rank_choice < 2 || rank_choice > 14) {
            printf("Неверный ранг карты! Попробуйте снова.\n");
            continue;
        }

        printf("Введите масть 1-ой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ");
        suit_choice = (int)scanf_secure("int");
        if (suit_choice == 0) {
            return;
        }
        if (suit_choice < 1 || suit_choice > 4) {
            printf("Неверная масть карты! Попробуйте снова.\n");
            continue;
        }

        // Чекаем на уникальность карты
        if (used_cards[rank_choice][suit_choice]) {
            printf("Эта карта уже используется в игре! Попробуйте другую карту.\n");
        }
        else {
            // Сохранение карты
            player->hand.card1.rank = (Rank)rank_choice;
            player->hand.card1.suit = (Suit)suit_choice;
            used_cards[rank_choice][suit_choice] = true;  // Обозначаем карту как использованную 
            break;
        }
    } while (1);

    // Ввод второй карты
    do {
        printf("Введите ранг 2-ой карты (2-14) или 0 для выхода: ");
        rank_choice = (int)scanf_secure("int");
        if (rank_choice == 0) {
            return;
        }
        if (rank_choice < 2 || rank_choice > 14) {
            printf("Неверный ранг карты! Попробуйте снова.\n");
            continue;
        }

        printf("Введите масть 2-ой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ");
        suit_choice = (int)scanf_secure("int");
        if (suit_choice == 0) {
            return;
        }
        if (suit_choice < 1 || suit_choice > 4) {
            printf("Неверная масть карты! Попробуйте снова.\n");
            continue;
        }

        // Проверка на уникальность карты и совпадение с первой картой
        if (used_cards[rank_choice][suit_choice]) {
            printf("Эта карта уже используется в игре! Попробуйте другую карту.\n");
        }
        else if (player->hand.card1.rank == rank_choice && player->hand.card1.suit == suit_choice) {
            printf("Эта карта совпадает с первой картой! Выберите другую.\n");
        }
        else {
            // Сохранение карты
            player->hand.card2.rank = (Rank)rank_choice;
            player->hand.card2.suit = (Suit)suit_choice;
            used_cards[rank_choice][suit_choice] = true;  
            break;
        }
    } while (1);
}



//==========Useful_functions==========//
// Функция для безопасного ввода различных типов данных
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

// Функция для перемешивания массива карт
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
            deck[index].suit = (Suit)suit;
            deck[index].rank = (Rank)rank;
            index++;
        }
    }
}

// Функция раздачи случайных карт двум игрокам
void deal_random_cards(Player* player1, Player* player2, short сurrent_player) {
    // Создаем деку
    Card deck[52];
    create_deck(deck);

    // Перемешиваем деку
    shuffle_deck(deck, 52);

    //Дилер раздает карты плеерам
    if (сurrent_player == 1) {
        player1->hand.card1 = deck[0];
        player1->hand.card2 = deck[1];
    }
    if (сurrent_player == 2) {
        player2->hand.card1 = deck[2];
        player2->hand.card2 = deck[3];
    }
    if (сurrent_player == 12) {
        player1->hand.card1 = deck[0];
        player1->hand.card2 = deck[1];
        player2->hand.card1 = deck[2];
        player2->hand.card2 = deck[3];
    }
   
}

// Определяем максимальный размер доски
#define MAX_BOARD_CARDS 5

void fill_board_with_random_cards(Game* game, const char* phase) {
    Card deck[52];
    create_deck(deck); // Создаем полную декуууу
    shuffle_deck(deck, 52); // Перемешиваем декууу

    // Помечаем карты которые уже есть у чмонь
    bool used[52] = { false };

    // Помечаем карты первого чмони
    used[game->player1.hand.card1.rank * 4 + game->player1.hand.card1.suit] = true;
    used[game->player1.hand.card2.rank * 4 + game->player1.hand.card2.suit] = true;

    // Помечаем карты второго чмони
    used[game->player2.hand.card1.rank * 4 + game->player2.hand.card1.suit] = true;
    used[game->player2.hand.card2.rank * 4 + game->player2.hand.card2.suit] = true;

  
    int cards_needed = 0;
    if (strcmp(phase, "preflop") == 0) {
        cards_needed = 3;  // На флопе выкладываются 3 заветные карты ну и там по аналогии...
    }
    else if (strcmp(phase, "flop") == 0) {
        cards_needed = 4;  
    }
    else if (strcmp(phase, "turn") == 0) {
        cards_needed = 5;  
    }
    else if (strcmp(phase, "river") == 0) {
        printf("Стол полный!\n");
        press_any_key_to_continue();
        clearConsole();
        return;
    }

    // Заполняем доску недостающими картами
    while (game->board.num_cards < cards_needed) {
        if (game->board.num_cards >= MAX_BOARD_CARDS) {
            printf("Ошибка: переполнение массива карт на доске.\n");
            press_any_key_to_continue();
            return; 
        }

        for (int j = 0; j < 52; j++) {
            if (!used[j]) {
                game->board.cards[game->board.num_cards++] = deck[j];
                used[j] = true; // Помечаем карту 
                break;
            }
        }
    }
}

void input_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards) {
    int rank_choice, suit_choice;

    // Временный массив для хранения карт, которые будут добавлены на стол, если ввод завершится корректно
    Card temp_cards[5];
    int temp_card_count = 0;

    for (int i = 0; i < num_cards; i++) {
        do {
            printf("Введите ранг карты %d (2-14) или 0 для выхода: ", start_index + i + 1);
            rank_choice = (int)scanf_secure("int");
            if (rank_choice == 0) {
                // Если пользователь выходит, возвращаемся без сохранения карт
                return;
            }
            if (rank_choice < 2 || rank_choice > 14) {
                printf("Неверный ранг карты! Попробуйте снова.\n");
                continue;
            }

            printf("Введите масть карты %d (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ", start_index + i + 1);
            suit_choice = (int)scanf_secure("int");
            if (suit_choice == 0) {
                // Если пользователь выходит, возвращаемся без сохранения карт
                return;
            }
            if (suit_choice < 1 || suit_choice > 4) {
                printf("Неверная масть карты! Попробуйте снова.\n");
                continue;
            }

            // Проверка на уникальность карты (среди всех уже использованных карт)
            if (used_cards[rank_choice][suit_choice]) {
                printf("Эта карта уже используется! Попробуйте другую карту.\n");
            }
            else {
                // Сохраняем карту во временный массив
                temp_cards[i].rank = (Rank)rank_choice;
                temp_cards[i].suit = (Suit)suit_choice;
                temp_card_count++;
                break;
            }
        } while (1);
    }

    // Если пользователь ввёл все карты, то сохраняем их на доске
    if (temp_card_count == num_cards) {
        for (int i = 0; i < num_cards; i++) {
            game->board.cards[start_index + i] = temp_cards[i];
            used_cards[temp_cards[i].rank][temp_cards[i].suit] = true;  // Помечаем карту как использованную
        }
        // Обновляем количество карт на доске
        game->board.num_cards = start_index + num_cards;

        // Изменяем фазу игры в зависимости от текущего состояния стола
        if (game->board.num_cards == 3) {
            strcpy(game->phase, "flop");
        }
        else if (game->board.num_cards == 4) {
            strcpy(game->phase, "turn");
        }
        else if (game->board.num_cards == 5) {
            strcpy(game->phase, "river");
        }
    }
    else {
        printf("Не удалось ввести все карты, изменения отменены.\n");
    }
}


void randomize_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards) {
    int rank_choice, suit_choice;

    // Временный массив для хранения карт, которые будут добавлены на стол
    Card temp_cards[5];
    int temp_card_count = 0;

    for (int i = 0; i < num_cards; i++) {
        do {
            // Генерация случайного ранга (от 2 до 14, где 14 = туз)
            rank_choice = rand() % 13 + 2;

            // Генерация случайной масти (от 1 до 4, где 1 = Черви, 2 = Бубны, 3 = Трефы, 4 = Пики)
            suit_choice = rand() % 4 + 1;

            // Проверка на уникальность карты (среди всех уже использованных карт)
            if (!used_cards[rank_choice][suit_choice]) {
                // Сохраняем карту во временный массив
                temp_cards[i].rank = (Rank)rank_choice;
                temp_cards[i].suit = (Suit)suit_choice;
                temp_card_count++;
                used_cards[rank_choice][suit_choice] = true;  // Помечаем карту как использованную
                break;
            }
        } while (1);  // Продолжаем генерировать до тех пор, пока не найдём уникальную карту
    }

    // Сохраняем карты на доске
    if (temp_card_count == num_cards) {
        for (int i = 0; i < num_cards; i++) {
            game->board.cards[start_index + i] = temp_cards[i];
        }

        // Обновляем количество карт на доске
        game->board.num_cards = start_index + num_cards;

        // Изменяем фазу игры в зависимости от текущего состояния стола
        if (game->board.num_cards == 3) {
            strcpy(game->phase, "flop");
        }
        else if (game->board.num_cards == 4) {
            strcpy(game->phase, "turn");
        }
        else if (game->board.num_cards == 5) {
            strcpy(game->phase, "river");
        }
    }
    else {
        printf("Не удалось ввести все карты, изменения отменены.\n");
    }
}




// Функция для очистки стола
void clear_board(Game* game, bool used_cards[15][5]) {

    if (game->board.cards[0].rank = NONE_RANK) {
        printf("Стол и так пустой\n");
    }

    // Сбрасываем все карты на борде
    for (int i = 0; i < 5; i++) {
        game->board.cards[i].rank = NONE_RANK;
        game->board.cards[i].suit = NONE_SUIT;
    }

    game->board.num_cards = 0;

    // Очищаем массив использованных карт
    for (int rank = 2; rank <= 14; rank++) {
        for (int suit = 1; suit <= 4; suit++) {
            used_cards[rank][suit] = false;
        }
    }

    strcpy(game->phase, "preflop");

    printf("Стол очищен!\n");
}


//Эта функция нигде не используется но мне жалко ее удалять по сути проверка была ли карта уже использована
bool is_card_used(Card* board_cards, int num_cards, Card new_card) {
    for (int i = 0; i < num_cards; i++) {
        if (board_cards[i].rank == new_card.rank && board_cards[i].suit == new_card.suit) {
            return true;  // Карта поюзанная
        }
    }
    return false;  // Карта не поюзанная
}
//////////////////////////////////////////////////////////////////////////////

// Функция для случайной генерации карты
Card generate_random_card(bool used_cards[15][5]) {
    Card card;
    do {
        card.rank = (Rank)(rand() % NUM_RANKS + 2);  // Ранги от 2 до 14 (2-10, J, Q, K, A)
        card.suit = (Suit)(rand() % NUM_SUITS + 1);  // Масти от 1 до 4
    } while (used_cards[card.rank][card.suit]);  // Проверяем, не используется ли эта карта
    used_cards[card.rank][card.suit] = true;
    return card;
}

// Проверка на уникальность всех карт в массиве
bool is_unique_cards(Card* cards, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (cards[i].rank == cards[j].rank && cards[i].suit == cards[j].suit) {
                return false;
            }
        }
    }
    return true;
}

// Функция для сравнения двух покерных рук, включая кикеры
int compare_hands(PokerCombination hand1, PokerCombination hand2) {
    // Сравниваем комбинации (старшинство комбинаций)
    if (hand1.hand_rank > hand2.hand_rank) return 1;
    if (hand1.hand_rank < hand2.hand_rank) return -1;

    // Если комбинации равны, сравниваем старшие карты комбинации
    if (hand1.high_card > hand2.high_card) return 1;
    if (hand1.high_card < hand2.high_card) return -1;

    // Сравнение дополнительных карт в зависимости от комбинации
    switch (hand1.hand_rank) {
    case HIGH_CARD:
    case ONE_PAIR:
    case TWO_PAIR:
    case THREE_OF_A_KIND:
    case FOUR_OF_A_KIND:
        // Для комбинаций с кикерами, начиная с старших кикеров
        for (int i = 0; i < 2; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case FULL_HOUSE:
        // Для фулл-хауса сравниваем тройки, затем пары
        if (hand1.kicker[0] > hand2.kicker[0]) return 1;
        if (hand1.kicker[0] < hand2.kicker[0]) return -1;
        break;

    case STRAIGHT:
    case FLUSH:
    case STRAIGHT_FLUSH:
        // Для стритов и флешей сравниваем старшие карты
        for (int i = 0; i < 5; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;
    }

    // Если все карты и кикеры равны - ничья
    return 0;
}



PokerCombination determine_hand(Hand hand, Board board) {
    PokerCombination result;
    result.hand_rank = HIGH_CARD;
    result.high_card = NONE_RANK;

    int card_count[15] = { 0 };
    int suit_count[5] = { 0 };
    Card all_cards[7];

    // Собираем все карты (2 карты руки + карты на борде)
    all_cards[0] = hand.card1;
    all_cards[1] = hand.card2;
    for (int i = 0; i < board.num_cards; i++) {
        all_cards[2 + i] = board.cards[i];
    }

    // Подсчет количества карт по рангу и масти
    for (int i = 0; i < 2 + board.num_cards; i++) {
        card_count[all_cards[i].rank]++;
        suit_count[all_cards[i].suit]++;
    }

    Rank top_pair = NONE_RANK, second_pair = NONE_RANK;
    Rank highest_rank = NONE_RANK;
    Rank kicker[2] = { NONE_RANK, NONE_RANK };
    int flush_suit_index = -1;

    int three_of_a_kind = 0, four_of_a_kind = 0;

    // Определение пар, тройки и каре
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] == 4) {
            four_of_a_kind = rank;
        }
        else if (card_count[rank] == 3) {
            three_of_a_kind = rank;
        }
        else if (card_count[rank] == 2) {
            if (top_pair == NONE_RANK) {
                top_pair = static_cast<Rank>(rank);
            }
            else {
                second_pair = top_pair;
                top_pair = static_cast<Rank>(rank);
            }
        }
        else if (card_count[rank] == 1 && rank > highest_rank) {
            highest_rank = static_cast<Rank>(rank);
        }
    }

    // Проверка на фулл-хаус (третье и второе условие)
    if (three_of_a_kind > 0 && top_pair > 0) {
        result.hand_rank = FULL_HOUSE;
        result.high_card = static_cast<Rank>(three_of_a_kind);  // Тройка — старшая
        result.kicker[0] = static_cast<Rank>(top_pair);         // Пара — младшая
        return result;
    }

    // Определение наличия флеша (5 карт одной масти)
    for (int suit = 0; suit < 5; suit++) {
        if (suit_count[suit] >= 5) {
            flush_suit_index = suit;
            break;
        }
    }

    // Если есть флеш, проверяем на стрит-флеш
    if (flush_suit_index != -1) {
        Rank flush_cards[7];
        int flush_card_count = 0;

        // Собираем карты, которые принадлежат одной масти
        for (int i = 0; i < 2 + board.num_cards; i++) {
            if (all_cards[i].suit == flush_suit_index) {
                flush_cards[flush_card_count++] = all_cards[i].rank;
            }
        }

        // Сортируем карты флеша по убыванию
        for (int i = 0; i < flush_card_count - 1; i++) {
            for (int j = i + 1; j < flush_card_count; j++) {
                if (flush_cards[i] < flush_cards[j]) {
                    Rank temp = flush_cards[i];
                    flush_cards[i] = flush_cards[j];
                    flush_cards[j] = temp;
                }
            }
        }

        // Проверяем наличие стрит-флеша
        int consecutive = 1;
        for (int i = 0; i < flush_card_count - 1; i++) {
            if (flush_cards[i] - flush_cards[i + 1] == 1) {
                consecutive++;
            }
            else if (flush_cards[i] != flush_cards[i + 1]) {
                consecutive = 1; // Сброс последовательности
            }

            // Если есть 5 последовательных карт, это стрит-флеш
            if (consecutive == 5) {
                result.hand_rank = STRAIGHT_FLUSH;
                result.high_card = flush_cards[i - 3]; // Старшая карта стрит-флеша
                return result;
            }
        }

        // Если стрит-флеша нет, определяем просто флеш
        result.hand_rank = FLUSH;
        result.high_card = flush_cards[0];  // Старшая карта флеша
        result.kicker[0] = flush_cards[1];
        result.kicker[1] = flush_cards[2];
        return result;
    }

    // Проверка на стрит
    int consecutive = 0;
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] > 0) {
            consecutive++;
            if (consecutive == 5) {
                result.hand_rank = STRAIGHT;
                result.high_card = static_cast<Rank>(rank + 4);  // Старшая карта стрита
                return result;
            }
        }
        else {
            consecutive = 0;
        }
    }

    // Остальная логика (пары, тройки, каре, и т.д.) остается без изменений...

    // Проверка на карманную пару
    if (hand.card1.rank == hand.card2.rank) {
        top_pair = hand.card1.rank;
        if (card_count[hand.card1.rank] == 3) {
            result.hand_rank = THREE_OF_A_KIND;
            result.high_card = hand.card1.rank;
            result.kicker[0] = NONE_RANK;  // Нет кикера для сета
            return result; // Карманная пара превращается в сет
        }
        if (card_count[hand.card1.rank] == 2) {
            result.hand_rank = ONE_PAIR;  // Карманная пара
            result.high_card = hand.card1.rank;
            // Заполнение кикеров для карманной пары
            int kicker_count = 0;
            for (int rank = ACE; rank >= TWO; rank--) {
                if (card_count[rank] > 0 && rank != hand.card1.rank) {
                    kicker[kicker_count++] = static_cast<Rank>(rank);
                    if (kicker_count == 2) break;
                }
            }
            result.kicker[0] = kicker[0];
            result.kicker[1] = kicker[1];
            return result;
        }
    }


    // Проверка на каре
    if (four_of_a_kind > 0) {
        result.hand_rank = FOUR_OF_A_KIND;
        result.high_card = static_cast<Rank>(four_of_a_kind);
        result.kicker[0] = highest_rank;
        return result;
    }

    // Проверка на трипс или сет
    if (three_of_a_kind > 0) {
        result.hand_rank = THREE_OF_A_KIND;
        result.high_card = static_cast<Rank>(three_of_a_kind);
        result.kicker[0] = highest_rank;
        result.kicker[1] = second_pair; // или другой кикер
        return result;
    }


    // Проверка на две пары
    if (top_pair > 0 && second_pair > 0) {
        result.hand_rank = TWO_PAIR;
        result.high_card = top_pair;
        result.kicker[0] = second_pair;
        result.kicker[1] = highest_rank;
        return result;
    }

    // Проверка на одну пару
    if (top_pair > 0) {
        result.hand_rank = ONE_PAIR;
        result.high_card = top_pair;

        // Кикеры для пары
        int kicker_count = 0;
        for (int rank = ACE; rank >= TWO; rank--) {
            if (card_count[rank] > 0 && rank != top_pair) {
                kicker[kicker_count++] = static_cast<Rank>(rank);
                if (kicker_count == 2) break;
            }
        }
        result.kicker[0] = kicker[0];
        result.kicker[1] = kicker[1];
        return result;
    }

    // Если ни одна комбинация не собрана — проверяем старшую карту и кикеры
    result.hand_rank = HIGH_CARD;
    result.high_card = (hand.card1.rank > hand.card2.rank) ? hand.card1.rank : hand.card2.rank;
    kicker[0] = (hand.card1.rank > hand.card2.rank) ? hand.card2.rank : hand.card1.rank;
    result.kicker[0] = kicker[0];

    return result;
}


void calculate_probabilities(Game* game, Player* player1, Player* player2, Board* board, bool used_cards[15][5], int choice_numSimulations) {
    player1->wins = 0;
    player1->ties = 0;
    player1->losses = 0;
    player2->wins = 0;
    player2->ties = 0;
    player2->losses = 0;

    for (int i = 0; i < choice_numSimulations; i++) {
        Card deck[52];
        int deck_index = 0;

        // Заполняем колоду, исключая карты, которые уже были использованы (в руках игроков или на борде)
        for (int rank = 2; rank <= 14; rank++) {
            for (int suit = 1; suit <= 4; suit++) {
                if (!used_cards[rank][suit]) {
                    deck[deck_index].rank = (Rank)rank;
                    deck[deck_index].suit = (Suit)suit;
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

        // Эмулируем недостающие карты на столе, создавая симулированный борд
        Card simulation_board[5];
        for (int j = 0; j < board->num_cards; j++) {
            simulation_board[j] = board->cards[j];  // Копируем уже известные карты
        }

        for (int j = board->num_cards; j < 5; j++) {
            simulation_board[j] = deck[--deck_index];  // Симулируем оставшиеся карты
        }

        // Создаем временный объект типа Board для симулированных карт
        Board simulated_board;
        simulated_board.num_cards = 5;  // Устанавливаем, что на борде всегда будет 5 карт
        for (int j = 0; j < 5; j++) {
            simulated_board.cards[j] = simulation_board[j];
        }

        // Оценка комбинаций для каждого игрока на симулированной доске
        PokerCombination hand1 = determine_hand(player1->hand, simulated_board);  // Используем симулированный борд!
        PokerCombination hand2 = determine_hand(player2->hand, simulated_board);  // Используем симулированный борд!

        // Сравнение комбинаций и увеличение счетчиков
        int comparison = compare_hands(hand1, hand2);
        if (comparison == 1) {
            player1->wins++;
            player2->losses++;
        }
        else if (comparison == -1) {  // Исправлено с comparison == 2 на -1
            player2->wins++;
            player1->losses++;
        }
        else {
            player1->ties++;
            player2->ties++;
        }

    }

    // Вывод результатов
    printf("Игрок 1:\n Победы: %.2f%%\n Поражения: %.2f%%\n Ничьи: %.2f%%\n",
        (float)player1->wins / choice_numSimulations * 100,
        (float)player1->losses / choice_numSimulations * 100,
        (float)player1->ties / choice_numSimulations * 100);

    printf("Игрок 2:\n Победы: %.2f%%\n Поражения: %.2f%%\n Ничьи: %.2f%%\n",
        (float)player2->wins / choice_numSimulations * 100,
        (float)player2->losses / choice_numSimulations * 100,
        (float)player2->ties / choice_numSimulations * 100);
}





// Заполнение колоды карт, исключая карты игроков и борда
void fillDeck(int deck[], int player1[], int player2[], int board[], int stage) {
    int cardCount = 0;

    for (int i = 0; i < 52; i++) {
        int card = i;

        // Исключение карт игроков и борда
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

