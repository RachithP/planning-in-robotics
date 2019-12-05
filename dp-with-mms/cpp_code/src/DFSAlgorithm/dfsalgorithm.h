//! \file dfsalgorithm.h
#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../LandBasedWheeled/landbasedwheeled.h"
#include "../Algorithm/algorithm.h"
#include <stack>

namespace fp
{
/**
    * @class    DFSAlgorithm dfsalgorithm.h "src/DFSAlgorithm/dfsalgorithm.h"
    * @brief    DFSAlgorithm class performs Depth First Search (DFS) operations on maze discovered in simulator.
    * @details  DFSAlgorithm class is a derived class of Algorithm class, designed to analyze the maze file discovered from the simulator and find a path
    *           from the start location to goal location. The DFS algorithm will evaluate the precense of a wall to
    *           the neighboring cells to determine a clear path. It follows a path through depth iteration. \n 
	* 			The accessible cell locations around the current position aree added to a queue of points to be evaluated. \n 
	* 			This process continues for each search "branch" produced by
    *           the search algorithm until an evaluated point reaches the goal area. \n
    *           As the search algorithm produces a path to the goal area, the robot is commanded to move through the visited
    *           point list towards the goal. Robot movement commands are acheived through the API commands in a separate function. \n
    *           solve(): Checks if an evaluated point has reached the goal location and traces final path produced from DFS algorithm. \n 
    *           generatePath(): Runs DFS algorithm to search and evaluate points while producing a suitable path to the goal. \n
    *           \headerfile dfsalgorithm.h
*/
    
class DFSAlgorithm : public Algorithm
{
	public:
		//! Constructor
		DFSAlgorithm(std::shared_ptr<fp::Maze> maze_ptr);
		
		//! Member functions
		virtual void solve(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) override;
		virtual bool generatePath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) override;
		
		//!Destructor
		virtual ~DFSAlgorithm(){}
		
	private:
		std::stack<int> xq_; // Queue to store x coordinates as we traverse path
		std::stack<int> yq_; // Queue to store y coordinates as we traverse path
};
}