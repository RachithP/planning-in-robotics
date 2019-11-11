#include "vertex.h"
#include "costmap.h"
#include "edge.h"
#include "minheap.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iomanip>

/* This function is to draw a circle using its center with a default radius */
void myCircle( cv::Mat* img, cv::Point center )
{
  circle( *img,
      center*1.5,
      1, //radius
      cv::Scalar( 0, 0, 255 ),
      cv::FILLED,
      cv::LINE_8 );
}

/* This function is to draw a line using 2 points */
void myLine( cv::Mat* img, cv::Point start, cv::Point end )
{
  line( *img,
    start*1.5,
    end*1.5,
    cv::Scalar( 255, 255, 255 ),
    0.5,
    cv::LINE_8 );
}

/* This function is to read vertices from the input file */
int readVertices( std::string path, heap::MinHeap* pq )
{
	std::string line; 	// each line in file
	int numVertices;	// num of vertices in the graph
	int flag{0};		// flag to identify start of coordinate info in file
	
	std::ifstream myFile (path); // file to be read
	
	if (myFile.is_open())
	{	
		while (getline (myFile,line))
		{			
			// To find the number of vertices
			if (line.find("DIMENSION : ") != std::string::npos)
			{
				numVertices = std::stoi(line.substr(line.find("DIMENSION : ")+12));
				std::cout << "Number of vertices are " << numVertices << "\n";
			}
			
			// Start reading the vertices
			if (line.find("NODE_COORD_SECTION") != std::string::npos)
			{
				flag = 1;
				continue;
			}
			
			if (flag == 1)
			{				
				if (line.find(' ') != std::string::npos)
				{
					int iD = std::stoi (line.substr(0, line.find(' ')));
					line.erase(0, line.find(' ') + 1);	// Erase including delimiter
					
					int xCoordinate = std::stoi (line.substr(0, line.find(' ')));
					line.erase(0, line.find(' ') + 1);	// Erase including delimiter
					
					int yCoordinate = std::stoi (line.substr(0, line.find(' ')));
					
					vertex::Vertex* v = new vertex::Vertex(iD, xCoordinate, yCoordinate);
					pq->push_back(v);
				}
			}
		}
		myFile.close();
	}
	else std::cout << "Unable to open the file" << "\n";
	return numVertices;
}

/* This function is to print vertices along with its details */
void printVertices( heap::MinHeap* q )
{
	for (auto it = q->getVector()->begin(); it != q->getVector()->end(); ++it)
	{
		std::cout << "Vertex : = " << (*it)->getiD() << "   Weight : = " << (*it)->getKey() << "\n";
//		std::cout << "Vertex x-coord  = " << (*it)->getXcoordinate() << "\n";
//		std::cout << "Vertex y-coord  = " << (*it)->getYcoordinate() << "\n";
//		std::cout << "Vertex's parent = " << (*it)->parent << "\n";
//		std::cout << "Vertex's key    = " << (*it)->getKey() << "\n";
//		std::cout << "--------------------------------------------------" << "\n";
	}
}

/* This function is to find MST of given complete metric graph */
void findMST( heap::MinHeap* pq, heap::MinHeap* mST, costmap::Matrix* weightMap )
{
	while(pq->empty() == false)
	{		
		vertex::Vertex* p = pq->top();	// access the top (least key) element
		pq->pop(); // Pop p

		// Insert vertex into MST (vector of vertices)
		mST->push_back(p);
		
		// For every other vertex in queue connected to p
		for (auto it = pq->getVector()->begin(); it != pq->getVector()->end(); ++it)
		{
			if ( not(mST->isPresent((*it))) && (weightMap->getEdge(p,(*it))->getWeight() < (*it)->getKey()) )	// Check if it is present in MST and if it's edge cost with p is lesser than its key
			{
//				std::cout << (*it)->getiD() << "'s key value is " << (*it)->getKey() << "\n";
//				std::cout << "Edge weight is " << weightMap->getEdge(p,(*it))->getWeight() << "\n";
				// update parent
				(*it)->parent = p;
				// update key
				(*it)->setKey(weightMap->getEdge(p,(*it))->getWeight());
			}
		}
	}
}

/* This function is to update every node with it's child once we get the MST */
void updateRootChildRelationship(heap::MinHeap* mST)
{
	// update vertices with it's child
	for (auto it = mST->getVector()->begin(); it!=mST->getVector()->end(); ++it)
	{
		if ((*it)->parent == NULL){		// this is root vertex case
			continue;	
		}
		else{
			(*it)->parent->push_back((*it));	// every vertex's parent's one of many children is that vertex itself
		}
	}
}

/* This function is to get MST tour length */
void printMSTLength(heap::MinHeap* mST)
{
	double sum{0};
//	std::cout << "Tour of MST is " << "\n";
	for (auto it = mST->getVector()->begin(); it != mST->getVector()->end(); ++it)
	{
//		std::cout << (*it)->getiD() << "\n";	// To print route on console
		sum += (*it)->getKey();					// MST cost
	}
	std::cout << "Sum of the MST edges is " << sum << "\n";
}

/* This function is to write thr output of a tour onto a file */
void writeTourOutput( std::string path, std::vector<vertex::Vertex*>* tour, double length, int numVertices )
{
	std::size_t index = path.find_last_of("/");
	std::string path2Dir = path.substr(0, index);		// path to dir where the file is stored
	std::string fileName = path.substr(index+1);		// name of file stored in the directory
	std::string rawFileName = fileName.substr(0, fileName.find('.')); // This is the name before extension
	
//	std::cout << "Name is " << eil << "\n";
//	std::cout << "Extension is " << fileName.substr(fileName.find('.')+1) << "\n";
//	std::cout << "Path to directory is " << path2Dir << "\n";
//	std::cout << "File name is " << fileName << "\n";
	
	std::string outputFileName = path2Dir + "/output/" + rawFileName + ".out.tour";
	std::cout << "output file name is " << outputFileName << "\n";
//	std::string dimension = rawFileName.substr(3, rawFileName.size());
	
	// Write certains lines as required by submission format
	std::ofstream myFile (outputFileName);
	myFile << "NAME : " + rawFileName + ".opt.tour\n";
	myFile << "COMMENT : Optimal tour for " + fileName + "  (";
	myFile << std::fixed << std::setprecision(4) << length;
	myFile << ")\n";
	myFile << "TYPE : TOUR\n";
	myFile << "DIMENSION : ";
	myFile << numVertices;
	myFile << "\n";
	myFile << "TOUR_SECTION\n";	
	
	for (auto it = tour->begin(); it != tour->end()-1; ++it)
	{
		try{
			myFile << (*it)->getiD();;
			myFile << "\n";
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception caught : " << e.what() << "\n"; 
		}
	}
	
	myFile << "-1\n";
	myFile << "EOF";
	myFile.close();
}

/* This function is to calculate the TSP tour */
void tspTour(vertex::Vertex* root, std::vector<vertex::Vertex*>* visited, std::vector<vertex::Vertex*>* tour)
{	

	if (std::find(visited->begin(), visited->end(), root) == visited->end())
	{
		visited->push_back(root);
		tour->push_back(root);
		
		while (root != NULL and root->childSize()!=false)
		{
//			std::cout << "\t" << root->child()->getiD() << "\n";
			int val = root->childSize();
			for (int i=0; i<val; ++i)
			{
				tspTour(root->child(), visited, tour);
				root->pop_back();
			}
		}
	}
	visited->pop_back();
	root = visited->back();
}

/* This function is to get tour length of any vector that has elements stored in it in order */
double getTourLength(std::vector<vertex::Vertex*>* tour, costmap::Matrix* weightMap)
{
	double tourCost{0};
//	std::cout << "Tour is ...\n";
	for ( auto it = tour->begin()+1; it != tour->end(); ++it )
	{
		if ( (*it) != NULL ){
//			std::cout << (*(it-1))->getiD() << "\n";
			if ( (*it) == tour->back() ){
//				std::cout << (*(it))->getiD() << "\n";
			}
		}
		tourCost += weightMap->getEdge((*(it-1)), (*(it)))->getWeight();
	}
	return tourCost;
}

/* This is for drawing graphs with nodes and edges */
void drawGraph(std::vector<vertex::Vertex*>* tour, int dimension)
{
	cv::Mat disp_image = cv::Mat::zeros( 200, 200, CV_8UC3 );		// Image to draw graph on
	cv::namedWindow("Graph", cv::WINDOW_NORMAL);									// Name the window
	cv::moveWindow("Graph", 200, 200);
	cv::resizeWindow("Graph",1000, 1000);							// resize it to a bigger picture

	cv::Size size(1200, 1200);
	
	for ( auto it = tour->begin()+1; it != tour->end(); ++it )
	{
		if ( (*it) != NULL ){
			myCircle(&disp_image, cv::Point((*(it-1))->getXcoordinate(), (*(it-1))->getYcoordinate()));
			if ( (*it) == tour->back() ){
				myCircle(&disp_image, cv::Point((*(it))->getXcoordinate(), (*(it))->getYcoordinate()));
			}
		}
		myLine(&disp_image, cv::Point((*(it-1))->getXcoordinate(), (*(it-1))->getYcoordinate()), cv::Point((*it)->getXcoordinate(), (*it)->getYcoordinate()));
	}
	cv::resize(disp_image, disp_image, size, CV_INTER_AREA);
	cv::imshow("Graph", disp_image);
}

/* This function has the check for pointing out crossed edges */
bool checkEdgeCrossing( vertex::Vertex* a, vertex::Vertex* b, vertex::Vertex* c, vertex::Vertex* d )
{
	// Check if any vertices from each edge are the same. Disregard this case.
	if (a==c or a==d or b==c or b==d)
		return false;
	
	double m1, m2, c1, c2, x, y;
	
	// This is the case when one edge is having slope 90 deg
	if ( a->getXcoordinate()==b->getXcoordinate() )
	{
		x = a->getXcoordinate();
		if ( c->getXcoordinate()==d->getXcoordinate() ) { return false;};
		
		m2 = double(d->getYcoordinate() - c->getYcoordinate()) / (d->getXcoordinate() - c->getXcoordinate());
		c2 = double((c->getYcoordinate() * d->getXcoordinate()) - (d->getYcoordinate() * c->getXcoordinate())) / (d->getXcoordinate() - c->getXcoordinate());
		
		y = m2*x+c2;
		
		if ( ((y>a->getYcoordinate()) and (y<b->getYcoordinate())) or ((y<a->getYcoordinate()) and (y>b->getYcoordinate())) )
			{
				if ( ((x<c->getXcoordinate()) and (x>d->getXcoordinate())) or ((x>c->getXcoordinate()) and (x<d->getXcoordinate())) )
				{
					return true;
				}
			}
		return false;
	}
	
	// This is the case when one edge is having slope 90 deg
	if ( c->getXcoordinate()==d->getXcoordinate() )
	{
		x = c->getXcoordinate();
		if ( a->getXcoordinate()==b->getXcoordinate() ) { return false;};
		
		m1 = double(b->getYcoordinate() - a->getYcoordinate()) / (b->getXcoordinate() - a->getXcoordinate());
		c1 = double((a->getYcoordinate() * b->getXcoordinate()) - (b->getYcoordinate() * a->getXcoordinate())) / (b->getXcoordinate() - a->getXcoordinate());
		
		y = m1*x+c1;
		
		if ( ((y>c->getYcoordinate()) and (y<d->getYcoordinate())) or ((y<c->getYcoordinate()) and (y>d->getYcoordinate())) )
			{
				if ( ((x<a->getXcoordinate()) and (x>b->getXcoordinate())) or ((x>a->getXcoordinate()) and (x<b->getXcoordinate())) )
				{
					return true;
				}
			}
		return false;
	}
	
	// When slope is not zero
	m1 = double(b->getYcoordinate() - a->getYcoordinate()) / (b->getXcoordinate() - a->getXcoordinate());
	c1 = double((a->getYcoordinate() * b->getXcoordinate()) - (b->getYcoordinate() * a->getXcoordinate())) / (b->getXcoordinate() - a->getXcoordinate());

	m2 = double(d->getYcoordinate() - c->getYcoordinate()) / (d->getXcoordinate() - c->getXcoordinate());
	c2 = double((c->getYcoordinate() * d->getXcoordinate()) - (d->getYcoordinate() * c->getXcoordinate())) / (d->getXcoordinate() - c->getXcoordinate());

	if ( m1!=m2 )	// if slope is same, then they do not intersect
	{
		x = (c1-c2) / (m2-m1);
		y = (m2*c1-m1*c2) / (m2-m1);		// not needed as of now
	
		if ( ((x>c->getXcoordinate()) and (x<d->getXcoordinate())) or ((x<c->getXcoordinate()) and (x>d->getXcoordinate())) )
		{
			if ( ((x<a->getXcoordinate()) and (x>b->getXcoordinate())) or ((x>a->getXcoordinate()) and (x<b->getXcoordinate())) )
			{
				return true;
			}
		}
	}
	return false;
}

/* This function checks if the graph is entangled or not */
bool checkGraphEntanglement( std::vector<vertex::Vertex*>* tour )
{
	for ( auto it = tour->begin(); it != tour->end()-2; ++it )
	{
		for (  auto jt = it+2; jt != tour->end()-1; ++jt )
		{
			if ( checkEdgeCrossing( *(it), *(it+1), *(jt), *(jt+1) ) ){
				return true;
			}
		}
	}
	return false;
}

/* This function applies heuristic to untangle crossed edges */
void applyHeuristic( std::vector<vertex::Vertex*>* tour )
{	
	while ( checkGraphEntanglement(tour) ){
		for ( auto it = tour->begin(); it != tour->end()-2; ++it )
		{
			for (  auto jt = it+2; jt != tour->end()-1; ++jt )
			{
				if ( checkEdgeCrossing( *(it), *(it+1), *(jt), *(jt+1) ) ){
					std::reverse( it+1, jt+1 );		// reverse this part of the tour
					drawGraph(tour, 200);
					cv::waitKey(1000);
				}
			}
		}
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
}

/* main code that decides when to call which function */
int main(int argc, char **argv)
{	
	// Measure time to start and end
	clock_t start, end;
	
	// Create an heap. Sorted according to key value. Here vector is used and low values are kept in the last
	heap::MinHeap pq;
	
	// Read file for data on the graph - this particular format contains vertex id with their coordinates
	int plotGraphFlag{0};
	std::string path;
//	path = "/home/rachith/academia/III-SEM/CMSC818B/workspaceCMSC/HW-1_MetricTSP/question/generateNodes/eil101.tsp";
	std::cout << "Input the absolute path to .tsp file." << "\n";
	std::cin >> path;
	std::cout << "Do you want to visualize graph, 1-YES, 0-NO? [1/0]" << "\n";
	std::cin >> plotGraphFlag;
	
	int dimension = readVertices(path, &pq);	// To read data from file and add it a vector of vertex class

//	printVertices(&pq);			// To print the values of vertex parameters
	
	start  = clock();			// Note the start time of algorithm
	
	// Create an adjacency map (of distance) from these vertices
	costmap::Matrix* weightMap = new costmap::Matrix(&pq);
//	weightMap->printCostMap(); // print to verify
	
	// Add zero as key to a random vertex. This will be the root node
	srand (time(NULL));			// Initialize random seed
	int randNum = rand() % 50;	// Generate a random number between 0-50
	vertex::Vertex* e = pq.getElement(randNum);
	e->setKey(0);
	
	// Find MST
	heap::MinHeap mST;	
	findMST(&pq, &mST, weightMap);
	// Print MST i.e vertices and its key value
//	printVertices(&mST);
	
	updateRootChildRelationship(&mST);	// update the child of every vertex to form a tree like structure

	// Sum edges of MST
	printMSTLength(&mST);
	
	// Find TSP tour of MST
	std::vector<vertex::Vertex*> visited;	// stack to keep track of visited nodes in order
	std::vector<vertex::Vertex*> tour;		// stack to keep track of the tour
	tspTour(e, &visited, &tour);			// perform TSP tour and update tour vector with vertices in the order of traversal
	tour.push_back(tour.front());			// Add root to the end for cyclic

	double tourLength = getTourLength(&tour, weightMap);	// Get tour length by adding the edge length of vertices in order
	std::cout << "Initial TSP Tour cost is " << tourLength << "\n";
//	std::cout << "Number of vertices in tour are " << tour.size() << "\n";
	
	if ( plotGraphFlag ){
		drawGraph(&tour, dimension);			// draw tour graph
		cv::waitKey(0);							// resume on user command
	}
	
	// Heuristic to improve TSP tour
	applyHeuristic(&tour);
	
	if ( plotGraphFlag ){
		drawGraph(&tour, dimension);			// draw improved tour graph
		cv::waitKey(0);							// resume on user command
		cv::destroyAllWindows();
	}
	
	double newLength = getTourLength(&tour, weightMap);
	std::cout << "TSP Tour length after applying heuristic is " << newLength << "\n";
//	std::cout << "Number of vertices in tour are " << tour.size() << "\n";
	
//	writeTourOutput(path, &tour, newLength, dimension);		// write output of the tour onto a file
	
	// Calculating total time to run
	end = clock();
	double timeElapsed = double(end-start)/(CLOCKS_PER_SEC);
	std::cout << "Time taken to complete is " << std::fixed << timeElapsed << std::setprecision(10) << " seconds " << "\n";
	std::cout << "-----------------------------------------------------------------" << "\n";
}
