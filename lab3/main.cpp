// Вариант 26

#include <iostream>
#include <ctime>
#include <utility>
#include <conio.h>
#include <cstring>
using namespace std;

struct Node 
{
    Node *next;
    int num;
    char *str;
};

class CyclicList 
{
private:
    int _count;
    bool _isEmpty;
    Node *_first;
    Node *newElement(char *s) 
    {
        Node *newElem = new Node();
        newElem->num = _count;
        newElem->next = nullptr;
        newElem->str = s;
        return newElem;
    }
    Node *getPrev(Node *first)
    {
        Node *prev = nullptr;
        Node *curr = first;
        do
        {
            prev = curr;
            curr = curr->next;
        } while (curr != first);
        return prev;
    }
    void freeElem(Node *elem) 
    {
        --_count;
        elem->next = nullptr;
        delete[] elem->str;
        delete elem;
    }
public:
    CyclicList(): _first(nullptr), _isEmpty(true), _count(0) {}
    ~CyclicList() 
    {
        if (_isEmpty) return;
        Node *curr = _first;
        do
        {
            Node *temp = curr;
            curr = curr->next;
            delete[] temp->str;
            delete temp;
        } while (curr != _first);
    }
    bool IsEmpty() { return _isEmpty; }
    int Count() { return _count; }
    void AddElem(char *s) 
    {
        Node *elem = newElement(s); 
        ++_count;
        if (_isEmpty) 
        {
            _first = elem;
            elem->next = elem;
            _isEmpty = false;
            return;
        }

        Node *current = _first;
        Node *prev = nullptr;
        do 
        {
            if (strcmp(elem->str, current->str) <= 0) 
            {
                elem->next = current;
                if (prev != nullptr) 
                {
                    prev->next = elem;
                    return;
                } 
                else if (_count == 2) // for second elem
                {
                    _first->next = elem;
                    _first = elem;
                } 
                else 
                {
                    getPrev(_first)->next = elem;
                    _first = elem;
                }
                break;
            }
            prev = current;
            current = current->next;
        } while (current != _first);

        if (prev != nullptr && strcmp(elem->str, prev->str) > 0) 
        {
            prev->next = elem;
            elem->next = _first;
        }
    }

    void PrintAll() 
    {
        if (_isEmpty) { cerr << "List is empty!" << endl; return; }
        Node *curr = _first;
        do 
        {
            cout << "" << curr->num << ": " << curr->str << endl;
            curr = curr->next;
        } while (curr != _first);
    }

    void Remove()
    {
        if (_isEmpty) { cerr << "List is empty!" << endl; return; }
        if (_count == 1) 
        { 
            cout << endl << "Successful removal " << _first->num << ": " << _first->str << endl;
            _isEmpty = true;
            freeElem(_first);
            _first = nullptr;
            return;
        } 
        Node *picked = _first;
        cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
        while (1)
        {
            Node *curr = _first;
            do 
            {
                if (curr == picked) 
                    cout << ">> " << curr->num << ": " << curr->str << " <<" << endl;
                else 
                    cout << "" << curr->num << ": " << curr->str << endl;
                curr = curr->next;
            } while (curr != _first);
            cout << "For navigate use [w / s], for removal [backspace]: ";

            char c = _getch();
            switch (c) 
            {
                case 'w':
                    picked = getPrev(picked);
                    break;
                case 's':
                    picked = picked->next;
                    break;
                case 8: // Backspace
                {
                    Node *prev = getPrev(picked);
                    if (picked == _first) _first = picked->next;
                    prev->next = picked->next;
                    cout << endl << "Successful removal " << picked->num << ": " << picked->str << endl;
                    freeElem(picked);
                    if (_count == 0) _isEmpty = true; 
                    return;
                }
                default: ;
            }
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
        }
    }

    Node *FindBySubstr(char *s) 
    {
        if (_isEmpty || s == nullptr || *s == '\0') 
            return nullptr;
        
        Node *curr = _first;
        do 
        {
            if (strstr(curr->str, s) != nullptr) 
                return curr;
            curr = curr->next;
        } while (curr != _first);

        return nullptr;
    }

    void ClearAll() 
    {
        if (_isEmpty) { cerr << "List is empty!" << endl; return; }
        Node *curr = _first->next;
        do 
        {
            Node *prev = curr;
            curr = curr->next;
            freeElem(prev);
        } while (curr != _first);
        _isEmpty = true;
        freeElem(_first);
        _first = nullptr;
        cout << "Successful deletion of all elements." << endl;
    }
};

// Generates a random string (char*) of numbers and letters (upper/lower case)
char *randStr(unsigned strSize) 
{
    char *s = new char[strSize + 1], *a = s;
    a += strSize; *a = '\0';
    for (--a; a >= s; --a) 
    {
        switch (rand() % 3) {
            case 0:
                *a = rand() % ('Z' - 'A') + 'A'; break;
            case 1:
                *a = rand() % ('0' - '9') + '0'; break;
            case 2:
                *a = rand() % ('a' - 'z') + 'a'; break;
        }
    }
    return s;
}

int enterNum(string str) 
{
    auto tryParse = [](string &i, int &o) -> bool {
        try { o = stoi(i); } 
        catch (invalid_argument) { return false; }
        return true;
    };
    int cnt = 0;
    string s;
    do
    {
        cout << str;
        getline(cin, s);
    } while (!tryParse(s, cnt));
    return cnt;
}

char *enterStr(string q) 
{
    cout << q;
    // string str;
    // getline(cin, str);
    char *s = new char[6];
    cin >> s;
    // cin.get();
    return s;
}

int main() 
{
    srand(time(NULL));
    CyclicList clist{};
    while (1) 
    {
        cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
        cout << "Welcome to singly linked circular list!" << endl
        << " [1] Add elements" << endl
        << " [2] Remove element" << endl
        << " [3] Find by substr" << endl
        << " [4] Print all elements" << endl
        << " [5] Remove all elements"<< endl
        << " [0] Exit program" << endl << endl;
        int swt = enterNum("Enter number: ");
        switch (swt) {
        case 0:
            return 0;
        case 1: {
            int cnt = enterNum("Enter count: "); 
            // char swt = 0;
            // while (swt != 'Y' && swt != 'N') {
            //     cout << "Enter the line yourself? [Y/N]: ";
            //     cin >> swt;
            // }

            for (int i = 0; i < cnt; ++i) 
            {
                clist.AddElem(
                    // swt == 'Y' ? enterStr("Enter string for element: ") : 
                    randStr(5));
            }
            break;
        }
        case 2:
            clist.Remove();
            cout << "Press any key...";
            _getch();
            break;
        case 3: {
            char *s = enterStr("Enter the sub-string you want to find: ");
            Node *res = clist.FindBySubstr(s);
            if (res != nullptr)
                cout << "Found element: " << res->num << " " << res->str << endl;
            else
                cout << "Nothing found." << endl;
            cout << "Press any key...";
            _getch();
            delete[] s;
            break;
        }
        case 4:
            clist.PrintAll(); 
            cout << "Press any key...";
            _getch();
            break;
        case 5:
            clist.ClearAll();
            cout << "Press any key...";
            _getch();
            break;
        default:
            cout << "There are no such nums." << endl;
            cout << "Press any key...";
            _getch();
            break;
        }
    }
}