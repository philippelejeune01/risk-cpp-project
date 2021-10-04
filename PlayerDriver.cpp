#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

int main()
{
    vector<Territories*> allTerritories;
    vector<Player*> allPlayers;

    //Create territories
    Territories *terr1 = new Territories(1);
    allTerritories.push_back(terr1);
    Territories *terr2 = new Territories(2);
    allTerritories.push_back(terr2);
    Territories *terr3 = new Territories(3);
    allTerritories.push_back(terr3);
    Territories *terr4 = new Territories(4);
    allTerritories.push_back(terr4);
    Territories *terr5 = new Territories(5);
    allTerritories.push_back(terr5);
    Territories *terr6 = new Territories(6);
    allTerritories.push_back(terr6);
    Territories *terr7 = new Territories(7);
    allTerritories.push_back(terr7);
    Territories *terr8 = new Territories(8);
    allTerritories.push_back(terr8);
    Territories *terr9 = new Territories(9);
    allTerritories.push_back(terr9);
    Territories *terr10 = new Territories(10);
    allTerritories.push_back(terr10);
    Territories *terr11 = new Territories(11);
    allTerritories.push_back(terr11);
    Territories *terr12 = new Territories(12);
    allTerritories.push_back(terr12);
    Territories *terr13 = new Territories(13);
    allTerritories.push_back(terr13);

    //Create Players
    Player *player1 = new Player();
    allPlayers.push_back(player1);
    Player *player2 = new Player();
    allPlayers.push_back(player2);
    Player *player3 = new Player();
    allPlayers.push_back(player3);

    cout << "Player count: " << Player::getPlayerCount() << endl;

    setPlayersTerritories(allTerritories, allPlayers, Player::getPlayerCount());

    cout << "Player Territories: " << endl;
    cout << "Player 1 Territory size: " << player1->getTerritories().size() << endl;
    cout << "Player 2 Territory size: " << player2->getTerritories().size() << endl;
    cout << "Player 3 Territory size: " << player3->getTerritories().size() << endl;

    cout << "Player 3 Territories to Defend: " << endl;
    for (auto x: player3->toDefend()) {
        std::cout << x->id << ' ';
    }
    cout << endl;
    cout << "Player 1 Territories to Defend: " << endl;
    for (auto x: player1->toDefend()) {
        std::cout << x->id << ' ';
    }
    cout << endl;

}
