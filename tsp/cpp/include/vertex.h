#ifndef VERTEX
#define VERTEX

#include <iostream>
#include <vector>

namespace vertex{
	class Vertex{
		int iD;
		int xCoordinate;
		int yCoordinate;
		double key;
		std::vector<Vertex*> children;
	public:
		Vertex* parent;
		int getiD() {return iD;};
		int getXcoordinate() {return xCoordinate;};
		int getYcoordinate() {return yCoordinate;};
		double getKey() {return key;};
		void setKey(double value) {key=value;};
		void push_back(Vertex*);
		void pop_back();
		Vertex* child();
		size_t childSize();
		Vertex(int, int, int);		//Constructor
	};
}
#endif