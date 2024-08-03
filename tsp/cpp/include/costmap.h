#ifndef COST_MAP
#define COST_MAP

#include "edge.h"
#include "minheap.h"
#include <map>

// This header file is to create an weight/cost matrix for all the vertices assuming a complete graph.
namespace costmap{
	class Matrix{
		std::map<vertex::Vertex*, std::map<vertex::Vertex*, edge::Edge*>> costMap;
	public:
		Matrix(heap::MinHeap*);		//Constructor
		edge::Edge* getEdge(vertex::Vertex* a, vertex::Vertex* b) {return costMap[a][b];};
		std::map<vertex::Vertex*, edge::Edge*>* getAdj(vertex::Vertex* a) {return &costMap[a];};
		void printCostMap();
	};
}
#endif
