#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include "Map.h"
#include "LoggingObserver.h"
using std::string;
//For storing elements
using std::list;
using std::cin;
using std::cout;
using std::ostream;

class Player;

//Declarations of Order class and its subclasses
//Declarations of Order class and its subclasses
class Order: public Subject, public ILoggable {
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
    virtual bool validate()=0;
    virtual void execute()=0;
    string getOrderType() const;

    static void setUpPlayerCannotAttackList();
    static void clearPlayerCannotAttackList();
    static void deletePlayerCannotAttackList();
    virtual string doPrint() const;
protected:
    Order(Territory* targetTerr, vector<Territory*>* ownedTerr, string oType);
    //targetTerritory refers to the territory affected by the order
    Territory* targetTerritory;
    //ownedTerritories refers to the list of territories a player owns
    vector<Territory*>* ownedTerritories;

    /*playersCannotAttackList is a dynamically allocated multidimensional array that
    stores pair of Player pointers. This indicates which players cannot attack each other
    for the round.
    */
    static Player*** playersCannotAttackList;
    static int sizeOfPlCantAttList;
    static int indexOfEnd;
    string orderType;
    LogObserver* logO;

};

//Declaration of OrdersList class
class OrdersList: public Subject, public ILoggable{
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
    bool isEmpty();
    list<Order*> getOrdList() const;
    string getFirstOrderType();
    //2 required methods
    void move(Order* order, int index);
    void remove(int index);
    void addOrder(Order* order);
    void executeFirstOrder();
    string stringToLog();
private:
    //List of orders
    list<Order*> ordList;
    bool lastAddedWasDeployed;
    LogObserver* logO;
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
    void setNAddedArmies(int nAA);
    int getNAddedArmies();
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    string stringToLog();
private:
    //nAddedArmies refers to the amount of armies to be deployed to the targetted territory
    int nAddedArmies;
    string doPrint() const;

};

//Advance validates if the source territory is owned by the calling player
class Advance: public Order{
public:
    //Constructors, Destructors, operator overload
    Advance();
    Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies, Territory* sourceTerr);
    Advance(Territory* targetTerritory, vector<Territory*>* ownedTerr, int nOfArmies,
             Territory* sourceTerr,vector<Territory*>* enemyTerrs, bool* flagConq);
    Advance(const Advance& adv);
    Advance& operator = (const Advance& adv);
    ~Advance();
    friend ostream& operator <<(ostream &strm, const Advance &adv);
    //Setters and Getters
    void setNOfArmies(int nOA);
    void setSourceTerritory(Territory* sourceTerr);
    void setFlagConqTerr(bool* flag);
    void setEnemyTerritories(vector<Territory*>* enmyTerrs);
    int getNOfArmies();
    Territory* getSourceTerritory();
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    string stringToLog();
private:
    //nMovedArmies refers to the amount of armies to be moved from one territory to another
    int nMovedArmies;
    //sourceTerritory refers to the territory where the armies are coming from
    Territory* sourceTerritory;
    //enemyTerritories refers to the vector of territories of which the targetTerritory belongs to
    //enemyTerritories can point to the same memory location of ownedTerritories
    vector<Territory*>* enemyTerritories;
    bool* flagConq;
    string doPrint() const;

};

//Bomb validates if the target territory is not owned by the calling player
class Bomb: public Order{
public:
    Bomb();
    Bomb(Territory* targetTerritory, vector<Territory*>* ownedTerr);
    Bomb(const Bomb& bomb);
    Bomb& operator = (const Bomb& bomb);
    ~Bomb();
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Bomb &bomb);
    string stringToLog();
private:
    string doPrint() const;
};

//Blockade validates if the target territory is owned by the calling player
class Blockade: public Order{
public:
    Blockade();
    Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr);
    Blockade(Territory* targetTerritory, vector<Territory*>* ownedTerr, Player* neutralPl);
    Blockade(const Blockade& block);
    Blockade& operator = (const Blockade& block);
    ~Blockade();
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    friend ostream& operator <<(ostream &strm, const Blockade &block);
    Player* getNeutralPlayer();
    void setNeutralPlayer(Player* nPl);
    string stringToLog();
private:
    string doPrint() const;
    Player* neutralPlayer;

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
    void setNOfArmies(int nOA);
    void setSourceTerritory(Territory* sourceTerr);
    int getNOfArmies();
    Territory* getSourceTerritory();
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    string stringToLog();
private:
    //nMovedArmies indicates the amount of armies to be moved
    int nMovedArmies;
    //sourceTerritory refersr to the territory where the armies move from
    Territory* sourceTerritory;
    string doPrint() const;
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
    //duplicate method
    Order* duplicate();
    //Functions every subclasses has to override
    bool validate();
    void execute();
    string stringToLog();
private:
    //callingPlayer refers to the player making the negotiate order
    Player* callingPlayer;
    //targetPlayer refers to the targetted player
    Player* targetPlayer;
    string doPrint() const;
};


#endif // ORDERS_H_INCLUDED
