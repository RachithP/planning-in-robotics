//! \file api.h

#pragma once
#include <string>

namespace fp
{
    
/** \class API api.h "src/API/api.h"
* @brief Defines API class */
class API
{
	public:
	
		/** @brief API Constructor */
		API(){}
		
		/** @brief Member function declaration */
        /** mazeWidth: Maze width reported from maze file valuation
         *  mazeHeight: Maze height reported from maze file evaluation
         *  wallFront: Boolean verification if wall is present infront of current location and heading
         *  wallRight: Boolean verification if wall is present to right of current location and heading
         *  wallLeft: Boolean verification if wall is present to left of current location and heading
         *  moveForward: Operation to move robot forward one position
         *  turnRight: Operation to rotate robot clockwise 90 deg
         *  turnLeft: Operation to rotate robot counter-clockwise 90 deg
         *  setWall: sets wall in specified location and direction
         *  clearWall: clears wall from specified location and direction
         *  setColor: sets color to wall in specified location and direction
         *  clearColor: clears wall colors around specified location
         *  clearAllColor: clears all wall colors in maze
         *  setText: sets text in maze cell at specific location
         *  clearText: clears text in specified maze cell
         *  clearAllText: clears all text in maze cells
         *  wasReset: resets maze and search operation, returns boolean for completiong confirmation
         *  ackReset: resets API response to verify external operations completed
         */
		static int mazeWidth();
		static int mazeHeight();

		static bool wallFront();
		static bool wallRight();
		static bool wallLeft();
		
		static void moveForward();
		static void turnRight();
		static void turnLeft();

		static void setWall(int x, int y, char direction);
		static void clearWall(int x, int y, char direction);

		static void setColor(int x, int y, char color);
		static void clearColor(int x, int y);
		static void clearAllColor();

		static void setText(int x, int y, const std::string& text);
		static void clearText(int x, int y);
		static void clearAllText();

		static bool wasReset();
		static void ackReset();

		/** @brief API Destructor */
		~API(){}
};
}