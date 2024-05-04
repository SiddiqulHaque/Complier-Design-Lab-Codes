#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
vector<int> stov(string &line)
{
    int i = 0;
    vector<int> v;
    while (i < line.size())
    {
        if (line[i] == '-')
        {
            int x = -1;
            v.push_back(x);
            i++;
        }
        else if (line[i] != '-' and line[i] != ' ')
        {
            v.push_back(line[i] - '0');
        }
        i++;
    }
    return v;
}
string isAccepted(string &s)
{
    fstream myfile("inputfile.txt", ios::in);

    int n = (int)s.size();
    vector<vector<int> > v;
    string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            vector<int> temp = stov(line);
            v.push_back(temp);
        }
    }
    myfile.close();
    int current = v[0][0];
    int sz=v[1].size();
    string ans = "";
    //ans.push_back(v[current+1][sz-1]+97);
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        int col = (int)ch - 97;
        if(col%2!=0){
        	col+=1;
        }
        int get = v[current + 1][col];
        if (get == -1)
            	break;
        ch = (char)(v[current+1][col+1] + 48);
        current = get;
        ans.push_back(ch);
    }
    return ans;
}

int main()
{
    cout<<"Mohd Siddiqul Haque 21bcs037"<<endl;
    string s;
    cout << "Enter the String: ";
    getline(cin, s);
    string ans = isAccepted(s);
   
        cout <<"output is : "<< ans << endl;
    

    return 0;
}
