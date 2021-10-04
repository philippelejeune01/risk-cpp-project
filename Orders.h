#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED
#include <iostream>
#include <list>
using std::string;
//For storing elements
using std::list;
using std::cin;
using std::cout;
using std::ostream;
//Declaration of the dummy classes Territory and Player. This is only for testing purposes.
class Territory{
public:
    Territory();
    Territory(int nOfArmies,string name);
    ~Territory();
    friend ostream& operator <<(ostream &strm, const Territory &terr);
    bool isAdjacent(Territory* adjTerr);
    void addEdges(Territory* adjTerr);
    int getAmountOfArmies();
private:
    string terrName;
    int amountOfArmies;
    list<Territory*> adjacentList;
};
class Player{
public:
    Player();
    Player(string newName);
    ~Player();
    friend ostream& operator <<(ostream &strm, const Player &pl);
    string getName();
    void setName(string newName);
private:
    string name;
};
//Declarations of Order class and its subclasses
class Order {
public:
    //Constructors
    Order();
    Order(const Order& ord);
    Order(Territory* targetTerr, list<Territory*>* ownedTerr);
    Order& operator = (const Order& ord);
    virtual ~Order();
    friend ostream& operator <<(ostream &strm, const Order &ord);
    //Setters and Getters
    Territory* getTargetTerritory() const;
    list<Territory*>* getOwnedTerritories() const;
    void setTargetTerritory(Territory* newTarTerr);
    void setOwnedTerritories(list<Territory*>* ownedTerr);
    //Functions every subclasses has to implement
    virtual bool validate();
    virtual void execute();
protected:
    //targetTerritory refers to the territory affected by the order
    Territory* targetTerritory;
    //ownedTerritories refers to the list of territories a player owns
    list<Territory*>* ownedTerritories;
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

    list<Order*> getOrdList() const;
    //2 required methods
    void move(Order* order, int index);
    void remove(int index);

private:
    //Is temporarily an array
    list<Order*> ordList;
    //Determines the index an Order is on the list
    int findOrder(Order* ord);
};



//Order's subclasses.
//Deploy validates only if the target territory is owned by the calling player
class Deploy: public Order {
public:
    //Constructors
    Deploy();
    Deploy(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies);
    Deploy(const Deploy& depl);
    Deploy& operator = (const Deploy& depl);
    //Destructor
    ~Deploy();
    friend ostream& operator <<(ostream &strm, const Deploy &depl);
    //Setter and Getter
    void setNAddedArmies(int nAA);
    int getNAddedArmies();
    //Functions every subclasses has to implement
    bool validate();
    void execute();
private:
    //nAddedArmies refers to the amount of armies to be deployed to the targetted territory
    int nAddedArmies;
};

//Advance validates if the source territory is owned by the calling player
class Advance: public Order{
public:
    Advance();
    Advance(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr);
    Advance(const Advance& adv);
    Advance& operator = (const Advance& adv);
    ~Advance();
    friend ostream& operator <<(ostream &strm, const Advance &adv);
    //Setters and Getters
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
};

//Bomb validates if the target territory is not owned by the calling player
class Bomb: public Order{
public:
    Bomb();
    Bomb(Territory* targetTerritory, list<Territory*>* ownedTerr);
    Bomb(const Bomb& bomb);
    Bomb& operator = (const Bomb& bomb);
    ~Bomb();
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Bomb &bomb);
};

//Blockade validates if the target territory is owned by the calling player
class Blockade: public Order{
public:
    Blockade();
    Blockade(Territory* targetTerritory, list<Territory*>* ownedTerr);
    Blockade(const Blockade& block);
    Blockade& operator = (const Blockade& block);
    ~Blockade();
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Blockade &block);
};

//Airlift validates if the source territory is owned by the calling player
class Airlift: public Order{
public:
    Airlift();
    Airlift(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr);
    Airlift(const Airlift& airLi);
    Airlift& operator = (const Airlift& airLi);
    ~Airlift();
    friend ostream& operator <<(ostream &strm, const Airlift &airL);
    //Setters and Getters
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
    void setCallingPlayer(Player* cPlayer);
    void setTargetPlayer(Player* tPlayer);
    Player* getCallingPlayer();
    Player* getTargetPlayer();
    bool validate();
    void execute();
private:
    //callingPlayer refers to the player making the negotiate order
    Player* callingPlayer;
    //targetPlayer refers to the targetted player
    Player* targetPlayer;
};


#endif // ORDERS_H_INCLUDED
