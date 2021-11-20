Territory::Territory(int tnum,int x,int y,int c,int num,Player* ownedP, string n)
{
    TerritoryNumber = tnum;
    xCoordinate = x;
    yCoordinate = y;
    continentNumber = c;
    amountOfArmies = num;
    ownedplayer = ownedP;
    name = n;
    isUnderAttack = false;
}
Territory::Territory(const Territory& t)
{
    this->TerritoryNumber = t.TerritoryNumber;
    this->xCoordinate = t.xCoordinate;
    this->yCoordinate = t.yCoordinate;
    this->continentNumber = t.continentNumber;
    this->amountOfArmies = t.amountOfArmies;
    this->ownedplayer = t.ownedplayer;
    this->name = t.name;
    isUnderAttack = false;
}
Territory::Territory()
{

}
Territory::~Territory()
{
    adjacentTerritories.clear();
    ownedplayer = NULL;
}
void Territory::setContinent(int c)
{
    continentNumber=c;
}

void Territory::setName(string n)
{
    name=n;
}
void Territory::setCoordinates(int x, int y)
{
    xCoordinate = x;
    yCoordinate = y;
}
void Territory::setTerritoryNum(int t)
{
    TerritoryNumber = t;
}
int Territory::getTerritoryNum()
{
    return TerritoryNumber;
}
void Territory::setPlayer(Player* p)
{
    ownedplayer = p;
}
Player* Territory::getPlayer()
{
    return ownedplayer;
}
int Territory::getContinent()
{
    return continentNumber;
}
string Territory::getName()
{
    return name;
}
int Territory::getAmountOfArmies()
{
    return amountOfArmies;
}
void Territory::setAmountOfArmies(int nOfArmies)
{
    amountOfArmies = nOfArmies;
}
bool Territory::isTerritoryUnderAttack()
{
    return isUnderAttack;
}
void Territory::setAttackStatus(bool attack)
{
    isUnderAttack = attack;
}
bool Territory::isAdjacentTo(Territory &t2)
{
    for (auto x: adjacentTerritories)
        if (x->getTerritoryNum() == t2.getTerritoryNum())
            return true;
    return false;
}
ostream& operator <<(ostream &strm, const Territory &terr)
{
    return strm << terr.name << ": Continent: " << terr.continentNumber << ": nOfArmies: " << terr.amountOfArmies;
}
