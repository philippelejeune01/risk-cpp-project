#ifndef Card_H
#define Card_H
#include <string>
#include <iostream>

class Card
{
    private:
        std::string type;
    public:
        Card(std::string type);

        void play();
        
        void setType(std::string type);

        std::string getType(){return type;}
};

#endif