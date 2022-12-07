#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H
#include <iostream>
#include "Graph.h" 
using namespace std;

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VertexList;
typedef std::list<Graph::Vertex>::iterator VertexItor;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Edge>::iterator EdgeItor;

class DepthFirstSearch
{
protected:
	Graph& graph; //graph
	Vertex start;
	bool done; // flag of search done
protected:
	void initialize();
	void dfsTraversal(Vertex& v, Vertex& target, VertexList& path);
	virtual void traverseDiscovery(const Edge& e, const Vertex& from) { } //traverse forword
	virtual void traverseBack(const Edge& e, const Vertex& from) { } //tarverse backword
	virtual void finishVisit(const Vertex& v) {} // what is it for?
	virtual bool isDone() const { return done; } //return done
	//utilities------------------------------------------- 
	void visit(Vertex& v); //set flag visted / vertex version
	void visit(Edge& e);//set flag visted / edge version
	void unvisit(Vertex& v); //set flag unvisted /vertex version
	void unvisit(Edge& e); //set flag unvisted /edge version
	bool isVisited(Vertex& v); //set flag unvisted /vertex version
	bool isVisited(Edge& e); //set flag unvisted /edge version
	void setEdgeStatus(Edge& e, EdgeStatus es); //set edge status
	EdgeStatus getEdgeStatus(Edge& e); //get edge status
public:
	DepthFirstSearch(Graph& g); //core function
	void findPath(Vertex& s, Vertex& t, VertexList& path); //finding path 
	Graph& getGraph() { return graph; } //return graph member
	void showConnectivity(ostream& fout); //print connection //ostream fout
private:
	VrtxStatus* pVrtxStatus;
	EdgeStatus** ppEdgeStatus;
	double** ppConnectivity; // two dimensional array; table of distance[v1][v2]
}; // end of class DepthFirstSearch
#endif