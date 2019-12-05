//! \file landbasedwheeled.cpp

#include "../LandBasedWheeled/landbasedwheeled.h" //!Includes LandBasedWheeled header file.
#include "../API/api.h"
#include "../Direction/direction.h"

//! Constructor Implementation for LandBasedWheeled
fp::LandBasedWheeled::LandBasedWheeled(std::string name, int x, int y, int wheel_number): LandBasedRobot(name, x, y), wheel_number_{wheel_number}{
	std::cout << "LandBasedWheeled::LandBasedWheeled is called\n";
}

void fp::LandBasedWheeled::MoveForward() //!Turn Robot 90 deg clockwise direction.
{
	std::cout<<"LandBasedWheeled::MoveForward is called"<<std::endl;  //!When right is called, cout output is activated identifying TurnRight.
	API::moveForward();
}

void fp::LandBasedWheeled::TurnLeft() //!Turn Robot 90 deg counter-clockwise direction.
{
	std::cout<<"LandBasedWheeled::TurnLeft is called"<<std::endl;  //!When left is called, cout output is activated identifying TurnLeft.
	API::turnLeft();
	switch(direction_){
		case fp::Direction::NORTH : direction_ = fp::Direction::WEST ; break;
		case fp::Direction::EAST  : direction_ = fp::Direction::NORTH; break;
		case fp::Direction::SOUTH : direction_ = fp::Direction::EAST ; break;
		case fp::Direction::WEST  : direction_ = fp::Direction::SOUTH; break;
	}
}
void fp::LandBasedWheeled::TurnRight() //!Turn Robot 90 deg clockwise direction.
{
	std::cout<<"LandBasedWheeled::TurnRight is called"<<std::endl;  //!When right is called, cout output is activated identifying TurnRight.
	API::turnRight();
	switch(direction_){
		case fp::Direction::NORTH : direction_ = fp::Direction::EAST ; break;
		case fp::Direction::EAST  : direction_ = fp::Direction::SOUTH; break;
		case fp::Direction::SOUTH : direction_ = fp::Direction::WEST ; break;
		case fp::Direction::WEST  : direction_ = fp::Direction::NORTH; break;
	}
}

//! FUNCTION ONLY IN LANDBASEDWHEELED.
void fp::LandBasedWheeled::SpeedUp(int delta){ //! Implements the speed increases in robot.
	std::cout<<"LandBasedWheeled::SpeedUp is called"<<std::endl; //!When SpeedUp is called, cout output is activated to identify SpeedUp.
}