#include <bits/stdc++.h>
using namespace std;

map<pair<int,int>,float>weights;
stack<int>stak;
int N;

int stringtoint(string s){ 
    stringstream ss(s);
    int ans = 0;
    ss >> ans;
    return ans;
}


void readGraph(vector<vector<int> >&edges){
    string line;
    string file = "graph-3.txt";
    ifstream myfile("graph-3.txt");
    if(myfile.is_open()){
        while(getline(myfile,line)){
            int n = line.length();
            string num1 = "";
            string num2 = "";
            bool flag = false;
            for(int i=0; i<n; i++){
                if(line[i] != ' ' and !flag){
                    num1 += line[i];
                }
                else if(line[i] == ' '){
                    flag = true;
                }
                else if(line[i] != ' ' and flag){
                    num2 += line[i];
                }
            }
            vector<int> sub;
            int n1 = stringtoint(num1);
            int n2 = stringtoint(num2);
            N = max(n1,n2);
            sub.push_back(n1);
            sub.push_back(n2);
            edges.push_back(sub);
            sub.clear();

        }
    }
    else{
        cout<<"Cannot open the file "<<file<<endl;
    }
}


void addEdge(map<int,vector<int> >& adjList, vector<vector<int> >& edges){
    for(int i=0; i<edges.size(); i++){
        adjList[edges[i][0]].push_back(edges[i][1]);
        adjList[edges[i][1]].push_back(edges[i][0]);
    }
}



int main(){
    vector<vector<int> > edges;
    map<int,vector<int> > adjList;
    readGraph(edges);
    addEdge(adjList,edges);
    //cout<<N;
    vector<int>label(N+1,0);
    for(int i=1;i<=N;i++){
        label[i]=i;
    }
       vector<int>counter(N+1,1);
       
       for(int i=1;i<=N;i++){
        int count = 0;
          int labelx = label[i];
          counter[label[i]]--;
          for(auto x:adjList[i]){
             if(counter[label[x]]>count){
                 count = counter[label[x]];
                 labelx = label[x];
             }
          }
          label[i] = labelx;
          counter[label[i]]++;
       }
        

      for(int i=1;i<=N;i++){
         cout<<i<<"->"<<label[i]<<endl;
      }
   
}