#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include "Card.h"
using namespace std;

//driver
/*int main(){
    srand((unsigned) time(0));
    vector<Card*> v;
    //creating Cards to put in deck
    int i;
    for(i=0;i<10;i++){
        Card *c = new Card();
        v.push_back(c);
    }

    Deck d(v);
    cout << d << endl;
    //fill hand with card from deck (hand size is inferred to be 5)
    Hand h;
    for(i=0;i<5;i++){
        h.getCards()->push_back(d.draw());
    }

    cout << "-After having drawn 5 cards-" << endl;
    cout << d << endl;
    cout << h << endl;

    vector<Order*> ol;

    ol.push_back(h.getCards()->at(0)->play(d, h));
    ol.push_back(h.getCards()->at(0)->play(d, h));
    ol.push_back(h.getCards()->at(0)->play(d, h));
    ol.push_back(h.getCards()->at(0)->play(d, h));
    ol.push_back(h.getCards()->at(0)->play(d, h));


    cout << "-After Having played 5 cards-" << endl;
    cout << d << endl;
    cout << h << endl;

}*/
