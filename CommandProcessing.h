#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <list>
#include <iostream>
using namespace std;

class Command
{
public:
    Command();
    Command(string command, string effect);
    //Copy constructor declaration:
    Command(const Command& c);
    //Overloaded assignment operator declaration:
    Command& operator = (const Command& c);
    //Getters declaration:
    string getCommand();
    string getEffect();
    //Setters declaration:
    void setCommand(string c);
    void setEffect(string e);
    void saveEffect(string command);
    friend std::ostream & operator << (std::ostream &out, const Command &c);
private:
    string command;
    string effect;
};


class CommandProcessor
{
public:
    CommandProcessor();
    CommandProcessor(list<Command*> lc);
    //Copy constructor declaration:
    CommandProcessor(const CommandProcessor& cp);
    ~CommandProcessor();
    //Overloaded assignment operator declaration:
    CommandProcessor& operator = (const CommandProcessor& cp);
    //Getters declaration:
    list<Command*> getCommandList();
    //Setters declaration:
    void setCommandList(list<Command*> lc);
    string getCommand();
    friend std::ostream & operator << (std::ostream &out, const CommandProcessor &cp);
protected:
    string readCommand();
    void saveCommand(Command* obj);
private:
    list<Command*> lc;
};

#endif // COMMANDPROCESSING_H
