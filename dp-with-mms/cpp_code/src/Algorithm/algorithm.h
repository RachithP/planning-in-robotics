#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../Direction/direction.h"
#include <vector>
#include <memory>

namespace fp
{
/*! \class Algorithm algorithm.h "src/Algorithm/algorithm.h"
 * \brief Algorithm class for solving the search objective.
 *  \headerfile algorithm.h
 */
class Algorithm
{
	public:
		//! Constructor
		Algorithm(std::shared_ptr<fp::Maze> maze_ptr);
		
		//! Member functions
		virtual void solve(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) = 0;
		virtual bool generatePath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) = 0;
		bool followPath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>);
		bool moveRobot(int, int, std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>);
		void printPath();
		void colorPath();
		
		//!Destructor
		virtual ~Algorithm(){}
		
	protected:
		std::vector<std::pair<int, int> > path_; // To track the path from current location to goal node.
		int xarr_[4]{0, 1, 0, -1}; // x list of possible movements on the grid. Order is in down, right, up and left i.e S, E, N, W
		int yarr_[4]{-1, 0, 1, 0}; // y list of possible movements on the grid. Order is in down, right, up and left i.e S, E, N, W
		char dir_[4]{fp::Direction::SOUTH, fp::Direction::EAST, fp::Direction::NORTH, fp::Direction::WEST}; // this list of directions is corresponding to the movement above
};
}

