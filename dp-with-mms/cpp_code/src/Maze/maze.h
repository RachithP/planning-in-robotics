//! \file maze.h

#pragma once

#include <map>

namespace fp
{
/*! @class Maze maze.h "src/Maze/maze.h"
 * @brief Maze class for maze file interpretation and manipulation.
 * @details Maze class interprets provided maze file for analysis.
 * Maze default size is set to 16x16 cells. Functions in Maze class are designed
 * to manipulate and set maze characteristics in mouse simulator. Outputs are mostly 
 * to simulator API. \n
 * Member functions of this class are as follows: \n
 * isWall(): Checks for wall present in specified direction. Returns false if no wall found \n
 * readWall(): Reads presence of wall in maze file from given position and current robot heading \n
 * setWall(): Sets wall in maze simulator based on discoveries from search algorithm and readWall \n
 * colorCenter(): Colors center of maze to distinguish goal in the simulator environment \n
 * textCenter(): Texts center of maze to mark goal in the simulator environment \n
 * setVisited(): Set a certain cell. Done by algorithm implementation \n
 * isVisited(): Checks if a certain cell is visited in the algorithm implementation \n
 * isGoal(): Checks if the input is one of the possible goal nodes or not \n
 * isCellValid(): Checks if the input location is a valid cell coordinate or not \n
 * getValue(): returns the value stored in a particular cell. Used for debugging \n
 * printMaze(): Prints maze in command window for debugging \n
 *  \headerfile maze.h
 */
class Maze
{
	public:
		/** @brief Constructor for Maze class */
		Maze();
		
		/** @brief Destructor for Maze class */
		~Maze(){}
		
		/** @brief Member functions for Maze class */
		bool isWall(int x, int y, char direction);
		void readWall(int x, int y, char curr_direction);
		void setWall(int x, int y, char direction);
		void colorCenter(char color);
		void textCenter(std::string text);
		void setVisited(int x, int y, bool status);
		bool isVisited(int x, int y);
		bool isGoal(int x, int y);
		bool isCellValid(int x, int y);
		unsigned char getValue(int x, int y);
		void printMaze();
	
		/** @brief Public Attributes for Maze class */
		/** @brief The width and height of the maze is preset to 16x16 */
		int WIDTH  = 16;
		int HEIGHT = 16;
		
		/** @brief The x and y positions of the possible goal cells.
         * @details Position of the goal cells is determine based on the width and height of the maze file loaded.
         */
		const int GLX = (WIDTH  - 1) / 2;
		const int GLY = (HEIGHT - 1) / 2;
		const int GUX = (WIDTH) / 2;
		const int GUY = (HEIGHT) / 2;
	
	private:
		/** @brief Maze is encoded in map data-structure using unsigned char or 8-bit value*/
        /** @details Current storage format is as shown below with each bit representing a boolean corresponding to separate entities as follows:
		 * bit 0 -> Presence of wall in True North or up direction \n
		 * bit 1 -> Presence of wall in True East or right direction \n
		 * bit 2 -> Presence of wall in True South or down direction \n
		 * bit 3 -> Presence of wall in True West or left direction \n
		 * bit 4 -> Visited status of a cell used in algorithm implementation \n
		 * bit 5 -> N/A \n
		 * bit 6 -> N/A \n
		 * bit 7 -> N/A \n
         * @param maze: _,_,_, Visited(1)/Not-Visited(0),W(0/1),S(0/1),E(0/1),N(0/1)
         */
		 std::map<int, std::map<int, unsigned char>> maze_; //! Current storage format is ==> _ _ _ Visited WSEN
};
}