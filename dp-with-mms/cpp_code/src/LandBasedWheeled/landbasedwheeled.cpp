//! \file landbasedwheeled.cpp

#include "../LandBasedWheeled/landbasedwheeled.h" //!Includes LandBaseTracked header file.
#include "../API/api.h" //!Includes API header file.
#include "../Direction/direction.h"

/** @brief Constructor Implementation for LandBasedWheeled */
fp::LandBasedWheeled::LandBasedWheeled(std::string name, int x, int y, int wheel_number): LandBasedRobot(name, x, y), wheel_number_{wheel_number}{
	std::cout << "LandBasedWheeled::LandBasedWheeled is called\n";
}

/** @brief When MoveForward is called, simulator API function called to move robot forward */
void fp::LandBasedWheeled::MoveForward()
{
	std::cout<<"LandBasedWheeled::MoveForward is called"<<std::endl;
	API::moveForward();
}

/** @brief When TurnLeft is called, simulator API function is called to turn robot counter-clockwise */
/** @details TurnLeft function will rotate robot counter-clockwise 90 degrees each time the function is called.
 * When the rotation occurs, the heading is updated for future operations to reflect the direction of the robot
 */
void fp::LandBasedWheeled::TurnLeft()
{
	std::cout<<"LandBasedWheeled::TurnLeft is called"<<std::endl;
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
void fp::LandBasedWheeled::TurnRight()
{
	std::cout<<"LandBasedWheeled::TurnRight is called"<<std::endl;
	API::turnRight();
	switch(direction_){
		case Direction::NORTH : direction_ = Direction::EAST ; break;
		case Direction::EAST  : direction_ = Direction::SOUTH; break;
		case Direction::SOUTH : direction_ = Direction::WEST ; break;
		case Direction::WEST  : direction_ = Direction::NORTH; break;
	}
}

/** @brief FUNCTION ONLY IN LANDBASEDWHEELED. */
void fp::LandBasedWheeled::SpeedUp(int delta){ //! Implements the speed increases in robot.
	std::cout<<"LandBasedWheeled::SpeedUp is called"<<std::endl; //!When SpeedUp is called, cout output is activated to identify SpeedUp.
}