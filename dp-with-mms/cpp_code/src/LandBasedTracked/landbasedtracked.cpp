//! \file landbasedtracked.cpp

#include "../LandBasedTracked/landbasedtracked.h" //!Includes LandBaseTracked header file.
#include "../API/api.h" //!Includes API header file.
#include "../Direction/direction.h"

//!Constructor implementation for LandBasedTracked robot using LandBasedRobot as derived object.
fp::LandBasedTracked::LandBasedTracked(std::string name, int x, int y, std::string track_type): LandBasedRobot(name, x, y), track_type_{track_type}{
	std::cout << "LandBasedTracked::LandBasedTracked is called\n";
}

void fp::LandBasedTracked::MoveForward() //!Move Robot Forward
{
	std::cout<<"LandBasedTracked::MoveForward is called"<<std::endl;  //!When right is called, cout output is activated identifying TurnRight.
	API::moveForward();
}

void fp::LandBasedTracked::TurnLeft() //!Turn Robot 90 deg counter-clockwise direction.
{
	std::cout<<"LandBasedTracked::TurnLeft is called"<<std::endl;  //!When left is called, cout output is activated identifying TurnLeft.
	API::turnLeft();
	switch(direction_){
		case fp::Direction::NORTH : direction_ = fp::Direction::WEST ; break;
		case fp::Direction::EAST  : direction_ = fp::Direction::NORTH; break;
		case fp::Direction::SOUTH : direction_ = fp::Direction::EAST ; break;
		case fp::Direction::WEST  : direction_ = fp::Direction::SOUTH; break;
	}
}

void fp::LandBasedTracked::TurnRight() //!Turn Robot 90 deg clockwise direction.
{
	std::cout<<"LandBasedTracked::TurnRight is called"<<std::endl;  //!When right is called, cout output is activated identifying TurnRight.
	API::turnRight();
	switch(direction_){
		case fp::Direction::NORTH : direction_ = fp::Direction::EAST ; break;
		case fp::Direction::EAST  : direction_ = fp::Direction::SOUTH; break;
		case fp::Direction::SOUTH : direction_ = fp::Direction::WEST ; break;
		case fp::Direction::WEST  : direction_ = fp::Direction::NORTH; break;
	}
}