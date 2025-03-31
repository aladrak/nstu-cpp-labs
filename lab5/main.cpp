// Вариант 5

#include <iostream>
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
    char** vertices;// Массив названий вершин
    int degrees[MAXV];
    EDGE* edges[MAXV];
};

// Инициализация графа
void initGraph(GRAPH *g, bool directed) {
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    EDGE **edgePtr = g->edges;
    for (int i = 0; i < MAXV; ++i, ++edgePtr) {
        *edgePtr = nullptr;
    }

    int *degreePtr = g->degrees;
    for (int i = 0; i < MAXV; ++i, ++degreePtr) {
        *degreePtr = 0;
    }
}

// Добавление ребра в граф
void insertEdge(GRAPH *g, int x, int y, bool directed) {
    EDGE *p = (EDGE *)malloc(sizeof(EDGE));
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

    FILE *fp;
    fp = fopen(vfilename, "r");
    if (fp == NULL) 
    {
        printf("Error while opening vertices file\n");
        return;
    }

    char buffer[MAXLEN];
    while (fgets(buffer, MAXLEN, fp)) g->nvertices++;
    fseek(fp, 0L, SEEK_SET);

    g->vertices = new char*[g->nvertices];
    char **vertexPtr = g->vertices;
    while (fgets(buffer, MAXLEN, fp)) 
    {
        *vertexPtr = new char[MAXLEN];
        sscanf(buffer, "%s", *vertexPtr);
        vertexPtr++;
    }
    fclose(fp);

    fp = fopen(efilename, "r");
    if (fp == NULL) 
    {
        printf("Error while opening edges file\n");
        return;
    }

    int m = 0;
    while (fgets(buffer, MAXLEN, fp)) m++;
    fseek(fp, 0L, SEEK_SET);

    for (int i = 0; i < m; i++) 
    {
        int x, y;
        fscanf(fp, "%d %d", &x, &y);
        insertEdge(g, x, y, g->directed);
    }
    fclose(fp);
}

void printGraph(GRAPH *g) {
    EDGE **edgePtr = g->edges;
    char **vertexPtr = g->vertices;
    int *degreePtr = g->degrees;

    for (int i = 0; i < g->nvertices; ++i, ++edgePtr, ++vertexPtr, ++degreePtr) {
        EDGE *cur = *edgePtr;
        printf("%d %s - (%d): ", i, *vertexPtr, *degreePtr);
        while (cur) 
        {
            printf(" %d %s", cur->y, g->vertices[cur->y]);
            cur = cur->pnext;
        }
        printf("\n");
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

    char filename_edges[] = "./edges.txt";
    char filename_vertices[] = "./vertices.txt";

    readGraph(g, g->directed, filename_edges, filename_vertices);
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