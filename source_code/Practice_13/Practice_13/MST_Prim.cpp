#include <algorithm>
#include "Graph.h"
#include "MST_Prim.h"


using namespace std;

void MinimumSpanningTree::initialize()
{
	Vertex* pVrtx = getGraph().getpVrtxArray();
	VrtxList vrtxLst;

	this->graph.vertices(vrtxLst); //insert vertex to vertexList
	int num_vertices = graph.getNumVertices(); 
	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED); //set status unvisited

	EdgeList edges;
	this->graph.edges(edges); //insert edges
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED); //set status unvisited
}

void MinimumSpanningTree::initDistMtrx() 
{
	double** ppDistMtrx; //distance matrix
	//double* pLeaseCostMtrx;
	int num_nodes; //size of graph
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int curVID, vID;
	//get details------------------------
	num_nodes = getNumVertices(); 
	pVrtxArray = this->graph.getpVrtxArray();
	pAdjLstArray = this->graph.getpAdjLstArray();
	ppDistMtrx = getppDistMtrx();

	for (int i = 0; i < num_nodes; i++) 
	{
		curVID = pVrtxArray[i].getID(); //get vertex index
		EdgeItor pe = pAdjLstArray[curVID].begin(); //iterator set begin
		while (pe != pAdjLstArray[curVID].end()) 
		{
			vID = (*(*pe).getpVrtx_2()).getID();
			ppDistMtrx[curVID][vID] = (*pe).getDistance(); //insert dinstance to distance matrix
			pe++; //next node
		}
		ppDistMtrx[curVID][curVID] = 0.0;  //what for zero??
	}
}

void MinimumSpanningTree::fprintDistMtrx(ostream& fout)
{
	double** ppDistMtrx;
	Vertex* pVrtxArray;
	int num_nodes;
	double dist;
	int vID;
	string vName;
	pVrtxArray = this->graph.getpVrtxArray();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();
	fout << "\nDistance Matrix of Graph (" << graph.getName() << ") :" << endl;
	fout << "       |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	}
	fout << endl;
	fout << "-------+";
	for (int i = 0; i < num_nodes; i++) 
	{
		fout << "-----";
	}
	fout << endl;
	for (int i = 0; i < num_nodes; i++) 
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName << "  |";
		for (int j = 0; j < num_nodes; j++) 
		{
			dist = ppDistMtrx[i][j];
			if (dist == PLUS_INF)
				fout << "  +oo";
			else
				fout << setw(5) << dist;
		}
		fout << endl;
	}
	fout << endl;
}

enum VertexStatus{ NOT_SELECTED, SELECTED };
void MinimumSpanningTree::PrimJarnikMST()
{
	int num_nodes, num_edges;
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int curVrtx_ID, vrtxID;
	double** ppDistMtrx;
	double* pDist;
	Graph::Edge* pEdge;
	int start, min_id, dist, min_dist, min_dist_org, min_dist_end, end_ID;
	VertexStatus* pVrtxStatus;

	Graph::Edge* pParentEdge, edge, min_edge; // edge that connects this node to the cloud
	list<Graph::Edge> selectedEdgeLst;
	list<Graph::Edge>::iterator edgeItor;


	num_nodes = graph.getNumVertices();
	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();
	initDistMtrx();
	ppDistMtrx = getppDistMtrx();
	pDist = new double[num_nodes];
	pVrtxStatus = new VertexStatus[num_nodes];
	pEdge = new Graph::Edge[num_nodes];
	pParentEdge = new Graph::Edge[num_nodes];
	for (int i = 0; i < num_nodes; i++) 
	{
		pDist[i] = PLUS_INF;
		pVrtxStatus[i] = NOT_SELECTED;
		pParentEdge[i] = Graph::Edge();
	}
	srand(time(0));
	start = rand() % num_nodes; // randomly select start node
	cout << "Start node : " << start << endl;
	pDist[start] = 0;
	selectedEdgeLst.clear();
	for (int round = 0; round < num_nodes; round++) {
		min_dist = PLUS_INF;
		min_id = -1;
		for (int n = 0; n < num_nodes; n++)
		{
			if ((pVrtxStatus[n] == NOT_SELECTED) && (pDist[n] < min_dist)) {
				min_dist = pDist[n];
				min_id = n;
			} // end if
		} // end for
		if (min_id == -1)
		{
			cout << "Error in finding Prim-Jarnik's algorithm !!";
			break;
		}
		pVrtxStatus[min_id] = SELECTED;
		EdgeItor pe = pAdjLstArray[min_id].begin();
		while (pe != pAdjLstArray[min_id].end())
		{
			end_ID = (*(*pe).getpVrtx_2()).getID();
			dist = (*pe).getDistance();
			if ((pVrtxStatus[end_ID] == NOT_SELECTED) && (dist <= pDist[end_ID])) {
				pDist[end_ID] = dist;
				pParentEdge[end_ID] = *pe;
			}
			pe++;
		} // end while
		if (min_id != start) {
			min_edge = pParentEdge[min_id];
			selectedEdgeLst.push_back(min_edge);
		}
		cout << "Dist after round [" << setw(2) << round << "] : ";
		for (int i = 0; i < num_nodes; i++) {
			if (pDist[i] == PLUS_INF)
				cout << " +oo ";
			else
				cout << setw(4) << pDist[i] << " ";
		}
		cout << endl;
	}
	cout << "\nEnd of finding Minimum Spanning Tree by Prim-Jarnik's Algorithm";
	cout << "selectedEdgeLst.size = "<< selectedEdgeLst.size() << endl;
	cout << "Selected edges: " << endl;
	edgeItor = selectedEdgeLst.begin();
	int cnt = 0;
	while (edgeItor != selectedEdgeLst.end())
	{
		cout << *edgeItor << ", ";
		edgeItor++;
		if ((++cnt % 5) == 0)
			cout << endl;
	}
	cout << endl;
}