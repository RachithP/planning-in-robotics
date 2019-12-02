#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../Algorithm/algorithm.h"
#include <queue>

namespace fp
{
/*! \class BFSAlgorithm bfsalgorithm.h "src/BFSAlgorithm/bfsalgorithm.h"
 * \brief BFSAlgorithm class for solving the search objective using BFS algorithm.
 *  \headerfile bfsalgorithm.h
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

