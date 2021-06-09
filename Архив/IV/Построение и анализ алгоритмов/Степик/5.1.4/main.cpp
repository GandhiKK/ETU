#include <iostream>
#include <string>
#include <vector>
using namespace std;

void prefixFunction(string &str, vector<long int> &P_vector);
void KMP(string &T, string &P, vector<long int> &P_vector);

int main()
{
    string T, P;
    cin >> P >> T;
    vector<long int> P_vector;
    KMP(T, P, P_vector);
    if (!P_vector.empty())
    {
        for (unsigned int i = 0; i < P_vector.size() - 1; i++)
            cout << P_vector[i] << ',';
        cout << P_vector[P_vector.size() - 1] << endl;
        return 0;
    }
    cout << "-1" << endl;
    return 0;
}

void prefixFunction(string &str, vector<long int> &PI)
{
    size_t size = str.size();
    for (size_t i = 1; i < size; i++)
    {
        size_t j = PI[i - 1];
        while (j > 0 && str[i] != str[j])
            j = PI[j - 1];
        if (str[i] == str[j])
            j++;
        PI[i] = j;
    }
}

void KMP(string &T, string &P, vector<long int> &P_vector)
{
    string str = P + ' ' + T;
    vector<long int> PI(str.size(), 0);
    prefixFunction(str, PI);
    for (unsigned int i = P.size() + 1; i < str.size(); i++)
            if (PI[i] == P.size())
                P_vector.push_back(i - 2 * P.size());
}
