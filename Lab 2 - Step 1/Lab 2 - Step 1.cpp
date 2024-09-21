#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
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
void handle_calculatorMenu_choice(int choice, Game* game, bool exit);
void print_calculatorMenu();
//
const char* get_rank_name(Rank rank);
const char* get_suit_name(Suit suit);
void input_player_cards(Player* player);
//
//Prototypes for Useful_function
//
double scanf_secure(const char* type);          // Функция для безопасного ввода различных типов данных
void clearConsole();                            // Функция для очистки консоли
void buffer_clear();                            // Функция для очистки буфера ввода
void line_remove(char* str);                    // Функция для удаления символа новой строки из строки
void string_get_secure(char* buffer, int size); // Функция для безопасного получения строки с защитой от переполнения буфера
void press_any_key_to_continue();
void press_any_key_to_continue_clearConsole();

//============MAIN_FUNCTION============//
int main(){
    system("chcp 65001");
    clearConsole();
    /// Установка кодировок консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "Rus");
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
        printf("Version program: 0.3");
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
    /// Инициализация ///
    Card card1 = { NONE_SUIT, NONE_RANK }; // Пример корректной инициализации карты: ранг "Двойка" и масть "Черви"
    Card card2 = { NONE_SUIT, NONE_RANK }; // Пример корректной инициализации карты: ранг "Тройка" и масть "Пики"
    Hand hand1 = { card1, card2 }; // Инициализация рук
    Hand hand2 = { card1, card2 }; // Для второго игрока тоже можно задать
    Player player1 = { hand1 }; // Инициализация игроков
    Player player2 = { hand2 };
    Board board = { NONE_SUIT }; // Инициализация доски
    Game game = { player1, player2, board }; // Инициализация структуры Game

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

        printf("================================================\n");
        printf("           Функционал калькулятора              \n");
        printf("================================================\n");
        printf("1. Добавить карты 1-му игроку\n");
        printf("2. Добавить карты 2-му игроку\n");
        printf("3. Рассчитать шансы выигрыша\n");
        printf("0. Назад\n");
        printf("================================================\n");
        printf("Ваш выбор: ");

        choice = (int)scanf_secure("int");
        handle_calculatorMenu_choice(choice, &game, exit);
    }
}



//Обработка выбора пользователя в меню калькулятора//
void handle_calculatorMenu_choice(int choice, Game* game, bool exit) {
    switch (choice) {
    case 0:
        printf("Возврат в главное меню...\n");
        exit = true;
        break;

    case 1:
        printf("------------------------------------------------\n");
        printf("        Добавление карт 1-му игроку             \n");
        printf("------------------------------------------------\n");
        input_player_cards(&game->player1);
        break;

    case 2:
        printf("Добавление карт 2-му игроку\n");
        input_player_cards(&game->player2);
        break;

    case 3:
        printf("Рассчитать шансы выигрыша...\n");
        // Вызов функции расчета эквити (вероятности выигрыша)
        break;

    default:
        printf("Неверный выбор! Попробуйте снова.\n");
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
// Функция для получения имени масти карты
const char* get_suit_name(Suit suit) {
    switch (suit) {
    case HEARTS: return "Черви \u2665";
    case DIAMONDS: return "Бубны";
    case CLUBS: return "Трефы";
    case SPADES: return "Пики";
    default: return "Неизвестно";
    }
}

//Ввод карт игрока//
void input_player_cards(Player* player) {
    int rank_choice, suit_choice;
    bool identical_cards;
    // Ввод первой карты
    do {
        printf("Введите ранг первой карты (2-14): ");
        rank_choice = (int)scanf_secure("int");
        if (rank_choice < 2 || rank_choice > 14) {
            printf("Неверный ранг! Попробуйте снова.\n");
        }
    } while (rank_choice < 2 || rank_choice > 14);
    player->hand.card1.rank = (Rank)rank_choice;

    do {
        printf("Введите масть первой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики): ");
        suit_choice = (int)scanf_secure("int");
        if (suit_choice < 1 || suit_choice > 4){
            printf("Вы ввели число вне диапазона, попробуйте снова!\n");
        }
    } while (suit_choice < 1 || suit_choice > 4);
    player->hand.card1.suit = (Suit)suit_choice;

    // Ввод второй карты
    do {
        printf("Введите ранг второй карты (2-14): ");
        rank_choice = (int)scanf_secure("int");
        if (rank_choice < 2 || rank_choice > 14) {
            printf("Неверный ранг! Попробуйте снова.\n");
        }

    } while (rank_choice < 2 || rank_choice > 14);
    player->hand.card2.rank = (Rank)rank_choice;

    do {
        printf("Введите масть первой карты (1 - Черви, 2 - Бубны, 3 - Трефы, 4 - Пики): ");
        suit_choice = (int)scanf_secure("int");
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
                printf("Ошибка ввода. Пожалуйста, введите целое число: ");
                buffer_clear();
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
//////////////////////////////////////////////
//ФУНКЦИИ ДЛЯ АЛГОРИТМА РАСЧЕТА ВЕРОЯТНОСТЕЙ//
//////////////////////////////////////////////
//////////////////////////////////////////////



