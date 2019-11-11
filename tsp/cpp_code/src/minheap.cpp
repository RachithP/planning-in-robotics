#include "minheap.h"
#include <algorithm>


bool heap::MinHeap::empty()
{
	return minKeyVertex.empty();
}

void heap::MinHeap::qsort()
{
	std::sort(minKeyVertex.begin(), minKeyVertex.end(), myComparator());
}

vertex::Vertex* heap::MinHeap::top()
{
	qsort();
	return minKeyVertex.back();
}

void heap::MinHeap::pop()
{
	qsort();
	minKeyVertex.pop_back();
}

void heap::MinHeap::push_back(vertex::Vertex *a)
{
	minKeyVertex.push_back(a);
}

int heap::MinHeap::size()
{
	return minKeyVertex.size();
}

bool heap::MinHeap::isPresent(vertex::Vertex* a)
{
	return (std::find(minKeyVertex.begin(), minKeyVertex.end(), a) != minKeyVertex.end());
}

std::vector<vertex::Vertex*>* heap::MinHeap::getVector()
{
	return &minKeyVertex;
}

vertex::Vertex* heap::MinHeap::getElement(int value)
{
	return minKeyVertex.at(value);
}
