#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;

class Card // Card class that is used to fill the deck
{
    public:
        int value;
        char suit;
};


class Deck // Deck class that is used for players to draw from
{
    public:
        Card deck[52]; // Array for holding the deck of cards

        Deck() // Constuctor fills up the deck
        {
            // Arrays to hold values and suits
            int valueList[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
            char suitList[] = {'C', 'D', 'H', 'S'};

            // Loop to fill the deck array
            int cardIndex = 0;
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 13; j++)
                {
                    deck[cardIndex].value = valueList[j];
                    deck[cardIndex].suit = suitList[i];
                    cardIndex++;
                }
            }
        }
};


class Player // Player class that is used for the player and the dealer
{
    public:
        int gamesWon = 0; // Integers for keeping track of current score and game record
        int gamesDrawn = 0;
        int gamesLost = 0;
        int currentHand = 0;

        // DrawCard() pulls a random index from the deck and adds its value to the players current hand
        // Since it doesn't remove the card from the deck, there is no card counting in my version
        // It is a limitation, but one that casinos would probably like, so I think it's ok here
        void DrawCard(Deck deck)
        {
            int cardIndex = rand() % 52;
            Card drawnCard = deck.deck[cardIndex];
            currentHand += drawnCard.value;
        }

        // Play() is the turn taking by the player. The player draws until they have either 17 or bust.
        // Once they hit one of those, the while loop is negative and stops.
        // Busts also give a player a hand value of 0, so they lose unless the other player busts as well.
        void Play(Deck deck)
        {
            currentHand = 0;
            bool playGame = true;
            while(playGame)
            {
                if(currentHand < 17)
                {
                    DrawCard(deck);
                }
                else if(currentHand > 21)
                {
                    currentHand = 0;
                    playGame = false;
                }
                else
                {
                    playGame = false;
                }
            }
        }

        double PercentageWon()
        {
            double totalGames = gamesWon + gamesDrawn + gamesLost;
            double winPercent = (gamesWon/totalGames) * 100;
            return winPercent;
        }

        double PercentageDrawn()
        {
            double totalGames = gamesWon + gamesDrawn + gamesLost;
            double drawPercent = (gamesDrawn/totalGames) * 100;
            return drawPercent;
        }

        double PercentageLost()
        {
            double totalGames = gamesWon + gamesDrawn + gamesLost;
            double lossPercent = (gamesLost/totalGames) * 100;
            return lossPercent;
        }

};


int main()
{
    // Instantiates all the classes
    Deck CardDeck;
    Player player;
    Player dealer;

    // Random code borrowed from https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    // the nullptr was recommended by clion
    srand(time(nullptr));

    int gameAmount = 10000000;// Determines how many games the simulation will run

    for(int i = 1; i <= gameAmount; i++)
    {
        // Both players take their turns
        player.Play(CardDeck);
        dealer.Play(CardDeck);


        // Outputs the game number, player score, and dealer score
        cout << "-----Game " << i << "-----" << endl;
        cout << "Player: " << player.currentHand << endl;
        cout << "Dealer: " << dealer.currentHand << endl;
        cout << endl;

        // Logic and output handling to determine game outcome
        if(player.currentHand > dealer.currentHand)
        {
            player.gamesWon += 1;
            cout << "You win!" << endl;
            cout << "Record: " << player.gamesWon << '-' << player.gamesDrawn << '-' << player.gamesLost << endl;
            cout << "--------------" << endl << endl;
        }
        else if(player.currentHand == dealer.currentHand)
        {
            player.gamesDrawn += 1;
            cout << "It's a tie!" << endl;
            cout << "Record: " << player.gamesWon << '-' << player.gamesDrawn << '-' << player.gamesLost << endl;
            cout << "--------------" << endl << endl;
        }
        else if(player.currentHand < dealer.currentHand)
        {
            player.gamesLost += 1;
            cout << "Sorry, you lose." << endl;
            cout << "Record: " << player.gamesWon << '-' << player.gamesDrawn << '-' << player.gamesLost << endl;
            cout << "--------------" << endl << endl;
        }
    }
    cout << player.PercentageWon() << "% - " << player.PercentageDrawn() << "% - " << player.PercentageLost() << "%" << endl;
    return 0;
}

