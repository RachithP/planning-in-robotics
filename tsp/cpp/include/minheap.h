#ifndef minheap
#define minheap

#include "vertex.h"

namespace heap{
	
	class MinHeap{
		std::vector<vertex::Vertex*> minKeyVertex;
	public:
		vertex::Vertex* top();
		void qsort();
		void pop();
		void push_back(vertex::Vertex*);
		bool empty();
		int size();
		bool isPresent(vertex::Vertex*);
		std::vector<vertex::Vertex*>* getVector();
		vertex::Vertex* getElement(int);
		};
	
	class myComparator{
	public:
		bool operator()(vertex::Vertex* a, vertex::Vertex* b)
		{
			return (a->getKey() > b->getKey());
		}
		};
}

#endif
