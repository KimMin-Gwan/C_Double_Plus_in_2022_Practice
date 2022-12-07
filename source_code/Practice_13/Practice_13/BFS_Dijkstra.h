#ifndef BFS_DIJKSTRA_H
#define BFS_DIJKSTRA_H
#include "Graph.h" 
#include <fstream>

using namespace std;
typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Vertex>::iterator VrtxItor;
typedef std::list<Graph::Edge>::iterator EdgeItor;

class BreadthFirstSearch
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
	BreadthFirstSearch(Graph& g) :graph(g) 
	{
		int num_nodes;
		num_nodes = g.getNumVertices();
		// initialize DistMtrx
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
	//void DijkstraShortestPathTree(ostream& fout, Vertex& s, int* pPrev);
	void DijkstraShortestPath(ostream& fout, Vertex& s, Vertex& t, VrtxList& path); //find shortest path
	Graph& getGraph() { return graph; } //get graph
	double** getppDistMtrx() { return ppDistMtrx; } //det distence metrix
	void findShortestPath(ostream& fout, Vertex& start, Vertex& target, VrtxList& path);
	void _bfsTraversal(ostream& fout, Vertex& start, Vertex& target, VrtxList& path);
	void visit(Vertex& v);
	bool isVisited(Vertex& v);

};
#endif