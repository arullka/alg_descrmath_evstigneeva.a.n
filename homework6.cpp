#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace std;

//задание 3
vector<pair<int, int>> findOutArcs(
    string repr, int v, int n, int m,
    vector<vector<int>>& matrSmezh,
    vector<vector<int>>& matrInc,
    vector<vector<int>>& spisokSmezh,
    vector<pair<int, int>>& spisokDug,
    vector<int>& nachalo)
{
    vector<pair<int, int>> result;

    if (repr == "matrSmezh") 
    {
        for (int j = 0; j < n; j++) 
        {
            if (matrSmezh[v][j] == 1) 
            {
                result.push_back({v, j});
            }
        }
    }
    else if (repr == "matrInc") 
    {
        for (int e = 0; e < m; e++) 
        {
            if (matrInc[v][e] == 1) 
            {
                for (int u = 0; u < n; u++) 
                {
                    if (matrInc[u][e] == -1) 
                    {
                        result.push_back({v, u});
                        break;
                    }
                }
            }
        }
    }
    else if (repr == "spisokSmezh") 
    {
        for (int i = 0; i < spisokSmezh[v].size(); i++) 
        {
            result.push_back({v, spisokSmezh[v][i]});
        }
    }
    else if (repr == "spisokDug") 
    {
        for (int i = 0; i < spisokDug.size(); i++) 
        {
            if (spisokDug[i].first == v) 
            {
                result.push_back(spisokDug[i]);
            }
        }
    }
    else if (repr == "uporSpisokDug") {
        for (int k = nachalo[v]; k < nachalo[v + 1]; k++) 
        {
            result.push_back(spisokDug[k]);
        }
    }

    return result;
}

//задание 4
void convertGraph(
    string from, string to, int n, int m,
    vector<vector<int>>& matrSmezh,
    vector<vector<int>>& matrInc,
    vector<vector<int>>& spisokSmezh,
    vector<pair<int, int>>& spisokDug)
{
    vector<pair<int, int>> dugi;

    if (from == "matrSmezh") 
    {
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (matrSmezh[i][j] == 1) 
                {
                    dugi.push_back({i, j});
                }
            }
        }
    }
    else if (from == "matrInc") 
    {
        for (int e = 0; e < m; e++) 
        {
            int otkuda = -1, kuda = -1;
            for (int i = 0; i < n; i++) 
            {
                if (matrInc[i][e] == 1)
                {
                    otkuda = i;
                }
                if (matrInc[i][e] == -1)
                {
                    kuda = i;
                }
            }
            dugi.push_back({otkuda, kuda});
        }
    }
    else if (from == "spisokSmezh") 
    {
        for (int i = 0; i < n; i++) 
        {
            for (int k = 0; k < spisokSmezh[i].size(); k++) 
            {
                dugi.push_back({i, spisokSmezh[i][k]});
            }
        }
    }
    else if (from == "spisokDug") 
    {
        dugi = spisokDug;
    }

    if (to == "matrSmezh") 
    {
        vector<vector<int>> novaya(n, vector<int>(n, 0));
        for (int i = 0; i < dugi.size(); i++) 
        {
            novaya[dugi[i].first][dugi[i].second] = 1;
        }
        cout << "матрица смежности:" << endl;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                cout << novaya[i][j] << " ";
            }
            cout << endl;
        }
    }
    else if (to == "spisokSmezh") 
    {
        vector<vector<int>> novyi(n);
        for (int i = 0; i < dugi.size(); i++) 
        {
            novyi[dugi[i].first].push_back(dugi[i].second);
        }
        cout << "список смежности:" << endl;
        for (int i = 0; i < n; i++) 
        {
            cout << i << ": ";
            for (int k = 0; k < novyi[i].size(); k++) 
            {
                cout << novyi[i][k] << " ";
            }
            cout << endl;
        }
    }
    else if (to == "matrInc") {
        int chisloDug = dugi.size();
        vector<vector<int>> novaya(n, vector<int>(chisloDug, 0));
        for (int e = 0; e < chisloDug; e++) 
        {
            novaya[dugi[e].first][e] = 1;
            novaya[dugi[e].second][e] = -1;
        }
        cout << "матрица инцидентности:" << endl;
        for (int i = 0; i < n; i++) 
        {
            for (int e = 0; e < chisloDug; e++) 
            {
                if (novaya[i][e] >= 0)
                {
                    cout << " ";
                }
                cout << novaya[i][e] << " ";
            }
            cout << endl;
        }
    }
    else if (to == "spisokDug") 
    {
        cout << "список дуг:" << endl;
        for (int i = 0; i < dugi.size(); i++) 
        {
            cout << "(" << dugi[i].first << "," << dugi[i].second << ") ";
        }
        cout << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    //задание 2
    int n = 5;
    int m = 8;
    //а)матрица смежности
    vector<vector<int>> matrSmezh = {
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    };

    //б)матрица инцидентности
    vector<vector<int>> matrInc = {
        {+1, +1, +1,  0,  0,  0,  0,  0},
        {-1,  0,  0, +1, +1, +1,  0,  0},
        { 0,  0, -1,  0, -1,  0,  0, -1},
        { 0,  0,  0,  0,  0, -1, -1, +1},
        { 0, -1,  0, -1,  0,  0, +1,  0}
    };

    //в)список смежности
    vector<vector<int>> spisokSmezh = {
        {1, 4, 2},
        {4, 3, 2},
        {},
        {2},
        {3}
    };

    //г)список дуг
    vector<pair<int, int>> spisokDug = {
        {0,1}, {0,2}, {0,4},
        {1,2}, {1,3}, {1,4},
        {3,2}, {4,3}
    };

    //д)упорядоченный список дуг(spisokDug + nachalo)
    vector<int> nachalo = { 0, 3, 6, 6, 7, 8 };


    //тест задания 3
    cout << "задание3" << endl;

    vector<pair<int, int>> result;

    result = findOutArcs("matrSmezh", 0, n, m, matrSmezh, matrInc, spisokSmezh, spisokDug, nachalo);
    cout << "из вершины 0 матрицы смежности:";
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" << result[i].first << "," << result[i].second << ") ";
    }
    cout << endl;

    result = findOutArcs("matrInc", 1, n, m, matrSmezh, matrInc, spisokSmezh, spisokDug, nachalo);
    cout << "из вершины 1 матрицы инцидентности:";
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" << result[i].first << "," << result[i].second << ") ";
    }
    cout << endl;

    result = findOutArcs("spisokSmezh", 1, n, m, matrSmezh, matrInc, spisokSmezh, spisokDug, nachalo);
    cout << "из вершины 1 списка смежности:";
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" << result[i].first << "," << result[i].second << ") ";
    }
    cout << endl;

    result = findOutArcs("spisokDug", 3, n, m, matrSmezh, matrInc, spisokSmezh, spisokDug, nachalo);
    cout << "из вершины 3 списка дуг:";
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" << result[i].first << "," << result[i].second << ") ";
    }
    cout << endl;

    result = findOutArcs("uporSpisokDug", 4, n, m, matrSmezh, matrInc, spisokSmezh, spisokDug, nachalo);
    cout << "из вершины 4 упорядоченного списка дуг:";
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" << result[i].first << "," << result[i].second << ") ";
    }
    cout << endl;

    //тест задания 4
    cout << endl << "задание4" << endl;

    cout << endl << "список дуг -> матрица смежности" << endl;
    convertGraph("spisokDug", "matrSmezh", n, m, matrSmezh, matrInc, spisokSmezh, spisokDug);

    cout << endl << "матрица смежности -> список смежности" << endl;
    convertGraph("matrSmezh", "spisokSmezh", n, m, matrSmezh, matrInc, spisokSmezh, spisokDug);

    cout << endl << "список смежности -> матрица инцидентности" << endl;
    convertGraph("spisokSmezh", "matrInc", n, m, matrSmezh, matrInc, spisokSmezh, spisokDug);

    cout << endl << "матрица инцидентности -> список дуг" << endl;
    convertGraph("matrInc", "spisokDug", n, m, matrSmezh, matrInc, spisokSmezh, spisokDug);

}

