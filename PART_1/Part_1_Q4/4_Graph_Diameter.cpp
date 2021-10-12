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
using namespace std;

//reads edges
vector<vector<int>> readEdges(){
	//ifstream is an input stream to read data from input.csv file
	ifstream fin;
	fin.open("../graph-1.txt");

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

//BFS used to visit every other node from the given source node and also marking the distance
void BFS(map<int,vector<int>> &adjList, vector<int> &distance, int source){
    queue<int> BFSqueue;
    BFSqueue.push(source);

    while(!BFSqueue.empty()){
        int node = BFSqueue.front();
        BFSqueue.pop();
		//check for neighbours of the current node and traverse them
        for(int i: adjList[node]){
            if(distance[i]==-1){
                distance[i] = distance[node]+1;
                BFSqueue.push(i);
            }
        }
    }
}

int main(){
	//Reading the file line by line till the end of file to store the edges of graph
	vector<vector<int>> edges = readEdges();
	//Constructing the adjacency List from the edges
	map<int,vector<int>> adjList = construct_adjList(edges);
	//Display adjacency List
	// display_adjList(adjList);
	//To check if graph is read fully and correctly
	cout<<"Number of edges: "<<edges.size()<<endl<<"Number of nodes: "<<adjList.size()<<endl;
    int n = adjList.size();

    vector<int> distance(n+1,-1);
    int diameter=-1;
	// Go through every node and apply BFS to find the diameter of the graph
	for(int i=1; i<=n; i++){
		//source is at distance 0 form itself
        distance[i]=0;
        BFS(adjList, distance, i);
		//store the largest path calculated till now
        diameter = max(*max_element(distance.begin(), distance.end()), diameter);
		//reinitialize the distances of all nodes
        fill(distance.begin(), distance.end(), -1);
    }
    cout<<"The diameter of the graph is: "<<diameter<<endl;
	return 0;
}