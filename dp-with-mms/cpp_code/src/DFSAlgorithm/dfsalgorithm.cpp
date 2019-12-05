#include "dfsalgorithm.h"
#include "../API/api.h"
#include "../Direction/direction.h"
#include <algorithm>

/** @brief Constructor of the class DFSAlgorithm
 * @details Calls base class constructor
 * @param maze_ptr pointer to the array of maze representing each cell in the maze
 * @return void
*/
fp::DFSAlgorithm::DFSAlgorithm(std::shared_ptr<fp::Maze> maze_ptr) : fp::Algorithm::Algorithm(maze_ptr) {}

/** @brief Sets the wall on the simulator and Generates the path through DFS search algorithm
 * @details Function sets the wall on the simulator by calling the respective API fucntion and calls the other functions 'generatePath' and 
 * 'followPath' to generate a path through DFS search algorithm and makes the robot to follow the path in the simulator and prints a Success statememt
 * when the robot reaches the goal point
 * @param maze_ptr pointer to the array of maze representing each cell in the maze
 * @param wheel_robot pointer to the robot
 * @return void
*/
void fp::DFSAlgorithm::solve(std::shared_ptr<fp::Maze> maze_ptr, std::shared_ptr<fp::LandBasedRobot> wheel_robot)
{
	// Read current location's walls
	maze_ptr->readWall(wheel_robot->get_x(), wheel_robot->get_y(), wheel_robot->get_direction());
	
	// Generate Path from initial location to destination
	while( not maze_ptr->isGoal(wheel_robot->get_x(), wheel_robot->get_y()) ){
		if( generatePath(maze_ptr, wheel_robot) ){
//			std::cerr << "Path exists to goal node" << std::endl;
//			printPath();
			colorPath();
			if( followPath(maze_ptr, wheel_robot) ) std::cerr << "Successfully reached one of the goal cell, Enjoy!!" << std::endl;
//			else std::cerr << "blockage reached!!" << std::endl;
		}
		else{
			std::cerr << "Path does not exist to goal node. Bye, bye!" << std::endl;
			break;
		}
	}		
}

/** @brief Generates a path for the robot through the Depth First Search Algorithm from start point to the goal point
 * @details Function implements the Depth First Search Algorithm and estimate an obstacle(wall) free path for the robot movement.
 * and it returns true when a path is found
 * @param maze_ptr pointer to the array of maze representing each cell in the maze
 * @param wheel_robot pointer to the robot
 * @return bool
*/
bool fp::DFSAlgorithm::generatePath(std::shared_ptr<fp::Maze> maze_ptr, std::shared_ptr<fp::LandBasedRobot> wheel_robot){
	
	//! Clear any existing path on the mms simulator
//	API::clearAllColor();
	maze_ptr->colorCenter('g');
//	maze_ptr->textCenter("G");
	
	//! Clear path is any stored previously
	path_.clear();
	
	//! Return flag
	bool success = false;
	
	//! set visited cells flag as false
	for(int x=0;x<maze_ptr->WIDTH; ++x){
		for(int y=0;y<maze_ptr->HEIGHT; ++y){
			maze_ptr->setVisited(x, y, false);
		}
	}
	
	//! Create a dummy variable to keep track of parent node
	std::map<int, std::map<int, std::pair<int, int> > > parent;
	
	//! Mark current node as visited
	maze_ptr->setVisited(wheel_robot->get_x(), wheel_robot->get_y(), true);
	
	//! Push initial nodes to stack
	xq_.push(wheel_robot->get_x());
	yq_.push(wheel_robot->get_y());
	
	//! Mark current nodes parent as -1,-1 to identify the start of the search algo
	parent[wheel_robot->get_x()][wheel_robot->get_y()] = std::make_pair(-1, -1);
	
	//! Keep track of current node outside the while loop so as to use it in the end as the ending point
	int curr_x{wheel_robot->get_x()}, curr_y{wheel_robot->get_y()};
	
	//! Loop until a goal is found or the stack are empty(there does not exist a goal!)
	while( not xq_.empty() ){
		
		//! Pop x and y positions from stack
		curr_x = xq_.top();
		curr_y = yq_.top();
		xq_.pop();
		yq_.pop();
				
		//! Check if goal is reached. Exit if true
		if( maze_ptr->isGoal(curr_x, curr_y) ){
			success = true;
			break;
		}
	
		//! Get all neighbours == possible cells it can go from current cell.
		for(int i=0; i<4; ++i){
			if( maze_ptr->isCellValid(curr_x + xarr_[i], curr_y + yarr_[i]) ){
				if( not maze_ptr->isWall(curr_x, curr_y, dir_[i]) ){
					if( not maze_ptr->isVisited(curr_x + xarr_[i], curr_y + yarr_[i]) ){
						maze_ptr->setVisited(curr_x + xarr_[i], curr_y + yarr_[i], true);
						xq_.push(curr_x + xarr_[i]);
						yq_.push(curr_y + yarr_[i]);
						parent[curr_x + xarr_[i]][curr_y + yarr_[i]] = std::make_pair(curr_x, curr_y);
					}
				}
			}
		}
	}

	//! curr_x and curr_y will be the end goal reached by the search algorithm
	path_.push_back(std::make_pair(curr_x, curr_y));
		
	//! Generate the path from goal to start cell
	while( not (curr_x == wheel_robot->get_x() and curr_y == wheel_robot->get_y()) ){
		path_.push_back(parent[curr_x][curr_y]);
		int local_x = parent[curr_x][curr_y].first;
		curr_y = parent[curr_x][curr_y].second;
		curr_x = local_x;
	}
	
	//! Reverse the path to get start to goal cell path
	std::reverse(path_.begin(), path_.end());
	
	//! Clear variables of algorithm once path is generated
	std::stack <int> empty;
	std::swap(xq_, empty);
	std::stack <int> empty1;
	std::swap(yq_, empty1);
	
	return success;
}