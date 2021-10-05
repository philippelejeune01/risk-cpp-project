#include "Map.h"
using namespace std;

Map::Map(vector<int>* adjacency,vector<Territory> listOfTerritories,int nOfContinents,int nOfTerritories,int endOf[])
{
    adjacencyList = adjacency;
    territories = listOfTerritories;
    numOfContinents = nOfContinents;
    numOfTerritories = nOfTerritories;

}

Map::Map(const Map& m)
{
    adjacencyList = m.adjacencyList;
    territories = m.territories;
    numOfContinents = m.numOfContinents;
    numOfTerritories = m.numOfTerritories;
}

Map::Map()
{

}
bool Map::validate()
{
    return true;
}
void Map::Print()
{
    for (int i=1;i<=numOfContinents;i++)
        cout<<"end of Continent: "<<i<<" "<<endofContinents[i]<<endl;
}
void Map::setAdjacency(vector<int>* adjacency)
{
    adjacencyList = adjacency;
}
void Map::setTerritories(vector<Territory> t)
{
    territories = t;
}
void Map::setNumberOfContinets(int n)
{
    numOfContinents = n;
}
void Map::setEndOfContinents(const int* arr)
{
    for (int i = 1; i <= numOfContinents; i++)
        endofContinents[i]=arr[i];
}
void Map::setNumberOfTerritories(int n)
{
    numOfTerritories = n;
}
Territory::Territory(int x,int y,int c, Player* ownedP, string n)
{
    xCoordinate = x;
    yCoordinate = y;
    continentNumber = c;
    ownedplayer = ownedP;
    name = n;
}
Territory::Territory()
{

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
void Print(vector<int> adjacency[],int total) //represent the graph for test
{
    bool flag = false;
    for (int i = 1; i < total; ++i)
    {
        cout << "\nTerritory " << i << " connects to: ";
        for (auto x : adjacency[i])
        {
            cout << " " << x;
            flag=true;
        }
        if (!flag)
            cout<<"This is not a valid map!";
        flag=false;
    }
}
MapLoader::MapLoader(string fpath)
{
    filepath=fpath;
}
Map MapLoader::Load()
{
    Map m;
    string s;
    int endOf[100];
    ifstream inputstream(filepath);
    int u, v;
    Territory* f;
    int numOfTerritories=0,numOfContinents;
    string name;
    int x,y,cnumber;
    int round=0,integer=0;
    bool flag=false;

    while (s!="[continents]") //skip over the [files] in the .map file
        inputstream>>s;
    inputstream>>s;

    while (s!="[countries]")
    {
        inputstream>>s;
        numOfContinents++;
    }
    numOfContinents/=3;
    int endOfContinents[numOfContinents];
    vector<Territory> territories;
    Territory t;
    cnumber = 1;
    while (s!="[borders]" )
    {
        inputstream>>s;
        if (round==0) numOfTerritories++;
        if (round==1) { name=s; t.setName(name); }
        if (round==2) {
                        if (stoi(s)!=cnumber)
                            endOf[cnumber]=numOfTerritories-1;
                        cnumber=stoi(s); t.setContinent(cnumber);
                      }
        if (round==3) x=stoi(s);
        if (round==4) { y=stoi(s); t.setCoordinates(x,y);  territories.push_back(t);}
        round = (round+1)%5;
    }
    endOf[numOfContinents] = numOfTerritories-1;

    numOfTerritories--; //exclude [borders]

    vector<int> adjacency[numOfTerritories+1];

    while (!inputstream.eof())
    {
        if (flag) //start of each border, if true, first value read is head of the connection
        {
            if (inputstream.peek()==EOF) break;
            u=stoi(s); //connection head
            flag=false;
        }
        else
        {
            if(s!="[borders]")
                v=stoi(s);//if we're reading a number,this is where the head is connecting to.
            if (u!=0)
                adjacency[u].push_back(v);
        }
        if (inputstream.peek()=='\n')
            flag=true;
        inputstream>>s;
    }
    inputstream.close();
    //Print(adjacency,numOfTerritories+1);

    m.setNumberOfContinets(numOfContinents);
    m.setNumberOfTerritories(numOfTerritories);
    m.setAdjacency(adjacency);
    m.setEndOfContinents(endOf);
    m.setTerritories(territories);

    return m;
}
void Map::load(string filepath)
{
//    Maploader* m(filepath);
}



