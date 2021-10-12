#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<list>
#include<fstream>
#include<sstream>
using namespace std;

//read edges
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

//construct adjacency list
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

//count degree frequency using the adjacency list
vector<int> countDegree_adjList(map<int,vector<int>> adjList){
    vector<int> degreeFreq(adjList.size(),0);
    for (auto it = adjList.begin(); it !=adjList.end(); it++)
	{
		degreeFreq[it->second.size()]++;
	}
    return degreeFreq;
}

//store the degree frequency by adjacency list in a file which will be used for plotting
void storeDegree_adjList(vector<int> &degreeFreq_adjList){
    ofstream fout;
    fout.open("adjList_degreeFreq.txt");

    if(fout.is_open()) cout<<"Started writing adjList degrees"<<endl;
	else cout<<"Cannot write adjList degrees"<<endl;

    for(int i=1; i<degreeFreq_adjList.size(); i++){
        fout<<i<<" "<<degreeFreq_adjList[i]<<endl;
    }

    fout.close();
    if(fout.is_open()) cout<<"Cannot close adjList degrees File"<<endl;
	else cout<<"Ended writing adjList degrees"<<endl;
}

//creates CSR
void construct_CSR(map<int,vector<int>> &adjList, vector<int> &offsets, vector<int> &neighbours){
	for (auto it = adjList.begin(); it !=adjList.end(); it++)
	{
		for(auto i = it->second.begin(); i!=it->second.end(); i++){
			neighbours.push_back(*i);
		}
		offsets.push_back(neighbours.size());
	}
}

//Displays CSR
void display_CSR(vector<int> &offsets, vector<int> &neighbours){
	for(int i: offsets) cout<<i<<" ";
	cout<<endl;
	for(int i: neighbours) cout<<i<<" ";
	cout<<endl;
}

//count degree frequency using the CSR
vector<int> countDegree_CSR(vector<int> &offsets, vector<int> &neighbours){
    vector<int> degreeFreq_CSR(offsets.size()-2,0);
    for (int i = 1; i < offsets.size()-1; i++)
	{
		degreeFreq_CSR[offsets[i+1] - offsets[i]]++;
	}
    return degreeFreq_CSR;
}

//store the degree frequency by CSR in a file which will be used for plotting
void storeDegree_CSR(vector<int> &degreeFreq_CSR){
    ofstream fout;
    fout.open("CSR_degreeFreq.txt");

    if(fout.is_open()) cout<<"Started writing CSR degrees"<<endl;
	else cout<<"Cannot write CSR degrees"<<endl;

    for(int i=1; i<degreeFreq_CSR.size(); i++){
        fout<<i<<" "<<degreeFreq_CSR[i]<<endl;
    }

    fout.close();
    if(fout.is_open()) cout<<"Cannot close CSR degrees File"<<endl;
	else cout<<"Ended writing CSR degrees"<<endl;
}

int main(){
	//Reading the file line by line till the end of file to store the edges of graph
	vector<vector<int>> edges = readEdges();
	//Constructing the adjListacency List from the edges
	map<int,vector<int>> adjList = construct_adjList(edges);
	
	//Display adjListacency List

	////////////////////PLEASE UN-COMMENT the following code to see the adjacency list representation////////////////
	// display_adjList(adjList);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//To check if graph is read fully and correctly
	// cout<<"Number of edges: "<<edges.size()<<endl<<"Number of nodes: "<<adjList.size()<<endl;

    vector<int> degreeFreq_adjList = countDegree_adjList(adjList);
    storeDegree_adjList(degreeFreq_adjList);

	vector<int> offsets;
	//to make it similar to 1-indexed CSR array
	//ignore the 0 index
	offsets.push_back(0);
	//starting offset is 0 for index 1 onwards
	offsets.push_back(0);
	vector<int> neighbours;

	construct_CSR(adjList, offsets, neighbours);

	////////////////////PLEASE UN-COMMENT the following code to see the CSR representation////////////////
	// display_CSR(offsets, neighbours);
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<int> degreeFreq_CSR = countDegree_CSR(offsets, neighbours);
    storeDegree_CSR(degreeFreq_CSR);

	return 0;
}