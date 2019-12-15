//! \file algorithm.h

#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../LandBasedWheeled/landbasedwheeled.h"
#include "../Direction/direction.h"
#include <queue>
#include <memory>

namespace fp
{
    
/**
    * @class    Algorithm algorithm.h "src/Algorithm/algorithm.h"
    * @brief    Algorithm class provides base class functionality for any algorithm to interact with mms simulator.
    * @details  Algorithm class is designed to analyze the maze file discovered from the simulator and find a path
    *           As the search algorithm produces a path to the goal area, the robot is commanded to move through the visited
    *           point list towards the goal. Robot movement commands are acheived through the API commands in a separate function. \n
    *           solve(): Checks if an evaluated point has reached the goal location and traces final path produced from required algorithm. \n 
    *           generatePath(): Runs required algorithm to search and evaluate points while producing a suitable path to the goal. \n
    *           followPath(): Performs checks to verify robot can move to next point among accessbile points. \n
    *           moveRobot(): Performs commands to API functions for robot to move through maze. \n
    *           printPath(): Displays path discovered from the algorithm. \n
    *           colorPath(): Sets different color to finalized path in simulation display. \n
    *           \headerfile algorithm.h
*/
    
class Algorithm
{
	public:

		/** @brief Constructor for Algorithm class */
		Algorithm(std::shared_ptr<fp::Maze>);
		
		/** @brief Member functions for Algorithm class */
		virtual void solve(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) = 0;
		virtual bool generatePath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) = 0;
		bool followPath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>);
		bool moveRobot(int, int, std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>);
		void printPath();
		void colorPath();
		
		/** @brief Destructor for Algorithm class
		* @details deletes any pointers if created as attributes.
		*/
		virtual ~Algorithm(){}
		
	protected:
/**
    * @brief    BFS algorithm utilizes various queue parameters to stage and evaluate individual cells
    * @param path_  Vector to build final path to goal node.
    * @param xq_    Queue value to store x coordinate of the cell being evaluated
    * @param y1_    Queue value to store y coordinate of the cell being evaluated
    * @param xarr_  X list of possible grid movements. Order implemented is down, right, up, left (S, E, N, W)
    * @param yarr_  Y list of possible grid movements. Order implemented is down, right, up, left (S, E, N, W)
    * @param dir_   List of compass directions corresponding to grid movements in xarr_ and yarr_
    * 
*/
		std::vector<std::pair<int, int> > path_; // To track the path to goal node.
		int xarr_[4]{0, 1, 0, -1}; // x list of possible movements on the grid. Order is in down, right, up and left i.e S, E, N, W
		int yarr_[4]{-1, 0, 1, 0}; // y list of possible movements on the grid. Order is in down, right, up and left i.e S, E, N, W
		char dir_[4]{fp::Direction::SOUTH, fp::Direction::EAST, fp::Direction::NORTH, fp::Direction::WEST}; // this list of directions is corresponding to the movement above
};
}
