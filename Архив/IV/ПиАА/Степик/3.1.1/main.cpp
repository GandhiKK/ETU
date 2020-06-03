#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define SIZE 10

class grph{
private:
    char *list;
    bool *check;
    int list_size = 0;
    double **array;
public:
    grph():list(new char[SIZE]), check(new bool[SIZE]()){
        array = new double*[SIZE];
        for(int i = 0; i < SIZE; i++)
            array[i] = new double[SIZE]();
    }

    bool find_min(int ver, int &min){
        min = -1;
        for(int i = 0; i < list_size; i++)
            if(array[ver][i] && !check[i]){
                min = i;
                break;
            }
        if(min == -1)
            return 0;
        for(int i = 0; i < list_size; i++)
            if(array[ver][i] && !check[i] && array[ver][i] < array[ver][min] && array[ver][i] != array[ver][min])
                min = i;
        check[min] = 1;
        return 1;
    }

    int find_path(int S, int T, deque<char>&path){
        path.push_back(list[S]);
        if(S == T)
            return -1;
        int min;
        int result;
        while(find_min(S, min)){
            result = find_path(min, T, path);
            if(result == -1)
                return -1;
            path.pop_back();
        }
        return 0;
    };

    void push(char key, char value, float weight){
        int k = find_vertex(key);
        int v = find_vertex(value);
        array[k][v] = weight;
    }

    int find_vertex(char litter){
        for(int i = 0; i < list_size; i++)
            if(list[i] == litter)
                return i;
        int new_size = add_vertex(litter);
        return new_size;
    }

    int add_vertex(char litter){
        resize();
        list[list_size] = litter;
        return list_size++;
    }

    void resize(){
        if(list_size%SIZE != 0 || !list_size)
            return;
        char *new_list = new char[list_size + SIZE];
        for(int i = 0; i < list_size; i++)
            new_list[i] = list[i];
        delete [] list;
        list = new_list;
        bool *new_check = new bool[list_size + SIZE]();
        for(int i = 0; i < list_size; i++)
            new_check[i] = check[i];
        delete [] check;
        check = new_check;
        double **new_array = new double*[list_size + SIZE];
        for(int i = 0; i < list_size + SIZE; i++)
            new_array[i] = new double[list_size + SIZE]();
        for(int i = 0; i < list_size; i++){
            for(int j = 0; j < list_size; j++)
                new_array[i][j] = array[i][j];
            delete [] array[i];
        }
        delete [] array;
        array = new_array;
    };
};

int main(){
    grph graph;
    deque <char> path; //двусторонняя очередь
    char S, T;
    cin >> S >> T;
    char from, to;
    float weight;
    while(cin >> from >> to >> weight){
        if(from == ' ')
            break;
        graph.push(from, to, weight);
    }
    if(!graph.find_path(graph.find_vertex(S), graph.find_vertex(T), path))
        return 0;
    else{
        while(!path.empty()){
            cout << path.front();
        path.pop_front();
        }
    }
    return 0;
}