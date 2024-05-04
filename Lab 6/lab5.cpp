#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void computingFollow(char c, vector<string> &cfg, map<char, string> &first, map<char, string> &follow)
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
                            for (int l = 0; l < first[cfg[i][k]].size(); l++)
                            {
                                if (first[cfg[i][k]][l] != '#')
                                {
                                    if (follow[c].find(first[cfg[i][k]][l]) >= follow[c].size())
                                        follow[c].push_back(first[cfg[i][k]][l]);
                                }
                                else
                                    flag = true;
                            }
                        }
                        else
                        {
                            if (follow[c].find(cfg[i][k]) >= follow[c].size())
                                follow[c].push_back(cfg[i][k]);
                            break;
                        }
                    }
                    else
                    {
                        if (cfg[i][0] == c)
                            break;
                        if (follow[cfg[i][0]].empty())
                            computingFollow(cfg[i][0], cfg, first, follow);
                        for (int l = 0; l < follow[cfg[i][0]].size(); l++)
                        {
                            if (follow[c].find(follow[cfg[i][0]][l]) >= follow[c].size())
                                follow[c].push_back(follow[cfg[i][0]][l]);
                        }
                    }
                    if (!flag)
                        break;
                }
            }
        }
    }
}

void computingFirst(char c, vector<string> &cfg, map<char, string> &first)
{
    if (!(c <= 'Z' and c >= 'A'))
    {
        if (first[c].find(c) >= first[c].size())
            first[c].push_back(c);
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
                for (int k = 0; k < first[cfg[i][j]].size(); k++)
                {
                    if (first[cfg[i][j]][k] != '#')
                    {
                        if (first[c].find(first[cfg[i][j]][k]) >= first[c].size())
                            first[c].push_back(first[cfg[i][j]][k]);
                    }
                    else if (j == cfg[i].size() - 1)
                    {
                        if (first[c].find('#') >= first[c].size())
                            first[c].push_back('#');
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
    ifstream myfile("cfg1.txt", ios::in);
    int curr_line = 0;
    string line;
    vector<string> cfg;
    while (getline(myfile, line))
    {
        string temp = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] != ' ')
            {
                temp += line[i];
            }
        }
        cfg.push_back(temp);
    }
    char s = cfg[0][0];
    map<char, string> first;
    map<char, string> follow;
    follow[s].push_back('$');
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
    for (auto it : first)
    {
        if ((it.first <= 'Z' and it.first >= 'A'))
        {
            cout << "First(" << it.first << ") :  { ";
            int j = 0;
            for (auto i : it.second)
            {
                cout << "'" << i << "'";
                if (j < it.second.size() - 1)
                    cout << " , ";
                j++;
            }
            cout << " }" << endl;
        }
    }
    cout << endl
         << endl;
    for (auto it : follow)
    {
        cout << "Follow(" << it.first << ") :  { ";
        int j = 0;
        for (auto i : it.second)
        {
            cout << "'" << i << "'";
            if (j < it.second.size() - 1)
                cout << " , ";
            j++;
        }
        cout << " }" << endl;
    }
    return 0;
}