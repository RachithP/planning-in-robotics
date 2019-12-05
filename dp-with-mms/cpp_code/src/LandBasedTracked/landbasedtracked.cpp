//! \file landbasedtracked.cpp

#include "../LandBasedTracked/landbasedtracked.h" //!Includes LandBaseTracked header file.
#include "../API/api.h" //!Includes API header file.
#include "../Direction/direction.h"

/** @brief Constructor implementation for LandBasedTracked robot using LandBasedRobot as derived object */
fp::LandBasedTracked::LandBasedTracked(std::string name, int x, int y, std::string track_type): LandBasedRobot(name, x, y), track_type_{track_type}{
	std::cout << "LandBasedTracked::LandBasedTracked is called\n";
}

/** @brief When MoveForward is called, simulator API function called to move robot forward */
void fp::LandBasedTracked::MoveForward()
{
	std::cout<<"LandBasedTracked::MoveForward is called"<<std::endl;
	API::moveForward();
}

/** @brief When TurnLeft is called, simulator API function is called to turn robot counter-clockwise */
/** @details TurnLeft function will rotate robot counter-clockwise 90 degrees each time the function is called.
 * When the rotation occurs, the heading is updated for future operations to reflect the direction of the robot
 */
void fp::LandBasedTracked::TurnLeft()
{
	std::cout<<"LandBasedTracked::TurnLeft is called"<<std::endl;
	API::turnLeft();
	switch(direction_){
		case Direction::NORTH : direction_ = Direction::WEST ; break;
		case Direction::EAST  : direction_ = Direction::NORTH; break;
		case Direction::SOUTH : direction_ = Direction::EAST ; break;
		case Direction::WEST  : direction_ = Direction::SOUTH; break;
	}
}

/** @brief When TurnRight is called, simulator API function is called to turn robot clockwise */
/** @details TurnRight function will rotate robot clockwise 90 degrees each time the function is called.
 * When the rotation occurs, the heading is updated for future operations to reflect the direction of the robot.
 */
void fp::LandBasedTracked::TurnRight()
{
	std::cout<<"LandBasedTracked::TurnRight is called"<<std::endl;
	API::turnRight();
	switch(direction_){
		case Direction::NORTH : direction_ = Direction::EAST ; break;
		case Direction::EAST  : direction_ = Direction::SOUTH; break;
		case Direction::SOUTH : direction_ = Direction::WEST ; break;
		case Direction::WEST  : direction_ = Direction::NORTH; break;
	}
}