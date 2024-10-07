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

// Игроки
typedef struct {
    Hand hand;     // Рука игрока
    double equity; // Вероятность забрать лавэ у соперника (пока не реализовано)
    int wins;
    int ties;
    int losses;
} Player;

//Игровое поле//
typedef struct {
	Card cards[5]; //Карты на борде
	int num_cards; //Количество карт на борде
}Board;

// Структура для представления игры с несколькими игроками
typedef struct {
    Player players[12]; // Массив игроков (до 12)
    int num_players;    // Количество игроков в игре
    int current_players;
    Board board;        // Игровое поле
    char phase[10];     // Фаза игры (например, префлоп, флоп, терн, ривер)
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
    Rank kicker[5];           // Кикеры макс 4
} PokerCombination;

typedef struct {
    bool ties_mode;
    bool wins_mode;
    int current_winner;
}Settings_debugging_mode;



//=========PROTOTYPE_FUNCTIONS=========//
void initialize_game(Game *game, int num_players);

// Print Menu Functions
void print_mainMenu(int* choice);
void print_editPlayerMenu(Game* game, bool used_cards[15][5]);
void print_editBoardMenu(Game* game, bool used_cards[15][5]);
void print_calculatorMenu();

// Main Menu Functions
void get_user_choice(int* choice);
void handle_mainMenu_choice(int choice);
void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[15][5], int* num_simulations, Settings_debugging_mode* settings_debugging_mode);
void initialize_used_cards(Game* game, bool used_cards[15][5]);
// Initialization Functions
void init_card(Card* card, Suit suit, Rank rank);
void init_randomCard(Card* card);
void init_hand(Hand* hand, Card card1, Card card2);
void init_player(Player* players, Hand hand);
void init_board(Board* board);
void init_game(Game* game, Player player1, Player player2, Board board, const char* phase);

// Menu Handling Functions
void handle_calculatorMenu_choice(int choice, Game* game, bool* exit);

// Utility Functions
const char* get_rank_name(Rank rank);
const char* get_suit_name(Suit suit);
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
void display_board_cards(const Board* board);
void randomize_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards);

// Прототип функции, если она определена в другом месте или файле
void calculate_probabilities(Game* game, bool used_cards[15][5], int choice_numSimulations, Settings_debugging_mode *settings);
void print_probabilityMenu(Game* game, bool used_cards[15][5]);
void compare_all_hands(Game* game, PokerCombination hands[]);

void calculate_probabilities_debugging(Game* game, Settings_debugging_mode* settings, Board simulated_board, PokerCombination* player_hands, int current_simulation, bool tie, int best_player);
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

// Инициализация игры для калькулятора с до 12 игроками
void initialize_game(Game* game, int num_players) {
    // Проверяем, что количество игроков в пределах допустимого
    if (num_players > 12) {
        num_players = 12; // Ограничение на 12 игроков
    }

    // Инициализируем игроков
    for (int i = 0; i < num_players; i++) {
        Card card1 = { NONE_SUIT, NONE_RANK };
        Card card2 = { NONE_SUIT, NONE_RANK };
        Hand hand = { card1, card2 };
        game->players[i].hand = hand;
        game->players[i].equity = 0.0;
        game->players[i].wins = 0;
        game->players[i].ties = 0;
        game->players[i].losses = 0;
    }

    // Инициализируем игровое поле
    for (int i = 0; i < 5; i++) {
        game->board.cards[i].suit = NONE_SUIT;
        game->board.cards[i].rank = NONE_RANK;
    }
    game->board.num_cards = 0;

    // Фаза игры
    strcpy(game->phase, "preflop");

    // Устанавливаем количество игроков
    game->num_players = num_players;

 

}


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
	printf("0. Выход из программы\n");
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
        break;
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
        printf("Status: Stable\n");
        printf("Version program: 2.1\n");
        printf("Author: Saifect@mail.ru\n");
        press_any_key_to_continue();
        break;

    default:
        break;
    }
}


//Меню калькулятора вероятностей//
void print_calculatorMenu() {
    srand(time(NULL));
    
    
    Game game;
    initialize_game(&game, 12);


    strcpy(game.phase, "preflop");
  
    game.current_players = 2;
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

        for (int i = 0; i < game.current_players; i++) {
            // Проверяем, были ли введены карты для текущего игрока
            if (game.players[i].hand.card1.rank != NONE_RANK && game.players[i].hand.card2.rank != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(game.players[i].hand.card1.rank),
                    get_suit_name(game.players[i].hand.card1.suit),
                    get_rank_name(game.players[i].hand.card2.rank),
                    get_suit_name(game.players[i].hand.card2.suit));
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
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
        printf("1. Редактор игроков\n");
        printf("2. Редактор стола и стадий игры\n");
        printf("3. Редактор вычисления вероятностей\n");
        printf("4. Проанализировать комбинациии игроков\n");
        printf("-----------------------------------------------\n");
        printf("0. Выйти из покерного калькулятора\n");
        printf("================================================\n");
        printf("Ваш выбор: ");


        get_user_choice(&choice);
        handle_calculatorMenu_choice(choice, &game, &exit);
    }
}



void handle_calculatorMenu_choice(int choice, Game* game, bool* exit) {
    // Инициализация результата вычисления комбинаций
    PokerCombination* result_player = (PokerCombination*)malloc(game->num_players * sizeof(PokerCombination));
    if (result_player == NULL) {
        printf("Ошибка: недостаточно памяти для вычисления комбинаций.\n");
        return;
    }

    // Массив для отслеживания занятых карт
    bool used_cards[15][5] = { false };

    used_cards[game->players[0].hand.card1.rank][game->players[0].hand.card1.suit] = true;
    used_cards[game->players[0].hand.card2.rank][game->players[0].hand.card2.suit] = true;
    used_cards[game->players[1].hand.card1.rank][game->players[1].hand.card1.suit] = true;
    used_cards[game->players[1].hand.card2.rank][game->players[1].hand.card2.suit] = true;

    // Помечаем карты на доске как занятые
    for (int i = 0; i < game->board.num_cards; i++) {
        used_cards[game->board.cards[i].rank][game->board.cards[i].suit] = true;
    }

    switch (choice) {
    case -1:
        clearConsole();
        break;

    case 0:
        printf("Вы уверены? Введённые вами карты сбросятся\n");
        printf("Y/yes - да\n");
        printf("N/no - нет\n");

        char str_choice[3];  // Массив для хранения ответа пользователя
        string_get_secure(str_choice, 3);  // Получаем безопасный ввод

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
        for (int i = 0; i < game->current_players && i < game->num_players; i++) {
            if (game->players[i].hand.card1.rank != NONE_RANK && game->players[i].hand.card2.rank != NONE_RANK) {
                result_player[i] = determine_hand(game->players[i].hand, game->board);
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

    free(result_player);
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
        // Текущая информация всегда на экране
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");

        for (int i = 0; i < game->current_players; i++) {
            // Проверяем, были ли введены карты для текущего игрока
            if (game->players[i].hand.card1.rank != NONE_RANK && game->players[i].hand.card2.rank != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(game->players[i].hand.card1.rank),
                    get_suit_name(game->players[i].hand.card1.suit),
                    get_rank_name(game->players[i].hand.card2.rank),
                    get_suit_name(game->players[i].hand.card2.suit));
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
        }

        // Карты на столе
        if (strcmp(game->phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            display_board_cards(&game->board);
        }
       
        printf("Текущяя стадия игры (улица): %s\n", game->phase);
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

void handle_probabilityMenu_choice(int choice, Game* game, bool* exit, bool used_cards[15][5], int *num_simulations, Settings_debugging_mode *settings_debugging_mode) {
    bool debugging_mode;
    int choice_user;
    char str_choice[4];
    int players_with_cards = 0; // Счётчик игроков с картами
    switch (choice) {
    case 0:
        *exit = true; // Изменяем значение через указатель
        clearConsole();
        break;

    case 1:
        

        // Цикл по всем игрокам
        for (int i = 0; i < game->current_players; i++) {
            // Проверяем, есть ли карты у игрока
            if (game->players[i].hand.card1.rank != NONE_RANK && game->players[i].hand.card2.rank != NONE_RANK) {
                players_with_cards++; // Увеличиваем счётчик
            }
            // Если хотя бы у двух игроков есть карты, прекращаем проверку
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

                char str_choice[3];  // Массив для хранения ответа пользователя
                string_get_secure(str_choice, 3);  // Получаем безопасный ввод

                // Приводим ввод к нижнему регистру для проверки
                for (int i = 0; str_choice[i]; i++) {
                    str_choice[i] = tolower(str_choice[i]);
                }

                if (strcmp(str_choice, "y") == 0 || strcmp(str_choice, "yes") == 0) {
                    // Если пользователь согласен, продолжаем выполнение
                    printf("Продолжаем выполнение в режиме отладки с %d симуляциями.\n", *num_simulations);
                    // Здесь можно добавить логику для продолжения процесса
                }
                else {
                    // Если пользователь отказался, выходим в меню
                    printf("Операция отменена.\n");
                    press_any_key_to_continue();
                    clearConsole();
                    break;
                }

                press_any_key_to_continue();  // Ожидаем, пока пользователь нажмет любую клавишу
                clearConsole();  // Очищаем консоль
            }
            printf("Не нажимайте ничего пока не загрузится результат \n");
            printf("Загрузка...\n");
            calculate_probabilities(game, used_cards, *num_simulations, settings_debugging_mode); // Передаем количество симуляций
            
            press_any_key_to_continue();
            clearConsole();
        }
        break;

    case 2: {
        // Обратите внимание на фигурные скобки вокруг case 2
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
            *num_simulations = num_simulations_new; // Обновляем количество симуляций
            printf("Вы установили %d симуляций для метода Монте-Карло\n", *num_simulations);
            press_any_key_to_continue();
            clearConsole();
        }
        else {
            printf("Вы ввели значение вне диапазона! Используем 250000 по умолчанию.\n");
            *num_simulations = 250000; // Устанавливаем значение по умолчанию
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
            else if (choice_user < 1 || choice_user > game->num_players) {
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
            if(settings_debugging_mode->wins_mode == true){
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
        printf("\n");
        printf("================================================\n");
        printf("             Текущая информация                 \n");
        printf("================================================\n");
        for (int i = 0; i < game->current_players; i++) {
            // Проверяем, были ли введены карты для текущего игрока
            if (game->players[i].hand.card1.rank != NONE_RANK && game->players[i].hand.card2.rank != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(game->players[i].hand.card1.rank),
                    get_suit_name(game->players[i].hand.card1.suit),
                    get_rank_name(game->players[i].hand.card2.rank),
                    get_suit_name(game->players[i].hand.card2.suit));
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
        }
        
        if (strcmp(game->phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют\n");
        }
        else {
            display_board_cards(&game->board);

        }

        printf("Текущяя стадия игры (улица): %s\n", game->phase);

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
            deal_cards(game->players, game->current_players, used_cards, choice_player);
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
            deal_random_cards(game->players, game->current_players, used_cards, choice_player);
            printf("Рука игрока %d сгенерирована случайно!\n", choice_player);
            press_any_key_to_continue();
            clearConsole();
            break;
        case 3:
            int choice_player;
            printf("Введите номер игрока или 0 для отмены: ");
            choice_player = scanf_secure("int");
            if (choice_player == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }
            else {
                clear_player_cards(game->players, game->current_players, used_cards, choice_player, false);
                printf("Рука игрока %d успешно очищена!\n", choice_player);
                press_any_key_to_continue();
                clearConsole();
            }
            break;

        case 4:
            clear_all_players_cards(game->players, game->current_players, used_cards, false);
            clearConsole();
            break;

        case 5:
            printf("Введите количество игроков (2-%d) или 0 для отмены: ", game->num_players);
            choice_player = scanf_secure("int");

            if (choice_player == 0) {
                printf("Отмена операции.\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }

            if (choice_player == game->current_players) {
                printf("У вас столько же игроков!\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }

            if (choice_player < 2 || choice_player > game->num_players) {
                printf("Вы ввели число вне диапазона!\n");
                press_any_key_to_continue();
                clearConsole();
                break;
            }

            // Если новое количество игроков меньше текущего
            if (choice_player < game->current_players) {
                // Очищаем карты всех лишних игроков
                for (int i = choice_player; i < game->current_players; i++) {
                    clear_player_cards(game->players, game->current_players, used_cards, i + 1, true);
                }
            }

            // Устанавливаем новое количество игроков
            game->current_players = choice_player;
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
        for (int i = 0; i < game->current_players; i++) {
            // Проверяем, были ли введены карты для текущего игрока
            if (game->players[i].hand.card1.rank != NONE_RANK && game->players[i].hand.card2.rank != NONE_RANK) {
                printf("Карты игрока %d: %s %s и %s %s\n", i + 1,
                    get_rank_name(game->players[i].hand.card1.rank),
                    get_suit_name(game->players[i].hand.card1.suit),
                    get_rank_name(game->players[i].hand.card2.rank),
                    get_suit_name(game->players[i].hand.card2.suit));
            }
            else {
                printf("Карты игрока %d: не заданы\n", i + 1);
            }
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
            if (game->board.num_cards < 3) {
                printf("Сначала необходо добавить flop и turn!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 3) {
                printf("Сначала необходо добавить turn!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 5) {
                printf("Сначала необходимо очистить River\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 4) {
                clear_board_turn(game, used_cards);
                printf("Turn очищен!\n");
                press_any_key_to_continue();
            }
           
            break;

        case 8:
            if (game->board.num_cards < 3) {
                printf("Сначала необходимо добавить flop и turn и river!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 3) {
                printf("Сначала необходимо добавить turn и river!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 4) {
                printf("Сначала необходимо добавить river!\n");
                press_any_key_to_continue();
            }
            else if (game->board.num_cards == 5) {
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
void init_player(Player* players, Hand hand) {
	players->hand = hand;
	players->equity = 0.0;  // Начальная вероятность выигрыша
}

//Инициализация игрового поля//
void init_board(Board* board) {
	board->num_cards = 0;  // В начале нет карт на столе 
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

void clear_player_cards(Player* players, int current_players, bool used_cards[15][5], int choice_player, bool mute_mode){

    if (mute_mode == false) {
        if (players[choice_player - 1].hand.card1.rank == NONE_RANK || players[choice_player - 1].hand.card2.rank == NONE_RANK) {
            printf("Рука игрока %d не задана, поэтому она не может быть очищена!\n", choice_player);
            return;
        }
    }



    used_cards[players->hand.card1.rank][players->hand.card1.suit] = false;
    used_cards[players->hand.card2.rank][players->hand.card2.suit] = false;

    players[choice_player - 1].hand.card1.rank = NONE_RANK;
    players[choice_player - 1].hand.card1.suit = NONE_SUIT;

    players[choice_player - 1].hand.card2.rank = NONE_RANK;
    players[choice_player - 1].hand.card2.suit = NONE_SUIT;

}

//mode = false - deffault; mode = true - mute
void clear_all_players_cards(Player* players, int current_players, bool used_cards[15][5], bool mute_mode) {
    
    for (int i = 0; i < current_players; i++) {
        if (players[i].hand.card1.rank != NONE_RANK || players[i].hand.card2.rank != NONE_RANK) {
            // Сбрасываем использование карт в массиве used_cards
            used_cards[players[i].hand.card1.rank][players[i].hand.card1.suit] = false;
            used_cards[players[i].hand.card2.rank][players[i].hand.card2.suit] = false;

            // Очищаем карты игрока
            players[i].hand.card1.rank = NONE_RANK;
            players[i].hand.card1.suit = NONE_SUIT;

            players[i].hand.card2.rank = NONE_RANK;
            players[i].hand.card2.suit = NONE_SUIT;

            if (mute_mode == false) {
                printf("Рука игрока %d успешно очищена!\n", i + 1);
            }
        }
        else {
            if (mute_mode == false) {
                printf("Рука игрока %d не задана, поэтому она не может быть очищена!\n", i + 1);
            }
        }
    }
    printf("Операция завершена!\n");
    press_any_key_to_continue();
}



void deal_cards(Player players[], int current_players, bool used_cards[15][5], int choice_player) {
    int rank_choice_card1, suit_choice_card1;
    int rank_choice_card2, suit_choice_card2;


    if (choice_player < 0 || choice_player > current_players) {
        printf("Игрока под таким номером не существует!\n");
        press_any_key_to_continue();
        clearConsole();
        return;
    }
    else {
        printf("------------------------------------------------\n");
        printf("          Ввод карт для игрока %d\n", choice_player);
        printf("------------------------------------------------\n");
        // Ввод первой карты
        printf("11 - Валет, 12 - Дама, 13 - Король, 14 - Туз\n");
        printf("1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики\n");
        printf("------------------------------------------------\n");
        do {
     
            printf("Введите ранг 1-ой карты или 0 для выхода: ");
            rank_choice_card1 = (int)scanf_secure("int");
            if (rank_choice_card1 == 0) {
                return;
            }
            if (rank_choice_card1 < 2 || rank_choice_card1 > 14) {
                printf("Неверный ранг карты! Попробуйте снова.\n");
                continue;
            }

            printf("Введите масть 1-ой карты или 0 для выхода: ");
            suit_choice_card1 = (int)scanf_secure("int");
            if (suit_choice_card1 == 0) {
                return;
            }
            if (suit_choice_card1 < 1 || suit_choice_card1 > 4) {
                printf("Неверная масть карты! Попробуйте снова.\n");
                continue;
            }

            // Проверка на уникальность карты
            if (used_cards[rank_choice_card1][suit_choice_card1]) {
                printf("Эта карта уже используется! Попробуйте другую карту.\n");
            }
            else {
                // Сохранение карты для игрока
                used_cards[players[choice_player - 1].hand.card1.rank][players[choice_player - 1].hand.card1.suit] = false;
                players[choice_player - 1].hand.card1.rank = (Rank)rank_choice_card1;
                players[choice_player - 1].hand.card1.suit = (Suit)suit_choice_card1;
                used_cards[rank_choice_card1][suit_choice_card1] = true;
                break;
            }
        } while (1);
        printf("\n");
        // Ввод второй карты
    
        do { 
            printf("Введите ранг 2-ой карты или 0 для выхода: ");
            rank_choice_card2 = (int)scanf_secure("int");
            if (rank_choice_card2 == 0) {
                used_cards[rank_choice_card1][suit_choice_card1] = false; // Отменяем первую карту
                players[choice_player - 1].hand.card1.rank = NONE_RANK;
                players[choice_player - 1].hand.card1.suit = NONE_SUIT;
                return;
            }
            if (rank_choice_card2 < 2 || rank_choice_card2 > 14) {
                printf("Неверный ранг карты! Попробуйте снова.\n");
                continue;
            }

         
            printf("Введите масть 2-ой карты или 0 для выхода: ");
            suit_choice_card2 = (int)scanf_secure("int");
            if (suit_choice_card2 == 0) {
                used_cards[rank_choice_card1][suit_choice_card1] = false; // Отменяем первую карту
                players[choice_player - 1].hand.card1.rank = NONE_RANK;
                players[choice_player - 1].hand.card1.suit = NONE_SUIT;
                return;
            }
            if (suit_choice_card2 < 1 || suit_choice_card2 > 4) {
                printf("Неверная масть карты! Попробуйте снова.\n");
                continue;
            }

            // Проверка на уникальность карты и совпадение с первой картой
            if (used_cards[rank_choice_card2][suit_choice_card2]) {
                printf("Эта карта уже используется! Попробуйте другую карту.\n");
            }
            else if (players[choice_player - 1].hand.card1.rank == rank_choice_card2 && players[choice_player - 1].hand.card1.suit == suit_choice_card2) {
                printf("Эта карта совпадает с первой картой! Выберите другую.\n");
            }
            else {
                // Сохранение второй карты для игрока
                used_cards[players[choice_player - 1].hand.card2.rank][players[choice_player - 1].hand.card2.suit] = false;
                players[choice_player - 1].hand.card2.rank = (Rank)rank_choice_card2;
                players[choice_player - 1].hand.card2.suit = (Suit)suit_choice_card2;
                used_cards[rank_choice_card2][suit_choice_card2] = true;
                break;
            }
        } while (1);
    }
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
void deal_random_cards(Player players[], int current_players, bool used_cards[15][5], int choice_player) {
    
    if (choice_player < 0 || choice_player > current_players) {
        printf("Игрока под таким номером не существует!\n");
        press_any_key_to_continue();
        clearConsole();
        return;
    }
    
    // Создаем деку
    Card full_deck[52];
    create_deck(full_deck);
    Card available_deck[52];
    int available_count = 0;

    // Фильтруем доступные карты
    for (int i = 0; i < 52; i++) {
        if (!used_cards[full_deck[i].rank][full_deck[i].suit]) {
            available_deck[available_count++] = full_deck[i];
        }
    }

    // Перемешиваем доступные карты
    shuffle_deck(available_deck, available_count);

    // Дилер раздает карты игрокам
   
        used_cards[players[choice_player - 1].hand.card1.rank][players[choice_player - 1].hand.card1.suit] = false;
        used_cards[players[choice_player - 1].hand.card2.rank][players[choice_player - 1].hand.card2.suit] = false;
        players[choice_player - 1].hand.card1 = available_deck[0];
        players[choice_player - 1].hand.card2 = available_deck[1];
        used_cards[players[choice_player - 1].hand.card1.rank][players[choice_player - 1].hand.card1.suit] = true;
        used_cards[players[choice_player - 1].hand.card2.rank][players[choice_player - 1].hand.card2.suit] = true;

}

// Определяем максимальный размер доски
#define MAX_BOARD_CARDS 5

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
        press_any_key_to_continue();
        return;
    }
    
    while (game->board.num_cards > 0)
    {
        int i = 0;
        used_cards[game->board.cards[i].rank][game->board.cards[i].suit] = false;
        game->board.num_cards--;
        i++;
    }

    // Сбрасываем все карты на борде
    for (int i = 0; i < 5; i++) {
        game->board.cards[i].rank = NONE_RANK;
        game->board.cards[i].suit = NONE_SUIT;
    }

    strcpy(game->phase, "preflop");
   

}

void clear_board_turn(Game* game, bool used_cards[15][5]) {

    if (game->board.cards[3].rank = NONE_RANK) {
        printf("Turn и так пустой\n");
        press_any_key_to_continue();
        return;
    }

    used_cards[game->board.cards[3].rank][game->board.cards[3].suit] = false;
    game->board.num_cards--;

    game->board.cards[3].rank = NONE_RANK;
    game->board.cards[3].suit = NONE_SUIT;
   
    strcpy(game->phase, "flop");
   
}

void clear_board_river(Game* game, bool used_cards[15][5]) {

    if (game->board.cards[4].rank = NONE_RANK) {
        printf("River и так пустой\n");
        press_any_key_to_continue();
        return;
    }

    used_cards[game->board.cards[4].rank][game->board.cards[4].suit] = false;
    game->board.num_cards--;

    game->board.cards[4].rank = NONE_RANK;
    game->board.cards[4].suit = NONE_SUIT;

    strcpy(game->phase, "turn");
   

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

int compare_hands(PokerCombination hand1, PokerCombination hand2) {
    // Сравниваем ранги комбинаций (старшинство комбинаций)
    if (hand1.hand_rank > hand2.hand_rank) return 1;
    if (hand1.hand_rank < hand2.hand_rank) return -1;

    // Если ранги комбинаций равны, сравниваем старшие карты комбинации
    if (hand1.high_card > hand2.high_card) return 1;
    if (hand1.high_card < hand2.high_card) return -1;

    // Если старшие карты комбинаций равны, сравниваем кикеры
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
        // У трипса только один кикер
        for (int i = 0; i < 2; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case ONE_PAIR:
    case TWO_PAIR:
        // Для пары и двух пар используются три кикера
        for (int i = 0; i < 3; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case FLUSH:
        // У флеша все пять карт сравниваются по убыванию
        for (int i = 0; i < 5; i++) {
            if (hand1.kicker[i] > hand2.kicker[i]) return 1;
            if (hand1.kicker[i] < hand2.kicker[i]) return -1;
        }
        break;

    case HIGH_CARD:
        // У старшей карты все пять карт сравниваются
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

    int card_count[15] = { 0 };   // Подсчет карт по рангу (индексы от 2 до Туза)
    int suit_count[5] = { 0 };    // Подсчет карт по мастям (индексы от 0 до 4)
    Card all_cards[7];            // Массив всех карт (рука + борд)

    // Собираем все карты (2 карты руки + карты на борде)
    all_cards[0] = hand.card1;
    all_cards[1] = hand.card2;
    for (int i = 0; i < board.num_cards; i++) {
        all_cards[2 + i] = board.cards[i];
    }

    // Подсчет количества карт по рангу и мастям
    for (int i = 0; i < 2 + board.num_cards; i++) {
        card_count[all_cards[i].rank]++;
        suit_count[all_cards[i].suit]++;
    }

    Rank top_pair = NONE_RANK, second_pair = NONE_RANK;
    Rank highest_rank = NONE_RANK;
    int flush_suit_index = -1;
    int three_of_a_kind = 0, second_three_of_a_kind = 0;
    int four_of_a_kind = 0;

    // Определение пар, троек, каре
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

    // Определение наличия флеша
    for (int suit = 0; suit < 5; suit++) {
        if (suit_count[suit] >= 5) {
            flush_suit_index = suit;
            break;
        }
    }

    // Проверка на фулл-хаус
    if (three_of_a_kind > 0 && (top_pair > 0 || second_three_of_a_kind > 0)) {
        result.hand_rank = FULL_HOUSE;
        result.high_card = static_cast<Rank>(three_of_a_kind); // Старший сет
        result.kicker[0] = static_cast<Rank>((top_pair > 0) ? top_pair : second_three_of_a_kind); // Пара

        return result;
    }

    // Проверка на стрит-флеш
    if (flush_suit_index != -1) {
        Rank flush_cards[7];
        int flush_card_count = 0;

        // Собираем карты одной масти
        for (int i = 0; i < 2 + board.num_cards; i++) {
            if (all_cards[i].suit == flush_suit_index) {
                flush_cards[flush_card_count++] = all_cards[i].rank;
            }
        }

        qsort(flush_cards, flush_card_count, sizeof(Rank), [](const void* a, const void* b) {
            return (*(Rank*)b - *(Rank*)a);
            });

        // Проверка на стрит-флеш
        for (int i = 0; i < flush_card_count - 4; i++) {
            if (flush_cards[i] - flush_cards[i + 1] == 1 &&
                flush_cards[i + 1] - flush_cards[i + 2] == 1 &&
                flush_cards[i + 2] - flush_cards[i + 3] == 1 &&
                flush_cards[i + 3] - flush_cards[i + 4] == 1) {
                result.hand_rank = STRAIGHT_FLUSH;
                result.high_card = flush_cards[i]; // Старшая карта стрит-флеша
                return result;
            }
        }

        // Определение обычного флеша
        result.hand_rank = FLUSH;
        result.high_card = flush_cards[0];  // Старшая карта флеша
        for (int i = 1; i < 5; i++) {
            result.kicker[i - 1] = flush_cards[i];
        }
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

    // Проверка на стрит A-2-3-4-5
    if (card_count[ACE] > 0 && card_count[TWO] > 0 && card_count[THREE] > 0 &&
        card_count[FOUR] > 0 && card_count[FIVE] > 0) {
        result.hand_rank = STRAIGHT;
        result.high_card = FIVE;  // Старшая карта стрита A-2-3-4-5
        return result;
    }

    // Проверка на каре
    if (four_of_a_kind > 0) {
        result.hand_rank = FOUR_OF_A_KIND;
        result.high_card = static_cast<Rank>(four_of_a_kind);
        result.kicker[0] = highest_rank;
        return result;
    }

    // Проверка на тройку
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

    // Проверка на две пары
    if (top_pair > 0 && second_pair > 0) {
        result.hand_rank = TWO_PAIR;
        result.high_card = top_pair;  // Старшая пара
        result.kicker[0] = second_pair;  // Вторая пара
        result.kicker[1] = highest_rank;  // Кикер
        return result;
    }

    // Проверка на пару
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

    // Если нет комбинаций, то просто старшая карта
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
    // Инициализируем победы, поражения и ничьи для каждого игрока
    for (int i = 0; i < game->current_players; i++) {
        game->players[i].wins = 0;
        game->players[i].ties = 0;
        game->players[i].losses = 0;
    }

    // Инициализация массива использованных карт (карты игроков и борда)
    initialize_used_cards(game, used_cards);

    for (int i = 0; i < choice_numSimulations; i++) {
        Card deck[52];
        int deck_index = 0;

        // Временно копируем used_cards для каждой симуляции
        bool sim_used_cards[15][5];
        memcpy(sim_used_cards, used_cards, sizeof(sim_used_cards));

        // Заполняем колоду, исключая карты, которые уже были использованы
        for (int rank = 2; rank <= 14; rank++) {
            for (int suit = 1; suit <= 4; suit++) {
                if (!sim_used_cards[rank][suit]) {
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

        // Копируем уже известные карты на борде
        for (int j = 0; j < game->board.num_cards; j++) {
            simulation_board[j] = game->board.cards[j];
        }

        // Дополняем борд случайными картами, не использованными ранее
        for (int j = game->board.num_cards; j < 5; j++) {
            bool card_found = false;
            while (!card_found) {
                simulation_board[j] = deck[--deck_index];  // Берём карту из перемешанной колоды
                // Проверяем, что карта не использована
                if (!sim_used_cards[simulation_board[j].rank][simulation_board[j].suit]) {
                    sim_used_cards[simulation_board[j].rank][simulation_board[j].suit] = true;  // Отмечаем как использованную
                    card_found = true;  // Карта найдена
                }
            }
        }

        // Создаем временный объект типа Board для симулированных карт
        Board simulated_board;
        simulated_board.num_cards = 5;  // Всегда 5 карт
        for (int j = 0; j < 5; j++) {
            simulated_board.cards[j] = simulation_board[j];
        }

        // Массив для хранения комбинаций всех игроков
        PokerCombination* player_hands = (PokerCombination*)malloc(game->current_players * sizeof(PokerCombination));

        // Оценка комбинаций для каждого игрока
        for (int j = 0; j < game->current_players; j++) {
            player_hands[j] = determine_hand(game->players[j].hand, simulated_board);  // Используем симулированный борд
        }

        // Находим лучшую комбинацию и проверяем на ничью
        int best_player = 0;
        bool tie = false;
        int tie_count = 1;

        for (int j = 1; j < game->current_players; j++) {
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

        // Обновляем статистику для каждого игрока
        for (int j = 0; j < game->current_players; j++) {
            if (tie && compare_hands(player_hands[j], player_hands[best_player]) == 0) {
                game->players[j].ties++;
            }
            else if (j == best_player) {
                game->players[j].wins++;
            }
            else {
                game->players[j].losses++;
            }
        }

        // В тестовом режиме выводим информацию о симуляции
        calculate_probabilities_debugging(game, settings, simulated_board, player_hands, i, tie, best_player);

        // Освобождаем память после использования
        free(player_hands);
    }

    // Выводим вероятность побед, поражений и ничьих для каждого игрока
    double total_simulations = (double)choice_numSimulations;

    for (int i = 0; i < game->current_players; i++) {
        printf("------------------\n   Игрок %d\n------------------\n", i + 1);
        printf("Победы: %.2f%%\n", (game->players[i].wins / total_simulations) * 100);
        printf("Поражения: %.2f%%\n", (game->players[i].losses / total_simulations) * 100);
        printf("Ничьи: %.2f%%\n", (game->players[i].ties / total_simulations) * 100);
    }
}




void initialize_used_cards(Game* game, bool used_cards[15][5]) {
    // Инициализируем массив, помечаем все карты как неиспользованные
    for (int rank = 2; rank <= 14; rank++) {
        for (int suit = 1; suit <= 4; suit++) {
            used_cards[rank][suit] = false;
        }
    }

    // Помечаем карты игроков как использованные
    for (int i = 0; i < game->current_players; i++) {
        Card card1 = game->players[i].hand.card1;
        Card card2 = game->players[i].hand.card2;
        used_cards[card1.rank][card1.suit] = true;
        used_cards[card2.rank][card2.suit] = true;
    }

    // Помечаем уже открытые карты на борде как использованные
    for (int i = 0; i < game->board.num_cards; i++) {
        Card board_card = game->board.cards[i];
        used_cards[board_card.rank][board_card.suit] = true;
    }
}



void calculate_probabilities_debugging(Game* game, Settings_debugging_mode* settings, Board simulated_board, PokerCombination* player_hands, int current_simulation, bool tie, int best_player) {
    
    
        if (settings->wins_mode == true) {
            if (best_player + 1 == settings->current_winner && settings->wins_mode == true) {
                printf("Симуляция %d:\n", current_simulation + 1);
                printf("Карты на столе: ");
                for (int j = 0; j < 5; j++) {
                    printf("%d%c ", simulated_board.cards[j].rank, simulated_board.cards[j].suit == HEARTS ? 'Ч' :
                        simulated_board.cards[j].suit == DIAMONDS ? 'Б' :
                        simulated_board.cards[j].suit == CLUBS ? 'Т' :
                        simulated_board.cards[j].suit == SPADES ? 'П' : '?');
                }
                printf("\n");

                for (int j = 0; j < game->current_players; j++) {
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
                    printf("%d%c ", simulated_board.cards[j].rank, simulated_board.cards[j].suit == HEARTS ? 'Ч' :
                        simulated_board.cards[j].suit == DIAMONDS ? 'Б' :
                        simulated_board.cards[j].suit == CLUBS ? 'Т' :
                        simulated_board.cards[j].suit == SPADES ? 'П' : '?');
                }
                printf("\n");

                if (tie) {
                    printf("Ничья между игроками.\n");
                }

                printf("\n");
            }
        }
     
    
    

}

void compare_all_hands(Game* game, PokerCombination hands[]) {
    for (int i = 0; i < game->current_players; i++) {
        for (int j = i + 1; j < game->current_players; j++) {
            int result = compare_hands(hands[i], hands[j]);

            if (result == 1) {
                // Игрок i побеждает игрока j
                game->players[i].wins++;
                game->players[j].losses++;
            }
            else if (result == -1) {
                // Игрок j побеждает игрока i
                game->players[i].losses++;
                game->players[j].wins++;
            }
            else {
                // Ничья между игроками i и j
                game->players[i].ties++;
                game->players[j].ties++;
            }
        }
    }
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