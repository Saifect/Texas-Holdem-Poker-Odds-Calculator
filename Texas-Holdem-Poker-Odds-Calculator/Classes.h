#pragma once
#include "Globals.h"

// ����� �����
typedef enum {
    NONE_SUIT = -1,
    HEARTS,   // �����
    DIAMONDS, // �����
    CLUBS,    // �����
    SPADES,   // ����
} Suit;

// ���� �����
typedef enum {
    NONE_RANK = -1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
} Rank;

class Card {
private:
    Suit suit;
    Rank rank;
    bool is_used; // ���� ������������� �����

public:
    // ����������� �� ���������
    Card();

    // ����������� � �����������
    Card(Suit suit, Rank rank);

    // �������
    Suit get_suit() const;
    Rank get_rank() const;

    // ���������� ��������
    void set_suit(Suit suit);
    void set_rank(Rank rank);
    bool is_valid() const;

    // ��������� ����� ������������� �����
    void set_used(bool used) {
        is_used = used;
    }

    // ���������� �������� �����
    const char* get_rank_name() const;

    // ���������� �������� �����
    const char* get_suit_name() const;

    // ������� ��� ����������� �����
    void print_card() const;

    // ������� ������������ �����
    void release_card(bool used_cards[NUM_RANKS][NUM_SUITS]);

    // ������������� �����
    void init_card(Suit suit, Rank rank, bool used_cards[NUM_RANKS][NUM_SUITS]);

    // ������������� ��������� �����
    void init_random_card(bool used_cards[NUM_RANKS][NUM_SUITS]);
};

class Hand {
private:
    Card card[2]; // ��� ����� ����

public:
    // ����������� �� ���������
    Hand();

    // ����������� � �����������
    Hand(const Card& card1, const Card& card2);

    // ��������� �����
    void set_card(int index, const Card& card);

    // ������������� ����
    void init_hand(const Card& card1, const Card& card2);

    // ������� ����
    void clear_hand(bool used_cards[NUM_RANKS][NUM_SUITS]);

    // ������ ��� �����
    const Card& get_const_card(int index) const;
    Card& get_card(int index);
};

class Player {
private:
    Hand hand;         // ���� ������
    double equity;     // ����������� ������
    int wins;          // ���������� �����
    int ties;          // ���������� ������
    int losses;        // ���������� ���������

public:
    Player();

    // ������� ��� ����������
    void set_equity(double e);
    void set_wins(int w);
    void set_ties(int t);
    void set_losses(int l);

    // ������ ��� ������� � ����
    Hand& get_hand();
    const Hand& get_hand() const;  // ����������� �����

    // ������ ��� ��������� ���� ������
    void set_hand(const Hand& h, bool used_cards[NUM_RANKS][NUM_SUITS]);

    // ������������� ������
    void init_player(const Hand& new_hand, bool used_cards[NUM_RANKS][NUM_SUITS]);

    // ������� ���� ������
    void clear_player_cards(bool used_cards[NUM_RANKS][NUM_SUITS]);

    // ������� ��� ��������� ���������� ������
    double get_equity() const;
    int get_wins() const;
    int get_ties() const;
    int get_losses() const;
};

class Board {
private:
    Card cards[5]; // �� 5 ���� �� �����
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
    void clear_all_players_cards(bool used_cards[14][4]);
    void init_game(int num_players);
    void add_player(const Player& player, int index);

private:
    Player players[12];   // ������
    int num_players;      // ����� ���������� �������
    int current_players;  // ������� ������ � ����
    Board board;          // ������� ����
    char phase[10];       // ������� ���� ����
};

// �������� ����������
typedef enum {
    HIGH_CARD,        // ������� ������
    ONE_PAIR,         // ����
    TWO_PAIR,         // ��� ����
    THREE_OF_A_KIND,  // ���
    STRAIGHT,         // �����
    FLUSH,            // ����
    FULL_HOUSE,       // ���� ������
    FOUR_OF_A_KIND,   // ����
    STRAIGHT_FLUSH,   // ����� ����
    ROYAL_FLUSH
} PokerHandRank;

// ��������� ��� �������� ����������
typedef struct {
    PokerHandRank hand_rank;
    Rank high_card;
    Rank kicker[5];
} PokerCombination;

class Settings {
private:



public:


};


typedef struct {
    bool ties_visible_mode;
    bool wins_visible_mode;
    bool simulations_visible_mode;
    bool tie;
    bool show;
    int current_winner;
    int debug_player_index; // ������ ������ ��� �������
} Settings_debugging_mode;
