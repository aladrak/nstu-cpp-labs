// Вариант 9
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <utility>
using namespace std;

int dwRand() { return (rand() % 7 + 1) * 100 + (rand() % 8) * 10 + (rand() % 8); }

pair<int*, int> readFile(char *path) 
{
    ifstream f(path, ios::in);
    int i = 0, cap = 1024;
    int *memloc = new int[cap];
    int *arr = memloc;
    if (f.is_open()) 
    {
        for (string s; getline(f, s); ++i) 
        {
            if (i > cap - 1) // extend capacity
            {
                memloc = new int[cap * 2];
                copy(arr, arr + cap, memloc);
                cap *= 2;
                delete[] arr;
                arr = (memloc);
            }
            *(arr + i) = stoi(s);
        }
    }
    f.close();
    return make_pair(arr, i);
}

void writeFile(string path, int *arr, size_t size) 
{
    ofstream f(path, ios::out);
    if (f.is_open()) 
    {
        for (int i = 0; i < size; ++i) 
        {
            f << *(arr + i) << endl;
        }
    }
    f.close();
}

void GenerateDataset (char *filename, int num) 
{
    ofstream f(filename, ios::out);
    if (f.is_open()) 
    {
        for (int i = 0; i < num; ++i) 
        {
            f << dwRand() << endl;
        }
    }
    f.close();
}

int SortDataset (char *filename)
{
    pair<int*, int> dataPair = readFile(filename);
    int *arr = dataPair.first, comps = 0; 
    size_t size = dataPair.second;
    int *gaps = new int[]{1, 4, 10, 23, 57, 132, 301, 701};

    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && arr[j] > arr[j + s]; j -= s) {
                comps++;
                swap(arr[j], arr[j + s]);
            }
        }
    }

    // for (int gap = size/2; gap > 0; gap /= 2)
    // {
    //     for (int i = gap; i < size; i += 1)
    //     {
    //         int temp = arr[i];
    //         int j;            
    //         for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
    //         {
    //             arr[j] = arr[j - gap];
    //             comps++;
    //         }
    //         arr[j] = temp;
    //     }
    // }

    string s(filename); 
    s.insert(s.find(".", 2), ".sort");
    writeFile(s, arr, size);
    delete[] arr;
    return comps;
}


int main() 
{
    srand(time(NULL));
    string path("./data.txt");
    GenerateDataset(path.data(), 1033);
    cout << "Shell sort" << endl <<
    "Compare count: \t" << SortDataset(path.data()) << endl;
}