#include <iostream>
#include <string>
#include <vector>
using namespace std;

long int find_last_prfx(string &tmp);
long int check(string const &P, string const &T);

int main()
{
    string A, B;
    cin >> A >> B;
    cout << check(A, B) << endl;
    return 0;
}

long int check(string const &P, string const &T)
{
    string temp;
    temp = P + P;

    long int res = -1;
    if (P.size() == T.size())
    {
        temp = P + P;
        res = temp.find(T, 0);
    }
    return res;
}
