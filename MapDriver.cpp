#include "Map.h"
#include <iostream>
using namespace std;

int main()
{
    MapLoader m("solar.map");
    Map test = m.Load();
    test.Print();

    return 0;
}
