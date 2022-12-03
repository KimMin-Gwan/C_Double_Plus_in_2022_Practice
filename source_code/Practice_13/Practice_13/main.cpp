#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS_Dijkstra.h" 
using namespace std;


void fgetGraph(Graph* g, string fin_name)
{
	ifstream fin;
	int num_vrtx;
	string gName, v1, v2;
	double dist;
	Vertex vrtx1, vrtx2, * pVrtx1, * pVrtx2;
	Edge e1, e2;
	int num_edge;
	fin.open(fin_name);
	if (fin.fail())
	{
		cout << "Fail to open an input file " << fin_name << " for graph initialization." << endl;
		exit(1);
	}
	num_edge = 0;
	fin >> gName >> num_vrtx;
	g->initGraph(gName, num_vrtx);
	cout << "Initializing graph (" << gName << ") from input data file(" << fin_name << ") ..." << endl;
	while (!fin.eof())
	{
		fin >> v1 >> v2 >> dist;
		cout << "insert edge (" << v1 << " -> " << v2 << " : " << dist << ")" << endl;
		vrtx1 = Vertex(v1, -1);
		pVrtx1 = g->insertVertex(vrtx1);
		vrtx2 = Vertex(v2, -1);
		pVrtx2 = g->insertVertex(vrtx2);
		e1 = Edge(*pVrtx1, *pVrtx2, dist);
		g->insertEdge(e1);
		e2 = Edge(*pVrtx2, *pVrtx1, dist);
		g->insertEdge(e2);
		num_edge++;
	}
	cout << "Total " << g->getNumVertices() << " vertices and " << num_edge << " bi-directional edges were inserted to graph." << endl;
	fin.close();
}

void main() 
{
	Graph simpleGraph;
	fgetGraph(&simpleGraph, "USA_7_cities.txt");
	VrtxList vtxLst;
	simpleGraph.vertices(vtxLst);
	int count = 0;
	cout << "Inserted vertices: ";
	for (VrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor) {
		cout << *vItor << ", ";
	}
	cout << endl;
	cout << "Inserted edges: " << endl;
	count = 0;
	EdgeList egLst;
	simpleGraph.edges(egLst);
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p) {
		count++;
		cout << *p << ", ";
		if (count % 5 == 0)
			cout << endl;
	}
	cout << endl;
	cout << "Print out Graph based on Adjacency List .." << endl;
	simpleGraph.fprintGraph(cout);
	VrtxList path;
	BreadthFirstSearch bfsGraph(simpleGraph);
	cout << "\nTesting Breadth First Search with Dijkstra Algorithm" << endl;
	bfsGraph.initDistMtrx();
	bfsGraph.fprintDistMtrx(cout);
	path.clear();
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	while (1)
	{
		cout << "Input start and end of path to search shortest path (. . to quit) : ";
		cin >> start_nm;
		if (start_nm == ".")
			break;
		cin >> end_nm;
		pStart = simpleGraph.getVertex(start_nm);
		pEnd = simpleGraph.getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex name !!" << endl;
			exit(1);
		}
		cout << "Dijkstra Shortest Path Finding from " << pStart->getName() << " to " << pEnd->getName() << " .... " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " -> ";
		}
		cout << endl;
		pEnd = simpleGraph.getVertex(start_nm); // test with reverse direction
		pStart = simpleGraph.getVertex(end_nm);
		cout << "Dijkstra Shortest Path Finding from " << pStart->getName() << " to " << pEnd->getName() << " .... " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " -> ";
		}
		cout << endl;
	}
}