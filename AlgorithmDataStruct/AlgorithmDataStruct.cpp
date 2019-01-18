// AlgorithmDataStruct.cpp: 
//

#include "stdafx.h"
#include "Sort.h"
#include "ADTTree.h"
#include "ADTGarph.h"
#include "Finding.h"

int main()
{
	/* quicck sort */
	std::vector<int> vec = {50, 10, 90, 30, 70, 40, 80, 30, 20};
	if (QuickSort(vec))
	{
		for each (auto var in vec)
		{
			std::cout << var << " ";
		}
		std::cout << std::endl;
	}


	/* tree */
	ADTTree<int> adtTree;
	adtTree.Create();
	adtTree.PrintLevelOrder();
	adtTree.PrintPreorder();
	adtTree.PrintInOrder();
	
	/*binary sort tree*/
	ADTBSTree<int> adtBSTree;
	// create
	adtBSTree.Create();
	// search
	Node<int> *node = new Node<int>();
	adtBSTree.Search(2, node);
	delete node;
	// insert
	std::vector<int> addtreeVec = { 1,2,3,4,5,6 };
	adtBSTree.Insert(addtreeVec);

	/* graph */ 
	std::cout << "Create a graph" << std::endl;
	// automatic create a tree
	Graph<int>* graph = new Graph<int>(4);
	//graph->BFS();

	// create a tree by user input vertex and edge
	std::vector<std::pair<int, int>> edgePair;
	edgePair.push_back(std::make_pair(0, 1));
	edgePair.push_back(std::make_pair(0, 2));
	edgePair.push_back(std::make_pair(1, 2));
	edgePair.push_back(std::make_pair(1, 3));
	edgePair.push_back(std::make_pair(2, 3));
	edgePair.push_back(std::make_pair(3, 4));
	edgePair.push_back(std::make_pair(4, 5));
	edgePair.push_back(std::make_pair(5, 1));
	edgePair.push_back(std::make_pair(6, 2));
	std::vector<int> weights(edgePair.size(), 1);
	graph = new Graph<int>(edgePair, 7, edgePair.size(), weights);
	//graph->BFS();

	// prim algorithm to find a minimum spanning tree
	edgePair.clear();
	edgePair.push_back(std::make_pair(0, 1));  // 10
	edgePair.push_back(std::make_pair(0, 5));  // 11
	edgePair.push_back(std::make_pair(1, 0));  // 10
	edgePair.push_back(std::make_pair(1, 2));  // 18
	edgePair.push_back(std::make_pair(1, 6));  // 16
	edgePair.push_back(std::make_pair(1, 8));  // 12
	edgePair.push_back(std::make_pair(2, 1));  // 18
	edgePair.push_back(std::make_pair(2, 8));  // 8
	edgePair.push_back(std::make_pair(2, 3));  // 22
	edgePair.push_back(std::make_pair(3, 2));  // 22
	edgePair.push_back(std::make_pair(3, 4));  // 20
	edgePair.push_back(std::make_pair(3, 6));  // 24
	edgePair.push_back(std::make_pair(3, 7));  // 16
	edgePair.push_back(std::make_pair(3, 8));  // 21
	edgePair.push_back(std::make_pair(4, 3));  // 20
	edgePair.push_back(std::make_pair(4, 5));  // 26
	edgePair.push_back(std::make_pair(4, 7));  // 7
	edgePair.push_back(std::make_pair(5, 0));  // 11
	edgePair.push_back(std::make_pair(5, 6));  // 17
	edgePair.push_back(std::make_pair(5, 4));  // 26
	edgePair.push_back(std::make_pair(6, 1));  // 16
	edgePair.push_back(std::make_pair(6, 5));  // 17
	edgePair.push_back(std::make_pair(6, 7));  // 19
	edgePair.push_back(std::make_pair(6, 3));  // 24
	edgePair.push_back(std::make_pair(7, 6));  // 19
	edgePair.push_back(std::make_pair(7, 3));  // 16
	edgePair.push_back(std::make_pair(7, 4));  // 7
	edgePair.push_back(std::make_pair(8, 1));  // 12
	edgePair.push_back(std::make_pair(8, 2));  // 8
	edgePair.push_back(std::make_pair(8, 3));  // 21	

	weights.clear();
	weights = { 10 , 11, 10, 18, 16, 12, 18, 8, 22, 22,
		20, 24, 16, 21, 20, 26, 7, 11, 17, 26, 16,
		17, 19, 24, 19, 16 , 7, 12, 8, 21 };
	graph = new Graph<int>(edgePair, 9, edgePair.size(), weights);
	graph->DFS();

	graph->Prim();

	graph->Dijstra(0, 9);


	// finding
	std::vector<int> dataF = { 0,1,1,2,3,4,5,6,8,9,10,11,11,15,26,41,42,49,53 };
	Finder<int> finder(dataF);
	finder.SeqFinder(5);
	finder.BinaryFinder(15);

	system("pause");

    return 0;
}

