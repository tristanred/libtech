#include "libtech/games/blackjack/blackjack.h"

#include <stdio.h>
#include "libtech/randomgen.h"

BlackjackGame::BlackjackGame()
{
    this->Player = new struct blackjack_player();
    this->Player->cards = new card_info*[MAX_CARD_NB];
    this->Player->card_amount = 0;

    this->Dealer = new struct blackjack_player();
    this->Dealer->cards = new card_info*[MAX_CARD_NB];
    this->Dealer->card_amount = 0;

    this->PreviousState = BLJK_GAME_START;
    this->CurrentState = BLJK_GAME_START;
    Gamebet = 0;

    memset(meters, 0, BLJK_METERS_COUNT);
}

BlackjackGame::~BlackjackGame()
{
    this->DeleteHands();
    this->DeletePlayers();
}

void BlackjackGame::UpdateGame()
{
    switch (this->CurrentState)
    {
        case BLJK_GAME_START:
        {
            printf("GAME_START\n");

            SetState(BLJK_BET_SELECT);

            DeleteHands();

            break;
        }
        case BLJK_BET_SELECT:
        {
            printf("BET SELECT\n");

            Gamebet = 1;
            printf("Setting bet to %d\n", Gamebet);

            SetState(BLJK_PLAYER_DRAW_STARTING_HAND);

            break;
        }
        case BLJK_PLAYER_DRAW_STARTING_HAND:
        {
            this->Player->cards[0] = draw_card();
            this->Player->cards[1] = draw_card();

            this->Player->card_amount = 2;

            SetState(BLJK_DEALER_DRAW_STARTING_HAND);

            break;
        }
        case BLJK_DEALER_DRAW_STARTING_HAND:
        {
            this->Dealer->cards[0] = draw_card();
            this->Dealer->cards[1] = draw_card();

            this->Dealer->card_amount = 2;

            if(count_cards(Player) == BLACKJACK_AMOUNT)
            {
                SetState(BLJK_PLAYER_BLACKJACK);
            }
            else
            {
                if(offer_insurance(Dealer))
                {
                    SetState(BLJK_OFFER_INSURANCE);
                }
                else
                {
                    SetState(BLJK_PLAYER_CHOICE);
                }
            }

            break;
        }
        case BLJK_OFFER_INSURANCE:
        {
            RandomGen rng;
            if(rng.GetRandomPercentage() > 50)
            {
                // Insure player
            }
            else
            {
                // Don't insure player
            }

            SetState(BLJK_PLAYER_CHOICE);

            break;
        }
        case BLJK_PLAYER_BLACKJACK:
        {
            // TODO : Count player blackjack
            SetState(BLJK_GAME_START);

            break;
        }
        case BLJK_PLAYER_CHOICE:
        {
            RandomGen rng;

            if(count_cards(Player) == BLACKJACK_AMOUNT)
            {
                SetState(BLJK_PLAYER_BLACKJACK);
                break;
            }

            // Check if player wants to split
            if(can_split(Player))
            {
                if(rng.GetRandomPercentage() > 50)
                {
                    SetState(BLJK_PLAYER_SPLIT);
                    break;
                }
            }

            // Check if player wants to double
            if(rng.GetRandomPercentage() > 50)
            {
                SetState(BLJK_PLAYER_DOUBLE);
                break;
            }

            // If player wants to hit
            if(rng.GetRandomPercentage() > 50)
            {
                SetState(BLJK_PLAYER_HIT);
                break;
            }

            SetState(BLJK_PLAYER_STAND);

            break;
        }
        case BLJK_PLAYER_STAND:
        {
            SetState(BLJK_DEALER_REVEAL);

            break;
        }
        case BLJK_PLAYER_HIT:
        {
            this->Player->cards[this->Player->card_amount] = draw_card();
            this->Player->card_amount++;

            if(count_cards(Player) > BLACKJACK_AMOUNT)
            {
                SetState(BLJK_PLAYER_BUST);
            }
            else if(count_cards(Player) == BLACKJACK_AMOUNT)
            {
                SetState(BLJK_PLAYER_BLACKJACK);
            }
            else
            {
                SetState(BLJK_PLAYER_CHOICE);
            }

            break;
        }
        case BLJK_PLAYER_DOUBLE:
        {
            this->Player->cards[this->Player->card_amount] = draw_card();
            this->Player->card_amount++;

            if(count_cards(Player) > BLACKJACK_AMOUNT)
            {
                SetState(BLJK_PLAYER_BUST);
            }
            else
            {
                SetState(BLJK_DEALER_REVEAL);
            }

            break;
        }
        case BLJK_PLAYER_SPLIT:
        {
            // Don't handle split for now, ask the player again for choice.
            SetState(BLJK_PLAYER_CHOICE);

            break;
        }
        case BLJK_DEALER_REVEAL:
        {
            if(count_cards(Dealer) == BLACKJACK_AMOUNT)
            {
                SetState(BLJK_DEALER_BLACKJACK);
            }
            else
            {
                SetState(BLJK_DEALER_CHOICE);
            }

            break;
        }
        case BLJK_DEALER_BLACKJACK:
        {
            SetState(BLJK_DEALER_WIN);

            break;
        }
        case BLJK_DEALER_CHOICE:
        {
            if(count_cards(Dealer) < DEALER_SOFT_STOP)
            {
                SetState(BLJK_DEALER_HIT);
            }
            else
            {
                SetState(BLJK_DEALER_STAND);
            }

            break;
        }
        case BLJK_DEALER_HIT:
        {
            this->Dealer->cards[this->Dealer->card_amount] = draw_card();
            this->Dealer->card_amount++;

            if(count_cards(Dealer) > BLACKJACK_AMOUNT)
            {
                SetState(BLJK_DEALER_BUST);
            }
            else
            {
                SetState(BLJK_DEALER_CHOICE);
            }

            break;
        }
        case BLJK_DEALER_STAND:
        {
            SetState(BLJK_COMPARE_SCORES);

            break;
        }
        case BLJK_DEALER_BUST:
        {
            SetState(BLJK_PLAYER_WIN);
            
            break;
        }
        case BLJK_COMPARE_SCORES:
        {
            int playerCount = count_cards(Player);
            int dealerCount = count_cards(Dealer);

            int playerDifference = BLACKJACK_AMOUNT - playerCount;
            int dealerDifference = BLACKJACK_AMOUNT - dealerCount;

            if(playerDifference < dealerDifference)
            {
                SetState(BLJK_PLAYER_WIN);
            }
            else
            {
                SetState(BLJK_DEALER_WIN);
            }

            break;
        }
        case BLJK_PLAYER_WIN:
        {
            SetState(BLJK_GAME_START);

            break;
        }
        case BLJK_DEALER_WIN:
        {
            SetState(BLJK_GAME_START);
            
            break;
        }
        default:
        {
            printf("Case not handled");
            break;
        }
    }
}

void BlackjackGame::SetState(enum blackjack_states newState)
{
    printf("%s -> %s\n", blackjack_states_names[this->CurrentState], blackjack_states_names[newState]);

    this->PreviousState = this->CurrentState;
    this->CurrentState = newState;
}

void BlackjackGame::DeleteHands()
{
    if(this->Player != NULL)
    {
        for(int i = 0; i < this->Player->card_amount; i++)
        {
            delete(this->Player->cards[i]);
        }
    }

    if(this->Dealer != NULL)
    {
        for(int i = 0; i < this->Dealer->card_amount; i++)
        {
            delete(this->Dealer->cards[i]);
        }
    }
}

void BlackjackGame::DeletePlayers()
{
    if(this->Player != NULL)
    {
        if(this->Player->cards != NULL)
            delete(this->Player->cards);

        delete(this->Player);
    }

    if(this->Dealer != NULL)
    {
        if(this->Dealer->cards != NULL)
            delete(this->Dealer->cards);

        delete(this->Dealer);
    }
}

struct card_info* draw_card()
{
    RandomGen rng;

    struct card_info* newCard = new struct card_info();
    newCard->count_value = card_values[rng.GetRandom(CARD_NAMES_COUNT)];
    newCard->name = (enum card_names)newCard->count_value;
    newCard->suit = (enum card_suits)rng.GetRandom(CARD_SUITS_COUNT);
    
    return newCard;
}

bool has_blackjack(struct blackjack_player* target)
{
    return count_cards(target) == BLACKJACK_AMOUNT;
}

int count_cards(struct blackjack_player* target)
{
    int total = 0;
    for(int i = 0; i < target->card_amount; i++)
    {
        total += target->cards[i]->count_value;
    }

    // Disregard the aces for now

    return total;
}

bool offer_insurance(struct blackjack_player* target)
{
    // Card 0 is shown to the player
    return target->cards[0]->name == CARD_ACE;
}

bool can_split(struct blackjack_player* target)
{
    return target->cards[0]->count_value == target->cards[1]->count_value;
}
