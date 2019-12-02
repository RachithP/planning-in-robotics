#include "algorithm.h"
#include "../API/api.h"

fp::Algorithm::Algorithm(fp::Maze* maze_ptr)
{
	API::clearAllColor();
	API::setColor(0, 0, 'G');
	//! Color center of the maze with Green
	maze_ptr->colorCenter('G');
	maze_ptr->textCenter("G");
	API::setText(0, 0, "S");
}

bool fp::Algorithm::followPath(fp::Maze* maze_ptr, fp::LandBasedRobot* wheel_robot)
{
	auto it=path_.begin()+1; //! Starting from robot's next position for execution
	
	//! loop until the end of path is reached, but if you get a wall in between, stop and return false
	while( it!=path_.end() )
	{
		// If robot is not able to move i.e encountered a wall in its path, return false
		if( not moveRobot(it->first, it->second, maze_ptr, wheel_robot) ){
			return false;
		}
		// After moving to the next cell, read all the walls present in that cell
		maze_ptr->readWall(wheel_robot->get_x(), wheel_robot->get_y(), wheel_robot->get_direction());
		
		++it;// Move to the next cell in path
	}
	return true;
}

bool fp::Algorithm::moveRobot(int next_x, int next_y, fp::Maze* maze_ptr, fp::LandBasedRobot* wheel_robot)
{
	int delta_x = next_x - wheel_robot->get_x(); //find the difference in x values of next cell we need to navigate to and the curr x of the robot
	int delta_y = next_y - wheel_robot->get_y(); //find the difference in y values of next cell we need to navigate to and the curr y of the robot
		
	// Determine the direction based on curr robot direction
	if( delta_x==1 and delta_y==0 ){ // We need to move to the right cell (this is w.r.t. global coordinate system)
		// Check if you can move to the cell or not ==> Check is wall is in your next movement direction
		if( maze_ptr->isWall(wheel_robot->get_x(), wheel_robot->get_y(), fp::Direction::EAST) ) return false;
		// Change the coordinates of the robot
		wheel_robot->set_x(next_x);
		// Print on the mms output window
		std::cerr <<  "Moving to (" << next_x << "," << next_y << ")" << std::endl;
		// Depending on the current direction of the robot, choose appropriate set of actions
		switch( wheel_robot->get_direction() ){
			case fp::Direction::NORTH :
				wheel_robot->TurnRight();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::EAST :
				wheel_robot->MoveForward();
				break;
			case fp::Direction::SOUTH :
				wheel_robot->TurnLeft();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::WEST :
				wheel_robot->TurnRight();
				wheel_robot->TurnRight();
				wheel_robot->MoveForward();
				break;
		}
	}
	else if( delta_x==0 and delta_y==1 ){ // We need to move to the upper cell (this is w.r.t. global coordinate system)
		// Check if you can move to the cell or not ==> Check is wall is in your next movement direction
		if( maze_ptr->isWall(wheel_robot->get_x(), wheel_robot->get_y(), fp::Direction::NORTH) ) return false;
		// Change the coordinates of the robot	
		wheel_robot->set_y(next_y);
		// Print on the mms output window
		std::cerr <<  "Moving to (" << next_x << "," << next_y << ")" << std::endl;
		// Depending on the current direction of the robot, choose appropriate set of actions
		switch( wheel_robot->get_direction() ){
			case fp::Direction::NORTH :
				wheel_robot->MoveForward();
				break;
			case fp::Direction::EAST :
				wheel_robot->TurnLeft();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::SOUTH :
				wheel_robot->TurnLeft();
				wheel_robot->TurnLeft();
				wheel_robot->MoveForward();				
				break;
			case fp::Direction::WEST :
				wheel_robot->TurnRight();
				wheel_robot->MoveForward();
				break;
		}
	}
	else if( delta_x==-1 and delta_y==0 ){ // We need to move to the left cell (this is w.r.t. global coordinate system)
		// Check if you can move to the cell or not ==> Check is wall is in your next movement direction
		if( maze_ptr->isWall(wheel_robot->get_x(), wheel_robot->get_y(), fp::Direction::WEST) ) return false;
		// Change the coordinates of the robot
		wheel_robot->set_x(next_x);
		// Print on the mms output window
		std::cerr <<  "Moving to (" << next_x << "," << next_y << ")" << std::endl;
		// Depending on the current direction of the robot, choose appropriate set of actions
		switch( wheel_robot->get_direction() ){
			case fp::Direction::NORTH :
				wheel_robot->TurnLeft(); 
				wheel_robot->MoveForward();
				break;
			case fp::Direction::EAST :
				wheel_robot->TurnLeft();
				wheel_robot->TurnLeft();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::SOUTH :
				wheel_robot->TurnRight();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::WEST :
				wheel_robot->MoveForward();
				break;
		}
	}
	else if( delta_x==0 and delta_y==-1 ){ // We need to move to the bottom cell (this is w.r.t. global coordinate system)
		// Check if you can move to the cell or not ==> Check is wall is in your next movement direction
		if( maze_ptr->isWall(wheel_robot->get_x(), wheel_robot->get_y(), fp::Direction::SOUTH) ) return false;
		// Change the coordinates of the robot	
		wheel_robot->set_y(next_y);
		// Print on the mms output window
		std::cerr <<  "Moving to (" << next_x << "," << next_y << ")" << std::endl;
		// Depending on the current direction of the robot, choose appropriate set of actions
		switch( wheel_robot->get_direction() ){
			case fp::Direction::NORTH :
				wheel_robot->TurnLeft();
				wheel_robot->TurnLeft();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::EAST :
				wheel_robot->TurnRight();
				wheel_robot->MoveForward();
				break;
			case fp::Direction::SOUTH :
				wheel_robot->MoveForward();				
				break;
			case fp::Direction::WEST :
				wheel_robot->TurnLeft();
				wheel_robot->MoveForward();
				break;
		}
	}
	return true;
}

void fp::Algorithm::printPath()
{
	std::cerr << "The path is as follows:" << std::endl;
	for(auto it=path_.begin(); it!=path_.end(); ++it)
	{
		std::cerr << it->first << ", " << it->second << std::endl;
	}
}

void fp::Algorithm::colorPath()
{
	for(auto it=path_.begin(); it!=path_.end(); ++it)
	{
		API::setColor(it->first, it->second, 'G');
	}
}