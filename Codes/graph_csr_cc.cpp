

#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <utility>
#include <time.h>
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

map<int,set<pair<int,int> > > adjList;

int Edges=0;
int Nodes=0;

void insert_edge(int a,int b,int wt,bool direction)
{
	if(adjList.find(a)!=adjList.end())
	{
		auto ret = adjList[a].insert({b,wt});
		if(ret.second==true)
			Edges++;
	}
	else
	{
		auto temp = set<pair <int,int> >();
		temp.insert({b,wt});
		adjList[a]=temp;
		Edges++;
	}
	if(!direction)
		insert_edge(b,a,wt,true);

}

int *visited;

void dfs(int src)
{
	visited[src]=1;
	auto it=adjList.find(src);
	if(it != adjList.end())
	{
		auto temp = (*it).second;
		for(auto ij : temp)
		{
			if(!visited[ij.first])
			{
				dfs(ij.first);
			}
		}
	}
}

int cc()
{
	int count=0;
	for(int i=1;i<=Nodes;i++)
	{
		if(!visited[i])
		{
			count++;
			dfs(i);

			if(i!=1)
			{
				insert_edge(1,i,rand()%100,false);
			}
		}
	}
	return count;
}

vector<int> values;

void search_degree_two_vertices()
{
	values.clear();
	for(auto e : adjList)
	{
		if(e.second.size() == 1)
		{
			values.push_back(e.first);
		}
	}
}

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

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

	int i,j;
	double wt;
	double eg;
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

	//	cout << nodes1 << " " << nodes2 << " " << edges << endl;

	//cin >> nodes1 >> nodes2 >> edges;

	//cout << temp << endl;

	for(int t=0;t<edges;t++)
	{
		//		fscanf(IN,"%d %d %d\n",&i,&j,&wt);
		if(weighted)
			cin >> i >> j >> wt;
		else
			cin >> i >> j;
		if(i == j)
			continue;
		insert_edge(i,j,(int)wt,false);
		//printf("i=%d j=%d Edges = %d\n",i,j,Edges);
	}

	visited=new int[nodes1+1];
	for(int i=0;i<(nodes1+1);i++)
		visited[i]=0;

	Nodes=nodes1;

	int num_components=cc();

	//search_degree_two_vertices();

	// while(!values.empty())
	// {
	// 	prune_degree_one_vertices();
	// 	search_degree_two_vertices();
	// }

	// cerr << "Number of vertices removed " << count_removed <<  endl;

	//printf("Number of Nodes=%d, number of edges=%d\n",Nodes,Edges);

	//printf("Number of Connected Components = %d\n",num_components);

	int count_edges_written=0;

	int count_nodes = nodes1;

	for(auto it : adjList)
	{
		count_edges_written += it.second.size();
	}

	//printf("%%%%MatrixMarket matrix coordinate integer symmetric\n");
	
	printf("%d\n%d\n",count_nodes,count_edges_written);

	for(auto it : adjList)
	{
		printf("%d ",it.first);
	}
	printf("\n");

	for(auto it : adjList)
	{
		auto temp=it.second;

		int val2;

		for(auto ij : temp)
		{
			val2 = ij.first;
			printf("%d ",val2);
		}
	}

	printf("\n");
	return 0;
}

