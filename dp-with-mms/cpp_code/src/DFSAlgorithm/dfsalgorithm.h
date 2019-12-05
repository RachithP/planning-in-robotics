#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../Algorithm/algorithm.h"
#include <stack>

namespace fp
{
/*! \class DFSAlgorithm dfsalgorithm.h "src/DFSAlgorithm/dfsalgorithm.h"
 * \brief DFSAlgorithm class for solving the search objective using DFS algorithm.
 *  \headerfile dfsalgorithm.h
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

