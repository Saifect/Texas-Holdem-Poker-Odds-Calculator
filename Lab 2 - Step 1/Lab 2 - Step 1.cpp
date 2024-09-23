#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>



//===============STRUCTS===============//

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
	Card card1; //Первая карта
	Card card2; //Вторая карта 
}Hand;

//Игрок//
typedef struct {
	Hand hand;     //Рука игрока
	double equity; //Вероятность выйгрыша 
}Player;

//Игровое поле//
typedef struct {
	Card cards[5]; //Карты на доске
	int num_cards; //Количество карт на доске
}Board;

//Структура для представления игры//
typedef struct {
	Player player1;   // Первый игрок
	Player player2;   // Второй игрок
	Board board;      // Игровое поле
	char phase[10];   // Фаза игры (например, "префлоп", "флоп", "терн", "ривер")
} Game;

// Покерные комбинации
typedef enum {
    HIGH_CARD,        // Старшая карта
    ONE_PAIR,         // Одна пара
    TWO_PAIR,         // Две пары
    THREE_OF_A_KIND,  // Сет (три одинаковые карты)
    STRAIGHT,         // Стрит
    FLUSH,            // Флеш
    FULL_HOUSE,       // Фулл-хаус
    FOUR_OF_A_KIND,   // Каре
    STRAIGHT_FLUSH,   // Стрит-флеш
    ROYAL_FLUSH       // Роял-флеш
} PokerHandRank;

// Структура для покерной комбинации
typedef struct {
    PokerHandRank hand_rank; // Ранг комбинации
    Rank high_card;          // Старшая карта в комбинации (важно для таких комбинаций как стрит или флеш)
    Rank kicker[4];           // Кикеры (максимум 4 кикера для ситуаций, когда у игроков комбинации с одинаковыми картами)
} PokerHand;


//=========PROTOTYPE_FUNCTIONS=========//
void print_mainMenu(int* choice);
void get_mainMenu_user_choice(int* choice);
void handle_mainMenu_choice(int choice);
//
void init_card(Card* card, Suit suit, Rank rank);
void init_randomCard(Card* card);
void init_hand(Hand* hand, Card card1, Card card2);
void init_player(Player* player, Hand hand);
void init_board(Board* board);
void init_game(Game* game, Player player1, Player player2, Board board, const char* phase);
//
void handle_calculatorMenu_choice(int choice, Game* game, bool* exit);
void print_calculatorMenu();
//
const char* get_rank_name(Rank rank);
const char* get_suit_name(Suit suit);
void input_player_cards(Player* player);

//Prototypes for Useful_function//

double scanf_secure(const char* type);          // Функция для безопасного ввода различных типов данных
void clearConsole();                            // Функция для очистки консоли
void buffer_clear();                            // Функция для очистки буфера ввода
void line_remove(char* str);                    // Функция для удаления символа новой строки из строки
void string_get_secure(char* buffer, int size); // Функция для безопасного получения строки с защитой от переполнения буфера
void press_any_key_to_continue();
void press_any_key_to_continue_clearConsole();

//Прототипы функций связанных с алгоритмом вычисления вероятности//

// Прототип функции для перемешивания массива карт
void shuffle_deck(Card* deck, int size);

// Прототип функции для создания полной колоды карт
void create_deck(Card* deck);

// Прототип функции для раздачи случайных карт двум игрокам
void deal_random_cards(Player* player1, Player* player2, short current_player);

PokerHand determine_hand(Hand hand, Board board);

int compare_hands(Hand hand1, Hand hand2, Game* game);

void print_preflop_hand(PokerHand hand);

void display_board_cards(const Board* board);

void fill_board_with_cards(Game* game, const char* phase);
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
        press_any_key_to_continue();
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
	printf("0. Выход\n");
    printf("================================================\n");
	printf("Ваш выбор: ");
    get_mainMenu_user_choice(choice);
    handle_mainMenu_choice(*choice);
}

//Получение выбора пользователя//
void get_mainMenu_user_choice(int *choice) {
    *choice = (int)scanf_secure("int"); 
}

//Обработка выбора пользователя в основном меню//
void handle_mainMenu_choice(int choice) {
    switch (choice) {
    case 0:
        printf("Выход из программы.\n");
        exit(0); // Используем exit для выхода из программы
        
    case 1:
        clearConsole();
        print_calculatorMenu();
        break;
    case 2:
        printf("Не реализовано\n");
        // Вызов функции отображения карты
        break;
    case 3:
        printf("Не реализовано\n");
        // Вызов функции отображения карты
        break;
    case 4:
        printf("Status: In development\n");
        printf("Version program: 0.6");
        printf("Author: Saifect@mail.ru\n");
        // Вызов функции отображения карты
        break;

    default:
        printf("Неверный выбор! Попробуйте снова.\n");
        break;
    }
}


//Меню калькулятора вероятностей//
void print_calculatorMenu() {
    srand(time(NULL));

    /// Инициализация ///
    Card card1 = { NONE_SUIT, NONE_RANK }; // Пример корректной инициализации карты: ранг "Двойка" и масть "Черви"
    Card card2 = { NONE_SUIT, NONE_RANK }; // Пример корректной инициализации карты: ранг "Тройка" и масть "Пики"
    Hand hand1 = { card1, card2 }; // Инициализация рук
    Hand hand2 = { card1, card2 }; // Для второго игрока тоже можно задать
    Player player1 = { hand1 }; // Инициализация игроков
    Player player2 = { hand2 };
    Board board = { NONE_SUIT }; // Инициализация доски
    Game game = { player1, player2, board }; // Инициализация структуры Game
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

        // Проверь, были ли карты введены для 1-го игрока
        if (game.player1.hand.card1.rank != NONE_RANK && game.player1.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 1: %s %s и %s %s\n", get_rank_name(game.player1.hand.card1.rank),
                get_suit_name(game.player1.hand.card1.suit),
                get_rank_name(game.player1.hand.card2.rank),
                get_suit_name(game.player1.hand.card2.suit));
        }
        else {
            printf("Карты игрока 1: не заданы\n");
        }

        // Проверь, были ли карты введены для 2-го игрока
        if (game.player2.hand.card1.rank != NONE_RANK && game.player2.hand.card2.rank != NONE_RANK) {
            printf("Карты игрока 2: %s %s и %s %s\n", get_rank_name(game.player2.hand.card1.rank),
                get_suit_name(game.player2.hand.card1.suit),
                get_rank_name(game.player2.hand.card2.rank),
                get_suit_name(game.player2.hand.card2.suit));
        }
        else {
            printf("Карты игрока 2: не заданы\n");
        }
        printf("-----------------------------------------------\n");
        if (strcmp(game.phase, "preflop") == 0) {
            printf("Карты на столе: отсутствуют (префлоп)\n");
        }


        else {
            display_board_cards(&game.board); // Передача по значению

        }
        printf("Текущяя стадия игры (улица): %s\n", game.phase);
        printf("================================================\n");
        printf("           Функционал калькулятора              \n");
        printf("================================================\n");
        printf("1. Добавить карты 1-му игроку\n");
        printf("2. Добавить карты 2-му игроку\n");
        printf("3. Добавить случайные карты 1-му игроку\n");
        printf("4. Добавить случайные карты 2-му игроку\n");
        printf("5. Раздать улицу на стол\n");
        printf("6. Рассчитать шансы выигрыша\n");
        printf("7. Проанализировать комбинацию игрока 1\n");
        printf("8. Проанализировать комбинацию игрока 2\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        choice = (int)scanf_secure("int");
        handle_calculatorMenu_choice(choice, &game, &exit);
    }
}



//Обработка выбора пользователя в меню калькулятора//
void handle_calculatorMenu_choice(int choice, Game* game, bool* exit) {
    PokerHand result_player1;
    PokerHand result_player2;
    switch (choice) {
    case 0:
        printf("Возврат в главное меню...\n");
        *exit = true;
        clearConsole();
        break;

    case 1:
        printf("------------------------------------------------\n");
        printf("        Добавление карт 1-му игроку             \n");
        printf("------------------------------------------------\n");
        input_player_cards(&game->player1);
        clearConsole();
        break;

    case 2:
        printf("Добавление карт 2-му игроку\n");
        input_player_cards(&game->player2);
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

        if (strcmp(game->phase, "preflop") == 0) {
            strcpy(game->phase, "flop");
            fill_board_with_cards(game, game->phase);
        }
        else if (strcmp(game->phase, "flop") == 0) {
            strcpy(game->phase, "turn");
            fill_board_with_cards(game, game->phase);
        }
        else if (strcmp(game->phase, "turn") == 0) {
            strcpy(game->phase, "river");
            fill_board_with_cards(game, game->phase);
        }
        clearConsole();
        break;

    case 6:
        printf("Рассчитать шансы выигрыша...\n");
        // Вызов функции расчета эквити (вероятности выигрыша)
        clearConsole();
        break;
    case 7:
        result_player1 = determine_hand(game->player1.hand, game->board);
        print_preflop_hand(result_player1);
        press_any_key_to_continue();
        clearConsole();
        break;
    case 8:
        result_player2 = determine_hand(game->player2.hand, game->board);
        print_preflop_hand(result_player2);
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


//Инициализация карты//
void init_card(Card* card, Suit suit, Rank rank){
	card->suit = suit;
	card->rank = rank;
}

//Случайная инициализация карты//
void init_randomCard(Card* card) {
	// Генерация случайной масти (от 0 до 3)
	card->suit = (Suit)(rand() % 4);

	// Генерация случайного ранга (от 2 до 14)
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
	snprintf(game->phase, sizeof(game->phase), "%s", phase);  // Установим фазу игры
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


void print_preflop_hand(PokerHand hand) {
    if (hand.hand_rank == ONE_PAIR) {
        printf("Комбинация: Пара %d\n", hand.high_card);
    }
    else if (hand.hand_rank == HIGH_CARD) {
        printf("Комбинация: Старшая карта %d\n", hand.high_card);
        printf("Кикер: %d\n", hand.kicker[0]);
    }
}

//Ввод карт игрока//
void input_player_cards(Player* player) {
    int rank_choice, suit_choice;
    bool identical_cards;
    // Ввод первой карты
    do {
        printf("Введите ранг 1-ой карты (2-14) или 0 для выхода: ");
        rank_choice = (int)scanf_secure("int");
        if (rank_choice == 0) {
            return;
        }
        if (rank_choice < 2 || rank_choice > 14) {
            printf("Неверный ранг карты! Попробуйте снова.\n");
        }
        
    } while (rank_choice < 2 || rank_choice > 14);
    player->hand.card1.rank = (Rank)rank_choice;

    do {
        printf("Введите масть 1-ой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ");
        suit_choice = (int)scanf_secure("int");
        if (rank_choice == 0) {
            return;
        }
        if (suit_choice < 1 || suit_choice > 4){
            printf("Вы ввели число вне диапазона, попробуйте снова!\n");
        }
    } while (suit_choice < 1 || suit_choice > 4);
    player->hand.card1.suit = (Suit)suit_choice;

    // Ввод второй карты
    do {
        printf("Введите ранг 2-ой карты (2-14) или 0 для выхода: ");
        rank_choice = (int)scanf_secure("int");
        if (rank_choice == 0) {
            return;
        }
        if (rank_choice < 2 || rank_choice > 14) {
            printf("Неверный ранг карты! Попробуйте снова.\n");
        }

    } while (rank_choice < 2 || rank_choice > 14);
    player->hand.card2.rank = (Rank)rank_choice;

    do {
        printf("Введите масть 2-ой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики) или 0 для выхода: ");
        suit_choice = (int)scanf_secure("int");
        if (rank_choice == 0) {
            return;
        }
        if (suit_choice < 1 || suit_choice > 4) {
            printf("Вы ввели число вне диапазона, попробуйте снова!\n");
        }
        if (player->hand.card1.suit == suit_choice) {
            identical_cards = true;
        }

    } while (suit_choice < 1 || suit_choice > 4);
    player->hand.card2.suit = (Suit)suit_choice;
}
//==========Useful_functions==========//
// Функция для безопасного ввода различных типов данных
double scanf_secure(const char* type) {
    while (1) {
        if (strcmp(type, "int") == 0) {
            int num;
            if (scanf("%d", &num) == 1) {
                while (getchar() != '\n'); // Очищаем буфер ввода
                return num;
            }
            else {
                printf("Ошибка ввода. Пожалуйста, введите целое число.\n");
                press_any_key_to_continue();
                buffer_clear();
                return 0;
            }
        }
        else if (strcmp(type, "float") == 0) {
            float num;
            if (scanf("%f", &num) == 1) {
                while (getchar() != '\n'); // Очищаем буфер ввода
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
                while (getchar() != '\n'); // Очищаем буфер ввода
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
                if (strcmp(input, "true") == 0 || strcmp(input, "1") == 0) {
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

// Очистка консоли
void clearConsole() {
    system("cls");
}

// Очистка буфера
void buffer_clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Удаление новой строки
void line_remove(char* str) {
    // Найти позицию символа новой строки и заменить его на нулевой символ
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

void press_any_key_to_continue_clearConsole() {
    printf("Нажмите любую клавишу для продолжения...\n");
    _getch(); // Ожидание нажатия клавиши
    system("cls"); // Очистка консоли (Windows)
}
//////////////////////////////////////////////
//ФУНКЦИИ ДЛЯ АЛГОРИТМА РАСЧЕТА ВЕРОЯТНОСТЕЙ//
//////////////////////////////////////////////

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
    // Создаем колоду
    Card deck[52];
    create_deck(deck);

    // Перемешиваем колоду
    shuffle_deck(deck, 52);

    // Раздаем карты игрокам
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

// Функция для сравнения рук двух игроков на префлопе, определения победителя
int compare_hands(Hand hand1, Hand hand2, Game *game) {
    // Определение комбинации первого игрока
    PokerHand result1 = determine_hand(hand1, game->board);

    // Определение комбинации второго игрока
    PokerHand result2 = determine_hand(hand2, game->board);

    // Сравнение комбинаций (например, пара против старшей карты)
    if (result1.hand_rank > result2.hand_rank) {
        return 1;  // Игрок 1 имеет более сильную комбинацию
    }
    else if (result2.hand_rank > result1.hand_rank) {
        return 2;  // Игрок 2 имеет более сильную комбинацию
    }
    else {
        // Если комбинации одинаковы, сравниваем старшие карты
        if (result1.high_card > result2.high_card) {
            return 1;  // Игрок 1 выигрывает по старшей карте
        }
        else if (result2.high_card > result1.high_card) {
            return 2;  // Игрок 2 выигрывает по старшей карте
        }
        else {
            // Если старшие карты одинаковы, сравниваем кикеры
            for (int i = 0; i < 4; i++) {
                if (result1.kicker[i] > result2.kicker[i]) {
                    return 1;  // Игрок 1 выигрывает по кикеру
                }
                else if (result2.kicker[i] > result1.kicker[i]) {
                    return 2;  // Игрок 2 выигрывает по кикеру
                }
            }
            return 0;  // Ничья, если все карты одинаковы
        }
    }
}


PokerHand determine_hand(Hand hand, Board board) {
    PokerHand result;
    result.hand_rank = HIGH_CARD;  // По умолчанию - старшая карта
    result.high_card = NONE_RANK;

    int card_count[15] = { 0 };  // Для подсчета карт по рангу (индексы 2-14, где 14 - это туз)
    int suit_count[4] = { 0 };   // Для подсчета карт по мастям (индексы для мастей: 0 - HEARTS, 1 - DIAMONDS и т.д.)

    Card all_cards[7];  // Все карты (максимум 7 карт: 2 на руках + 5 на столе)
    all_cards[0] = hand.card1;
    all_cards[1] = hand.card2;
    for (int i = 0; i < board.num_cards; i++) {
        all_cards[2 + i] = board.cards[i];
    }

    // Подсчет количества карт каждого ранга и масти
    for (int i = 0; i < 2 + board.num_cards; i++) {
        card_count[all_cards[i].rank]++;
        suit_count[all_cards[i].suit]++;
    }

    // Переменные для анализа комбинаций
    int pairs = 0, three_of_a_kind = 0, four_of_a_kind = 0;
    int highest_pair = 0, second_highest_pair = 0;
    int highest_rank = 0, kicker[2] = { 0 };

    // Определение пар, троек и каре
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] == 4) {
            four_of_a_kind = rank;
        }
        else if (card_count[rank] == 3) {
            three_of_a_kind = rank;
        }
        else if (card_count[rank] == 2) {
            if (highest_pair == 0) {
                highest_pair = rank;
            }
            else {
                second_highest_pair = highest_pair;
                highest_pair = rank;
            }
        }
        else if (card_count[rank] == 1 && rank > highest_rank) {
            highest_rank = rank;
        }
    }

    // Проверка на флэш
    int flush_suit = -1;
    for (int i = 0; i < 4; i++) {
        if (suit_count[i] >= 5) {
            flush_suit = i;
            break;
        }
    }

    // Если есть флэш, выбираем старшие карты той же масти
    if (flush_suit != -1) {
        result.hand_rank = FLUSH;
        int flush_cards[5];
        int count = 0;
        for (int i = 0; i < 2 + board.num_cards; i++) {
            if (all_cards[i].suit == flush_suit) {
                flush_cards[count++] = all_cards[i].rank;
                if (count == 5) break;
            }
        }
        result.high_card = (Rank)flush_cards[0];  // Явное приведение типа

        // Проверка на стрит-флэш
        for (int i = 0; i < count - 1; i++) {
            if (flush_cards[i] - 1 != flush_cards[i + 1]) {
                break;
            }
            if (i == count - 2) {
                result.hand_rank = STRAIGHT_FLUSH;
                result.high_card = (Rank)flush_cards[0];  // Явное приведение типа
                return result;
            }
        }
    }

    // Проверка на стрит
    int consecutive = 0;
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] > 0) {
            consecutive++;
            if (consecutive == 5) {
                result.hand_rank = STRAIGHT;
                result.high_card = (Rank)rank;  // Явное приведение типа
                return result;  // Возвращаем результат, если найден стрит
            }
        }
        else {
            consecutive = 0;
        }
    }

    // Проверка на каре (четыре одинаковые карты)
    if (four_of_a_kind > 0) {
        result.hand_rank = FOUR_OF_A_KIND;
        result.high_card = (Rank)four_of_a_kind;  // Явное приведение типа
        return result;
    }

    // Проверка на фулл-хаус (тройка и пара)
    if (three_of_a_kind > 0 && highest_pair > 0) {
        result.hand_rank = FULL_HOUSE;
        result.high_card = (Rank)three_of_a_kind;  // Явное приведение типа
        result.kicker[0] = (Rank)highest_pair;  // Явное приведение типа
        return result;
    }

    // Проверка на тройку
    if (three_of_a_kind > 0) {
        result.hand_rank = THREE_OF_A_KIND;
        result.high_card = (Rank)three_of_a_kind;  // Явное приведение типа
        return result;
    }

    // Проверка на две пары
    if (highest_pair > 0 && second_highest_pair > 0) {
        result.hand_rank = TWO_PAIR;
        result.high_card = (Rank)highest_pair;  // Явное приведение типа
        result.kicker[0] = (Rank)second_highest_pair;  // Явное приведение типа
        return result;
    }

    // Проверка на одну пару
    if (highest_pair > 0) {
        result.hand_rank = ONE_PAIR;
        result.high_card = (Rank)highest_pair;  // Явное приведение типа
        result.kicker[0] = (Rank)highest_rank;  // Явное приведение типа
        return result;
    }

    // Если ничего не найдено, просто старшая карта
    result.hand_rank = HIGH_CARD;
    result.high_card = (Rank)((hand.card1.rank > hand.card2.rank) ? hand.card1.rank : hand.card2.rank);  // Явное приведение типа
    kicker[0] = (hand.card1.rank > hand.card2.rank) ? hand.card2.rank : hand.card1.rank;
    result.kicker[0] = (Rank)kicker[0];  // Явное приведение типа

    return result;
}



// Функция для заполнения доски картами в зависимости от стадии игры
void fill_board_with_cards(Game *game, const char* phase) {
    Card deck[52];
    create_deck(deck); // Создаем полную колоду
    shuffle_deck(deck, 52); // Перемешиваем колоду

    // Помечаем карты, которые уже есть у игроков
    bool used[52] = { false };

    // Помечаем карты первого игрока
    used[game->player1.hand.card1.rank * 4 + game->player1.hand.card1.suit] = true;
    used[game->player1.hand.card2.rank * 4 + game->player1.hand.card2.suit] = true;

    // Помечаем карты второго игрока как использованные
    used[game->player2.hand.card1.rank * 4 + game->player2.hand.card1.suit] = true;
    used[game->player2.hand.card2.rank * 4 + game->player2.hand.card2.suit] = true;

    // Определяем сколько карт должно быть на доске в зависимости от стадии игры
    int cards_needed = 0;
    if (strcmp(phase, "flop") == 0) {
        cards_needed = 3;  // На флопе выкладываются 3 карты
    }
    else if (strcmp(phase, "turn") == 0) {
        cards_needed = 4;  // На терне добавляется ещё одна карта (итого 4 карты)
    }
    else if (strcmp(phase, "river") == 0) {
        cards_needed = 5;  // На ривере добавляется последняя карта (итого 5 карт)
    }

    // Заполняем доску недостающими картами
    while (game->board.num_cards < cards_needed) {
        for (int j = 0; j < 52; j++) {
            if (!used[j]) {
                game->board.cards[game->board.num_cards++] = deck[j];
                used[j] = true; // Помечаем карту как использованную
                break;
            }
        }
    }
}

// Проверка, была ли карта уже использована
bool is_card_used(Card* board_cards, int num_cards, Card new_card) {
    for (int i = 0; i < num_cards; i++) {
        if (board_cards[i].rank == new_card.rank && board_cards[i].suit == new_card.suit) {
            return true;  // Если карта уже на доске, вернём true
        }
    }
    return false;  // Карта не использовалась
}



