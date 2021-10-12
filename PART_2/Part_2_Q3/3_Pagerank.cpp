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

string file = "facebook_edges.csv";
//reads edges
vector<vector<int>> readEdges(){
	//ifstream is an input stream to read data from input.csv file
	ifstream fin;
	fin.open(file);

	if(fin.is_open()) cout<<"Started Reading File"<<endl;
	else cout<<"Cannot open File"<<endl;

	string line, Node;
	char delimeter = ',';
    vector<vector<int>> edges;
	
	while(!fin.eof()){
		getline(fin, line);
		//to convert the string into a stream to read comma seperated individual values.
		if(line[0]=='i' || line[0]=='\0') continue;
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
		adjList[it[1]].push_back(it[0]);
		adjList[it[0]];
	}
    return adjList;
}

//Displays adjacency list
void display_adjList(map<int,vector<int>> &adjList){
	for (auto it = adjList.begin(); it !=adjList.end(); it++)
	{
		cout<<"index "<<it->first;
		for(auto i = it->second.begin(); i!=it->second.end(); i++){
			cout<<" <- "<<*i;
		}
		cout<<endl;
	}
}

//Single pass of calculating pagerank for all nodes
void pagerank_pass(map<int,vector<int>> &adjList, vector<pair<int,float>> &PRT, vector<int> &CT, float dampening_factor){
    for(auto &it: adjList){
        float k = 0;
        for(int j = 0; j < it.second.size(); j++){
            float pr_in = PRT[it.second[j]].second;
            int ct_in = CT[it.second[j]];
            k += pr_in/ct_in;
        }
        // cout<<k<<endl;
        PRT[it.first].second = k*dampening_factor;
        PRT[it.first].second += 1-dampening_factor;
    }

}

//reading the target data to display the page details
vector<vector<string>> readData(){
	//ifstream is an input stream to read data from input.csv file
	ifstream fin;
	fin.open("facebook_target.csv");

	if(fin.is_open()) cout<<"Started Reading File"<<endl;
	else cout<<"Cannot open File"<<endl;

	string line, data;
	char delimeter = ',';
    vector<vector<string>> page_data;
	
	while(!fin.eof()){
		getline(fin, line);
		//to convert the string into a stream to read comma seperated individual values.
		if(line[0]=='i' || line[0]=='\0') continue;
		stringstream s(line);
		int i=0;
		//vector to store the curent edge
		vector<string> v;
		//to read the line using the string stream 
		while(getline(s, data, delimeter))  v.push_back(data);
		page_data.push_back(v);
	}
	fin.close();

	if(fin.is_open()) cout<<"Cannot close File"<<endl;
	else cout<<"Ended Reading File"<<endl;

    return page_data;
}

//utility to sort according to the second value of a pair
bool sortbysec(pair<int,float> &a, pair<int,float> &b){
    if(a.second > b.second) return true;
    return false;
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


    float dampening_factor = 0.85; // the dampening factor (d or beta)
    vector<pair<int,float>> PRT;   // the vector containing the pagerank with their node id
    vector<int> CT(adjList.size(),0); // the count of outbounding links for each node

    for(int i=0; i<adjList.size(); i++) PRT.push_back({i,1}); // start with pagerank 1 for all the nodes

	// calculate the out-degrees for every node using the adjacency list
    for(auto &it: adjList){
        for(int j = 0; j < it.second.size(); j++){
            CT[it.second[j]]++;
        }
    }

	// repeat the pagerank algorithm till the pageranks start converging
    for(int i=0; i<40; i++) pagerank_pass(adjList, PRT, CT, dampening_factor);

	// sort the pagerank according to the highest pageranks
    sort(PRT.begin(), PRT.end(), sortbysec);

	//read data about the pages
    vector<vector<string>> pageData = readData();

    cout<<"ID      PageRank    PageName"<<endl;
	// display the top 10 page details
    for(int i=0; i<10; i++){
        cout<<pageData[PRT[i].first][0]<<"   "<<PRT[i].second<<"     "<<pageData[PRT[i].first][2]<<endl;
    }

	return 0;
}