#ifndef EDGE
#define EDGE

#include "vertex.h"

namespace edge{
	class Edge{
		double weight;
		vertex::Vertex* startVertex;
		vertex::Vertex* endVertex;
	public:
		Edge(vertex::Vertex*, vertex::Vertex*);		//Constructor
		double getWeight(){return weight;};
	};	
}
#endif
