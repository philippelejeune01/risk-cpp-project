#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

//Declaration of the dummy classes Territory, Hand and Card. This is only for testing purposes.
//Dummy class Territory
class Territory{
public:
    Territory();
    Territory(int nOfArmies,string name);
    ~Territory();
    friend ostream& operator <<(ostream &strm, const Territory &terr);
    bool isAdjacent(Territory* adjTerr);
    void addEdges(Territory* adjTerr);
    int getAmountOfArmies();
    string getName();
    vector<Territory*> getAdjacentList() const;
private:
    string terrName;
    int amountOfArmies;
    vector<Territory*> adjacentList;
};
//Dummy class Card
class Card
{
    private:
        string type;
    public:
        Card();
        Card(string s);
        Card(const Card& c);
        Card& operator = (const Card& h);
        ~Card();

        void play();

        void setType(string s);

        string getType() const;
        friend ostream & operator << (ostream &out, const Card &c);
        friend ostream & operator << (ostream &out, const Card* c);
        friend istream & operator >> (istream &in, Card &c);
};
//Dummy class Hand
class Hand
{
    private:
        vector<Card*> cards;
    public:
        Hand();
        Hand(vector<Card*> c);
        Hand(const Hand& h);
        Hand& operator = (const Hand& h);
        ~Hand();

        vector<Card*> const & getCards() const;
        friend ostream & operator << (ostream &out, const Hand &h);
        friend ostream & operator << (ostream &out, const Hand *h);

};

class Order {
public:
    //Constructors
    Order();
    Order(const Order& ord);
    Order(Territory* targetTerr, vector<Territory*>* ownedTerr);
    Order& operator = (const Order& ord);
    virtual ~Order();
    friend ostream& operator <<(ostream &strm, const Order &ord);
    //Setters and Getters
    Territory* getTargetTerritory() const;
    vector<Territory*>* getOwnedTerritories() const;
    void setTargetTerritory(Territory* newTarTerr);
    void setOwnedTerritories(vector<Territory*>* ownedTerr);
    //Functions every subclasses has to implement
    virtual string getOrderType() const;
    virtual bool validate();
    virtual void execute();
protected:
    //targetTerritory refers to the territory affected by the order
    Territory* targetTerritory;
    //ownedTerritories refers to the list of territories a player owns
    vector<Territory*>* ownedTerritories;
    string orderType;
};

//Declaration of OrdersList class
class OrdersList{
public:
    //Constructors
    OrdersList();
    OrdersList(std::list<Order*> ls);
    OrdersList(const OrdersList& ordsL);
    //Overloaded assignment op
    OrdersList& operator = (const OrdersList& ls);
    //Destructor
    ~OrdersList();
    friend ostream& operator <<(ostream &strm, const OrdersList &ordLs);
    friend ostream& operator <<(ostream &strm, const OrdersList* ordLs);

    list<Order*> const & getOrdList() const;
    //2 required methods
    void move(Order* order, int index);
    void remove(int index);

private:
    //Is temporarily an array
    list<Order*> ordList;
    //Determines the index an Order is on the list
    int findOrder(Order* ord);
};

class Player
{
    public:
        Player();
        Player(string newName);
        Player(string newName, Hand* aHand);
        Player(string newName, vector <Territory*> &terr);
        Player(string newName, vector <Territory*> &terr, Hand* aHand);
        Player(const Player& pl);
        Player& operator = (const Player& pl);
        ~Player();
        friend ostream& operator <<(ostream &strm, const Player &aPlayer);
        //Required Methods
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder(string ordType, Territory* targetTerritory, int nOfArmies);
        void issueOrder(string ordType, Territory* targetTerritory, int nOfArmies, Territory* sourceTerr);
        void issueOrder(string ordType, Territory* targetTerritory);
        void issueOrder(string ordType, Player* targetPlayer);
        //Accesors and Mutators
        string getName();
        void setName(string newName);
        vector <Territory*> getTerritories() const;
        void setTerritories(vector <Territory*> &terr);
        Hand* getHand() const;
        void setHand(Hand* h);
        OrdersList* getOrderList() const;
        void setOrderList(OrdersList* aOrdersList);
        static int getPlayerCount();


    private:
        string name;
        static int playerCount;
        //The player's territories
        vector <Territory*> territories;
        Hand* hand;
        OrdersList* ordersList;

};
//Global function to assign territories to player's
void setPlayersTerritories(vector <Territory*> allTerritories, vector <Player*> allPlayers, int playerCount);

//Order's subclasses.
//Deploy validates only if the target territory is owned by the calling player
class Deploy: public Order {
public:
    //Constructors
    Deploy();
    Deploy(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies);
    Deploy(const Deploy& depl);
    Deploy& operator = (const Deploy& depl);
    //Destructor
    ~Deploy();
    friend ostream& operator <<(ostream &strm, const Deploy &depl);
    //Setter and Getter
    string getOrderType() const;
    void setNAddedArmies(int nAA);
    int getNAddedArmies();
    //Functions every subclasses has to implement
    bool validate();
    void execute();
private:
    //nAddedArmies refers to the amount of armies to be deployed to the targetted territory
    int nAddedArmies;
    string orderType;
};

//Advance validates if the source territory is owned by the calling player
class Advance: public Order{
public:
    Advance();
    Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr);
    Advance(const Advance& adv);
    Advance& operator = (const Advance& adv);
    ~Advance();
    friend ostream& operator <<(ostream &strm, const Advance &adv);
    //Setters and Getters
    string getOrderType() const;
    void setNOfArmies(int nOA);
    void setSourceTerritory(Territory* sourceTerr);
    int getNOfArmies();
    Territory* getSourceTerritory();
    bool validate();
    void execute();
private:
    //nMovedArmies refers to the amount of armies to be moved from one territory to another
    int nMovedArmies;
    //sourceTerritory refers to the territory where the armies are coming from
    Territory* sourceTerritory;
    string orderType;
};

//Bomb validates if the target territory is not owned by the calling player
class Bomb: public Order{
public:
    Bomb();
    Bomb(Territory* targetTerritory, vector<Territory*>* ownedTerr);
    Bomb(const Bomb& bomb);
    Bomb& operator = (const Bomb& bomb);
    ~Bomb();
    string getOrderType() const;
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Bomb &bomb);

private:
    string orderType;
};

//Blockade validates if the target territory is owned by the calling player
class Blockade: public Order{
public:
    Blockade();
    Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr);
    Blockade(const Blockade& block);
    Blockade& operator = (const Blockade& block);
    ~Blockade();
    string getOrderType() const;
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Blockade &block);

private:
    string orderType;
};

//Airlift validates if the source territory is owned by the calling player
class Airlift: public Order{
public:
    Airlift();
    Airlift(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr);
    Airlift(const Airlift& airLi);
    Airlift& operator = (const Airlift& airLi);
    ~Airlift();
    friend ostream& operator <<(ostream &strm, const Airlift &airL);
    //Setters and Getters
    string getOrderType() const;
    void setNOfArmies(int nOA);
    void setSourceTerritory(Territory* sourceTerr);
    int getNOfArmies();
    Territory* getSourceTerritory();
    bool validate();
    void execute();
private:
    //nMovedArmies indicates the amount of armies to be moved
    int nMovedArmies;
    //sourceTerritory refersr to the territory where the armies move from
    Territory* sourceTerritory;
    string orderType;
};

//Negotiate validates if the target player is not already in a cease fire with the calling player
class Negotiate: public Order{
public:
    Negotiate();
    Negotiate(Player* cPlayer, Player* tPlayer);
    Negotiate(const Negotiate& negotiate);
    Negotiate& operator = (const Negotiate& negotiate);
    ~Negotiate();
    friend ostream& operator <<(ostream &strm, const Negotiate &negotiate);
    //Setter and Getter
    string getOrderType() const;
    void setCallingPlayer(Player* cPlayer);
    void setTargetPlayer(Player* tPlayer);
    Player* getCallingPlayer() const;
    Player* getTargetPlayer() const;
    bool validate();
    void execute();
private:
    //callingPlayer refers to the player making the negotiate order
    Player* callingPlayer;
    //targetPlayer refers to the targetted player
    Player* targetPlayer;
    string orderType;
};

#endif // PLAYER_H
