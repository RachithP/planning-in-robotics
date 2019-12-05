//! \file bfsalgorithm.h
#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../LandBasedWheeled/landbasedwheeled.h"
#include "../Algorithm/algorithm.h"
#include <queue>

namespace fp
{
/**
    * @class    BFSAlgorithm bfsalgorithm.h "src/BFSAlgorithm/bfsalgorithm.h"
    * @brief    BFSAlgorithm class performs Breadth First Search (BFS) operations on maze discovered in simulator.
    * @details  BFSAlgorithm class is a derived class of Algorithm class, designed to analyze the maze file discovered from the simulator and find a path
    *           from the start location to goal location. The BFS algorithm will evaluate the precense of a wall to
    *           the neighboring cells to determine a clear path. The accessible cell locations around the current position
    *           are added to a queue of points to be evaluated. This process continues for each search "branch" produced by
    *           the search algorithm until an evaluated point reaches the goal area. \n
    *           As the search algorithm produces a path to the goal area, the robot is commanded to move through the visited
    *           point list towards the goal. Robot movement commands are acheived through the API commands in a separate function. \n
    *           solve(): Checks if an evaluated point has reached the goal location and traces final path produced from BFS algorithm. \n 
    *           generatePath(): Runs BFS algorithm to search and evaluate points while producing a suitable path to the goal. \n
    *           \headerfile bfsalgorithm.h
*/
class BFSAlgorithm : public Algorithm
{
	public:
		//! Constructor
		BFSAlgorithm(std::shared_ptr<fp::Maze> maze_ptr);
		
		//! Member functions
		virtual void solve(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) override;
		virtual bool generatePath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) override;
		
		//!Destructor
		virtual ~BFSAlgorithm(){}
		
	private:
		std::queue<int> xq_; // Queue to store x coordinates as we traverse path
		std::queue<int> yq_; // Queue to store y coordinates as we traverse path
};
}