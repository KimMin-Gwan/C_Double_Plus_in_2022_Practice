/**
*파일명 : "Practice_13"
*프로그램의 목적 및 기본 기능: 
*      -이 프로그램은 Graph자료구조를 넓이 우선탐색을 사용하여 노드간의
*       최단 거리를 구하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 12월 05일)
*최종 Update : Version 1.0, 2022년 12월 05일(김민관)
*============================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS_Dijkstra.h"
#include "DepthFirstSearch.h"
using namespace std;

void fgetGraph(Graph* g, string fin_name);				// Get Graph data from file
void test_DijkstraShortestPathSearch(Graph* pG);
void test_BreadthFirstSearch(Graph* pG);
void test_DepthFirstSearch(Graph* pG);

void main()
{
	Graph simpleGraph;
	int test_mode;
	fgetGraph(&simpleGraph, "USA_7_cities.txt");		// get 2 x 3 mesh data from file
	//fgetGraph(&simpleGraph, "Mesh_4x4.txt");			// get 4 x 4 mesh data from file
	//fgetGraph(&simpleGraph, "USA_7_cities.txt");		// get USA city data from file
	simpleGraph.fprintGraph(cout);						// print out Graph
	cout << endl;
	while (1)
	{
		cout << ">>>Input Test Mode" << endl << "1 : Depth_First_Search(DFS)" << endl << "2 : Breadth_First_Search(BFS)" << endl
			<< "3 : Dijkstra_Shortest_Path_Search" << endl << "0 : Quit" << endl << "Input Test Menu : ";
		cin >> test_mode;		// input test mode
		switch (test_mode)
		{
		case 1:
			test_DepthFirstSearch(&simpleGraph);
			break;
		case 2:
			test_BreadthFirstSearch(&simpleGraph);
			break;
		case 3:
			test_DijkstraShortestPathSearch(&simpleGraph);
			break;
		case 0:
			return;
		}
	}
}

void fgetGraph(Graph* g, string fin_name)				// Get Graph data from file
{
	ifstream fin;
	int num_vrtx;
	string gName, v1, v2;
	double dist;
	Vertex vrtx1, vrtx2, * pVrtx1, * pVrtx2;
	Edge e1, e2;
	int num_edge = 0;
	fin.open(fin_name);									// open input file
	if (fin.fail())										// file open check
	{
		cout << "Fail to open an input file " << fin_name << " for graph initialization." << endl;
		exit(1);
	}
	fin >> gName >> num_vrtx;							// get graph name and vertex
	g->initGraph(gName, num_vrtx);
	cout << "Initializing graph (" << gName << ") from input data file(" << fin_name << ") ..." << endl;
	while (!fin.eof())									// until end of file
	{
		fin >> v1 >> v2 >> dist;						// vertex1, vertex2, distance
		cout << "insert edge (" << v1 << " -> " << v2 << " : " << dist << ")" << endl;
		vrtx1 = Vertex(v1, -1);
		pVrtx1 = g->insertVertex(vrtx1);				// insert vertex
		vrtx2 = Vertex(v2, -1);
		pVrtx2 = g->insertVertex(vrtx2);				// insert vertex
		e1 = Edge(*pVrtx1, *pVrtx2, dist);
		g->insertEdge(e1);								// insert edge
		e2 = Edge(*pVrtx2, *pVrtx1, dist);
		g->insertEdge(e2);								// insert edge
		num_edge++;
	}
	cout << "Total " << g->getNumVertices() << " vertices and " << num_edge << " bi-directional edges were inserted to graph." << endl;
	fin.close();
}

void test_DijkstraShortestPathSearch(Graph* pG)
{
	VrtxList path;
	BreadthFirstSearch bfsGraph(*pG);
	cout << "\nTesting Breadth First Search with Dijkstra Algorithm" << endl;
	bfsGraph.initDistMtrx();
	bfsGraph.fprintDistMtrx(cout);
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	while (1)
	{
		cout << "Input start and end of path to search shortest path (. to quit) : ";
		cin >> start_nm;
		if (start_nm == ".")
			break;
		cin >> end_nm;
		pStart = pG->getVertex(start_nm);
		pEnd = pG->getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex name !!" << endl;
			exit(1);
		}
		cout << "Dijkstra Shortest Path Finding from " << pStart->getName();
		cout << " to " << pEnd->getName() << " .... " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from :" << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " -> ";
		}
		cout << endl;
		pEnd = pG->getVertex(start_nm);
		pStart = pG->getVertex(end_nm);
		cout << "Dijkstra Shortest Path Finding from " << pStart->getName();
		cout << " to " << pEnd->getName() << " .... " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by DijkstraShortestPath from " << *pStart << " to " << *pEnd << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		{
			cout << *vItor;
			if (*vItor != *pEnd)
				cout << " -> ";
		}
		cout << endl;
	} // end while
}

void test_BreadthFirstSearch(Graph* pG)
{
		cout << "\n*********************************************" << endl;
	cout << "Testing bfsGraph..." << endl;
	BreadthFirstSearch bfsGraph(*pG);
	bfsGraph.fprintDistMtrx(cout);
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	Graph::VrtxList path;
	while (1)
	{
		cout << "Input start and end of path to search shortest path (. to quit) : ";
		cin >> start_nm;
		if (start_nm == ".")
			break;
		cin >> end_nm;
		pStart = pG->getVertex(start_nm);
		pEnd = pG->getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex name !!" << endl;
			return;
		}
		path.clear();
		cout << "\nFinding shortest paths (using BFS) from " << pStart->getName() << " to " << pEnd->getName() << " : " << endl;
		bfsGraph.findShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by BFS (shortest) from " << pStart->getName() << " to " << pEnd->getName() << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
			cout << *vItor << " ";
		cout << endl;
		bfsGraph.findShortestPath(cout, *pEnd, *pStart, path);
		cout << "Path found by BFS (shortest) from " << pEnd->getName() << " to " << pStart->getName() << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
			cout << *vItor << " ";
		cout << endl;
	}
}

void test_DepthFirstSearch(Graph* pG)
{
	cout << "\n*****************************************************************************" << endl;
	cout << "Testing dfsGraph..." << endl;
	DepthFirstSearch dfsGraph(*pG);
	dfsGraph.showConnectivity(cout);
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	VrtxList path;
	while (1)
	{
		cout << "Input start and end of path to search shortest path (. to quit) : ";
		cin >> start_nm;
		if (start_nm == ".")
			break;
		cin >> end_nm;
		pStart = pG->getVertex(start_nm);
		pEnd = pG->getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex name !!" << endl;
			exit(1);
		}
		dfsGraph.findPath(*pStart, *pEnd, path);
		cout << "\nPath found by DFS (" << pStart->getName() << " => " << pEnd->getName() << ") : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
			cout << setw(4) << *vItor << " ";
		cout << endl;
		dfsGraph.findPath(*pEnd, *pStart, path);
		cout << "Path found by DFS (" << pEnd->getName() << " => " << pStart->getName() << ") : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
			cout << setw(4) << *vItor << " ";
		cout << endl;
	}
}



