#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

//Command class declaration.
class Command
{
public:
    //Default constructor declaration:
    Command();
    //Parameterized constructor declaration:
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
    //Other methods declarations:
    void saveEffect(string command);
    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const Command &c);
private:
    string command;
    string effect;
};

//CommandProcessor class declaration.
class CommandProcessor
{
public:
    //Default constructor declaration:
    CommandProcessor();
    //Parameterized constructor declaration:
    CommandProcessor(list<Command*> lc);
    //Destructor:
    virtual ~CommandProcessor();
    //Copy constructor declaration:
    CommandProcessor(const CommandProcessor& cp);
    //Overloaded assignment operator declaration:
    CommandProcessor& operator = (const CommandProcessor& cp);
    //Getters declaration:
    list<Command*> getCommandList();
    //Setters declaration:
    void setCommandList(list<Command*> lc);
    //Other methods declarations:
    string getCommand();
    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const CommandProcessor &cp);
protected:
    virtual string readCommand();
    void saveCommand(Command* obj);
private:
    list<Command*> lc;
};

//FileLineReader class declaration.
class FileLineReader
{
public:
    //Parameterized constructor declaration:
    FileLineReader(string filename);
    //Destructor:
    ~FileLineReader();
    //Copy constructor declaration:
    FileLineReader(const FileLineReader& flr);
    //Other methods declarations:
    string readLineFromFile();
    //Overloaded stream insertion operators declarations: (using friend for having access to private variables)
    friend std::ostream & operator << (std::ostream &out, const FileLineReader &flr);
private:
    ifstream stream;
    string filename;
};

//FileCommandProcessorAdapter class declaration (subclass of CommandProcessor class).
class FileCommandProcessorAdapter : public CommandProcessor
{
public:
    //Parameterized constructor declaration:
    FileCommandProcessorAdapter(FileLineReader* obj);
    //Destructor:
    ~FileCommandProcessorAdapter();
    //Copy constructor declaration:
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcpa);
    //Overloaded assignment operator declaration:
    FileCommandProcessorAdapter& operator = (const FileCommandProcessorAdapter& fcpa);
    //Getters declaration:
    FileLineReader* getFileLineReader();
    string readCommand();
private:
    FileLineReader* flr;
};

#endif // COMMANDPROCESSING_H
