
#include<bits/stdc++.h>
#include<fstream>

using namespace std;
int convertToInt(string &s) {
	int i = 0;
	int ans = 0;
	while(i < s.size()) {
		int t = s[i]-'0';
		ans = ans*10 + t;
		i++;
	}
	return ans;
}
vector<set<int>> stringToVectorOfSet(string &line) {
	int i = 0;
	vector<set<int>> v;
	set<int> s;
	while(i < line.size()) {
			if(line[i] == '-') {
				int x = -1;
				s.insert(x);
				v.push_back(s);
				s.clear();
				i++;
			} else if(line[i] != '-' and line[i] != ' '){
				string t = "";
				while(line[i] != ' ' and i < line.size()) {
					t += line[i];
					i++;
				}
				string k = "";
				for(int j = 0;j < t.size();j++) {
				    if(t[j] != ',') {
					    k += t[j];
					} else {
						int x = convertToInt(k);
						k = "";
						s.insert(x);
					}
				}
				if(k != "") {
					int x = convertToInt(k);
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
int main() {
	ifstream myfile("NFA.txt", ios::in);
	int curr_line = 0;
    string line;
	int istate = 0;
	set<int> finalState;
	vector<vector<set<int>>> nfa;
	while(getline(myfile, line)) {
		int state;
		vector<set<int>> temp;
		if(curr_line == 0) {
			istate = convertToInt(line);
		} else if(curr_line == 1) {
			string t;
			for(int i = 0;i < line.size();i++) {
				if(line[i] != ',') {
					t += line[i];
				} else {
					int x = convertToInt(t);
					t = "";
					finalState.insert(x);
				}
			}
			if(t != "") {
				int x = convertToInt(t);
				t = "";
				finalState.insert(x);
			}
		} else {
			vector<set<int>> v = stringToVectorOfSet(line);
			nfa.push_back(v);
		}
		curr_line++;
	}
    map<int, set<int>> convergeStates;
	map<set<int>, int> mapping;
    int n = nfa.size();
    for(int i = 0;i < nfa.size();i++) {
		for(int j = 0;j < nfa[i].size();j++) {
			if(nfa[i][j].size() > 1) {
				convergeStates[n] = nfa[i][j];
				mapping[nfa[i][j]] = n;
				n++;
			}
		}
	}
    int m = nfa[0].size();
	
	for(auto it : convergeStates) {
        set<int> s;
        vector<set<int>> nS;
        for(int j = 0;j < m;j++) {
            set<int> newSet;
            for(auto i: it.second) {
                for(auto k: nfa[i][j]) {
                    if(k != -1) {
                        newSet.insert(k);
                    }
                }
            }
            if(newSet.size() > 1) {
                if(mapping.find(newSet) == mapping.end()) {
                    convergeStates[n] = newSet;
                    mapping[newSet] = n;
                    n++;
                }
            }
            if(newSet.size() == 0) newSet.insert(-1);
            nS.push_back(newSet);
        }
		nfa.push_back(nS);
	}

    // for(int i = 0;i < nfa.size();i++) {
	// 	for(int j = 0;j < nfa[i].size();j++) {
	// 		for(auto it: nfa[i][j]) {
	// 			cout<<it;
	// 		}
    //         cout<<" ";
	// 	}
    //     cout<<endl;
	// }
    // cout<<endl;
    // cout<<endl;
    // cout<<endl;

    vector<vector<int>> dfa;
    for(int i = 0;i < nfa.size();i++) {
        vector<int> v;
        for(int j = 0;j < nfa[i].size();j++) {
            if(nfa[i][j].size() == 1) {
                v.push_back(*nfa[i][j].begin());
            } else {
                for(auto it: nfa[i][j]) {
                    if(finalState.find(it) != finalState.end()) {
                        finalState.insert(mapping[nfa[i][j]]);
                        break;
                    }
                }
                v.push_back(mapping[nfa[i][j]]);
            }
        }
        dfa.push_back(v);
    }
    ofstream fout("convertedDFA.txt", ios::out);
    fout<<istate;
    fout<<endl;
    

    for(auto it: finalState) {
        cout<<it<<" ";
        fout<<it<<" ";
    }
    fout<<endl;

    cout<<endl;

    for(int i = 0;i < dfa.size();i++) {
        for(int j = 0;j < dfa[i].size();j++) {
            cout<<dfa[i][j]<<" ";
            fout<<dfa[i][j]<<" ";
        }
        fout<<endl;
        cout<<endl;
    }

	return 0;
}
