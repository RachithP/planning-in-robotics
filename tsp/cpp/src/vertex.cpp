#include "vertex.h"
#include <math.h>

// Constructor
vertex::Vertex::Vertex(int a, int b, int c)
{
	iD = a;
	xCoordinate = b;
	yCoordinate = c;
	parent = NULL;
	key = INFINITY;
}

void vertex::Vertex::push_back(vertex::Vertex* v)
{
	children.push_back(v);
}

vertex::Vertex* vertex::Vertex::child()
{
	return children.back();
}

void vertex::Vertex::pop_back()
{
	children.pop_back();
}

size_t vertex::Vertex::childSize()
{
	return children.size();
}
