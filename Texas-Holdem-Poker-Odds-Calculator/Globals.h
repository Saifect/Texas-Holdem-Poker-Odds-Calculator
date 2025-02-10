#pragma once
#define GLOBALS_H

#include <string>
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm> // Подключаем заголовочный файл для std::sort
#include <chrono>
#include <thread>
#include <ostream>   // для std::ostream

#define NUM_RANKS 13
#define NUM_SUITS 4
#define MAX_BOARD_CARDS 5
#define DEF_SIMULATIONS 250000
#define ESC_KEY 27   // ASCII-код клавиши Esc

extern bool used_cards[NUM_RANKS][NUM_SUITS]; // Объявление глобальной переменной

