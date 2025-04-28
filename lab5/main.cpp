// Вариант 5

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

#define MAXV 200
#define MAXLEN 256

using namespace std;

struct EDGE {
    int y;          // Вершина, с которой связана текущая вершина
    int weight;     // Вес ребра (степень дружбы)
    EDGE *pnext;    // Указатель на следующее ребро
};

struct GRAPH {
    bool directed;
    int nvertices;  // Количество вершин фактическое
    int nedges;     // Количество ребер фактическое
    string *vertices;// Массив названий вершин
    int degrees[MAXV];
    EDGE *edges[MAXV];
};

void initGraph(GRAPH *g, bool directed) {
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    EDGE **edgePtr = g->edges;
    for (int i = 0; i < MAXV; ++i, ++edgePtr) *edgePtr = nullptr;
    
    int *degreePtr = g->degrees;
    for (int i = 0; i < MAXV; ++i, ++degreePtr) *degreePtr = 0;
}

// Добавление ребра в граф
void insertEdge(GRAPH *g, int x, int y, bool directed) {
    EDGE *p = new EDGE();
    p->y = y;
    p->weight = 1; // Степень дружбы (вес ребра)
    p->pnext = g->edges[x];
    g->edges[x] = p;
    g->degrees[x]++;

    if (!directed) {
        insertEdge(g, y, x, true); // Добавляем обратное ребро для неориентированного графа
    } else {
        g->nedges++;
    }
}

void reverse(int *begin, int *end) {
    while (begin < end) {
        int temp = *begin;
        *begin = *end;
        *end = temp;
        ++begin;
        --end;
    }
}

// Чтение графа из файлов
void readGraph(GRAPH *g, bool directed, char *efilename, char *vfilename) {
    initGraph(g, directed);

    ifstream f(vfilename, ios::in);
    if (!f.is_open()) { cerr << "File read error!" << endl; return; }

    for (string s; getline(f, s); ++(g->nvertices));
    f.clear();
    f.seekg(0, f.beg);
    g->vertices = new string[g->nvertices];
    string *vertexPtr = g->vertices;
    for (string s; getline(f, s); ++vertexPtr)
        *vertexPtr = s;
    f.close();

    f.open(efilename, ios::in);
    if (!f.is_open()) { cerr << "File read error!" << endl; return; }

    for (string s; getline(f, s);) 
    {
        int space = s.find(" ");
        insertEdge(
            g,
            stoi(s.substr(0, space)),                   // x
            stoi(s.substr(space + 1, s.length() - 1)),  // y
            g->directed
        );
    }
    f.close();
}

void printGraph(GRAPH *g) {
    EDGE **edgePtr = g->edges;
    string *vertexPtr = g->vertices;
    int *degreePtr = g->degrees;

    for (int i = 0; i < g->nvertices; ++i, ++edgePtr, ++vertexPtr, ++degreePtr) {
        EDGE *cur = *edgePtr;
        cout << i << " " << *vertexPtr << " - (" << *degreePtr << "): ";
        while (cur) 
        {
            cout << " " << cur->y << " " << g->vertices[cur->y];
            cur = cur->pnext;
        }
        cout << endl;
    }
}

// Поиск кратчайшего пути между двумя вершинами (поиск в ширину)
bool findShortestPath(GRAPH *g, int start, int end, int *path, int &pathLength) {
    if (start == end) {
        path[0] = start;
        pathLength = 1;
        return true;
    }

    queue<int> q;
    bool visited[MAXV] = {false};
    int parent[MAXV] = {-1};

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        EDGE *cur = g->edges[current];
        while (cur) {
            int neighbor = cur->y;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);

                if (neighbor == end) {
                    // Восстанавливаем путь
                    int node = end;
                    pathLength = 0;
                    while (node != start) {
                        path[pathLength++] = node;
                        node = parent[node];
                    }
                    path[pathLength++] = start;
                    reverse(path, path + pathLength);
                    return true;
                }
            }
            cur = cur->pnext;
        }
    }

    return false; // Путь не найден
}

int main() {
    GRAPH *g = new GRAPH;
    initGraph(g, false);

    char path_edges[] = "./edges.txt";
    char path_vertices[] = "./vertices.txt";

    readGraph(g, g->directed, path_edges, path_vertices);
    printGraph(g);
    int userVertex;
    cout << "\nEnter your vertex number: ";
    cin >> userVertex;

    int path[MAXV];
    int pathLength;
    if (findShortestPath(g, userVertex, userVertex, path, pathLength)) {
        cout << "You are a friend to yourself!" << endl;
    } else {
        cout << "You are not a friend to yourself." << endl;
    }

    // Поиск кратчайшего пути между двумя вершинами
    int start, end;
    cout << "\nEnter start vertex: ";
    cin >> start;
    cout << "Enter end vertex: ";
    cin >> end;

    if (findShortestPath(g, start, end, path, pathLength)) {
        cout << "Shortest path from " << start << " to " << end << ": ";
        for (int i = 0; i < pathLength; i++) {
            cout << path[i];
            if (i < pathLength - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found between " << start << " and " << end << "." << endl;
    }

    return 0;
}