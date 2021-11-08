#include "CommandProcessing.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

CommandProcessor::CommandProcessor()
{
    list<Command*> l;
    this->lc = l;
}

CommandProcessor::CommandProcessor(list<Command*> lc)
{
    this->lc = lc;
}

CommandProcessor::CommandProcessor(const CommandProcessor& cp)
{
    this->lc = cp.lc;
}

CommandProcessor::~CommandProcessor()
{
    while(!lc.empty()) delete lc.front(), lc.pop_front();
    lc.clear();
}

CommandProcessor& CommandProcessor::operator = (const CommandProcessor& cp)
{
    this->lc = cp.lc;
    return *this;
}

list<Command*> CommandProcessor::getCommandList()
{
    return lc;
}

void CommandProcessor::setCommandList(list<Command*> lc)
{
    lc = lc;
}

void CommandProcessor::saveCommand(Command* obj)
{
    lc.push_back(obj);
}

void Command::saveEffect(string eff)
{
    setEffect(eff);
}


std::string CommandProcessor::getCommand()
{
    string command = readCommand();
    Command* c = new Command(command, " ");
    saveCommand(c);
    return command;
}

std::string CommandProcessor::readCommand()
{
    string command;
    cout << "Please enter a valid command:" << endl;
    //user inputs a string using the keyboard that is stored in the string command.
    getline(std::cin, command);
    return command;
}


std::ostream & operator << (std::ostream &out, const CommandProcessor &cp)
{
    list<Command*> l = cp.lc;
    out << "The list of commands is: \n";
    for (const auto& i: l)
    {
        out << *(i) << endl;
    }
    return out;
}

std::ostream &operator << (std::ostream &out, const Command &c)
{
    out << "command: "
    << c.command << endl
    << "effect : "
    << c.effect << endl;
    return out;
}


Command::Command()
{
    this->command = "";
    this->effect = "";
}

Command::Command(string c, string e)
{
    this->command = c;
    this->effect = e;
}

Command::Command(const Command& c)
{
    this->command = c.command;
    this->effect = c.effect;
}

Command& Command::operator = (const Command& c)
{
    this->command = c.command;
    this->effect = c.effect;
    return *this;
}

string Command::getCommand()
{
    return this->command;
}

string Command::getEffect()
{
    return this->effect;
}

void Command::setCommand(string c)
{
    this->command = c;
}

void Command::setEffect(string e)
{
    effect = e;
}
