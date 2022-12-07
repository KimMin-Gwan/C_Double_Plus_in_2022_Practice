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
	cout << "init param" << endl;
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i]; //set least cost pointer to start vertex ID
		pPrev[i] = start_vID;
		pBFS_Process_Stat[i] = NOT_SELECTED; //init not selected
		cout << "pLeastCost[" << i << "] = " << pLeastCost[i] << endl;
		cout << "pPrev[" << i << "] = " << pPrev[i] << endl;
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
		cout << "searching the min ID vertex" << endl;
		for (int i = 0; i < num_nodes; i++) // find a node with LeastCost 
		{
			//minCost보다 더 작은 값은 찾아야함
			cout << endl  << "i = " << i << endl;
			cout << "pLeastCost[" << i << "] = " << pLeastCost[i] << endl;
			cout << "minCost = " << minCost<< endl;
			cout << "pBFS_Porcess_Stat[" << i << "] =  " << ((pBFS_Process_Stat[i] == SELECTED) ? "SELECTED" : "NOTSELECTED") << endl << endl;
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED)) //sequential search
			{
				//더 작은 값을 발견하면 인덱스와 최소 값을 갱신
				minID = i; 
				minCost = pLeastCost[i];

				cout << "We found the Index" << endl;
				cout << "minID = i (" << minID << " = " << i << ")" << endl;
				cout << "minCost = pLeastCost[" << i <<"] (" << minCost<< " = " << pLeastCost[i] << ")" << endl;
			}
		}
		
		if (minID == -1)  //for exception
		{
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
		}

		else //이번에 선택된 노드를 선택됨으로 변경하고 선택한 노드의 수를 증가
		{
			cout << minID << " vertex is now selected " << endl;
			pBFS_Process_Stat[minID] = SELECTED;  //select least cost vertex
			num_selected++; //count up
			cout << "num_selected increased (" << num_selected << ")" << endl << endl;
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

			cout << endl << "if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] >(pLeastCost[minID] + ppDistMtrx[minID][i])))" << endl;
			cout << "pBFS_Porcess_Stat[" << i << "] =  " << ((pBFS_Process_Stat[i] == SELECTED) ? "SELECTED" : "NOTSELECTED") << endl << endl;
			cout << "pLeastCost[" << i << "] = " << pLeastCost[i] << endl;
			cout << "pLeastCost[" << minID << "] (" << pLeastCost[minID] << ") + " <<  "ppDistMtrx[" << minID << "]" << "[" << i << "] (" 
				 << ppDistMtrx[minID][i] << ") = " <<  (pLeastCost[minID] + ppDistMtrx[minID][i]) << endl; 

			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))
			{
				cout << endl << "we found index" << endl;
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];
				cout << "pPrev[" << i << "] = " << minID << endl;
				cout << "pLeastCost[" << i << "] = " << pLeastCost[minID] + ppDistMtrx[minID][i] << endl << endl;
			}
		}
		// print out the pLeastCost[] for debugging
		for (int i = 0; i < num_nodes; i++)
		{
			cout << endl;
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				fout << " +oo";
			else
				fout << setw(5) << pLeastCost[i];
		}
		fout << " ==> selected vertex : " << pVrtxArray[minID] << endl << endl;
		cout << "end of this loop" << endl;
	} // end while()
}


void BreadthFirstSearch::findShortestPath(ostream& fout, Vertex& start, Vertex& target, VrtxList& path)
{
	initialize();
	path.clear();

	initDistMtrx(); //fprintDistMtrx(fout);
	_bfsTraversal(fout, start, target, path);
}

void BreadthFirstSearch::_bfsTraversal(ostream& fout, Vertex& start, Vertex& target, VrtxList& path)
{	int* nodeLevel;
	int num_nodes, num_visited;
	int* pPrev;
	int vID;
	Vertex* pVrtxArray, * pVrtx;
	Vertex vrtx, v;
	Edge e;
	int start_vID, target_vID, cur_vID, vID_1, vID_2;
	VrtxList vrtxs;
	VrtxItor vItor;
	EdgeList edges;
	EdgeItor eItor;
	if (start == target)
	{
		done = true;
		path.push_back(start);
		return;
	}
	pVrtxArray = graph.getpVrtxArray();
	start_vID = start.getID();
	target_vID = target.getID();
	num_nodes = getNumVertices();
	pPrev = new int[num_nodes];
	nodeLevel = new int[num_nodes];
	for (int i = 0; i < num_nodes; i++)
	{
		nodeLevel[i] = -1;
		pPrev[i] = -1;
	}
	graph.vertices(vrtxs);
	visit(start);
	vItor = vrtxs.begin();
	pPrev[start_vID] = start_vID;
	num_visited = 0;
	int level = 0;
	nodeLevel[start_vID] = 0;
	while (num_visited < num_nodes)
	{
		fout << "Level (" << setw(2) << level << ") :";
		// find UN_VISITED Vertex
		vItor = vrtxs.begin();
		while (vItor != vrtxs.end())
		{
			vID = vItor->getID();
			if (isVisited(*vItor) && (nodeLevel[vID] == level))
			{
				fout << *vItor << ", ";
				graph.incidentEdges(*vItor, edges);
				eItor = edges.begin();
				// eItor = edges.begin();
				while (eItor != edges.end())
				{
					pVrtx = eItor->getpVrtx_2();
					if (pVrtx->getvrtxStatus() != VISITED)
					{
						nodeLevel[pVrtx->getID()] = level + 1;
						pVrtx->setVrtxStatus(VISITED);
						eItor->setEdgeStatus(DISCOVERY);
						pPrev[pVrtx->getID()] = vItor->getID();
					}
					else
					{
						eItor->setEdgeStatus(CROSS);
					}
					++eItor;
				} // end while(eItor != edges.end())
				num_visited++;
			} // end if (isVisited() ...)
			++vItor;
		} // end while (vItor != vrtxs.end())
		fout << endl;
		if (num_visited >= num_nodes)
			break;
		level++;
	} // end while (num_visited < num_nodes)
	vID = target_vID;
	while (vID != start_vID)
	{
		pVrtx = &pVrtxArray[vID];
		path.push_front(*pVrtx);
		vID = pPrev[vID];
	}
	path.push_front(pVrtxArray[vID]);
}

void BreadthFirstSearch::visit(Vertex& v)
{
	int numNodes = getGraph().getNumVertices();
	int vID = v.getID();
	if (isValidvID(vID))
	{
		Vertex* pVrtx = getGraph().getpVrtxArray();
		pVrtx[vID].setVrtxStatus(VISITED);
		//pVrtxStatus[vID] = VISITED;
	}
}

bool BreadthFirstSearch::isVisited(Vertex& v)
{
	int numNodes = getGraph().getNumVertices();
	int vID = v.getID();
	if (isValidvID(vID))
	{
		Vertex* pVrtx = getGraph().getpVrtxArray();
		return (pVrtx[vID].getvrtxStatus() == VISITED);
		//return (pVrtxStatus[vID] == VISITED);
	}
}
