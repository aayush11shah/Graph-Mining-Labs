#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
#include <iterator>
#include<algorithm>
using namespace std;

string file = "graph-1.txt";
//reads edges
vector<vector<int>> readEdges(){
	//ifstream is an input stream to read data from input.csv file
	ifstream fin;
	fin.open("../" + file);

	if(fin.is_open()) cout<<"Started Reading File"<<endl;
	else cout<<"Cannot open File"<<endl;

	string line, Node;
	char delimeter = ' ';
    vector<vector<int>> edges;
	
	while(!fin.eof()){
		getline(fin, line);
		//to convert the string into a stream to read comma seperated individual values.
		if(line[0]=='%' || line[0]=='\0') continue;
		stringstream s(line);
		int i=0;
		//vector to store the curent edge
		vector<int> v(2,0);
		//to read the line using the string stream 
		while(getline(s, Node, delimeter))  v[i++] = stoi(Node);
		edges.push_back(v);
	}
	fin.close();

	if(fin.is_open()) cout<<"Cannot close File"<<endl;
	else cout<<"Ended Reading File"<<endl;

    return edges;
}

//creates adjacency list
map<int,vector<int>> construct_adjList(vector<vector<int>> &edges){
    map<int,vector<int>> adjList;
	for(auto it : edges){
		adjList[it[0]].push_back(it[1]);
		adjList[it[1]].push_back(it[0]);
	}
    return adjList;
}

//Displays adjacency list
void display_adjList(map<int,vector<int>> &adjList){
	for (auto it = adjList.begin(); it !=adjList.end(); it++)
	{
		cout<<"index "<<it->first;
		for(auto i = it->second.begin(); i!=it->second.end(); i++){
			cout<<" -> "<<*i;
		}
		cout<<endl;
	}
}

//Function to print the DFS starting from v
//It returns true if the degree of the v after processing is less than k else false
bool DFS(int v, vector<bool>& visited, vector<int> &degrees, int k, map<int,vector<int> >& adjList){

    // mark the current node as visited and print it
    visited[v] = true;
    for(auto it: adjList[v]){
        // degree of v is less than k, then degree of adjacent must be reduced
        if(degrees[v] < k){
            degrees[it]--;
        }
        if(!visited[it]){
            // If degree of the adjacent after processing becomes less than k, then reduce the degree of v
            DFS(it,visited,degrees,k, adjList);
        }
    }
    // return true if degree of v is less than k
    return (degrees[v] < k);
}
void printKCores(int k, int V, map<int,vector<int> >& adjList, int &maximumCore){
    vector<bool> visited(V,false);
    vector<bool> processed(V,false);
    int mindeg = INT_MAX;
    int startvertex;

    // store degrees of all vertices
    vector<int> degrees(V);
    for(int i=0; i<V; i++){
        degrees[i] = adjList[i].size();
        if(degrees[i] < mindeg){
            mindeg = degrees[i];
            startvertex = i;
        }
    }
    DFS(startvertex,visited,degrees,k,adjList);

    // if graph is disconnected
    for(int i = 0; i<V; i++){
        if(visited[i] == false){
            DFS(i,visited,degrees,k,adjList);
        }
    }
    
    // printing k cores
    cout<<"K-Cores: \n";
    for(int v=0; v<V; v++){
        if(degrees[v] >=k){
            if(v >= maximumCore){
                maximumCore = v;
            }
            cout<<"\n["<<v<<"]";
        }

        for(auto it: adjList[v]){
            if(degrees[it] >= k){
                cout<<"->"<<it;
            }
        }
    }
    cout<<endl;
}

int main()
{
	//Reading the file line by line till the end of file to store the edges of graph
	vector<vector<int>> edges = readEdges();
	//Constructing the adjListacency List from the edges
	map<int,vector<int>> adjList = construct_adjList(edges);
	//Display adjListacency List
	display_adjList(adjList);
	//To check if graph is read fully and correctly
	// cout<<"Number of edges: "<<edges.size()<<endl<<"Number of nodes: "<<adjList.size()<<endl;
	int V = adjList.size();
    int k = 3; // taking k = 3 and remove all the vertices less than 3
    int maximumCore = INT_MIN;
    printKCores(k,V,adjList,maximumCore);
    cout<<"Maximum core of given graph "<<file<<" is "<<maximumCore<<endl;

	return 0;
}