#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<list>
#include<fstream>
#include<sstream>
using namespace std;

vector<vector<int>> readEdges(){
	//ifstream is an input stream to read data from input.csv file
	ifstream fin;
	fin.open("../input.txt");

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

map<int,vector<int>> construct_adjList(vector<vector<int>> &edges){
    map<int,vector<int>> adjList;
	for(auto it : edges){
		adjList[it[0]].push_back(it[1]);
		adjList[it[1]].push_back(it[0]);
	}
    return adjList;
}

void construct_CSR(map<int,vector<int>> &adjList, vector<int> &offsets, vector<int> &neighbours){
	for (auto it = adjList.begin(); it !=adjList.end(); it++)
	{
		for(auto i = it->second.begin(); i!=it->second.end(); i++){
			neighbours.push_back(*i);
		}
		offsets.push_back(neighbours.size());
	}
}

void display_adjList(map<int,vector<int>> adjList){
	for (auto it = adjList.begin(); it !=adjList.end(); it++)
	{
		cout<<"index "<<it->first;
		for(auto i = it->second.begin(); i!=it->second.end(); i++){
			cout<<" -> "<<*i;
		}
		cout<<endl;
	}
}

void display_CSR(vector<int> &offsets, vector<int> &neighbours){
	for(int i: offsets) cout<<i<<" ";
	cout<<endl;
	for(int i: neighbours) cout<<i<<" ";
	cout<<endl;
}

int main(){
	//Reading the file line by line till the end of file to store the edges of graph
	vector<vector<int>> edges = readEdges();
	//Constructing the adjListacency List from the edges
	map<int,vector<int>> adjList = construct_adjList(edges);
	
	//Display adjListacency List

	////////////////////PLEASE UN-COMMENT the following code to see the adjacency list representation////////////////
	display_adjList(adjList);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//To check if graph is read fully and correctly
	cout<<"Number of edges: "<<edges.size()<<endl<<"Number of nodes: "<<adjList.size()<<endl;

	vector<int> offsets;
	//to make it similar to 1-indexed CSR array
	//ignore the 0 index
	offsets.push_back(0);
	//starting offset is 0 for index 1 onwards
	offsets.push_back(0);
	vector<int> neighbours;

	construct_CSR(adjList, offsets, neighbours);

	////////////////////PLEASE UN-COMMENT the following code to see the CSR representation////////////////
	display_CSR(offsets, neighbours);
	//////////////////////////////////////////////////////////////////////////////////////////////////////





	return 0;
}