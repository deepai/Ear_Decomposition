#include <ogdf/basic/Graph.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/layered/DfsAcyclicSubgraph.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/augmentation/DfsMakeBiconnected.h>
#include <ogdf/basic/basic.h>
 
using namespace ogdf;
 
int main()
{
	Graph G;
	List<edge> list;
	DfsMakeBiconnected connector;
	randomSimpleGraph(G, 10, 20);

	//connector.doCall(G,list);	
 
	return 0;
}
