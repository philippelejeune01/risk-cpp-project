#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED
#include <iostream>
#include <list>
#include <vector>
#include "Map.h"
using std::string;
//For storing elements
using std::list;
using std::cin;
using std::cout;
using std::ostream;

class Player;

//Declarations of Order class and its subclasses
//Declarations of Order class and its subclasses
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
    //duplicate method
    virtual Order* duplicate()=0;
    //Functions every subclasses has to implement
    virtual string getOrderType() const;
    virtual bool validate()=0;
    virtual void execute();
protected:
    //targetTerritory refers to the territory affected by the order
    Territory* targetTerritory;
    //ownedTerritories refers to the list of territories a player owns
    vector<Territory*>* ownedTerritories;
    string orderType;
private:
    virtual string doPrint() const;
};

//Declaration of OrdersList class
class OrdersList{
public:
    //Constructors
    OrdersList();
    OrdersList(list<Order*>* ls);
    OrdersList(const OrdersList& ordsL);
    //Overloaded assignment op
    OrdersList& operator = (const OrdersList& ls);
    //Destructor
    ~OrdersList();
    friend ostream& operator <<(ostream &strm, const OrdersList &ordLs);
    list<Order*> const & getOrdList() const;
    //2 required methods
    void move(Order* order, int index);
    void remove(int index);
    void addOrder(Order* order);

private:
    //Is temporarily an array
    list<Order*> ordList;
};



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
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
private:
    //nAddedArmies refers to the amount of armies to be deployed to the targetted territory
    int nAddedArmies;
    string orderType;
    string doPrint() const;
};

//Advance validates if the source territory is owned by the calling player
class Advance: public Order{
public:
    //Constructors, Destructors, operator overload
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
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
private:
    //nMovedArmies refers to the amount of armies to be moved from one territory to another
    int nMovedArmies;
    //sourceTerritory refers to the territory where the armies are coming from
    Territory* sourceTerritory;
    string doPrint() const;
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
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Bomb &bomb);
private:
    string doPrint() const;
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
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Blockade &block);
private:
    string doPrint() const;
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
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
private:
    //nMovedArmies indicates the amount of armies to be moved
    int nMovedArmies;
    //sourceTerritory refersr to the territory where the armies move from
    Territory* sourceTerritory;
    string doPrint() const;
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
    Player* getCallingPlayer();
    Player* getTargetPlayer();
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
private:
    //callingPlayer refers to the player making the negotiate order
    Player* callingPlayer;
    //targetPlayer refers to the targetted player
    Player* targetPlayer;
    string doPrint() const;
    string orderType;
};

#endif // ORDERS_H_INCLUDED
