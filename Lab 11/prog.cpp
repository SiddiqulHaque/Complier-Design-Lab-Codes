#include<bits/stdc++.h>
using namespace std;
map<int,int>mp;

pair<int,int> generate(string &str,int &count){
    count++;
    mp[count]++;
    if(str.length()>=5){
    string ss=str.substr(str.length()-5,5);
    string ss2=ss.substr(0,4);
         if(ss2=="goto"){
        int t=ss[ss.length()-1]-'0';
       
        if(mp.find(t)!=mp.end()){
            return {t,count};
         }
       }
    }
    return {-1 ,-1};
}
int main(){
    cout<<"Mohd Siddiqul haque 21bcs037"<<endl<<endl;
     ifstream myfile("Input.txt");
     string line;
     int count=0;
     vector<pair<int,int>>v;
     while(getline(myfile,line)){
       pair<int,int>p= generate(line,count);
       if(p.first!=-1 && p.second!=-1)
         v.push_back(p);
     }
    for(int i=0;i<v.size();i++){
        pair<int,int>p=v[i];
        int first=p.first;
        int second=p.second;
        cout<<"Loops are present between the line "<<first<<" and "<<second<<endl;
        myfile.clear();
        myfile.seekg(0);
        int c=0;
        while(getline(myfile,line)){    
             if(c==first-1 || c==second-1){
                cout<<c+1<<" "<< line<<endl;
             }
             c++;
        }
    }
         
    return 0;
}