#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<fstream>
#include<sstream>
#include<iterator>
#include<algorithm>
using namespace std;

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

map<int,vector<int>> construct_adjList(vector<vector<int>> &edges){
    map<int,vector<int>> adjList;
	for(auto it : edges){
		adjList[it[0]].push_back(it[1]);
		adjList[it[1]].push_back(it[0]);
	}
    return adjList;
}

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

// DFS iterative version to avoid system tack overflows for very large graphs
// it calculates the size of a single connected component at once
int iterativeDFS(map<int,vector<int>> &adjList, vector<bool> &visited, int source){
    stack<int> stack;
    stack.push(source);
	int current_node_count=0;
    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();
        if (visited[node]){
			continue;
		}
		visited[node]=true;
		current_node_count++;
        for (auto i: adjList[node]){
            if (!visited[i]) stack.push(i);
		}
    }
	return current_node_count;
}

int main(){
	//Reading the file line by line till the end of file to store the edges of graph
	vector<vector<int>> edges = readEdges();
	//Constructing the adjListacency List from the edges
	map<int,vector<int>> adjList = construct_adjList(edges);
	//Display adjListacency List
	// display_adjList(adjList);
	//To check if graph is read fully and correctly
	cout<<"Number of edges: "<<edges.size()<<endl<<"Number of nodes: "<<adjList.size()<<endl;
    int n = adjList.size();

	//to ensure that nodes visiteed already are not visited again
    vector<bool> visited(n+1,false);
    int largest_node_count=-1;

	// run DFS from every node and thus calculate the largest connected component
	for(int i=1; i<=n; i++){
        int current_node_count = iterativeDFS(adjList, visited, i);
        largest_node_count = max(current_node_count, largest_node_count);
    }
    cout<<"The size of largest connected component of the graph is: "<<largest_node_count<<endl;
	return 0;
}