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
    int y;
    EDGE *pnext;
};

struct GRAPH {
    bool directed;
    int nvertices;      // Количество вершин
    int nedges;         // Количество рёбер
    string *vertices;   // Названия вершин
    int degrees[MAXV];  // Степени вершин
    EDGE *edges[MAXV];  // Список смежности
};

void initGraph(GRAPH *g, bool directed) {
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (int i = 0; i < MAXV; ++i) {
        g->edges[i] = nullptr;
        g->degrees[i] = 0;
    }
}

void insertEdge(GRAPH *g, int x, int y, bool directed) {
    EDGE *p = new EDGE();
    p->y = y;
    p->pnext = g->edges[x];
    g->edges[x] = p;
    g->degrees[x]++;

    if (!directed) {
        insertEdge(g, y, x, true);
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

void readGraph(GRAPH *g, bool directed, const char *efilename, const char *vfilename) {
    initGraph(g, directed);

    ifstream vf(vfilename);
    if (!vf.is_open()) {
        cerr << "Read error!" << endl;
        return;
    }

    for (string s; getline(vf, s); ++g->nvertices);
    vf.clear();
    vf.seekg(0);
    g->vertices = new string[g->nvertices];

    for (int i = 0; i < g->nvertices; ++i) {
        getline(vf, g->vertices[i]);
    }
    vf.close();

    ifstream ef(efilename);
    if (!ef.is_open()) {
        cerr << "Read error!" << endl;
        return;
    }

    string s;
    while (getline(ef, s)) {
        int space = s.find(" ");
        int x = stoi(s.substr(0, space));
        int y = stoi(s.substr(space + 1));
        insertEdge(g, x, y, g->directed);
    }
    ef.close();
}

void printGraph(GRAPH *g) {
    cout << "Graph:" << endl;
    for (int i = 0; i < g->nvertices; ++i) {
        cout << i << ": " << g->vertices[i] << " -> ";
        EDGE *curr = g->edges[i];
        while (curr) {
            cout << curr->y << " ";
            curr = curr->pnext;
        }
        cout << endl;
    }
}

bool hasSelfLoop(GRAPH *g, int vertex) {
    EDGE *e = g->edges[vertex];
    while (e != nullptr) {
        if (e->y == vertex)
            return true;
        e = e->pnext;
    }
    return false;
}

bool findShortestPath(GRAPH *g, int start, int end, int *path, int &pathLength) {
    if (start == end) {
        path[0] = start;
        pathLength = 1;
        return true;
    }

    bool visited[MAXV] = {false};
    int parent[MAXV] = {-1};
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front(); q.pop();

        EDGE *e = g->edges[current];
        while (e != nullptr) {
            int neighbor = e->y;

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);

                if (neighbor == end) {
                    pathLength = 0;
                    int node = end;
                    while (node != start) {
                        path[pathLength++] = node;
                        node = parent[node];
                    }
                    path[pathLength++] = start;
                    reverse(path, path + pathLength);
                    return true;
                }
            }
            e = e->pnext;
        }
    }

    return false;
}

int main() {
    GRAPH *g = new GRAPH;
    initGraph(g, false);

    const char *efilename = "./edges.txt";
    const char *vfilename = "./vertices.txt";

    readGraph(g, false, efilename, vfilename);
    printGraph(g);

    int userVertex;
    cout << "\nEnter your vertex number: ";
    cin >> userVertex;

    int path[MAXV];
    int pathLength = 0;

    if (hasSelfLoop(g, userVertex)) {
        cout << "Yes, you are a friend to yourself (direct self-loop)." << endl;
    }
    else if (findShortestPath(g, userVertex, userVertex, path, pathLength) && pathLength > 1) {
        cout << "Yes, you are a friend to yourself through others:" << endl;
        for (int i = 0; i < pathLength; ++i) {
            cout << g->vertices[path[i]];
            if (i < pathLength - 1) cout << " -> ";
        }
        cout << endl;
    }
    else {
        cout << "No, you are not a friend to yourself." << endl;
        cout << "There is no loop or connection to yourself." << endl;
    }

    int start, end;
    cout << "\nEnter the starting vertex: ";
    cin >> start;
    cout << "Enter the ending vertex: ";
    cin >> end;

    if (findShortestPath(g, start, end, path, pathLength)) {
        cout << "The shortest path from " << start << " to " << end << ": ";
        for (int i = 0; i < pathLength; ++i) {
            cout << g->vertices[path[i]];
            if (i < pathLength - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found between " << start << " and " << end << "." << endl;
    }

    delete g;
}