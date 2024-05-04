#include <bits/stdc++.h>
using namespace std;
bool check(vector<vector<char>> production, string s, int i, stack<char> st)
{
    if (i == s.length() && !st.empty())
    {
        return false;
    }
    if (st.size() > s.length() - i + 1)
    {
        return false;
    }
    while (!st.empty() && st.top() == 'e')
    {
        st.pop();
    }
    if (st.empty())
    {
        return false;
    }
    while (i < s.length() && st.top() == s[i])
    {
        i++;
        st.pop();
        if (st.empty())
        {
            break;
        }
    }
    if (i == s.length() && st.empty())
    {
        return true;
    }
    if (st.empty())
    {
        return false;
    }
    char c = st.top();
    st.pop();
    if ('a' <= c && c <= 'z')
    {
        return false;
    }
    for (int j = 0; j < production.size(); j++)
    {
        if (production[j][0] == c)
        {
            for (int k = production[j].size() - 1; 1 <= k; k--)
            {
                st.push(production[j][k]);
            }
            if (check(production, s, i, st))
            {
                return true;
            }
            for (int k = production[j].size() - 1; 1 <= k; k--)
            {
                st.pop();
            }
        }
    }
    return false;
}
int main()
{
    ifstream file;
    file.open("Input.txt", ios::out);
    vector<vector<char>> production;
    string s;
    stack<char> st;
    st.push('S');
    while (!file.eof())
    {
        string temp;
        getline(file, temp);
        vector<char> v;
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp[i] != ' ')
            {
                v.push_back(temp[i]);
            }
        }
        production.push_back(v);
    }
    cout << "Mohd Siddiqul Haque 21bcs037"
         << endl;
    cout << "\n\nThe production is: \n";
    for (int i = 0; i < production.size(); i++)
    {
        cout << production[i][0] << " -> ";
        for (int j = 1; j < production[i].size(); j++)
        {
            cout << production[i][j];
        }
        cout << endl;
    }
    cout << endl;
    while (1)
    {

        cout << "Enter the string to be checked: ";
        cin >> s;
        int i = 0;

        if (check(production, s, i, st))
        {
            cout << "String can be derived from the given grammar\n"
                 << endl;
        }
        else
        {
            cout << "String cannot be derived from the given grammar\n"
                 << endl;
        }
    }
    return 0;
}
