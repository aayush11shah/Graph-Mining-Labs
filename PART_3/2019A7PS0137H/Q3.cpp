#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
#include<iterator>
#include<algorithm>
#include<stack>
#include<set>
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
                if(line[i] != ' ' && !flag){
                    num1 += line[i];
                }
                else if(line[i] == ' '){
                    flag = true;
                }
                else if(line[i] != ' ' && flag){
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




vector<int> enumerate(map<int,vector<int>> adjlist, int start, int n, set<int> &leaf_node){
       queue<int>q;
       q.push(start);
       map<pair<int,int>,int>mark;
       vector<int> weight(n+1,0);
       vector<int> visited(n+1,0);
       stack<int> st;
       st.push(start);
       visited[start] = 1;
       weight[start] = 1;
       int count = 1;
       vector<int>level(n+1,0);
       while(!q.empty()){
           int sz = q.size();
           while(sz--){
            int p = q.front();
            q.pop();
            int old_q = q.size();
            for(auto x : adjlist[p]){
                if(mark[make_pair(min(x,p),max(x,p))] == 0){
                      weight[x] += weight[p]; 
                      mark[make_pair(min(x,p),max(x,p))] = 1;
                }
                                                                                                                                                                                                                   
                if(!visited[x]){
                    visited[x] = 1;
                    level[x] = 1+level[p];
                    count++;
                    q.push(x);
                    st.push(x);
                }
             }
          
            }
       }

       for(int i=1;i<=n;i++){
           bool flag = true;
           for(auto x:adjlist[i]){
                if(level[x]>level[i]){
                   flag = false;
               }
           } 
           if(flag){
               leaf_node.insert(i);     
            }
       }

       weight[start] = 0;
       stak=st;
       return weight;
}



void counter(map<int,vector<int>> adjlist, int n, map<pair<int,int>,float> &edge_values,vector<int> node_values, set<int> &leaf_node){
    queue<int>q;
    vector<int>visited(n+1,0);
    map<pair<int,int>,float>edge_weights;
    map<int,float>value;
    map<pair<int,int>,int>mark;
    while(!stak.empty()){
        int k = stak.top(); stak.pop();
        for(auto x : adjlist[k]){
            if(mark[make_pair(min(x,k),max(x,k))] == 0){
                mark[make_pair(min(x,k),max(x,k))] = 1;
                     if(leaf_node.find(k)!=leaf_node.end()){
                            edge_weights[make_pair(min(k,x),max(k,x))] = (float) node_values[x]/node_values[k] ;
                            value[x] += (float) node_values[x]/node_values[k] ;
                            weights[make_pair(min(k,x),max(k,x))] += edge_weights[make_pair(min(k,x),max(k,x))];

                     }
                     else{
                            edge_weights[make_pair(min(k,x),max(k,x))] = (float)(1 + value[k])/node_values[k];
                            value[x] += (float)(1 + value[k])/node_values[k];
                            weights[make_pair(min(k,x),max(k,x))] += edge_weights[make_pair(min(k,x),max(k,x))] ;
                     }   
            }
                    
                 }               
        }
          
 }


void init(map<int,vector<int>> adjlist, int n){

   for(int i=1;i<=n;i++){
        map<pair<int,int>,float> edge_values;
        set<int> leaf_node;
        vector<int> node_values = enumerate(adjlist,i,n, leaf_node);
        counter(adjlist, n, edge_values, node_values, leaf_node);

   }
}

void dfs(map<int,vector<int> > adjList , vector<int>&visited, int k){
    visited[k] = 1;
    for(auto x:adjList[k]){
         if(visited[x]==0){
           dfs(adjList,visited,x);
       }
    }
}

int number_of_components( map<int,vector<int> > adjList , int n){
    vector<int>visited(n+1,0);
    int count = 0;
    for(int i=1;i<=n;i++){
       if(visited[i]==0){
           count++;
           dfs(adjList,visited,i);
       }
    }
    return count;
}



int main(){
    vector<vector<int> > edges;
    map<int,vector<int> > adjList;
    readGraph(edges);
    addEdge(adjList,edges);
    init(adjList,N);
 
 do{
    int maximum_weight = -1;
   for(auto x:weights){
       maximum_weight = max(maximum_weight,(int)x.second);
   }
   for(auto x:weights){
       if((int)x.second == maximum_weight){
             int p = x.first.first;
             int k = x.first.second;
             int p_index , k_index;
             for(int i=0;i<=adjList[p].size();i++){
                 if(adjList[p][i] == k){
                      k_index = i;
                      break;
                 }
             }
            for(int i=0;i<=adjList[k].size();i++){
                 if(adjList[k][i] == p){
                      p_index = i;
                      break;
                 }
             }
             adjList[p].erase(adjList[p].begin()+k_index);
             adjList[k].erase(adjList[k].begin()+p_index);
       }
  }
  
   } while(number_of_components(adjList,N)==1);

 cout<<"Number of Communities : "<<number_of_components(adjList,N);
   
}