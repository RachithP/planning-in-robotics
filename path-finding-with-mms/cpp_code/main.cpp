//! \file main.cpp
/*! \mainpage Hola!, Mucho Gusto ;)
 * Micromouse Simulation integrated path finding algorithms.
*/

#include <memory>
#include "./src/LandBasedRobot/landbasedrobot.h"
#include "./src/LandBasedTracked/landbasedtracked.h"
#include "./src/LandBasedWheeled/landbasedwheeled.h"
#include "./src/API/api.h"
#include "./src/Maze/maze.h"
#include "./src/Algorithm/algorithm.h"
#include "./src/BFSAlgorithm/bfsalgorithm.h"
#include "./src/DFSAlgorithm/dfsalgorithm.h"
#include "./src/DIJKSTRAlgorithm/dijkstralgorithm.h"


/**
	* @brief	Main function
	* @details	Calls on LandBasedRobot inherited classes to generate new robot, create instance of provided maze, \n
	*			and implements Dynamic Programming algorithms such as BFS, DFS to navigate from start location (0,0) to goal location.
	* @param argc	Length of number of arguments passed to main function when it was called. Command line arguments.
	* @param argv	Each argument can be accessed through this parameter.
	* @return return 0
*/

int main(int argc, char **argv)
{
	printf("Alright, let's start it!!\n");
	
	// LandBasedWheeled Robot initialization
//	fp::LandBasedRobot* wheel_robot = new fp::LandBasedWheeled("Husky", 0, 0);
	
	// LandBasedTracked Robot initialization
	std::shared_ptr<fp::LandBasedRobot> track_robot = std::make_shared<fp::LandBasedTracked>("Houston", 0, 0);
	
	// Create an instance of maze
	std::shared_ptr<fp::Maze> maze_ptr = std::make_shared<fp::Maze>();
	
	// Create an instance of Algorithm class
	std::unique_ptr<fp::Algorithm> bfs_algo = std::make_unique<fp::DIJKSTRAlgorithm>(maze_ptr);

	// Call solve from Algorithm to start solving
	bfs_algo->solve(maze_ptr, track_robot);	
	
	return 0;
}