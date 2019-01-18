#pragma once
#include "stdafx.h"
#include "ADTTree.h"


template<typename T>
class NodeEdge
{
public:
	NodeEdge() : next(nullptr) {};

	NodeEdge(const int a) : adjVer(a), next(nullptr) {}

	NodeEdge(const int a, const int b) : adjVer(a), weight(b), next(nullptr) {}

	~NodeEdge() {};

	int adjVer;
	double weight;
	NodeEdge<T> * next;

private:

};


template<typename T>
class NodeVertex
{
public:
	NodeVertex() : firstEdge(nullptr) {};
	//NodeVertex(const T& d, double x=1) : data(d), weight(x){};
	~NodeVertex() {};

	T data;
	NodeEdge<T> * firstEdge;

private:

};


template<typename T>
class Graph
{
public:
	Graph() = default;

	// create a full edges graph
	Graph(const int v) : edgeNum(v*(v - 1) / 2), vertexNum(v) 
	{
		nodeVers.clear();
		NodeVertex<T> * currVer = nullptr;;
		
		for (int i = 0; i < vertexNum; ++i)
		{
			currVer = new NodeVertex<T>();
			std::cout << "vertex: " << i << " @ " << currVer << std::endl;

			nodeVers.push_back(currVer);
			NodeEdge<T> * currEdge = nullptr;
			//edgeNum for each vertex is factorial
			for (int j = 0; j < vertexNum - i-1; ++j)
			{
				NodeEdge<T> * nodeEdge = new NodeEdge<T>(j+1);
				if (j == 0)
				{
					currVer->firstEdge = nodeEdge;
					currVer->data = i;				
					//std::cout << " firstedge: " << i << " => " << " @ " << currEdge->next << std::endl;
				}
				else
				{
					currEdge->next = nodeEdge;
				}
				currEdge = nodeEdge;
				std::cout << "  edge:" << i << " => " << currEdge->adjVer << " @ " << nodeEdge << std::endl;
			}

		}
	};

	// create graph according user input
	Graph(const std::vector<std::pair<int, int>> &p, const int v, const int e, const std::vector<T> &w) :
		edgeNum(e), vertexNum(v), edgePair(p), weights(w)
	{
		std::cout << "creat a graph: " << std::endl;
		nodeVers.clear();
		NodeVertex<T> * currVer = nullptr;

		for (int i = 0; i < vertexNum; ++i)
		{
			currVer = new NodeVertex<T>();
			nodeVers.push_back(currVer);
			bool flag = true;
			NodeEdge<T> *curEdge = nullptr;
			std::cout << "vertex: " << i << " @ " << currVer << std::endl;

			for (int j = 0; j < edgeNum; ++j)
			{
				if (i == edgePair[j].first)
				{
					if (flag)
					{
						flag = false;
						curEdge = new NodeEdge<T>(edgePair[j].second, weights[j]);
						currVer->firstEdge = curEdge;
						std::cout << " edge: " << i << " => " << edgePair[j].second << std::endl;
					}
					else
					{
						curEdge->next = new NodeEdge<T>(edgePair[j].second, weights[j]);
						std::cout << " edge: " << i << " => " << edgePair[j].second << std::endl;
						curEdge = curEdge->next;
					}

				}
			}
		}
	};

	// depth search
	void DFS();

	// breadth search
	void BFS();

	// prim algorithm finds a minimum spanning tree
	void Prim();

	// get minimum
	int GetMiniDistance(const std::vector<int> &dist, const std::vector<bool> &visited);

	// Dijkstra
	void Dijstra(const int src, const int dst);

	~Graph() {};

	int vertexNum;
	int edgeNum;
	std::vector<std::pair<int, int> > edgePair;

	std::vector<NodeVertex<T> *> nodeVers;
	std::vector<int> weights;

private:

};

template<typename T>
void Graph<T>::DFS()
{
	NodeVertex<T> *nodeVer = nodeVers[0];
	NodeEdge<T> *nodeEdge = nullptr;
	
	std::stack<NodeVertex<T> *> s;
	std::vector<bool> verVisited(vertexNum, false);
	verVisited[0] = true;
	s.push(nodeVer);
	std::cout << "First Verter: 0" << std::endl;

	while (!s.empty())
	{
		nodeVer = s.top();
		nodeEdge = nodeVer->firstEdge;
		while (nodeEdge)
		{
			int adjVerNum = nodeEdge->adjVer;  // number of vertex
			if (!verVisited[adjVerNum])
			{
				verVisited[adjVerNum] = true;
				std::cout << "First Verter: " << adjVerNum << std::endl;

				s.push(nodeVers[adjVerNum]);
				break;
			}
			nodeEdge = nodeEdge->next;
		}

		if (!nodeEdge) s.pop();  // if all the adj vertexs were found and have been visited, then back
	}
}

template<typename T>
void Graph<T>::BFS()
{
	std::cout << "BFS for a graph:" << std::endl;
	std::vector<bool> visited;
	std::queue<NodeVertex<T> *> q;

	for (int i=0; i< vertexNum; ++i)
	{
		visited.push_back(false);
	}

	for (int i = 0; i< vertexNum; ++i)
	{
		if(visited[i]) continue;

		std::cout << "vertex: " << i << std::endl;
		visited[i] = true;
		q.push(nodeVers[i]);

		while (!empty(q))
		{
			NodeVertex<T> *vertex = q.front();
			q.pop();
			NodeEdge<T> *edge = vertex->firstEdge;
			while (edge != nullptr)
			{
				if (!visited[edge->adjVer])
				{
					visited[edge->adjVer] = true;
					std::cout << "vertex: " << edge->adjVer << " ==> " << i << std::endl;
					q.push(nodeVers[edge->adjVer]);
				}
				edge = edge->next;
			}
		}

	}
}

template<typename T>
void Graph<T>::Prim()
{
	std::cout << "Prim algorithm to find a minimum spanning tree " << std::endl;
	std::vector<int> dist(vertexNum, MAX_INT);
	dist[0] = 0;
	std::vector<int> adjVer(vertexNum, 0);

	// first node
	NodeVertex<T> *vertex = nodeVers[0];
	NodeEdge<T> *nodeEdge = vertex->firstEdge;
	
	while (nodeEdge !=nullptr)
	{
		if (nodeEdge->weight < MAX_INT)
		{
			dist[nodeEdge->adjVer] = nodeEdge->weight;
			adjVer[nodeEdge->adjVer] = 0;               // init adj vertexs as 0
		}
		nodeEdge = nodeEdge->next;
	}

	// beign process
	for (int i = 1; i < vertexNum; ++i)
	{
		// search the minimun edge
		int min = MAX_INT;
		int kVertex = 0;
		for (int i = 1; i < vertexNum; ++i)
		{
			if (dist[i] < min && dist[i] != 0)
			{
				min = dist[i];
				kVertex = i;
			}
		}
		//int kVertex = GetMiniDistance(dist, visited);
		
		for each (auto var in dist)
		{
			std::cout << var << " ";
		}
		std::cout << std::endl;

		dist[kVertex] = 0;
		std::cout << "find the vertex from: " << adjVer[kVertex] << " => "<< kVertex <<
			", with edge weight of " << min << std::endl;

		// update dist and adjVer
		nodeEdge = nodeVers[kVertex]->firstEdge;
		while (nodeEdge != nullptr)
		{
			if (dist[nodeEdge->adjVer] != 0 && nodeEdge->weight < dist[nodeEdge->adjVer])
			{
				dist[nodeEdge->adjVer] = nodeEdge->weight;
				adjVer[nodeEdge->adjVer] = kVertex;               // init adj vertexs as 1
			}
			nodeEdge = nodeEdge->next;
		}
	}
}

template<typename T>
int Graph<T>::GetMiniDistance(const std::vector<int> &dist, const std::vector<bool> &visited)
{
	int min = MAX_INT;
	int kVertex = 0;
	for (int i = 0; i < vertexNum; ++i)
	{
		if (dist[i] < min && visited[i] == false)
		{
			min = dist[i];
			kVertex = i;
		}
	}

	return kVertex;
}

template<typename T>
void Graph<T>::Dijstra(const int src, const int dst)
{
	std::vector<int> dist(vertexNum, INT_MAX);  // store the distance of each vertex from the begin vertex
	dist[src] = 0;  // first vertex set to 0
	std::vector<bool> visited(vertexNum, false); // store the visited status for each vertex

	NodeEdge<T> *nodeEdge = nodeVers[src]->firstEdge;

	// for each vertex
	for (int i = 0; i < vertexNum; ++i)
	{
		// get mini
		int u = GetMiniDistance(dist, visited);
		visited[u] = true; 
		// print
		std::cout << "Vertex: " << u << " with weight of: " << dist[u] << std::endl;
		for (int iv = 0; iv < vertexNum; ++iv)
		{
			if (visited[iv]) std::cout << "=>" << iv;
		}
		std::cout << std::endl;

		// reprocess
		nodeEdge = nodeVers[u]->firstEdge;
		while (nodeEdge != nullptr)
		{
			int v = nodeEdge->adjVer;
			if (visited[v] == false && nodeEdge->weight + dist[u] < dist[v] && dist[u] != MAX_INT)
			{
				dist[v] = nodeEdge->weight + dist[u];
			}
			nodeEdge = nodeEdge->next;
		}
	}
}