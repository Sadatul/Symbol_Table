#include <iostream>
#include "SymbolTable.h"

#define TOKEN_SIZE 100;

using namespace std;

int tokenize(string s, string del, string tokens[])
{
    int i = 0;
    int start, end = -1 * del.size();
    do
    {
        start = end + del.size();
        end = s.find(del, start);
        // cout << s.substr(start, end - start) << endl;
        tokens[i++] = s.substr(start, end - start);
    } while (end != -1);

    return i;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int totalBuckets;
    cin >> totalBuckets;
    string garbage;
    getline(cin, garbage); // This is given for the trailing \n after the integer input

    SymbolTable s(totalBuckets, true);
    int cmdTracker = 1;
    while (1)
    {
        string input;
        getline(cin, input);
        cout << "Cmd " << cmdTracker << ": " << input << endl;
        cmdTracker++;
        string tokens[100];
        int count = tokenize(input, " ", tokens);

        if (tokens[0] == "I")
        {
            if (count != 3)
            {
                cout << "\tWrong number of arugments for the command I" << endl;
                continue;
            }
            s.insert(tokens[1], tokens[2], true);
        }
        else if (tokens[0] == "D")
        {
            if (count != 2)
            {
                cout << "\tWrong number of arugments for the command D" << endl;
                continue;
            }
            s.remove(tokens[1], true);
        }
        else if (tokens[0] == "L")
        {
            if (count != 2)
            {
                cout << "\tWrong number of arugments for the command L" << endl;
                continue;
            }
            s.lookUp(tokens[1], true);
        }
        else if (tokens[0] == "S")
        {
            if (count != 1)
            {
                cout << "\tWrong number of arugments for the command S" << endl;
                continue;
            }
            s.enterScope(true);
        }
        else if (tokens[0] == "E")
        {
            if (count != 1)
            {
                cout << "\tWrong number of arugments for the command E" << endl;
                continue;
            }
            s.exitScope(true);
        }
        else if (tokens[0] == "P")
        {
            if (count != 2)
            {
                cout << "\tWrong number of arugments for the command P" << endl;
                continue;
            }
            if (tokens[1] == "A")
            {
                s.printAllScopeTable();
            }
            else if (tokens[1] == "C")
            {
                s.printCurScopeTable();
            }
            else
            {
                cout << "\tInvalid argument for the command P" << endl;
            }
        }
        else if (tokens[0] == "Q")
        {
            if (count != 1)
            {
                cout << "\tWrong number of arugments for the command Q" << endl;
                continue;
            }
            return 0;
        }
    }
}

// int main(void)
// {
//     SymbolTable s1(5);
//     // s1.printAllScopeTable();
//     s1.insert("i", "var");
//     s1.enterScope();
//     s1.insert("foo", "FUNCTION");
//     s1.insert("i", "var2");
//     s1.printAllScopeTable();
//     s1.remove("i");
//     s1.printAllScopeTable();
//     s1.exitScope();
//     s1.printAllScopeTable();
//     cout << s1.lookUp("i")->getType() << endl;
//     // ScopeTable s1("1.1.1", 5);
//     // cout << s1.insert("i", "var1") << endl;
//     // cout << s1.insert("j", "var2") << endl;
//     // cout << s1.insert("k", "var3") << endl;
//     // cout << s1.insert("l", "var4") << endl;
//     // cout << s1.insert("m", "var5") << endl;
//     // cout << s1.insert("n", "var6") << endl;
//     // cout << s1.insert("o", "var7") << endl;
//     // cout << s1.insert("p", "var8") << endl;
//     // cout << s1.insert("q", "var9") << endl;
//     // cout << s1.insert("r", "var10") << endl;
//     // cout << s1.insert("s", "var11") << endl;
//     // cout << s1.insert("t", "var12") << endl;
//     // cout << s1.lookUp("i")->getType() << endl;
//     // cout << s1.lookUp("j")->getType() << endl;
//     // cout << s1.lookUp("k")->getType() << endl;
//     // cout << s1.lookUp("l")->getType() << endl;
//     // cout << s1.lookUp("m")->getType() << endl;
//     // cout << s1.lookUp("n")->getType() << endl;
//     // cout << s1.lookUp("o")->getType() << endl;
//     // cout << s1.lookUp("p")->getType() << endl;
//     // cout << s1.lookUp("q")->getType() << endl;
//     // cout << s1.lookUp("r")->getType() << endl;
//     // cout << s1.lookUp("s")->getType() << endl;
//     // cout << s1.lookUp("t")->getType() << endl;
//     // s1.print();
//     // cout << s1.Delete("i") << endl;
//     // s1.print();
//     // cout << s1.Delete("j") << endl;
//     // cout << s1.Delete("k") << endl;
//     // cout << s1.Delete("l") << endl;
//     // cout << s1.Delete("m") << endl;
//     // cout << s1.Delete("n") << endl;
//     // cout << s1.Delete("o") << endl;
//     // s1.print();
//     // s1.insert("sadi", "rabbi");
//     // s1.print();
//     // cout << s1.Delete("p") << endl;
//     // cout << s1.Delete("q") << endl;
//     // cout << s1.Delete("r") << endl;
//     // cout << s1.Delete("s") << endl;
//     // cout << s1.Delete("t") << endl;
//     // s1.print();
// }