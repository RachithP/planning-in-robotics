#include "costmap.h"
#include <cmath>


// This function is to create the weight/cost matrix
costmap::Matrix::Matrix(heap::MinHeap* pq)
{
//	const size_t N = pq->size();
//	std::cout << "Length of the vector is " << N << "\n";	
	for (auto it = pq->getVector()->begin(); it != pq->getVector()->end(); it++)
	{
//		std::cout << (**it).getiD() << "\n";
		for (auto jt = pq->getVector()->begin(); jt != pq->getVector()->end(); jt++)
		{
//			std::cout << "Element number is [" << (**it).getiD() << "," << (**jt).getiD() << "]" << "\n";
			edge::Edge* line = new edge::Edge((*it), (*jt));
			costMap[(*it)][(*jt)] = line;
		}
	}
}

// This function is to print the elements of the weight/cost matrix
void costmap::Matrix::printCostMap()
{
	std::cout << costMap.size() << "\n";
	std::cout << costMap[0].size() << "\n";
	
	std::map<vertex::Vertex*, std::map<vertex::Vertex*, edge::Edge*>>::iterator it = costMap.begin();
	while (it != costMap.end())
	{
		std::cout << (it->first)->getiD() << "\n";
		for (auto jt = (it->second).begin(); jt != (it->second).end(); jt++)
		{
			std::cout << (jt->first)->getiD() << "::::"<<(jt->second)->getWeight()<<"\n";
		}
		it++;
	}
}
