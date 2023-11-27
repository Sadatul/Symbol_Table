#include <iostream>
#include "SymbolTable.h"

using namespace std;

int main(void)
{
    ScopeTable s1("1.1.1", 5);
    cout << s1.insert("i", "var1") << endl;
    cout << s1.insert("j", "var2") << endl;
    cout << s1.insert("k", "var3") << endl;
    cout << s1.insert("l", "var4") << endl;
    cout << s1.insert("m", "var5") << endl;
    cout << s1.insert("n", "var6") << endl;
    cout << s1.insert("o", "var7") << endl;
    cout << s1.insert("p", "var8") << endl;
    cout << s1.insert("q", "var9") << endl;
    cout << s1.insert("r", "var10") << endl;
    cout << s1.insert("s", "var11") << endl;
    cout << s1.insert("t", "var12") << endl;
    cout << s1.lookUp("i")->getType() << endl;
    cout << s1.lookUp("j")->getType() << endl;
    cout << s1.lookUp("k")->getType() << endl;
    cout << s1.lookUp("l")->getType() << endl;
    cout << s1.lookUp("m")->getType() << endl;
    cout << s1.lookUp("n")->getType() << endl;
    cout << s1.lookUp("o")->getType() << endl;
    cout << s1.lookUp("p")->getType() << endl;
    cout << s1.lookUp("q")->getType() << endl;
    cout << s1.lookUp("r")->getType() << endl;
    cout << s1.lookUp("s")->getType() << endl;
    cout << s1.lookUp("t")->getType() << endl;
    s1.print();
    cout << s1.Delete("i") << endl;
    s1.print();
    cout << s1.Delete("j") << endl;
    cout << s1.Delete("k") << endl;
    cout << s1.Delete("l") << endl;
    cout << s1.Delete("m") << endl;
    cout << s1.Delete("n") << endl;
    cout << s1.Delete("o") << endl;
    s1.print();
    s1.insert("sadi", "rabbi");
    s1.print();
    cout << s1.Delete("p") << endl;
    cout << s1.Delete("q") << endl;
    cout << s1.Delete("r") << endl;
    cout << s1.Delete("s") << endl;
    cout << s1.Delete("t") << endl;
    s1.print();
}