// lab 10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <clocale>
#include <iostream>

#define MAX_NODES 400
using namespace std;

int s = 0;

// Функция для генерации случайной матрицы смежности
void generateRandomGraph(int graph[MAX_NODES][MAX_NODES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0; // Нет петель
            }
            else {
                int random_value = rand() % 2; // Генерируем 0 или 1
                graph[i][j] = random_value;
                graph[j][i] = random_value; // Граф неориентированный
            }
        }
    }
}


// Функция для поиска расстояний в графе с использованием BFS
void bfs(int graph[MAX_NODES][MAX_NODES], int n, int startNode) {
    bool visited[MAX_NODES] = { false };
    int distances[MAX_NODES] = { 0 };
    std::queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distances[i] = distances[currentNode] + 1;
            }
        }
    }

    // Выводим расстояния от startNode до всех остальных узлов
    for (int i = 0; i < n; i++) {
        if (distances[i] == 0) {
            printf("До вершины %d: No way\n", i);
        }
        else {
            printf("До вершины %d: %d\n", i, distances[i]);
        }
    }
}

// Функция для определения эксцентриситета вершины
int findEccentricity(int graph[MAX_NODES][MAX_NODES], int n, int vertex) {
    bool visited[MAX_NODES] = { false };
    int distances[MAX_NODES] = { 0 };
    std::queue<int> q;

    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distances[i] = distances[currentNode] + 1;
            }
        }
    }

    // Находим максимальное расстояние (эксцентриситет)
    int eccentricity = 0;
    for (int i = 0; i < n; i++) {
        if (distances[i] > eccentricity) {
            eccentricity = distances[i];
        }
    }

    return eccentricity;
}

// Функция для определения радиуса графа
int findRadius(int graph[MAX_NODES][MAX_NODES], int n) {
    int minEccentricity = INT_MAX;

    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if ((eccentricity < minEccentricity) && (eccentricity > 0)) {
            minEccentricity = eccentricity;
        }
    }

    return minEccentricity;
}

// Функция для определения диаметра графа
int findDiameter(int graph[MAX_NODES][MAX_NODES], int n) {
    int maxEccentricity = 0;

    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity > maxEccentricity) {
            maxEccentricity = eccentricity;
        }
    }

    return maxEccentricity;
}

// Функция для определения центральных вершин
void findCentralVertices(int graph[MAX_NODES][MAX_NODES], int n, int radius) {
    printf("Центральные вершины:\n");
    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity == radius) {
            printf("%d\n", i);
        }
    }
}

// Функция для определения периферийных вершин
void findPeripheralVertices(int graph[MAX_NODES][MAX_NODES], int n, int diameter) {
    printf("Периферийные вершины:\n");
    for (int i = 0; i < n; i++) {
        int eccentricity = findEccentricity(graph, n, i);

        if (eccentricity == diameter) {
            printf("%d\n", i);
        }
    }
}

int getOptimalPoint(int graph[MAX_NODES][MAX_NODES], int n) {
    int minSum = INT_MAX; // Изначально устанавливаем наименьшую сумму равной максимальному значению int
    int optimalPoint = -1; // Изначально устанавливаем оптимальную вершину как -1

    // Проходимся по всем вершинам графа
    for (int vertex = 0; vertex < n; vertex++) {
        int sum = 0; // Переменная для хранения суммы расстояний от текущей вершины до всех остальных

        // Проходимся по всем вершинам графа, кроме текущей вершины
        for (int otherVertex = 0; otherVertex < n; otherVertex++) {
            if (otherVertex != vertex) {
                sum += graph[vertex][otherVertex]; // Добавляем расстояние от текущей вершины до другой вершины
            }
        }

        // Если текущая сумма меньше минимальной суммы, обновляем минимальную сумму и оптимальную вершину
        if (sum < minSum) {
            minSum = sum;
            optimalPoint = vertex;
        }
    }

    return optimalPoint; // Возвращаем оптимальную вершину
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    double nDouble;
    bool go = true, goku = true;
    while (goku) {
        go = true;
        while (go) {
            cout << "Введите размер матрицы: ";
            cin >> nDouble;
            if (nDouble > 0 && double(int(nDouble)) == nDouble && nDouble < 100) {
                goku = false;
                go = false;
            }
            else {
                cout << "Ошибка!\n";
                go = false;
                cin.clear(ios_base::goodbit);
                cin.ignore(100, '\n');
            }
        }
    }
    int n = int(nDouble); 

    int graph[MAX_NODES][MAX_NODES] = { 0 };

    generateRandomGraph(graph, n);

    // Выводим матрицу смежности
    printf("Матрица смежности графа:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    int startNode;
    printf("Введите начальную для поиска расстояний(от 0 до %d): ", n - 1);
    scanf("%d", &startNode);
    int distances[MAX_NODES];
    for (int i = 0; i < n; ++i) {
        distances[i] = INT_MAX;
    }


    bfs(graph, n, startNode);
    
    if (n == 1) {
        printf("Расстояний нет \n");
    }
    else {
        int radius = findRadius(graph, n);
        int diameter = findDiameter(graph, n);
        int centr = getOptimalPoint(graph, n);
        printf("Радиус графа: %d\n", radius);
        printf("Диаметр графа: %d\n", diameter);
        printf("Центр тяжести графа: %d\n", centr);
        findCentralVertices(graph, n, radius);
        findPeripheralVertices(graph, n, diameter);
    }

    

    // Определение центральных и периферийных вершин
   

    getchar();
    getchar();
    return 0;
}
