// Вариант 26

#include <iostream>
#include <ctime>
#include <utility>
#include <conio.h>
using namespace std;

const int STR_SIZE {5};

// Generates random string
char *randStr() 
{
    char *s = new char[STR_SIZE + 1], *a = s;
    a += STR_SIZE; *a = '\0';
    for (--a; a >= s; --a) 
    {
        *a = rand() % 57 + 65;
    }
    return s;
}

class CyclicList 
{
private:
    int _count;
    bool _isEmpty;
    struct Node 
    {
        Node *next;
        int num;
        char *str;
    };
    Node *_first;
    Node *newElement(char *s) 
    {
        Node *newElem = new Node();
        newElem->num = _count;
        newElem->next = nullptr;
        newElem->str = s;
        return newElem;
    }
    void freeElem(Node *elem) 
    {
        elem->next = nullptr;
        delete elem;
    }
public:
    CyclicList() { _isEmpty = true; _count = 0; _first = nullptr; }

    void AddElem() 
    {
        Node *elem = newElement(randStr()); ++_count;
        if (_isEmpty)
        {
            elem->next = nullptr;
            _first = elem;
            _isEmpty = false;
        }
        else if (_first->next == nullptr) 
        {
            _first->next = elem;
            elem->next = _first;
        }
        else
        {
            Node *curr = _first;
            while (curr->next != _first) 
            {
                curr = curr->next;
            }
            curr->next = elem;
            elem->next = _first;
        }
    }

    void PrintAll() 
    {
        if (_isEmpty) { cerr << "Empty list!" << endl; return; }
        Node *curr = _first;
        while (curr->next != _first && curr->next != nullptr) 
        {
            cout << curr->num << " " << curr->str << endl;
            curr = curr->next;
        }
        cout << curr->num << " " << curr->str << endl;
    }

    void Remove()
    {
        if (_isEmpty) { cerr << "Empty list!" << endl; return; }
        while (1) 
        {
            char c = _getch();
        }
    }

    pair<int, char*> Find(string s) 
    {
        if (_isEmpty) { cerr << "Empty list!" << endl; return make_pair(NULL, nullptr); }

    }
};

int main() 
{
    srand(time(NULL));
    CyclicList clist{};
    for (int i = 0; i < 10; i++) 
    {
        clist.AddElem();
    }
    clist.PrintAll();
    clist.Remove();
    // cout << randStr() << endl;
}