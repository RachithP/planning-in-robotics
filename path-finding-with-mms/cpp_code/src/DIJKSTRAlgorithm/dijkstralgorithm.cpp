#include "dijkstralgorithm.h"
#include "../API/api.h"
#include "../Direction/direction.h"
#include "../MinHeap/minheap.h"
#include <algorithm>

fp::DIJKSTRAlgorithm::DIJKSTRAlgorithm(std::shared_ptr<fp::Maze> maze_ptr) : fp::Algorithm::Algorithm(maze_ptr) {}

void fp::DIJKSTRAlgorithm::solve(std::shared_ptr<fp::Maze> maze_ptr, std::shared_ptr<fp::LandBasedRobot> wheel_robot)
{
	// Read current location's walls
	maze_ptr->readWall(wheel_robot->get_x(), wheel_robot->get_y(), wheel_robot->get_direction());
	
	// Generate Path from initial location to destination - BFS
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

bool fp::DIJKSTRAlgorithm::generatePath(std::shared_ptr<fp::Maze> maze_ptr, std::shared_ptr<fp::LandBasedRobot> wheel_robot){
	
	//! Clear any existing path on the mms simulator
	API::clearAllColor();
	maze_ptr->colorCenter('G');
	maze_ptr->textCenter("G");
	API::setColor(wheel_robot->get_x(), wheel_robot->get_y(), 'G');
	
	//! Clear path is any stored previously
	path_.clear();

	//! initialize the unique pointer to heap
	std::unique_ptr<fp::MinHeap> heap = std::make_unique<fp::MinHeap>();
	
	//! Return flag
	bool success = false;
	
	//! set visited cells flag as false and Set all cost as a high number for unexplored regions except starting node.
	for(int x=0;x<maze_ptr->WIDTH; ++x){
		for(int y=0;y<maze_ptr->HEIGHT; ++y){
			maze_ptr->setVisited(x, y, false);
			cost2come_[x][y] = 1000000.0;
		}
	}

	//! Create a dummy variable to keep track of parent node
	std::map<int, std::map<int, std::pair<int, int> > > parent;
	
	//! Mark current node as visited
	maze_ptr->setVisited(wheel_robot->get_x(), wheel_robot->get_y(), true);
	
	//! Initial cost of the start node is 0.0 - least considering non-negative cost
	cost2come_[wheel_robot->get_x()][wheel_robot->get_y()] = 0.0;	
	
	//! Push initial nodes to heap
	heap->push(std::pair<unsigned char, double>(getKey(wheel_robot->get_x(), wheel_robot->get_y()), 0.0));
		
	//! Keep track of current node outside the while loop so as to use it in the end as the ending point
	int curr_x= wheel_robot->get_x(), curr_y = wheel_robot->get_y();
		
	//! Loop until a goal is found or the queue are empty(there does not exist a goal!)
	while( not heap->empty() ){

		//! Pop x and y positions from queue
		curr_x = getX(heap->top().first);
		curr_y = getY(heap->top().first);
		heap->pop();

		//! Mark cell as visited
//		maze_ptr->setVisited(curr_x, curr_y, true);
		
		//! Check if goal is reached. Exit if true
		if( maze_ptr->isGoal(curr_x, curr_y) ){
			success = true;
			break;
		}
	
//		Don't do anything if the value stored for this node in cost2come is less than the value in queue
//		if(cost2come_[curr_x][curr_y] < dist) continue;
		
		//! Get all neighbours == possible cells it can go from current cell.
		for(int i=0; i<4; ++i){			
			if( maze_ptr->isCellValid(curr_x + xarr_[i], curr_y + yarr_[i]) ){			
				if( not maze_ptr->isWall(curr_x, curr_y, dir_[i]) ){

					if( maze_ptr->isVisited(curr_x + xarr_[i], curr_y + yarr_[i]) ){
						if( cost2come_[curr_x + xarr_[i]][curr_y + yarr_[i]] > (cost2come_[curr_x][curr_y] + 1.0) ){
							cost2come_[curr_x + xarr_[i]][curr_y + yarr_[i]] = cost2come_[curr_x][curr_y] + 1.0;
							heap->push(std::pair<unsigned char, double>(getKey(curr_x + xarr_[i], curr_y + yarr_[i]), cost2come_[curr_x + xarr_[i]][curr_y + yarr_[i]]));
							parent.at(curr_x + xarr_[i]).at(curr_y + yarr_[i]) = std::make_pair(curr_x, curr_y);
						}
					}
					else{
						maze_ptr->setVisited(curr_x+xarr_[i], curr_y+yarr_[i], true);
						cost2come_[curr_x + xarr_[i]][curr_y + yarr_[i]] = cost2come_[curr_x][curr_y] + 1.0;
						heap->push(std::pair<unsigned char, double>(getKey(curr_x + xarr_[i], curr_y + yarr_[i]), cost2come_[curr_x + xarr_[i]][curr_y + yarr_[i]]));
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

	return success;
}

unsigned char fp::DIJKSTRAlgorithm::getKey(int x, int y)
{
	return (x << 4) | y;
}

int fp::DIJKSTRAlgorithm::getX(unsigned char key)
{
	return static_cast<int>(key>>4);
}

int fp::DIJKSTRAlgorithm::getY(unsigned char key)
{
	return static_cast<int>(key&15);
}