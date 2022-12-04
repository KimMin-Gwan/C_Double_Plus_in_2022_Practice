#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;
#define PLUS_INF INT_MAX/2
enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED, EDGE_NOT_FOUND };

class Graph // Graph based on Adjacency Matrix
{
public:
	class Vertex; // == node
	class Edge; // == line
	typedef std::list<Graph::Vertex> VrtxList;
	typedef std::list<Graph::Edge> EdgeList;
	typedef std::list<Graph::Vertex>::iterator VrtxItor;
	typedef std::list<Graph::Edge>::iterator EdgeItor;
private:
	string name; //graph name 
	Vertex* pVrtxArray; //Vertex array pointer
	EdgeList* pAdjLstArray; //adjust list array
	int num_vertices; //size of graph
public:
	class Vertex // node
	{
		friend ostream& operator<<(ostream& fout, Vertex v)
		{
		fout << v.getName();
		return fout;
		}
	public:
		Vertex() : name(), ID(-1) {}
		Vertex(string n, int id) : name(n), ID(id) { }
		Vertex(int id) : ID(id) {}
		//accesser, mutator and overloading-----------------------------------
		string getName() { return name; } //get name
		void setName(string c_name) { name = c_name; } //set name
		int getID() { return ID; }  // get id
		void setID(int id) { ID = id; } // set id
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; } //set vertex
		VrtxStatus getvrtxStatus() { return vrtxStatus; } //get vertex
		bool operator==(Vertex other) { return ((ID == other.getID()) && (name == other.getName())); }
		bool operator!=(Vertex other) { return ((ID != other.getID()) || (name != other.getName())); }
	private:
		string name; //name
		int ID; //index
		VrtxStatus vrtxStatus; //status
	};
public:
	class Edge // Graph::Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e)
		{
			fout << "Edge(" << setw(2) << *e.getpVrtx_1() << ", " << setw(2) << *e.getpVrtx_2();
			fout << ", " << setw(2) << e.getDistance() << ")";
			return fout;
		}
	public:
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {}

		Edge(Vertex& v1, Vertex& v2, double d)
			:distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED) { }

		void endVertices(VrtxList& vrtxLst)
		{
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}

		Vertex opposite(Vertex v)
		{
			//opposite vertex of input vertex
			if (v == *pVrtx_1) 
				return *pVrtx_2;
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			//not exist vertex
			else
			{
				cout << "Error in opposite()" << endl;
				return Vertex(NULL);
			}
		}

		//accesser and mutator -------------------------------------
		Vertex* getpVrtx_1() { return pVrtx_1; }  //get first vertex
		Vertex* getpVrtx_2() { return pVrtx_2; } //get second vertex
		double getDistance() { return distance; } //get distance of vertexex
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; } //set first vertex
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; } //set second vertex
		void setDistance(double d) { distance = d; } //set distanc of vertexes
		bool operator!=(Edge e) { return ((pVrtx_1 != e.getpVrtx_1()) || (pVrtx_2 != e.getpVrtx_2())); } 
		bool operator==(Edge e) { return ((pVrtx_1 == e.getpVrtx_1()) && (pVrtx_2 == e.getpVrtx_2())); }
		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; } //set statut
		EdgeStatus getEdgeStatus() { return edgeStatus; }
	private:
		Vertex* pVrtx_1; //first
		Vertex* pVrtx_2; //second
		double distance; //distance 
		EdgeStatus edgeStatus; //status
	};
public:
	Graph()
		: name(""), pVrtxArray(NULL), pAdjLstArray(NULL), num_vertices(0) {} // default constructor
	Graph(string nm, int num_nodes)
		: name (nm), pVrtxArray(NULL), pAdjLstArray(NULL)
	{
		//num_vertices = num_nodes;
		this->pVrtxArray = new Graph::Vertex[num_nodes];
		for (int i = 0; i<num_nodes; i++) // set all vertex as NULL 
			this->pVrtxArray[i] = NULL;
		this->pAdjLstArray = new EdgeList[num_nodes];

		for (int i = 0; i< num_nodes; i++) //clear the adjacency list array
			this->pAdjLstArray[i].clear();
		this->num_vertices = 0; 
		// num_vertices is increased at insertVertex
	}

	string getName() { return name; }

	void initGraph(string nm, int num_nodes)
	{
		this->name = nm;
		this->pVrtxArray = new Graph::Vertex[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			this->pVrtxArray[i] = NULL;
		this->pAdjLstArray = new EdgeList[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			this->pAdjLstArray[i].clear();
		this->num_vertices = 0;
	}

	void vertices(VrtxList& vrtxLst) 
	{
		vrtxLst.clear();
		for (int i = 0; i < getNumVertices(); i++) //push back
			vrtxLst.push_back(this->pVrtxArray[i]); 
	}
	
	void edges(EdgeList& edges) 
	{
		EdgeItor eItor;
		Graph::Edge e;
		edges.clear();
		for (int i = 0; i < getNumVertices(); i++) 
		{
			eItor = this->pAdjLstArray[i].begin();
			while (eItor != this->pAdjLstArray[i].end()) 
			{
				e = *eItor;
				edges.push_back(e);
				eItor++;
			}
		}
	}

	Vertex* insertVertex(Vertex& newV)  //insert vertex
	{
		int vID;
		string vName;

		vName = newV.getName(); //get vertex name 
		//exception handling------------------------------
		for (int i = 0; i < this->num_vertices; i++)  //check all vertex to find same vertex
		{
			if (this->pVrtxArray[i].getName() == vName) //if same vertex exists
				return &pVrtxArray[i]; //return the same vertex pointer
		}
		//-----------------------------------------------
		
		vID = this->num_vertices;
		newV.setID(vID); //id of the new vertex is the number of vertex
		if (pVrtxArray[vID] == NULL) //if the index of vertex array is null
		{
			pVrtxArray[vID] = newV; //insert new vertex
			this->num_vertices++;  //increase size
		}
		return &pVrtxArray[vID];  //return new vertex
	}

	Vertex* getVertex(string vName) //get vertex
	{ 
		for (int i = 0; i < this->num_vertices; i++) //sequential searching
		{
			if (pVrtxArray[i].getName() == vName)
				return &pVrtxArray[i]; // vertex is already existing 
		}
		return NULL;
	}

	void insertEdge(Edge & e)  //insert edge
	{
		Vertex vrtx_1, vrtx_2;
		Vertex* pVrtx;
		int vrtx_1_ID, vrtx_2_ID;
		//Gets both vertex of edge -------
		vrtx_1 = *e.getpVrtx_1();
		vrtx_2 = *e.getpVrtx_2();
		vrtx_1_ID = vrtx_1.getID();
		vrtx_2_ID = vrtx_2.getID();
		//if each vertex is empty, insert vertex------------------
		if (pVrtxArray[vrtx_1_ID] == NULL)
			pVrtxArray[vrtx_1_ID] = vrtx_1;
		if (pVrtxArray[vrtx_2_ID] == NULL) 
			pVrtxArray[vrtx_2_ID] = vrtx_2;
		//link both vertex
		e.setpVrtx_1(&pVrtxArray[vrtx_1_ID]);
		e.setpVrtx_2(&pVrtxArray[vrtx_2_ID]);
		// indsert edge to adjacency list array's back (insert stack)
		pAdjLstArray[vrtx_1_ID].push_back(e);
	}

	int getNumVertices() { return num_vertices; }
	Vertex* getpVrtxArray() { return pVrtxArray; }
	EdgeList* getpAdjLstArray() { return pAdjLstArray; }

	void incidentEdges(Vertex v, EdgeList & edgeLst) //what is it for?
	{
		Graph::Edge e;
		EdgeItor eItor;
		int vID = v.getID(); 
		eItor = pAdjLstArray[vID].begin();
		while (eItor != pAdjLstArray[vID].end())
		{
			e = *eItor;
			edgeLst.push_back(e);
			eItor++;
		}
	}


	bool isValidvID(int vid) //valid index
	{
		if ((vid >= 0) && (vid < num_vertices))
			return true;
		else
		{
			//cout << "Vertex ID (" << vid << ") is invalid for Graph (" << getName();
			//cout << ") with num_vertices (" << num_vertices << ")" << endl;
			return false;
		}
	}

	void fprintGraph(ostream & fout) //print
	{
		int i, j;
		EdgeItor eItor;
		Graph::Edge e;
		int numOutgoingEdges;
		fout << this->getName() << " with " << this->getNumVertices() << " vertices has following adjacency lists :" << endl;
		for (i = 0; i < num_vertices; i++)
		{
			fout << " vertex (" << setw(3) << pVrtxArray[i].getName() << ") : ";
			numOutgoingEdges = pAdjLstArray[i].size();
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				e = *eItor;
				fout << e << " ";
				eItor++;
			}
			fout << endl;
		}
	} // end fprintGraph()
};

#endif