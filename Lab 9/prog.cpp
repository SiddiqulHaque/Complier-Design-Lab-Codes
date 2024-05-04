#include <bits/stdc++.h>
#include <iostream>
using namespace std;

set<int> FindingLeaders(vector<string> &Tac)
{
    set<int> s;
    s.insert(1);
    for (int i = 0; i < Tac.size(); i++)
    {
        int n = Tac[i].size();
        for (int j = 0; j < Tac[i].size(); j++)
        {
            if (Tac[i][j] == 'g')
            {
                if (Tac[i].substr(j, 4) == "goto")
                {
                    int st = j + 4;
                    int temp = 0;
                    for (int k = st; k <= n - 1; k++)
                    {
                        temp = temp * 10 + (Tac[i][k] - '0');
                    }
                    s.insert(temp);
                    if (i + 2 <= Tac.size())
                    {

                        s.insert(i + 2);
                    }
                }
            }
        }
    }
    return s;
}
map<int, vector<string>> FindingBlocks(vector<string> &Tac, set<int> &leaders)
{
    map<int, vector<string>> ans;
    vector<int> temp;
    for (auto it : leaders)
    {
        temp.push_back(it);
    }
    int i;
    for (i = 0; i < temp.size() - 1; i++)
    {
        int s = temp[i] - 1;
        int e = temp[i + 1] - 1;
        for (int j = s; j < e; j++)
        {
            ans[i + 1].push_back(Tac[j]);
        }
    }
    int s = temp[i] - 1;
    int e = Tac.size();
    for (int j = s; j < e; j++)
    {
        ans[i + 1].push_back(Tac[j]);
    }
    return ans;
}
int findline(set<int> &leaders, int t)
{
    vector<int> temp;
    for (auto it : leaders)
    {
        temp.push_back(it);
    }
    int n = temp.size();
    if (t >= temp[n - 1])
    {
        return n;
    }
    for (int i = 1; i < temp.size(); i++)
    {
        if (temp[i - 1] <= t and temp[i] > t)
        {
            return i;
        }
    }
    return -1;
}
void buildingADJM(map<int, vector<string>> &Blocks, vector<vector<int>> &adj, set<int> &leaders)
{
    int n = adj.size();
    for (int i = 0; i < n - 1; i++)
    {
        adj[i][i + 1] = 1;
    }
    for (auto it : Blocks)
    {
        int n1 = it.first;
        int vsz = it.second.size();
        string laststr = it.second[vsz - 1];
        int strsz = laststr.length();
        for (int i = 0; i < strsz; i++)
        {
            if (laststr[i] == 'g')
            {
                int t = 0;
                int st = i + 4;
                for (int j = st; j < strsz; j++)
                {
                    t = t * 10 + (laststr[j] - '0');
                }
                int n2 = findline(leaders, t);
                if (n2 != -1)
                    adj[n1 - 1][n2 - 1] = 1;
                if (i == 0)
                {
                    adj[n1 - 1][n1] = 0;
                }
                break;
            }
        }
    }
}
int main()
{
    cout<<"Mohd Siddiqul Haque 21bcs037"<<endl;
    ifstream myfile("Tac.txt", ios::in);
    int curr_line = 0;
    string line;
    vector<string> Tac;
    while (getline(myfile, line))
    {
        string temp = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] != ' ' and line[i] != '(' and line[i] != ')')
            {
                temp += line[i];
            }
        }
        Tac.push_back(temp);
    }
    set<int> Leaders = FindingLeaders(Tac);
    map<int, vector<string>> Blocks = FindingBlocks(Tac, Leaders);
    int n = Blocks.size();
    vector<vector<int>> adjMat(n, vector<int>(n, 0));
    buildingADJM(Blocks, adjMat, Leaders);
    cout << "----------Leaders----------" << endl;
    for (auto it : Leaders)
    {
        cout << it << " ";
    }
    cout << endl;
    cout << "----------Blocks----------" << endl;
    for (auto it : Blocks)
    {
        cout << "Block - " << it.first << endl;
        for (auto i : it.second)
        {
            cout << i << endl;
        }
        cout << endl;
    }
    cout<<endl;
     cout << "----------Adjacency Matrix-----------" << endl;
    for (auto it : adjMat)
    {
        for (auto i : it)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}