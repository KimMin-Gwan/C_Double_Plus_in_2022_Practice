#ifndef MST_PRIM_H 
#define MST_PRIM_H 
#include "Graph.h" 
#include <fstream>

using namespace std;
typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Vertex>::iterator VrtxItor;
typedef std::list<Graph::Edge>::iterator EdgeItor;

class MinimumSpanningTree 
{
protected:
	Graph& graph; //exist graph
	bool done; // flag of search done
	double** ppDistMtrx; // distance matrix
protected:
	void initialize(); //initialize 
	bool isValidvID(int vid) { return graph.isValidvID(vid); } //check the valid index
	int getNumVertices() { return graph.getNumVertices(); } //get number of vertice
public:
	MinimumSpanningTree(Graph& g)
		:graph(g) 
	{
		int num_nodes;
		num_nodes = g.getNumVertices();
		// initialize distance matrix
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new double* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new double[num_nodes];
		for (int i = 0; i < num_nodes; i++) 
		{
			for (int j = 0; j < num_nodes; j++)
				ppDistMtrx[i][j] = PLUS_INF;
		}
		initDistMtrx();
	}

	void initDistMtrx(); //initialize
	void fprintDistMtrx(ostream& fout); //print function
	void PrimJarnikMST();
	//void DijkstraShortestPath(ostream& fout, Vertex& s, Vertex& t, VrtxList& path); //find shortest path
	Graph& getGraph() { return graph; } //get graph
	double** getppDistMtrx() { return ppDistMtrx; } //det distence metrix
};
#endif