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
    SymbolInfo **table;

    int childNum; // This is used to track the scopeTables childs so that we can
                  // create the id;
public:
    ScopeTable *parentScope;

    ScopeTable(string id, int totalBuckets, ScopeTable *parentScope = NULL)
    {
        this->id = id;
        this->totalBuckets = totalBuckets;
        table = new SymbolInfo *[totalBuckets];
        for (int i = 0; i < totalBuckets; i++)
        {
            table[i] = NULL;
        }
        this->parentScope = parentScope;
        childNum = 0;
    }

    ~ScopeTable()
    {
        for (int i = 0; i < totalBuckets; i++)
        {
            deleteRecur(table[i]);
        }

        delete[] table;
    }

    void childAdded()
    {
        childNum++;
    }

    int getChildNum()
    {
        return childNum;
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

class SymbolTable
{
    ScopeTable *cur;
    int totalBuckets;

    void deleteRecur(ScopeTable *table)
    {
        if (table == NULL)
        {
            return;
        }

        deleteRecur(table->parentScope);
        delete table;
    }

public:
    SymbolTable(int totalBuckets)
    {
        this->totalBuckets = totalBuckets;
        cur = new ScopeTable("1", totalBuckets);
    }

    ~SymbolTable()
    {
        deleteRecur(cur);
    }

    void enterScope()
    {
        cur->childAdded();
        string id = cur->getId() + "." + to_string(cur->getChildNum());
        cur = new ScopeTable(id, totalBuckets, cur);
    }

    void exitScope()
    {
        if (cur->parentScope == NULL)
        {
            return;
        }

        ScopeTable *tmp = cur;
        cur = cur->parentScope;
        delete (tmp);
    }

    bool insert(string name, string type)
    {
        return cur->insert(name, type);
    }

    bool remove(string name)
    {
        return cur->Delete(name);
    }

    SymbolInfo *lookUp(string name)
    {
        ScopeTable *tmp = cur;
        while (tmp)
        {
            SymbolInfo *symbol = tmp->lookUp(name);
            if (symbol != NULL)
            {
                return symbol;
            }
            tmp = tmp->parentScope;
        }

        return NULL;
    }

    void printCurScopeTable()
    {
        cur->print();
    }

    void printAllScopeTable()
    {
        ScopeTable *tmp = cur;
        while (tmp)
        {
            tmp->print();
            tmp = tmp->parentScope;
        }
    }
};