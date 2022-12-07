#include <iostream>
#include <list>
#include <algorithm>
#include "Graph.h" 
#include "DepthFirstSearch.h"
using namespace std;

DepthFirstSearch::DepthFirstSearch(Graph& g) 
	:graph(g) 
{
	int num_nodes = this->graph.getNumVertices();
	this->pVrtxStatus = new VrtxStatus[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		this->pVrtxStatus[i] = UN_VISITED;
	this->ppEdgeStatus = new EdgeStatus * [num_nodes];
	for (int i = 0; i < num_nodes; i++)
		this->ppEdgeStatus[i] = new EdgeStatus[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			this->ppEdgeStatus[i][j] = EDGE_UN_VISITED;
	this->ppConnectivity = new double* [num_nodes];
	for (int i = 0; i < num_nodes; i++)
		this->ppConnectivity[i] = new double[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			this->ppConnectivity[i][j] = PLUS_INF; // initially not connected
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	EdgeList edges;
	edges.clear();
	graph.edges(edges);

	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
	{
		vrtx_1 = *(*pe).getpVrtx_1(); vID_1 = vrtx_1.getID();
		vrtx_2 = *(*pe).getpVrtx_2(); vID_2 = vrtx_2.getID();
		this->ppConnectivity[vID_1][vID_2] = (*pe).getDistance();
	}
	for (int i = 0; i < num_nodes; i++)
		this->ppConnectivity[i][i] = 0; // distance of same node
}

void DepthFirstSearch::initialize()
{
	int num_nodes = this->graph.getNumVertices();
	VertexList verts; //vertex list
	this->graph.vertices(verts);
	Vertex vrtx_1, vrtx_2; //edge's vertex
	this->done = false; //flag 

	for (int i = 0; i < num_nodes; i++)
		pVrtxStatus[i] = UN_VISITED; //set all vertexes are unvisited
	for (int i = 0; i < num_nodes; i++)
		for (int j = 0; j < num_nodes; j++)
			ppEdgeStatus[i][j] = EDGE_UN_VISITED; //set all edges are unvisited
}

void DepthFirstSearch::showConnectivity(ostream& fout) 
{
	int num_nodes = this->graph.getNumVertices(); //get size of vertex
	double dist; //distence
	Vertex* pVrtxArray = this->graph.getpVrtxArray();

	fout << "Connectivity of graph: " << endl;
	fout << "     | ";
	for (int i = 0; i < num_nodes; i++)
		fout <<  setw(5) << pVrtxArray[i].getName();
	fout << endl;
	fout << "-----+";
	for (int i = 0; i < num_nodes; i++)
		fout << "-----";
	fout << endl;
	for (int i = 0; i < num_nodes; i++) {
		fout << " " << setw(3) << pVrtxArray[i].getName() << " | ";
		for (int j = 0; j < num_nodes; j++) {
			dist = ppConnectivity[i][j];
			if (dist == PLUS_INF)
				fout << "  +oo";
			else
				fout << setw(5) << dist;
		} 
			fout << endl;
	}
}

void DepthFirstSearch::dfsTraversal(Vertex& v, Vertex& target, VertexList& path) 
{
	visit(v);
	if (v == target) 
	{
		done = true;
		return;
	}
	EdgeList incidentEdges;
	incidentEdges.clear();
	graph.incidentEdges(v, incidentEdges);
	EdgeItor pe = incidentEdges.begin();
	while (!isDone() && pe != incidentEdges.end()) 
	{
		Edge e = *pe++;
		EdgeStatus eStat = getEdgeStatus(e);
		if (eStat == EDGE_UN_VISITED) 
		{
			visit(e);
			Vertex w = e.opposite(v);
			if (!isVisited(w)) 
			{
				path.push_back(w);
				setEdgeStatus(e, DISCOVERY);
				if (!isDone()) 
				{
					dfsTraversal(w, target, path); // recursive call
					if (!isDone()) 
					{
						//traverseBack(e, v);
						// check whether node w is already in path as a cycle
						Vertex last_pushed = path.back(); // for debugging
						path.pop_back();
					}
				}
			}
			else
			{
				setEdgeStatus(e, BACK);
			}
		}
	} 
}

void DepthFirstSearch::findPath(Vertex& start, Vertex& target, VertexList& path)
{
	initialize();
	path.clear();
	path.push_back(start);
	dfsTraversal(start, target, path);
}

void DepthFirstSearch::visit(Vertex& v) //vertex version
{
	Graph::Vertex* pVtx;
	int numNodes = getGraph().getNumVertices(); //size of vertex
	int vID = v.getID();

	if (this->graph.isValidvID(vID))  //check the index is valid
		this->pVrtxStatus[vID] = VISITED; //set status visited
}

void DepthFirstSearch::visit(Edge& e)  //edge version
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (this->graph.isValidvID(vID_1) && this->graph.isValidvID(vID_2))  //check both vertex is valid
		this->ppEdgeStatus[vID_1][vID_2] = EDGE_VISITED;  //set status visited
}

void DepthFirstSearch::unvisit(Vertex& v)  //vertex version
{
	Graph::Vertex* pVtx;
	int numNodes = getGraph().getNumVertices(); //get size
	int vID = v.getID();
	if (this->graph.isValidvID(vID))   //check the index is valid
		pVrtxStatus[vID] = UN_VISITED; //
}

void DepthFirstSearch::unvisit(Edge& e) //edge version
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (this->graph.isValidvID(vID_1) && this->graph.isValidvID(vID_2))
		ppEdgeStatus[vID_1][vID_2] = EDGE_UN_VISITED;
}

bool DepthFirstSearch::isVisited(Vertex& v)  //vertex version
{
	Graph::Vertex* pVtx;
	int numNodes = getGraph().getNumVertices(); //get size
	int vID = v.getID();
	if (this->graph.isValidvID(vID))  //check the index is valid
		return (pVrtxStatus[vID] == VISITED);
	return false;
}

bool DepthFirstSearch::isVisited(Edge& e) 
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	EdgeStatus eStat;
	int numNodes = getGraph().getNumVertices();
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (this->graph.isValidvID(vID_1) && this->graph.isValidvID(vID_2))  //check both vertex valid
	{
		eStat = ppEdgeStatus[vID_1][vID_2];
		if ((eStat == EDGE_VISITED) || (eStat == DISCOVERY) || (eStat == BACK)) //if visited
			return true; //return true
		else //isn't visited, return false
			return false;
	}
	return false; //if vertex is not valid return false
}


void DepthFirstSearch::setEdgeStatus(Edge& e, EdgeStatus es) 
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices(); //get size
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (this->graph.isValidvID(vID_1) && this->graph.isValidvID(vID_2))  //check both vertex valid
		ppEdgeStatus[vID_1][vID_2] = es; //set status
}

EdgeStatus DepthFirstSearch::getEdgeStatus(Edge& e) 
{
	Vertex vrtx_1, vrtx_2;
	int vID_1, vID_2;
	int numNodes = getGraph().getNumVertices();
	EdgeStatus eStat;
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (this->graph.isValidvID(vID_1) && this->graph.isValidvID(vID_2)) //check bot vertex valid
	{
		eStat = ppEdgeStatus[vID_1][vID_2]; //get status
		return eStat; //and return
	}
	else 
	{
		cout << "Edge (" << e << ") was not found from AdjacencyList" << endl;
		return EDGE_NOT_FOUND;
	}
}
