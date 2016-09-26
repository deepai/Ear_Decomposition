#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>

#include <iostream> 

using namespace ogdf;
 
int main(int argc,char **argv)
{
	Graph G;

	G.newEdge(G.newNode(),G.newNode());

	std::cout << G.numberOfEdges() << std::endl;
 
	return 0;
}
