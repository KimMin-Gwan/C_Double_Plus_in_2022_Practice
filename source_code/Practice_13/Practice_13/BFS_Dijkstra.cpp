#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Graph.h"
#include "BFS_Dijkstra.h" 
using namespace std;

void BreadthFirstSearch::initialize()
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

void BreadthFirstSearch::initDistMtrx() 
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

void BreadthFirstSearch::fprintDistMtrx(ostream& fout)
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

enum BFS_PROCESS_STATUS { NOT_SELECTED, SELECTED };
void BreadthFirstSearch::DijkstraShortestPath(ostream& fout, Vertex& start, Vertex& target, VrtxList& path)
{
	double** ppDistMtrx;
	double* pLeastCost, minCost;
	int num_nodes, num_selected, minID;
	BFS_PROCESS_STATUS* pBFS_Process_Stat;
	int* pPrev;
	Vertex* pVrtxArray;
	Vertex vrtx, * pPrevVrtx, v;
	Edge e;
	int start_vID, target_vID, curVID, vID;

	EdgeList* pAdjLstArray; //근접 edge 포인터
	pVrtxArray = graph.getpVrtxArray(); //노드 어레이
	pAdjLstArray = graph.getpAdjLstArray(); //근접 노드 어레이 
	start_vID = start.getID(); //시작노드 
	target_vID = target.getID(); //목표 노드
	num_nodes = getNumVertices(); //총 노드 갯수
	ppDistMtrx = getppDistMtrx(); // 표로 표현된 주변 노드간의 거리
	pLeastCost = new double[num_nodes]; // 동적할당
	pPrev = new int[num_nodes]; //근접 노드?
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes]; //선택했었는지 아닌지 확인하기 위한 파라미터

	//
	//  A -- 3 -- B --- 5 --- E
	//  |                     |
	//  |                     |
	//  5                     |
	//  |                     |
	//  C --4--- D ----- 7 ----
	//  |        |
	//  |        |
	//  |        4
	//  5        |
	//  |        |
	//  -------- F
	//
	//    ppDistMtrx[][]
	//        A   B   C   D   E   F   
	//        0   1   2   3   4   5
	//
	// A 0    0   3   5  oo  oo  oo
	// B 1    3   0  oo  oo   5  oo
	// C 2    5  oo   0   4  oo   5 
	// D 3   oo  oo   4   0   7   4
	// E 4   oo   5  oo   7   0  oo
	// F 5   oo  oo   5   4  oo   0
	//   
	//
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i]; //set least cost pointer to start vertex ID
		pPrev[i] = start_vID;
		pBFS_Process_Stat[i] = NOT_SELECTED; //init not selected
	}
	pBFS_Process_Stat[start_vID] = SELECTED;  //start node set selected
	num_selected = 1;
	path.clear();
	int round = 0;
	int cost;
	string vName;
	fout << "Dijkstra::Least Cost from Vertex (" << start.getName() << ") at each round : " << endl;
	fout << " |";

	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	}

	fout << endl;
	fout << "-----------+";
	for (int i = 0; i < num_nodes; i++)
	{
		fout << setw(5) << "-----";
	}
	fout << endl;
	//--------------------------------------------------

	while (num_selected < num_nodes)
	{
		round++;
		fout << "round [" << setw(2) << round << "] |";
		minID = -1;
		minCost = PLUS_INF;
		for (int i = 0; i < num_nodes; i++) // find a node with LeastCost 
		{
			//minCost보다 더 작은 값은 찾아야함
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED)) //sequential search
			 {//더 작은 값을 발견하면 인덱스와 최소 값을 갱신
				minID = i; 
				minCost = pLeastCost[i];
			}
		}
		
		if (minID == -1)  //for exception
		{
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
		}

		else //이번에 선택된 노드를 선택됨으로 변경하고 선택한 노드의 수를 증가
		{
			pBFS_Process_Stat[minID] = SELECTED;  //select least cost vertex
			num_selected++; //count up
			//근데 만약에 이번에 선택한 노드가 목표노드라면 while문을 탈출해야함 == 탐색이 끝남
			if (minID == target_vID) 
			{
				fout << endl << "reached to the target node ("
					<< pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl; 
				vID = minID;

				do { // 경로로 지정해야함
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];
				} while (vID != start_vID); 

				vrtx = pVrtxArray[vID];
				path.push_front(vrtx); // start node
				break;
			}
		}
		/* Edge relaxation */
		for (int i = 0; i < num_nodes; i++)
		{
			if ((pBFS_Process_Stat[i] != SELECTED) &&
				(pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))
			{
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];
			}
		}
		// print out the pLeastCost[] for debugging
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				fout << " +oo";
			else
				fout << setw(5) << pLeastCost[i];
		}
		fout << " ==> selected vertex : " << pVrtxArray[minID] << endl;
	} // end while()
}
