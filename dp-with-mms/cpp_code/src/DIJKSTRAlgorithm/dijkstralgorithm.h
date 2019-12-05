#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../Algorithm/algorithm.h"
#include <memory>

namespace fp
{
/*! \class DIJKSTRAlgorithm dijkstralgorithm.h "src/DIJKSTRAlgorithm/dijkstralgorithm.h"
 * \brief DIJKSTRAlgorithm class for solving the search objective using BFS algorithm.
 *  \headerfile dijkstralgorithm.h
 */
class DIJKSTRAlgorithm : public Algorithm
{
	public:
		//! Constructor
		DIJKSTRAlgorithm(std::shared_ptr<fp::Maze>);
		
		//! Member functions
		virtual void solve(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) override;
		virtual bool generatePath(std::shared_ptr<fp::Maze>, std::shared_ptr<fp::LandBasedRobot>) override;
		unsigned char getKey(int x, int y);
		int getX(unsigned char);
		int getY(unsigned char);
		
		//!Destructor
		virtual ~DIJKSTRAlgorithm(){}
		
	private:
//		std::map<int, std::map<int, double>> cost2come_;
		double cost2come_[16][16] = {};
};
}

