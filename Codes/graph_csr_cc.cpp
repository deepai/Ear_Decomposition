#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <utility>
#include <time.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

map<int,int> relabel;

class csr_graph
{

	struct compare
	{
		bool operator()(const pair<int,int> &lhs, const pair<int,int> &rhs)
		{
			if(lhs.first < rhs.first)
				return true;
			else if(lhs.first > rhs.first)
				return false;
			else 
				return (lhs.second <= rhs.second);
		}
	};

	vector<int> row_offsets;

	vector<pair<int,int> > edges;

	int row_size;
	int col_size;

public:
	csr_graph()
	{

	}

	~csr_graph()
	{
		edges.clear();
		row_offsets.clear();
	}

	void insert_edge(int a,int b,bool direction)
	{
		edges.push_back({a,b});
		if(!direction)
			insert_edge(b,a,true);
	}

	void sort_edges()
	{
		std::sort(edges.begin(),edges.end(),compare());
	}

	void set_nodes_edges(int nodes,int edges)
	{
		row_size = nodes;
		col_size = edges;

		row_offsets.resize(row_size);
	}

	void construct_csr_graph()
	{
		for(int i=0;i<edges.size();i++)
		{
			row_offsets[edges[i].first]++;
		}

		int prev = 0,curr;

		for(int i=0;i<row_offsets.size();i++)
		{
			curr = row_offsets[i];
			row_offsets[i] = prev;
			prev = prev + curr;
		}
	}

	void print_graph()
	{
		printf("%d\n",row_size);
		printf("%d\n",col_size);

		for(int i=0;i<row_offsets.size();i++)
		{
			assert(row_offsets[i] < col_size);
			printf("%d ",row_offsets[i] + 1);
		}
		//std::cerr << row_offsets[row_offsets.size() - 1] + 1 << std::endl;

		printf("\n");

		for(int i=0;i<edges.size();i++)
		{
			assert(edges[i].first < row_size);
			printf("%d ",edges[i].first + 1);
		}

		printf("\n");
	}

};

int main(int argc,char* argv[])
{

	if(argc < 2)
	{
		printf("The first argument should indicate 0 for unweighted and 1 for weighted\n");
		return 0;
	}
	
	int weighted = atoi(argv[1]);

	srand(time(NULL));

	int nodes1,nodes2,edges;

	string temp;

	getline(cin,temp);

	while(temp[0] == '%')
	{
		getline(cin,temp);
	}

	vector<string> graph_dimension = split(temp,' ');

	nodes1 = stoi(graph_dimension[0]);
	nodes2 = stoi(graph_dimension[1]);
	edges  = stoi(graph_dimension[2]);

	int u,v;
	double wt = 0;

	int unique_nodes_count = 0;

	csr_graph graph;

	for(int i=0;i<edges;i++)
	{
		if(weighted)
		{
			cin >> u >> v >> wt;
		}
		else
			cin >> u >> v;

		u--;
		v--;

		if(relabel.find(u) == relabel.end())
			relabel[u] = unique_nodes_count++;

		if(relabel.find(v) == relabel.end())
			relabel[v] = unique_nodes_count++;

		graph.insert_edge(relabel[u],relabel[v],false);
	}

	graph.set_nodes_edges(unique_nodes_count, 2*edges);
	graph.sort_edges();
	graph.construct_csr_graph();
	graph.print_graph();


	return 0;
	
}

