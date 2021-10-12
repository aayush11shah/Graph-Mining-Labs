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

//visits nodes and helps to counts path of given length
void DFS(map<int,vector<int>> &adjList, vector<bool> &visited, int n, int vert, int start, int &count)
{
	// mark the vertex vert as visited
	visited[vert] = true;
	// if the path of length (n-1) is found
	if (n == 0) {
		// mark vert as un-visited to make it usable again.
		visited[vert] = false;
		// Check if vertex vert can end with vertex start
		int found=0;
		for(int i: adjList[vert]) if(i==start) found=1;
		
		if(found){
			count++;
			return;
		}
		else return;
	}

	// For searching every possible path of length (n-1)
	for (int i: adjList[vert])
		if (!visited[i])
			// DFS for searching path
			DFS(adjList, visited, n-1, i, start, count);

	// marking vert as unvisited to make it usable again.
	visited[vert] = false;
}

// Counts cycles of length N in an undirected and connected graph.
int countCycles(map<int,vector<int>> &adjList, int n)
{
	// all vertex are visited un-visited initially.
	vector<bool> visited(adjList.size()+1,false);

	// Searching for cycle by using v-n+1 vertices
	int count = 0;
	for (int i = 1; i <= adjList.size() - (n - 1); i++) {
		DFS(adjList, visited, n-1, i, i, count);
		visited[i] = true;
	}

	return count/2;
}

int main()
{
	//Reading the file line by line till the end of file to store the edges of graph
	vector<vector<int>> edges = readEdges();
	//Constructing the adjListacency List from the edges
	map<int,vector<int>> adjList = construct_adjList(edges);
	//Display adjListacency List
	// display_adjList(adjList);
	//To check if graph is read fully and correctly
	cout<<"Number of edges: "<<edges.size()<<endl<<"Number of nodes: "<<adjList.size()<<endl;

	int cycles_3 = countCycles(adjList, 3);
	int cycles_4 = countCycles(adjList, 4);
	
	cout<<"Total cycles of length 3 are "<<cycles_3<<endl;
	cout<<"Total cycles of length 4 are "<<cycles_4<<endl;
	return 0;
}