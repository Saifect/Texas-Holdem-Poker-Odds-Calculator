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
	HEARTS,   // Черви
	DIAMONDS, // Бубны
	CLUBS,    // Трефы
	SPADES    // Пики
}Suit;

//Ранк карты//
typedef enum {
	TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
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
void handle_calculatorMenu_choice(int choice);
void print_calculatorMenu();
//


//Prototypes for Useful_function
double scanf_secure(const char* type);          // Функция для безопасного ввода различных типов данных
void сonsole_clear();                           // Функция для очистки консоли
void buffer_clear();                            // Функция для очистки буфера ввода
void line_remove(char* str);                    // Функция для удаления символа новой строки из строки
void string_get_secure(char* buffer, int size); // Функция для безопасного получения строки с защитой от переполнения буфера
void press_any_key_to_continue();
void press_any_key_to_continue_clearConsole();

//============MAIN_FUNCTION============//
int main(){
	
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	// Инициализация генератора случайных чисел
	srand(time(NULL));

    while (true) {
        int choice;
        print_mainMenu(&choice);
        press_any_key_to_continue();
        сonsole_clear();
    }
   
	 



	return 0;
}

//======IMPLENTATION_OF_FUNCTIONS======//

//Начальное меню//
void print_mainMenu(int* choice) {
	printf("\n");
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
        exit(0); // Используем exit для выхода из программы
        
    case 1:
        сonsole_clear();
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
        printf("Version program: 0.2\n");
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
    int choice;
    bool edit_mode = false;
    printf("\n");
    printf("================================================\n");
    printf("             Текущая информация                 \n");
    printf("================================================\n");
    printf("Карты игрока 1: \n");
    printf("Карты игрока 2: \n");
    printf("================================================\n");
    printf("           Функционал калькулятора              \n");
    printf("================================================\n");
    printf("1. Добавить карты 1-му игроку\n");
    printf("2. Добавить карты 2-му игроку\n");
    printf("3. Рассчитать шансы выигрыша\n");
    printf("0. Назад\n");
    if (edit_mode = false) {
        printf("Ваш выбор: ");
        choice = (int)scanf_secure("int");
        handle_calculatorMenu_choice(choice);
    }
    else if (edit_mode = true) {
        printf("Введите карты игрока %d: "); //ДОДЕЛАТЬ РЕДАКТИРОВАНИЯ КАРТ, СОБСТВЕННО ЖЕСТКО ИНИЦИАЛИЗИРОВАТЬ ИХ В MAIN
    }

    
    
}


//Обработка выбора пользователя в меню калькулятора//
void handle_calculatorMenu_choice(int choice) {
    switch (choice) {
    case 0:
        printf("Не реализовано\n");
        exit(0); 

    case 1:
        printf("Не реализовано\n");
        break;
    case 2:
        printf("Не реализовано\n");
       
        break;
    case 3:
        printf("Не реализовано\n");
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
void сonsole_clear() {
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