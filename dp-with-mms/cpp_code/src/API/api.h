#pragma once
#include <string>

namespace fp
{
/*! \class API api.h "src/API/api.h"
 * \brief API class for interaction with mms simulator.
 * \details API class interacts with the mms simulator through std::cout and std::cin to send and receive
 * command/information. \n
 * Member functions of this class are as follows: \n
 * mazeWidth(): 
 * mazeHeight(): 
 * wallFront(): 
 * wallRight(): 
 * wallLeft(): 
 * moveForward(): 
 * turnRight(): 
 * turnLeft(): 
 * setWall(): 
 * clearWall(): 
 * setColor(): 
 * clearColor():
 * clearAllColor():
 * setText():
 * clearText():
 * clearAllText():
 * wasReset():
 * ackReset():
 *  \headerfile maze.h
 */
class API
{
	public:
	
		//! Constructor
		API(){}
		
		//! Member function declaration
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

		//! Destructor
		~API(){}
};
}
