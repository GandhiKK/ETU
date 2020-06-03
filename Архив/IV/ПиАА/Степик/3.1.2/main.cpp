#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define SIZE 10

struct Vertex{
    char value;
    double weight;
    char from;
};

class grph{
private:
    char *list;
    int list_size = 0;
    double **array;
public:
    grph():list(new char[SIZE]){
        array = new double*[SIZE];
        for(int i = 0; i < SIZE; i++)
            array[i] = new double[SIZE]();
    }
    size_t find_min(vector <Vertex> &arr, size_t T){
        size_t min = 0;
        for(size_t i = 0; i < arr.size(); i++)
        {
            if(arr[i].weight + abs(arr[i].value - list[T]) < arr[min].weight + abs(arr[min].value - list[T]))
                min	= i;
            if(arr[i].weight + abs(arr[i].value - list[T]) == arr[min].weight + abs(arr[min].value - list[T]))
                if(abs(arr[i].value - list[T]) <  abs(arr[min].value - list[T]))
                    min = i;
        }
        return min;
    }
    void find_way(char S, char T, stack <char> &path)
    {
        vector <Vertex> arr_wait;
        vector <Vertex> arr_past;
        arr_wait.push_back({list[S], 0, 0});
        Vertex X, Y;
        while(!arr_wait.empty()){
            vector <Vertex>::iterator it = arr_wait.begin();
            char min = find_min(arr_wait, T);
            advance(it, min);
            X = arr_wait.at(min);
            arr_wait.erase(it);
            arr_past.push_back(X);
            if(X.value == list[T])
                break;
            for(int i = 0; i < list_size; i++){
                char index_x = find_vertex(X.value);
                if(array[index_x][i] != 0){
                    Y = {list[i], array[index_x][i] + X.weight, X.value};
                    if(is_in_array(Y.value, arr_past))
                        continue;
                    if(!is_in_array(Y.value, arr_wait))
                        arr_wait.push_back(Y);
                    else{
                        Vertex &old_Y = arr_wait[is_I_in_array(Y.value, arr_wait)];
                        if(Y.weight < old_Y.weight){
                            old_Y.weight = Y.weight;
                            old_Y.from = Y.from;
                        }
                    }
                }
            }
        }
        if(!is_in_array(list[T], arr_past))
            return;
        Vertex *ptr = &X;
        while(ptr->value != list[S]){
            path.push(ptr->value);
            ptr = &arr_past[is_I_in_array(ptr->from, arr_past)];
        }
        path.push(ptr->value);
    }
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
    bool is_in_array(char c, vector <Vertex> &arr){
        for(unsigned int i = 0; i < arr.size(); i++)
            if(arr[i].value == c)
                return 1;
        return 0;
    };
    int is_I_in_array(char c, vector <Vertex> &arr){
        for(size_t i = 0; i < arr.size(); i++)
            if(arr[i].value == c)
                return i;
        return 0;
    };
};

int main(){
    grph graph;
    char S, T;
    cin >> S >> T;
    char from, to;
    double weight;
    while(cin >> from >> to >> weight){
        if(from == ' ')
            break;
        graph.push(from, to, weight);
    }
    stack <char> path;
    graph.find_way(graph.find_vertex(S), graph.find_vertex(T), path);
    while(!path.empty()){
        cout << path.top();
        path.pop();
    }
    cout << endl;
    return 0;
}

/*
a e
a b 3.0
b c 1.0
c d 1.0
a d 5.0
d e 1.0
*/