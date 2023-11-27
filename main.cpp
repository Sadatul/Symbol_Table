#include <iostream>
#include "SymbolTable.h"

using namespace std;

int main(void)
{
    SymbolInfo *s1 = new SymbolInfo("S2");
    SymbolInfo s("Sadi", "name", s1);
    s1->setName("N2");
    s1->setType("Sada");
    // s.setNext(s1);
    cout << s.getNext()->getName() << s.getNext()->getType() << endl;
}