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
int isAccepted(string &s)
{
    fstream myfile("inputfile.txt", ios::in);

    int n=(int)s.size();
    vector<vector<int>> v;
    string line;
    if(myfile.is_open())
    {
        while (getline(myfile, line))
        {
            vector<int> temp=stov(line);
            v.push_back(temp);
        }
    }
    myfile.close();
    for(int i=0;i<v.size();i++){
    	for(int j=0;j<v[i].size();j++){
    		cout<<v[i][j]<<" ";
    	}
    	cout<<endl;
    }
    return 0;
}

int main()
{

    string s;
    cout << "Enter the String: ";
    getline(cin, s);
    if (isAccepted(s))
    {
        cout << "Accepted" << endl;
    }
    else{
        cout << "Not Accepted" << endl;
    }
        

    return 0;
}
