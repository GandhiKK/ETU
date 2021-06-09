#include<iostream>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

struct AAStack{
    int y, high;
}   stack[55];

struct AASolution{
    int len;
    int x, y;
}   temp[2505], solution[2505];

bool a[55][55];
int r[55][55], d[55][55];
int width = 300;
int M = 20;
int f[2505];
int N;

void backtracking(int x, int y, int sum, int S);
int solver(int);

int main()
{
    int yy = 0;
    cin >> yy;
    solver(yy);
    return 0;
}

void backtracking(int x, int y, int sum, int S)
{
    if (sum + f[S] >= M)
        return;
    if (x<N){
        int tot = 0;
        for (int i = 1; i <= N; ++i)
            if (a[x + 1][i])
                i += r[x + 1][i];
            else{
                while (i<N && !a[x + 1][i])
                    ++i;
                ++tot;
            }
            if (sum + tot >= M)
                return;
    }
    if (x>N){
        M = sum;
        memcpy(solution, temp, sizeof(AASolution)*M);
        return;
    }
    else if (y>N){
        int i, top = 0, tot = 0, mid, s = 0, temp;
        x++;
        if (x <= N){
            for (i = 1; i <= N; ++i)
                if (!a[x][i]){
                    while (i < N && !a[x][i + 1]){
                        i++;
                        struct AAStack n;
                        n.y = i;
                        n.high = 0;
                        stack[top++] = n;
                    }
                }
                else{
                    if (top&&stack[top - 1].high <= d[x][i]){
                        mid = stack[--top].high;
                        if (top)
                            while (top&&stack[top - 1].high <= d[x][i]){
                                top--;
                                if (i - stack[top].y - 1 <= stack[top].high - mid)
                                    temp = (stack[top].high - mid) / (i - stack[top].y - 1);
                                else
                                    temp = 0;
                                tot += temp;
                                s += (stack[top].high - mid)*(i - stack[top].y - 1) - temp * (i - stack[top].y - 1)*(i - stack[top].y - 1);
                                mid = stack[top].high;
                            }
                        else if (d[x][i] != mid){
                                if (i - 1 <= d[x][i] - mid)
                                    temp = (d[x][i] - mid) / (i - 1);
                                else
                                    temp = 0;
                                tot += temp;
                                s += (d[x][i] - mid)*(i - 1) - temp * (i - 1)*(i - 1);
                            }
                    }
                    struct AAStack n;
                    n.y = i + r[x][i] - 1;
                    n.high = d[x][i];
                    stack[top++] = n;
                    i += r[x][i] - 1;
                }
                mid = stack[top - 1].high;
                if (top){
                    while(--top)
                        s += (stack[top].y - stack[top - 1].y)*(N - (x + stack[top].high - 1));
                    s += stack[top].y*(N - (x + stack[top].high - 1));
                }
                else
                    if (N != x + mid - 1)
                        tot += N / (N - (x + mid - 1));
                if (sum + tot + f[s] >= M)
                    return;
        }
        backtracking(x, 1, sum, S);
    }
    else if (a[x][y])
        backtracking(x, y + r[x][y], sum, S);
        else{
            int i = y;
            while (i - y + 2<N && i<N && i<N - x + y && !a[x][i + 1])
                ++i;
            int j, len = i - y + 1;
            for (i = 0; i<len; ++i)
                for (j = 0; j<len; ++j)
                    a[x + i][y + j] = 1;
            for (; len; --len){
                r[x + len][y] = 0;
                for (i = 0; i<len; ++i)
                    r[x + i][y] = len;
                for (i = 0; i <= len; ++i)
                    d[x + i][y] = len - i;
                struct AASolution n;
                n.len = len;
                n.x = x;
                n.y = y;
                temp[sum] = n;
                backtracking(x, y + len, sum + 1, S - len * len);
                for (i = 0; i<len; ++i)
                    a[x + len - 1][y + i] = 0;
                for (i = 0; i<len; ++i)
                    a[x + i][y + len - 1] = 0;
            }
        }
}

int solver(int t){
    memset(f, 127, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= 2500; i++){
        for (int j = 1; j*j <= i; j++)
            f[i] = min(f[i], f[i - j * j]);
        f[i]++;
    }
    M = 20;
    N = t;
    memset(a, 0, sizeof(a));
    backtracking(1, 1, 0, N*N);
    cout << M << endl;
    for (int i = 0; i < M; i++)
        cout << solution[i].x << " " << solution[i].y << " " << solution[i].len << endl;
    return 0;
}