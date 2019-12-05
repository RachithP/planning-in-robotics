//!Group 10 - fp
//! \file landbasedrobot.cpp


#include "landbasedrobot.h" //!Includes basic LandBasedRobot header file for methods and attribute access.

fp::LandBasedRobot::LandBasedRobot(std::string name, int x, int y, double speed, double width, double length, double height, double capacity, char direction)
: name_{name}, speed_{speed}, width_{width}, length_{length}, height_{height}, capacity_{capacity}, x_{x}, y_{y}, direction_{direction}{}