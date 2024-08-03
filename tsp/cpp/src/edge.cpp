#include "edge.h"
#include <math.h>

// Constructor
edge::Edge::Edge(vertex::Vertex* a, vertex::Vertex* b)
{
	weight = (double)(sqrt(pow((a->getXcoordinate() - b->getXcoordinate()),2) + pow((a->getYcoordinate() - b->getYcoordinate()),2))); // calculate the euclidean distance
	startVertex = a;
	endVertex = b;
}
