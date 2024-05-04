#include <bits/stdc++.h>
#include <fstream>

using namespace std;
vector<set<int>> readingFile(string &line)
{
	int i = 0;
	vector<set<int>> v;
	set<int> s;
	while (i < line.size())
	{
		if (line[i] == '-')
		{
			int x = -1;
			s.insert(x);
			v.push_back(s);
			s.clear();
			i++;
		}
		else if (line[i] != '-' and line[i] != ' ')
		{
			string t = "";
			while (line[i] != ' ' and i < line.size())
			{
				t += line[i];
				i++;
			}
			string k = "";
			for (int j = 0; j < t.size(); j++)
			{
				if (t[j] != ',')
				{
					k += t[j];
				}
				else
				{
					int x = stoi(k);
					k = "";
					s.insert(x);
				}
			}
			if (k != "")
			{
				int x = stoi(k);
				k = "";
				s.insert(x);
			}
			v.push_back(s);
			s.clear();
		}
		i++;
	}
	return v;
}
int main()
{
	cout<<"MOHD SIDDIQUL HAQUE 21BCS037"<<endl;
	ifstream myfile("NFA.txt", ios::in);
	int curr = 0;
	string line;
	int istate = 0;
	set<int> fstates;
	vector<vector<set<int>>> nfa;
	while (getline(myfile, line))
	{
		int state;
		vector<set<int>> temp;
		if (curr == 0)
		{
			istate = stoi(line);
		}
		else if (curr == 1)
		{
			string t;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] != ',')
				{
					t += line[i];
				}
				else
				{
					int x = stoi(t);
					t = "";
					fstates.insert(x);
				}
			}
			if (t != "")
			{
				int x = stoi(t);
				t = "";
				fstates.insert(x);
			}
		}
		else
		{
			vector<set<int>> v = readingFile(line);
			nfa.push_back(v);
		}
		curr++;
	}
	map<int, set<int>> newStates;
	int n = nfa.size();
	vector<vector<set<int>>> dfa=nfa;
	int nInputs= nfa[0].size();
	set<int> check;
	for (int i = 0; i < nfa.size(); i++)
	{
		for (int j = 0; j < nfa[i].size(); j++)
		{
			if (nfa[i][j].size() > 1)
			{
				newStates[n] = nfa[i][j];
				check.insert(n);
				n++;
			}
		}
	}

	for (auto it : newStates)
	{
		set<int> s;
		vector<set<int>> nS;
		int num=0;
		for (int j = 0; j < nInputs; j++)
		{
			set<int> newSet;
			for (auto i : it.second)
			{
				for (auto k : nfa[i][j])
				{
					if (k != -1)
					{
						newSet.insert(k);
						
					}
				}
			}
			if(newSet.size() > 1) {
				if(check.find(n)==check.end()){
					newStates[n] = newSet;
                    n++;
                    check.insert(n);
				}
                    
            }
			if (newSet.size() == 0){
				newSet.insert(-1);	
			}
			nS.push_back(newSet);
			
		}
		fstates.insert(num);
		nfa.push_back(nS);
	}
	for(auto it :newStates){
		int num=0;
		for(auto i:it.second){
			num=num*10+i;
		}
		for(auto i:it.second){
			if(fstates.find(i)!=fstates.end()){
				fstates.insert(num);
				break;
			}
		}
	}
	fstates.erase(0);
	//<<"Final States : ";
	//for(auto it:fstates){
	//	cout<<it<<" ";
	//}
	cout<<endl;
cout<<"-------------DFA---------------"<<endl;
	for (int i = 0; i < nfa.size(); i++)
	{
		for (int j = 0; j < nfa[i].size(); j++)
		{
			for (auto it : nfa[i][j])
			{
				cout << it;
			}
			cout << " ";
		}
		cout << endl;
	}
	return 0;
}
