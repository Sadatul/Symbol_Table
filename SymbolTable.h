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
private:
    unsigned long hash(const string &str)
    {
        // Using sdbm hash
        unsigned long hash = 0;
        for (char c : str)
        {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash % totalBuckets;
    }

    void deleteRecur(SymbolInfo *node)
    {
        if (node == NULL)
            return;

        deleteRecur(node->getNext());
        delete (node);
    }

    int totalBuckets;
    string id;
    ScopeTable *parentScope;
    SymbolInfo **table;

public:
    ScopeTable(string id, int totalBuckets)
    {
        this->id = id;
        this->totalBuckets = totalBuckets;
        table = new SymbolInfo *[totalBuckets];
        for (int i = 0; i < totalBuckets; i++)
        {
            table[i] = NULL;
        }
    }

    ~ScopeTable()
    {
        for (int i = 0; i < totalBuckets; i++)
        {
            deleteRecur(table[i]);
        }

        delete[] table;
    }
    string getId()
    {
        return id;
    }

    // void setId(string id){
    //     this->id = id;
    // }

    int getTotalBuckets()
    {
        return totalBuckets;
    }

    ScopeTable *getParentScope()
    {
        return parentScope;
    }

    void setParentScope(ScopeTable *p)
    {
        this->parentScope = p;
    }

    SymbolInfo *lookUp(string name)
    {
        int index = hash(name); // %totalBuckets is being done inside the hash function
        SymbolInfo *tmp = table[index];
        while (tmp)
        {
            if (tmp->getName() == name)
            {
                return tmp;
            }

            tmp = tmp->getNext();
        }

        return NULL;
    }

    bool insert(string name, string type)
    {
        int index = hash(name); // %totalBuckets is being done inside the hash function
        if (table[index] == NULL)
        {
            table[index] = new SymbolInfo(name, type);
            return true;
        }

        SymbolInfo *tmp = table[index];
        while (true)
        {
            if (tmp->getName() == name)
            {
                return false;
            }
            if (tmp->getNext() == NULL)
            {
                tmp->setNext(new SymbolInfo(name, type));
                return true;
            }
            tmp = tmp->getNext();
        }
    }

    bool Delete(string name)
    {
        int index = hash(name); // %totalBuckets is being done inside the hash function
        if (table[index] == NULL)
        {
            return false;
        }
        if (table[index]->getName() == name)
        {
            SymbolInfo *tmp = table[index];
            table[index] = tmp->getNext();
            delete tmp;
            return true;
        }

        SymbolInfo *parent = table[index];

        while (SymbolInfo *child = parent->getNext())
        {
            if (child->getName() == name)
            {
                parent->setNext(child->getNext());
                delete child;
                return true;
            }
            parent = child;
        }

        return false;
    }

    void print()
    {
        cout << "\tScopeTable# " << id << " created" << endl;
        for (int i = 0; i < totalBuckets; i++)
        {
            cout << "\t" << i + 1;

            SymbolInfo *tmp = table[i];
            while (tmp)
            {
                cout << " --> (" << tmp->getName() << "," << tmp->getType() << ")";
                tmp = tmp->getNext();
            }
            cout << endl;
        }
    }
};