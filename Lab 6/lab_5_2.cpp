#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void computingFollow(char c, vector<string> &cfg, map<char, set<char>> &first, map<char, set<char>> &follow)
{
    for (int i = 0; i < cfg.size(); i++)
    {
        for (int j = 1; j < cfg[i].size(); j++)
        {
            if (cfg[i][j] == c)
            {
                for (int k = j + 1; k <= cfg[i].size(); k++)
                {
                    bool flag = false;
                    if (k < cfg[i].size())
                    {
                        if (cfg[i][k] <= 'Z' && cfg[i][k] >= 'A')
                        {
                            for (auto it:first[cfg[i][k]])
                            {
                                if (it!= '~')
                                {
                                        follow[c].insert(it);
                                }
                                else
                                    flag = true;
                            }
                        }
                        else
                        {
                                follow[c].insert(cfg[i][k]);
                            break;
                        }
                    }
                    else
                    {
                        if (cfg[i][0] == c)
                            break;
                        if (follow[cfg[i][0]].empty())
                            computingFollow(cfg[i][0], cfg, first, follow);
                        for (auto it: follow[cfg[i][0]])
                        {
                                follow[c].insert(it);
                        }
                    }
                    if (!flag)
                        break;
                }
            }
        }
    }
}

void computingFirst(char c, vector<string> &cfg, map<char, set<char>> &first)
{
    if (!(c <= 'Z' and c >= 'A'))
    {
            first[c].insert(c);
            return;
    }
    for (int i = 0; i < cfg.size(); i++)
    {
        if (cfg[i][0] == c)
        {
            for (int j = 1; j < cfg[i].size(); j++)
            {
                if (cfg[i][j] == c)
                {
                    break;
                }
                bool flag = false;
                if (first[cfg[i][j]].empty())
                    computingFirst(cfg[i][j], cfg, first);
                for (auto it : first[cfg[i][j]])
                {
                    if (it != '~')
                    {
                            first[c].insert(it);
                    }
                    else if (j == cfg[i].size() - 1)
                    {
                            first[c].insert('~');
                    }
                    else
                        flag = true;
                }
                if (!flag)
                    break;
            }
        }
    }
}
int main()
{
    cout<<"Mohd Siddiqul Haque 21bcs037"<<endl;
    ifstream myfile("cfg.txt", ios::in);
    string line;
    vector<string> cfg;
    while (getline(myfile, line))
    {
        string temp = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] != ' ' and line[i]!='-' and line[i]!='>')
            {
                temp += line[i];
            }
        }
        cfg.push_back(temp);
    }
    char s = cfg[0][0];
    map<char, set<char>> first;
    map<char, set<char>> follow;
    follow[s].insert('$');
    for (int i = 0; i < cfg.size(); i++)
    {
        for (int j = 0; j < cfg[i].size(); j++)
        {
            computingFirst(cfg[i][0], cfg, first);
        }
    }
    for (int i = 0; i < cfg.size(); i++)
    {
        for (int j = 0; j < cfg[i].size(); j++)
        {
            computingFollow(cfg[i][0], cfg, first, follow);
        }
    }
    cout<<"---------------First-------------"<<endl;
    for (auto it : first)
    {
        if ((it.first <= 'Z' and it.first >= 'A'))
        {   
            cout<<it.first<<" - { ";
            for (auto i : it.second)
            {
                cout << "'" << i << "' ";
            }
            cout<<" }";
            cout<< endl;
        }
    }
    cout << endl
         << endl;
         cout<<"-------------Follow-------------"<<endl;
    for (auto it : follow)
    {
        cout<<it.first<<" - { ";
        for (auto i : it.second)
        {
            cout << "'" << i << "' ";
        }
        cout << " }" << endl;
    }
    return 0;
}