#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED
#include <iostream>
#include <list>
using std::string;
//For storing elements
using std::list;
using std::cin;
using std::cout;
//Declaration of the dummy classes Territory and Player. This is only for testing purposes.
class Territory{
public:
    Territory();
    Territory(int nOfArmies);
    ~Territory();
    bool isAdjacent(Territory* adjTerr);
    void addEdges(Territory* adjTerr);
private:
    int amountOfArmies;
    list<Territory*> adjacentList;
};
class Player{
public:
    Player();
    Player(string name);
    ~Player();
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
    ~Order();
    //Setters and Getters
    Territory* getTargetTerritory() const;
    list<Territory*>* getOwnedTerritories() const;
    void setTargetTerritory(Territory* newTarTerr);
    void setOwnedTerritories(list<Territory*>* ownedTerr);

    //Functions every subclasses has to implement
    bool validate();
    void execute();
protected:
    Territory* targetTerritory;
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

    list<Order*> getOrdList() const;
    //2 required methods
    void move(Order* order, int index);
    void remove(Order* order);

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
    //Setter and Getter
    void setNAddedArmies(int nAA);
    int getNAddedArmies();
    //Functions every subclasses has to implement
    bool validate();
    void execute();
private:
    int nAddedArmies;
};

//Advance validates if the source territory is owned by the calling player
class Advance: public Order{
public:
    Advance();
    Advance(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerritory);
    Advance(const Advance& adv);
    ~Advance();
    //Setters and Getters
    void setNOfArmies(int nOA);
    void setSourceTerritory(Territory* sourceTerritory);
    int getNOfArmies();
    Territory* getSourceTerritory();
private:
    int nMovedArmies;
    Territory* sourceTerritory;
};

//Bomb validates if the target territory is not owned by the calling player
class Bomb: public Order{
public:
    Bomb();
    Bomb(Territory* targetTerritory, list<Territory*>* ownedTerr);
    Bomb(const Bomb& boom);
    ~Bomb();
};

//Blockade validates if the target territory is owned by the calling player
class Blockade: public Order{
public:
    Blockade();
    Blockade(Territory* targetTerritory, list<Territory*>* ownedTerr);
    Blockade(const Blockade& block);
    ~Blockade();
};

//Airlift validates if the source territory is owned by the calling player
class Airlift: public Order{
public:
    Airlift();
    Airlift(Territory* targetTerritory, list<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerritory);
    Airlift(const Airlift& airli);
    ~Airlift();
    //Setters and Getters
    void setNOfArmies(int nOA);
    void setSourceTerritory(Territory* sourceTerritory);
    int getNOfArmies();
    Territory* getSourceTerritory();
private:
    int nMovedArmies;
    Territory* sourceTerritory;
};

//Negotiate validates if the target player is not already in a cease fire with the calling player
class Negotiate: public Order{
public:
    Negotiate();
    Negotiate(Player* player, Player* targetPlayer);
    Negotiate(const Negotiate& negotia);
    ~Negotiate();
    //Setter and Getter
    void settargetPlayer(Player* tPlayer);
    Player* getTargetPlayer();
private:
    Player* targetPlayer;
};


#endif // ORDERS_H_INCLUDED
