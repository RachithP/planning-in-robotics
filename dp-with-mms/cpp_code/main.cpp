//! Group 10 - FP
//! \file main.cpp
/*! \mainpage ENPM809Y Group 10
 * Final Project
 * Micromouse Simulation
*/

#include "src/LandBasedRobot/landbasedrobot.h"
#include "src/LandBasedTracked/landbasedtracked.h"
#include "src/LandBasedWheeled/landbasedwheeled.h"
#include "src/API/api.h"
#include "src/Maze/maze.h"
#include "src/Algorithm/algorithm.h"
#include "src/BFSAlgorithm/bfsalgorithm.h"
#include "src/DFSAlgorithm/dfsalgorithm.h"
#include "src/DIJKSTRAlgorithm/dijkstralgorithm.h"
#include <memory>

/**
	* @brief	Main function
	* @details	Calls on LandBasedRobot inherited classes to generate new robot, create instance of provided maze,
	*			and implements Dynamic Programming algorithms such as BFS, DFS to navigate from start location (0,0) to goal location.
	* @param argc	Length of number of arguments passed to main function when it was called. Command line arguments.
	* @param argv	Each argument can be accessed through this parameter.
	* @return int 0
*/
int main(int argc, char **argv)
{
	std::cerr << "Alright, let's start it!!" << std::endl;
	
/**
    * @brief    LandBasedTracked Robot initialization
    * @details  Passes new robot parameters to LandBasedTracked robot as Name: Houston and starting point (0,0).
*/

	std::shared_ptr<fp::LandBasedRobot> track_robot = std::make_shared<fp::LandBasedTracked>("Houston", 0, 0);
	
/**
    * @brief    Creates an instance of maze file
    * @details  Creates an instance of the maze file discovered in the simulator. This instance can be used to verify
    *           explored points are within the maze perimeter and the goal is reached. This maze instance will be passed
    *           to the solving and tracing functions.
*/
	std::shared_ptr<fp::Maze> maze_ptr = std::make_shared<fp::Maze>();
	
/**
    * @brief    Create Algorithm class instance
    * @details  Creates an instance of Algorithm class to of the Breadth First Search solving algorithm. The parameter
    *           maze_ptr is passed to the new Algorithm class to perform valid point checks and evaluation of wall presense.
*/

	std::unique_ptr<fp::Algorithm> bfs_algo = std::make_unique<fp::DIJKSTRAlgorithm>(maze_ptr);

/**
    * @brief    Call solve() from Algorithm
    * @details  Previously generated Algorithm class instance called bfs_algo calls solve function in bfsalgorithm.cpp
    *           to perform maze solving operations and track tracing once search is completed.
    * @param maze_ptr   Maze pointers passed to solve function to perform cell analysis and wall discovery operations.
    * @param track_robot    Instance of track robot gets passed to solve function to provide characteristics and parameters 
    *                       for analysis and information storage. Key parameters that are passed are current robot position,
    *                       and heading.
 */
	bfs_algo->solve(maze_ptr, track_robot);	
	
	return 0;
}