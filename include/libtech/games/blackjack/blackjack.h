#pragma once

#include "libtech/libtech.h"
#include "libtech/randomgen.h"
#include <stack>

#define DEALER_SOFT_STOP 17
#define BLACKJACK_AMOUNT 21
enum blackjack_states
{
    BLJK_GAME_START,
    BLJK_BET_SELECT,
    BLJK_PLAYER_DRAW_STARTING_HAND,
    BLJK_DEALER_DRAW_STARTING_HAND,
    BLJK_OFFER_INSURANCE,
    BLJK_PLAYER_BLACKJACK,
    BLJK_PLAYER_CHOICE,
    BLJK_PLAYER_STAND,
    BLJK_PLAYER_HIT,
    BLJK_PLAYER_DOUBLE,
    BLJK_PLAYER_SPLIT,
    BLJK_PLAYER_BUST,
    BLJK_DEALER_REVEAL, // Start of dealer sequence
    BLJK_DEALER_BLACKJACK,
    BLJK_DEALER_CHOICE,
    BLJK_DEALER_HIT,
    BLJK_DEALER_STAND,
    BLJK_DEALER_BUST,
    BLJK_COMPARE_SCORES,
    BLJK_PLAYER_WIN,
    BLJK_DEALER_WIN,

    BLJK_STATES_COUNT
};

const char* blackjack_states_names[BLJK_STATES_COUNT] = {
    "GAME_START",
    "BET_SELECT",
    "PLAYER_DRAW_STARTING_HAND",
    "DEALER_DRAW_STARTING_HAND",
    "OFFER_INSURANCE",
    "PLAYER_BLACKJACK",
    "PLAYER_CHOICE",
    "PLAYER_STAND",
    "PLAYER_HIT",
    "PLAYER_DOUBLE",
    "PLAYER_SPLIT",
    "PLAYER_BUST",
    "DEALER_REVEAL",
    "DEALER_BLACKJACK",
    "DEALER_CHOICE",
    "DEALER_HIT",
    "DEALER_STAND",
    "DEALER_BUST",
    "COMPARE_SCORES",
    "PLAYER_WIN",
    "DEALER_WIN"
};

enum card_suits
{
    SUIT_HEART,
    SUIT_SPADE,
    SUIT_DIAMOND,
    SUIT_CLUBS,

    CARD_SUITS_COUNT
};

const char* card_suits_names[CARD_SUITS_COUNT] = {
    "HEART",
    "SPADE",
    "DIAMOND",
    "CLUBS"
};

enum card_names
{
    CARD_ACE,
    CARD_ONE,
    CARD_TWO,
    CARD_THREE,
    CARD_FOUR,
    CARD_FIVE,
    CARD_SIX,
    CARD_SEVEN,
    CARD_EIGHT,
    CARD_NINE,
    CARD_TEN,
    CARD_JACK,
    CARD_QUEEN,
    CARD_KING,

    CARD_NAMES_COUNT
};

const char* card_values_names[CARD_NAMES_COUNT] = {
    "ACE",
    "ONE",
    "TWO",
    "THREE",
    "FOUR",
    "FIVE",
    "SIX",
    "SEVEN",
    "EIGHT",
    "NINE",
    "TEN",
    "JACK",
    "QUEEN",
    "KING"
};

int card_values[CARD_NAMES_COUNT] = {
    11, // Can also count for 1
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    10, // Jack
    10, // Queen
    10 // King
};

struct card_info
{
    enum card_names name;
    enum card_suits suit;
    int count_value;
};

#define MAX_CARD_NB 16
struct LIBTECH_CLASS blackjack_player
{
    size_t card_amount;
    card_info** cards;
};

enum blackjack_meters
{
    METER_PLAYER_WIN,
    METER_DEALER_WIN,

    METER_PLAYER_HIT,
    METER_PLAYER_STAND,
    METER_PLAYER_SPLIT,
    METER_PLAYER_DOUBLE,
    METER_PLAYER_BLACKJACK,
    METER_PLAYER_BUST,

    METER_DEALER_HIT,
    METER_DEALER_STAND,
    METER_DEALER_BLACKJACK,
    METER_DEALER_BUST,

    BLJK_METERS_COUNT
};

const char* blackjack_meters_names[BLJK_METERS_COUNT] = {
    "PLAYER_WIN",
    "DEALER_WIN",

    "METER_PLAYER_HIT",
    "METER_PLAYER_STAND",
    "METER_PLAYER_SPLIT",
    "METER_PLAYER_DOUBLE",
    "METER_PLAYER_BLACKJACK",
    "METER_PLAYER_BUST",

    "METER_DEALER_HIT",
    "METER_DEALER_STAND",
    "METER_DEALER_BLACKJACK",
    "METER_DEALER_BUST",
};


bool has_blackjack(struct blackjack_player* target);
int count_cards(struct blackjack_player* target);
bool offer_insurance(struct blackjack_player* target);
bool can_split(struct blackjack_player* target);

#define INITIAL_DECK_COUNT 4

class LIBTECH_CLASS BlackjackGame
{
public:
    BlackjackGame();
    ~BlackjackGame();
    
    void UpdateGame();
    void SetState(enum blackjack_states newState);

    struct card_info* DrawCard();
    void RegenerateDecks();

    void DeleteHands();
    void DeletePlayers();


    void SaveMeters();

    // Game State
    int CountGames;
    int Gamebet;
    enum blackjack_states PreviousState;
    enum blackjack_states CurrentState;
    struct blackjack_player* Dealer;
    struct blackjack_player* Player;

    // Card & decks
    std::stack<card_info*>* cards;

    // Random
    RandomGen* rng;

    // Meters
    int meters[BLJK_METERS_COUNT];
};