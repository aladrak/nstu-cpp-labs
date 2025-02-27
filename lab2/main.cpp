#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <iomanip>
using namespace std;

// Generate a three-digit octal integer
int dwRand() { return (rand() % 2 ? 1 : -1) * ( (rand() % 7 + 1) * 100 + (rand() % 8) * 10 + (rand() % 8) ); }

/* Reads file lines, return pair<array, size>
   increases the capacity of the array if overflowed */
pair<int*, size_t> readFile(char *path) 
{
    ifstream f(path, ios::in);
    unsigned i = 0, cap = 1024;
    int *memloc = new int[cap];
    int *arr = memloc;
    if (f.is_open()) 
    {
        for (string s; getline(f, s); ++i, ++arr) 
        {
            if (i > cap - 1) // extend capacity
            {
                memloc = new int[cap * 2];
                arr -= i;
                copy(arr, arr + cap, memloc);
                cap *= 2;
                delete[] arr;
                arr = (memloc); 
                arr += i;
            }
            *arr = stoi(s);
        }
    }
    f.close();
    arr -= i;
    return make_pair(arr, i);
}

// Simple write to file
void writeFile(string path, int *arr, size_t size) 
{
    ofstream f(path, ios::out); unsigned i;
    if (f.is_open()) 
    {
        for (i = 0; i < size; ++i, ++arr) 
            f << *arr << endl;
    }
    arr -= i;
    f.close();
}

void GenerateDataset (char *filename, int num) 
{
    int *arr = new int[num]; unsigned i;
    for (i = 0; i < num; ++i, ++arr)
        *arr = dwRand();
    arr -= i;
    writeFile(filename, arr, num);
    delete[] arr;
}

int SortDataset (char *filename)
{
    pair<int*, size_t> dataPair = readFile(filename);
    int *arr = dataPair.first; 
    size_t size = dataPair.second;
    unsigned long comps = 0; 
    // int gaps[]{1750, 701, 301, 132, 57, 23, 10, 4, 1}; // Ciura seq
    int gaps[]{2660, 1182, 525, 233, 103, 46, 20, 9, 4, 1}; // Tokuda seq

    // Shell sort
    for (int gap : gaps) 
    {
        for (int *current = arr + gap; current < arr + size; ++current) 
        {
            int *left = current - gap;
            int *right = current;
            for (comps += 1; left >= arr && *left > *right; ++comps) 
            {
                swap(*left, *right);
                right = left;
                left -= gap;
            }
        }
    }

    string s(filename); 
    s.insert(s.find(".", 2), ".sort");
    writeFile(s, arr, size);
    delete[] arr;
    return comps;
}

void generateTable(string path, unsigned *arr, size_t size) 
{
    ofstream f(path, ios::out);
    if (f.is_open()) 
    {
        f << "   num  | " << 
        setw(11) << " Тe  | " << 
        setw(13) << " Т1  |" <<
        setw(11) << " Т2  |" <<
        setw(17) << " Тe / Т1  |" <<
        setw(12) << " Тe / Т2" << endl;
        for (double n = 8; n <= 4096; n *= 2, ++arr) 
        { 
            f << "  " << setw(4) << n << 
            "  | " << setw(6) << *arr << 
            "  | " << setw(9) << static_cast<int>(n*n) << 
            "  | " << setw(6) << n*log2(n) <<
            "  | " << setw(11) << static_cast<double>(*arr) / (n * n) <<
            "  | " << setw(9) << static_cast<double>(*arr) / (n*log2(n)) << endl;
        }
    }
    f.close();
    arr -= size; 
    delete[] arr;
}


int main() 
{
    srand(time(NULL));
    string path("./data.txt");
    unsigned *compsArr = new unsigned[10];
    int i = 0;
    for (int n = 8; n <= 4096; n *= 2, ++i, ++compsArr) 
    {
        GenerateDataset(path.data(), n);
        *compsArr = SortDataset(path.data());
        cout << n << " \telements -> " << *compsArr << endl;
    }
    compsArr -= i;
    generateTable("./table.txt", compsArr, 10);
}