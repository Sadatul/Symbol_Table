#include <iostream>

using namespace std;

class SymbolInfo
{
    string name;
    string type;
    SymbolInfo *next;

public:
    SymbolInfo(string name = "", string type = "", SymbolInfo *next = NULL)
    {
        this->name = name;
        this->type = type;
        this->next = next;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getType()
    {
        return type;
    }

    void setType(string type)
    {
        this->type = type;
    }

    SymbolInfo *getNext()
    {
        return next;
    }

    void setNext(SymbolInfo *next)
    {
        this->next = next;
    }
};

class ScopeTable
{
};