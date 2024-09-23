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
	Card card1; //Первая классная карта
	Card card2; //Вторая великолепная карта 
}Hand;

//Игрок//
typedef struct {
	Hand hand;     //Рука игрока
	double equity; //Вероятность забрать лавэ у соперника НЕ РЕАЛИЗОВАНО ПОКА но скоро будет 
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
void print_editPlayerMenu(Game* game, bool used_cards[15][5]);
//
const char* get_rank_name(Rank rank);
const char* get_suit_name(Suit suit);
void input_player_cards(Player* player, bool used_cards[15][5]);

//Prototypes for Useful_function//

double scanf_secure(const char* type);          // Функция для безопасного ввода различных типов данных
void clearConsole();                            // Функция для очистки консоли
void buffer_clear();                            // Функция для очистки буфера ввода
void line_remove(char* str);                    // Функция для удаления символа новой строки из строки
void string_get_secure(char* buffer, int size); // Функция для безопасного получения строки с защитой от переполнения буфера
//Какая-то функция 
void press_any_key_to_continue();

//Еще функции
void print_editBoardMenu(Game* game, bool used_cards[15][5]);

void input_board_cards(Game* game, bool used_cards[15][5], int start_index, int num_cards);

void shuffle_deck(Card* deck, int size);

void create_deck(Card* deck);

void deal_random_cards(Player* player1, Player* player2, short current_player);

//И еще больше функций
PokerHand determine_hand(Hand hand, Board board);

int compare_hands(Hand hand1, Hand hand2, Game* game);

void print_preflop_hand(PokerHand hand);

void display_board_cards(const Board* board);

void fill_board_with_random_cards(Game* game, const char* phase);

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
        printf("Status: In development\n");
        printf("Version program: 0.7\n");
        printf("Author: Saifect@mail.ru\n");

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
        printf("3. Рассчитать шансы выигрыша\n");
        printf("4. Проанализировать комбинациии игроков\n");
        printf("-----------------------------------------------\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");


        choice = (int)scanf_secure("int");
        handle_calculatorMenu_choice(choice, &game, &exit);
    }
}



void handle_calculatorMenu_choice(int choice, Game* game, bool* exit) {
    PokerHand result_player1;
    PokerHand result_player2;

    //массив для отслеживания занятых карт
    bool used_cards[15][5] = { false };

    //Помечаем карты которые уже были выданы 
    used_cards[game->player1.hand.card1.rank][game->player1.hand.card1.suit] = true;
    used_cards[game->player1.hand.card2.rank][game->player1.hand.card2.suit] = true;
    used_cards[game->player2.hand.card1.rank][game->player2.hand.card1.suit] = true;
    used_cards[game->player2.hand.card2.rank][game->player2.hand.card2.suit] = true;

    //Помечаем карты на доске как занятые
    for (int i = 0; i < game->board.num_cards; i++) {
        used_cards[game->board.cards[i].rank][game->board.cards[i].suit] = true;
    }

    switch (choice) {

    case -1:
        //ОПЯТЬ НЕ КОСТЫЛЬ А ФИЧА РАБОТАЕТ ЖЕ
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
        printf("Не реализовано\n");
        press_any_key_to_continue();
        clearConsole();
        break;

    case 4:
        if (game->player1.hand.card1.rank != NONE_RANK && game->player1.hand.card2.rank != NONE_RANK) {
            result_player1 = determine_hand(game->player1.hand, game->board);
            print_preflop_hand(result_player1);
           
        }
        else {
            printf("Карты 1-го игрока не заданы, поэтому у него не может быть комбинации!\n");
        }

        if (game->player2.hand.card1.rank != NONE_RANK && game->player2.hand.card2.rank != NONE_RANK) {
            result_player2 = determine_hand(game->player2.hand, game->board);
            print_preflop_hand(result_player2);
          
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


void print_editPlayerMenu(Game* game, bool used_cards[15][5]) {
    int choice;
    bool back = false;

    while (!back) {
        printf("================================================\n");
        printf("            Редактор карт игроков               \n");
        printf("================================================\n");
        printf("1. Добавить/Изменить карты 1-му игроку\n");
        printf("2. Добавить/Изменить карты 2-му игроку\n");
        printf("3. Добавить случайные карты 1-му игроку\n");
        printf("4. Добавить случайные карты 2-му игроку\n");
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
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            press_any_key_to_continue();
            clearConsole();
            break;
        }
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


void print_preflop_hand(PokerHand hand) {
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
        printf("Комбинация: Сет (тройка) %d\n", hand.high_card);
        break;
    case TWO_PAIR:
        printf("Комбинация: Две пары\n");
        printf("Старшая пара: %d\n", hand.high_card);
        printf("Младшая пара: %d\n", hand.kicker[0]);
        break;
    case ONE_PAIR:
        printf("Комбинация: Пара %d\n", hand.high_card);
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

// Очистка консолииииииии
void clearConsole() {
    system("cls");
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

// Функция для сравнения рук двух игроков на префлопе, определения победителя
int compare_hands(Hand hand1, Hand hand2, Game *game) {
    // Определение комбинации первого игрока
    PokerHand result1 = determine_hand(hand1, game->board);

    // Определение комбинации второго игрока
    PokerHand result2 = determine_hand(hand2, game->board);

    // Сравнение комбинаций 
    if (result1.hand_rank > result2.hand_rank) {
        return 1;  // Игрок 1 имеет более сильную комбинацию
    }
    else if (result2.hand_rank > result1.hand_rank) {
        return 2;  // Игрок 2 имеет более сильную комбинацию
    }
    else {
        // Если комбинации одинаковы, сравниваем старшие карты
        if (result1.high_card > result2.high_card) {
            return 1;  
        }
        else if (result2.high_card > result1.high_card) {
            return 2; 
        }
        else {
           
            for (int i = 0; i < 4; i++) {
                if (result1.kicker[i] > result2.kicker[i]) {
                    return 1;  // Игрок 1 выигрывает по кикеру
                }
                else if (result2.kicker[i] > result1.kicker[i]) {
                    return 2;  // Игрок 2 выигрывает по кикеру
                }
            }
            return 0;  // Ничья если все карты одинаковы
        }
    }
}

//Оно работает и ладно... Если надо смотри чертижи
PokerHand determine_hand(Hand hand, Board board) {
    PokerHand result;
    result.hand_rank = HIGH_CARD;  
    result.high_card = NONE_RANK;

    int card_count[15] = { 0 };  
    int suit_count[5] = { 0 };   

    Card all_cards[7];  // всее карты (максимум 7 карт 2 на руках + 5 на столе)
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

    // Переменные для анализа комбинашион
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA я запутался
    int pairs = 0, three_of_a_kind = 0, four_of_a_kind = 0;
    int highest_pair = 0, second_highest_pair = 0;
    int highest_rank = 0, kicker[2] = { 0 };
    int flush_suit = -1; 

    // Определение пар троек и каре
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

    // Проверка на флээээээш
    for (int i = 0; i < 4; i++) {
        if (suit_count[i] >= 5) {
            flush_suit = i;
            break;
        }
    }

    //Оно вроде работает правильно (но это не точно)
    // Если есть флээээш выбираем старшие карты той же масти
    if (flush_suit != -1) {
        result.hand_rank = FLUSH;
        int flush_cards[5] = { 0 };  
        int count = 0;

        for (int i = 0; i < 2 + board.num_cards; i++) {
            if (all_cards[i].suit == flush_suit) {
                flush_cards[count++] = all_cards[i].rank;
                if (count == 5) break;  // Останавливаемся если набрано 5 карт
            }
        }

        //Тут проблемы были какие-то с буфером я вроде починил но может и нет
        // Проверка на корректныйй флеш
        if (count == 5) {
            result.high_card = (Rank)flush_cards[0];  

            // Проверка на стрит флэээээээээээш
            bool is_straight_flush = true;
            for (int i = 0; i < count - 1; i++) {
                if (flush_cards[i] - 1 != flush_cards[i + 1]) {
                    is_straight_flush = false;
                    break;
                }
            }

            if (is_straight_flush) {
                result.hand_rank = STRAIGHT_FLUSH;
                result.high_card = (Rank)flush_cards[0]; 
                return result;
            }
        }
    }


    // Проверка на стриииит
    int consecutive = 0;
    for (int rank = ACE; rank >= TWO; rank--) {
        if (card_count[rank] > 0) {
            consecutive++;
            if (consecutive == 5) {
                result.hand_rank = STRAIGHT;
                result.high_card = (Rank)rank;  
                return result;  
            }
        }
        else {
            consecutive = 0;
        }
    }

    // Проверка на каре
    if (four_of_a_kind > 0) {
        result.hand_rank = FOUR_OF_A_KIND;
        result.high_card = (Rank)four_of_a_kind;  // Устанавливаем старшую карту каре

        // Поиск кикера 
        for (int rank = ACE; rank >= TWO; rank--) {
            if (card_count[rank] > 0 && rank != four_of_a_kind) {
                result.kicker[0] = (Rank)rank;  // Устанавливаем кикер
                break;  
            }
        }

        return result;
    }

    // Проверка на фулл-хаус (тройничек и пара)
    if (three_of_a_kind > 0 && highest_pair > 0) {
        result.hand_rank = FULL_HOUSE;
        result.high_card = (Rank)three_of_a_kind;  
        result.kicker[0] = (Rank)highest_pair;  
        return result;
    }

    // Проверка на тройку (тройничек)
    if (three_of_a_kind > 0) {
        result.hand_rank = THREE_OF_A_KIND;
        result.high_card = (Rank)three_of_a_kind; 
        return result;
    }

    //Две пары чекаем
    // Проверка на то являются ли две пары карт влюбленными друг в друга (две пары)
    if (highest_pair > 0 && second_highest_pair > 0) {
        result.hand_rank = TWO_PAIR;
        result.high_card = (Rank)highest_pair;  
        result.kicker[0] = (Rank)second_highest_pair;  
        return result;
    }

    // Проверка на то являются ли две карты влюбленными друг в друга (парой)
    if (highest_pair > 0) {
        result.hand_rank = ONE_PAIR;
        result.high_card = (Rank)highest_pair; 
        result.kicker[0] = (Rank)highest_rank; 
        return result;
    }

    // Если ничего не найдено просто старшая карта
    result.hand_rank = HIGH_CARD;
    result.high_card = (Rank)((hand.card1.rank > hand.card2.rank) ? hand.card1.rank : hand.card2.rank);  
    kicker[0] = (hand.card1.rank > hand.card2.rank) ? hand.card2.rank : hand.card1.rank;
    result.kicker[0] = (Rank)kicker[0];  

    return result;
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
    if (strcmp(phase, "flop") == 0) {
        cards_needed = 3;  // На флопе выкладываются 3 заветные карты ну и там по аналогии...
    }
    else if (strcmp(phase, "turn") == 0) {
        cards_needed = 4;  
    }
    else if (strcmp(phase, "river") == 0) {
        cards_needed = 5;  
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

void print_editBoardMenu(Game* game, bool used_cards[15][5]) {
    int choice;
    bool exit_editor = false;

    while (!exit_editor) {
        printf("================================================\n");
        printf("               Редактор стола                   \n");
        printf("================================================\n");
        printf("1. Добавить/изменить Flop (3 карты)\n");
        printf("2. Добавить/изменить Turn (4-ая карта)\n");
        printf("3. Добавить/изменить River (5-ая карта)\n");
        printf("------------------------------------------------\n");
        printf("0. Выйти\n");
        printf("================================================\n");
        printf("Выберите действие: ");
        choice = (int)scanf_secure("int");

        switch (choice) {
        case 1:
            printf("Редактирование Flop (первая, вторая и третья карты на столе)\n");
            input_board_cards(game, used_cards, 0, 3);  // Ввод трёх карт на флопетский
            break;

        case 2:
            if (game->board.num_cards < 3) {
                printf("Сначала необходимо добавить Flop!\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование Turn (четвёртая карта)\n");
                input_board_cards(game, used_cards, 3, 1);  // Ввод одной карты на тёёёрн
            }
            break;

        case 3:
            if (game->board.num_cards < 4) {
                printf("Сначала необходимо добавить Turn!\n");
                press_any_key_to_continue();
            }
            else {
                printf("Редактирование River (пятая карта)\n");
                input_board_cards(game, used_cards, 4, 1);  // Ввод одной карты на river
            }
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

            // Проверка на уникальность card (среди всех уже использованных карт)aaaaaaaa
            if (used_cards[rank_choice][suit_choice]) {
                printf("Эта карта уже используется! Попробуйте другую карту.\n");
            }
            else {
                // Сохранение карты на доске
                game->board.cards[start_index + i].rank = (Rank)rank_choice;
                game->board.cards[start_index + i].suit = (Suit)suit_choice;
                used_cards[rank_choice][suit_choice] = true;  // Помечаем fisting card
                if (start_index + i >= game->board.num_cards) {
                    game->board.num_cards++;
                }
                break;
            }
        } while (1);
    }
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


