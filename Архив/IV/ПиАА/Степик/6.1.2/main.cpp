#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

struct Bor
{
    map<char, int> next;
    vector<int> patternNumber;
    int suffixL;
    map<char, int> auto_move;
    int parent;
    int CompressedSuffixL;
    bool isStr;
    char symbol;
};

struct Answer
{
    int index;
    int word;
};

vector<Bor> bor;
vector<wstring> patterns;
vector<string> patterns_NR;
Bor makeBor(int parentN, char sym);
void addtoBor(const wstring &s);
void addtoBor_NR(const string &s);
int getLink(int node);
int getAM(int node, char sym);
int getCompressedLink(int node);

vector<int> ACtester (const wstring &T, vector<wstring> P);
vector<int> ACtester_UPGR (const string &P, const string &pattern, char joker);
void AC(const wstring &s);
void AC_UPGR(const string& s, vector<size_t>& count, const vector<int>& lngth);

extern vector<Bor> bor;
extern vector<wstring> patterns;
extern vector<string> patterns_NR;

Bor makeBor(int parentN, char sym)
{
    Bor borS;
    borS.next[sym] = borS.auto_move[sym] = -1;
    borS.isStr = false;
    borS.suffixL = -1;
    borS.parent = parentN;
    borS.symbol = sym;
    borS.CompressedSuffixL = -1;
    return borS;
}

void addtoBor(const wstring &s)
{
    int number = 0;
    for (size_t i=0; i<s.length(); ++i)
    {
        wchar_t sym = s[i];
        if ((bor[number].next.find(sym) == bor[number].next.end()) || (bor[number].next[sym] == -1))
        {
            bor.push_back(makeBor(number, sym));
            bor[number].next[sym] = bor.size() - 1;
        }
        number = bor[number].next[sym];
    }
    bor[number].isStr = true;
    patterns.push_back(s);
    bor[number].patternNumber.push_back(patterns.size() - 1);
}

void addtoBor_NR(const string &s)
{
    int number = 0;
    for (size_t i=0; i<s.length(); ++i)
    {
        char sym = s[i];
        if ((bor[number].next.find(sym) == bor[number].next.end()) || (bor[number].next[sym] == -1))
        {
            bor.push_back(makeBor(number, sym));
            bor[number].next[sym] = bor.size() - 1;
        }
        number = bor[number].next[sym];
    }
    bor[number].isStr = true;
    patterns_NR.push_back(s);
    bor[number].patternNumber.push_back(patterns_NR.size() - 1);
}

int getLink(int node)
{
    if (bor[node].suffixL == -1)
    {
        if (node == 0 || bor[node].parent == 0)
            bor[node].suffixL = 0;
        else
            bor[node].suffixL = getAM(getLink(bor[node].parent), bor[node].symbol);
    }
    return bor[node].suffixL;
}

int getAM(int node, char sym)
{
    if ((bor[node].auto_move.find(sym) == bor[node].auto_move.end())||(bor[node].auto_move[sym] == -1))
    {
        if ((bor[node].next.find(sym) != bor[node].next.end())&&(bor[node].next[sym] != -1))
            bor[node].auto_move[sym] = bor[node].next[sym];
        else
        {
            if (node == 0)
                bor[node].auto_move[sym] = 0;
            else
                bor[node].auto_move[sym] = getAM(getLink(node), sym);
        }
    }
    return bor[node].auto_move[sym];
}

int getCompressedLink(int node)
{
    if (bor[node].CompressedSuffixL == -1)
    {
        int link = getLink(node);
        if (link == 0)
            bor[node].CompressedSuffixL = 0;
        else
        {
            if (bor[link].isStr)
                bor[node].CompressedSuffixL = link;
            else bor[node].CompressedSuffixL = getCompressedLink(link);
        }
    }
    return bor[node].CompressedSuffixL;
}

void AC(const wstring &s)
{
    Answer answer[3000] = {};
    int u = 0;
    int k = 0;
    for(size_t i = 0; i < s.length(); i++)
    {
        k = getAM(k, s[i]);
        for(int j = k; j != 0; j = getCompressedLink(j))
            if (bor[j].isStr)
            {
                //cout << i+1 - patterns[bor[j].patternNumber[0]].length() + 1 << " " << bor[j].patternNumber[0] + 1 << endl;
                answer[u].index = i+1 - patterns[bor[j].patternNumber[0]].length() + 1;
                answer[u].word = bor[j].patternNumber[0] + 1;
                u++;
            }
    }

    std::qsort(answer, u, sizeof *answer, [](const void* a, const void* b)
        {
            Answer x1 = *static_cast<const Answer*>(a);
            Answer x2 = *static_cast<const Answer*>(b);

            if(x1.index > x2.index)
                return 1;
            else if(x1.index < x2.index)
                return -1;
            else
            {
                if(x1.word > x2.word)
                    return 1;
                else if(x1.word < x2.word)
                    return -1;
                else
                    return 0;
            }
        });
    for(int h = 0; h < u; h++)
            if(answer[h].index != 0)
                cout << answer[h].index << " " << answer[h].word << endl;
}

void AC_UPGR(const string& s,vector<size_t>& count, const vector<int>& lngth)
{
    int u = 0;
    for(size_t i = 0; i < s.length(); i++)
    {
        u = getAM(u, s[i]);
        for(int j = u; j != 0; j = getCompressedLink(j))
            if (bor[j].isStr)
                for(const auto& current: bor[j].patternNumber)
                    if((size_t)(i+1-lngth[current])<count.size())
                        count[i+1-lngth[current]]++;
    }
}

vector<int> ACtester_UPGR (const string &P, const string &pattern, char joker)
{
    vector<int> result;
    bor.push_back(makeBor(0, '$'));

    stringstream str_pat(pattern);
    vector<size_t> count(P.size(),0);

    vector<int> lenght;
    int len=0;
    string tmp;
    while(getline(str_pat, tmp, joker))
    {
        if(tmp.size()>0)
        {
            len+=tmp.size();
            lenght.push_back(len);
            addtoBor_NR(tmp);
        }
        len++;
    }

    AC_UPGR(P, count, lenght);

    for(size_t i=0; i<P.size(); i++)
        if(count[i] == patterns_NR.size())
            result.push_back(i+1);

    return result;
}

vector<int> ACtester (const wstring &T, vector<wstring> P)
{
    vector<int> answer;

    bor.clear();
    patterns.clear();

    bor.push_back(makeBor(0, '$'));
    for (auto current: P)
        addtoBor(current);

    int k = 0;
    for(size_t i = 0; i < T.length(); i++)
    {
        k = getAM(k, T[i]);
        for(int j = k; j != 0; j = getCompressedLink(j))
        {
            if (bor[j].isStr)
            {
                answer.push_back(i+1 - patterns[bor[j].patternNumber[0]].size()+1);
                answer.push_back(bor[j].patternNumber[0] + 1);
            }
        }
    }

    return answer;
}

int main()
{
    bor.push_back(makeBor(0, '$'));
    string T, temp;
    char joker;
    cin >> T;
    cin >> temp;
    cin >> joker;

    stringstream str_pat(temp);
    vector<size_t> count(T.size(),0);

    vector<int> lenght;
    int len=0;
    string tmp;
    while(getline(str_pat, tmp, joker))
    {
        if(tmp.size()>0)
        {
            len+=tmp.size();
            lenght.push_back(len);
            addtoBor_NR(tmp);
        }
        len++;
    }

    AC_UPGR(T, count, lenght);

    for(size_t i=0; i<T.size(); i++)
    {
       // cout << "i-1 = " << i-1 << endl;
      //  cout << "size = " << (temp.size()) << endl;
        if((count[i] == patterns_NR.size()) && (i-1) != (T.size()-temp.size()))
            cout << i+1 << endl;
    }

    return 0;
}