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
		DFSAlgorithm(fp::Maze* maze_ptr);
		
		//! Member functions
		virtual void solve(fp::Maze*, fp::LandBasedRobot*) override;
		virtual bool generatePath(fp::Maze*, fp::LandBasedRobot*) override;
		
		//!Destructor
		virtual ~DFSAlgorithm(){}
		
	private:
		std::stack<int> xq_; // Queue to store x coordinates as we traverse path
		std::stack<int> yq_; // Queue to store y coordinates as we traverse path
};
}

