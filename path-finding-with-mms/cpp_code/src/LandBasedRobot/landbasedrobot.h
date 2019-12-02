//! \file landbasedrobot.h

#pragma once
#include <iostream>
#include <string>

namespace fp //! fp namespace defined for all classes.
{
class LandBasedRobot //! Creating basic Land Based Robot class.
{
public: //! Public access of class methods.

    //! Land Based Robot class constructor.
    LandBasedRobot(std::string name = "none",
        int x = 0,
        int y = 0,
        double speed = 0.0,
        double width = 0.0,
        double length = 0.0,
        double height = 0.0,
        double capacity = 0.0,
		char direction = 'n');
		
    //! Accessors or Getters for position and action
    //! Accessor to get x.
    int get_x() const{return x_;} //! Returns value for Robot X position.
    //! Accessor to get y.
    int get_y() const{return y_;} //! Returns value for Robot Y position.
    //! Accessor to get name.
    std::string get_name() const{return name_;} //! Returns name of the Robot.
	//! Accessor to get speed.
    double get_speed() const{return speed_;} //! Returns value for Robot speed.
	//! Accessor to get width.
    double get_width() const{return width_;} //! Returns value for Robot X width.
	//! Accessor to get length.
    double get_length() const{return length_;} //! Returns value for Robot X length.
	//! Accessor to get height.
    double get_height() const{return height_;} //! Returns value for Robot X height.
	//! Accessor to get capacity.
    double get_capacity() const{return capacity_;} //! Returns value for Robot X capacity.
	//! Accessor to get direction.
    char get_direction() const{return direction_;} //! Returns value for Robot X capacity.

    //! Mutators or Setters for position and action.
    //! Mutator to set x.
    void set_x(int x){x_ = x;} //! Sets x value to robot attribute for x-maze position.
    //! Mutator to set y.
    void set_y(int y){y_ = y;} //! Sets y to robot attribute for y-maze position.
    //! Mutator to set name string.
    void set_name(std::string name){name_ = name;} //! Sets name string to robot attribute.
	//! Mutator to set direction
	void set_direction(char dir){direction_ = dir;} //! Sets direction of robot.

    //! Function Prototyping.
    virtual void MoveForward() = 0;       	//! Move the robot forward in the maze.
    virtual void TurnLeft() = 0;   			//! Turn Robot 90 deg counter-clockwise direction.
    virtual void TurnRight() = 0;  			//! Turn Robot 90 deg clockwise direction.

    //! Land Based Robot class destructor.
    virtual ~LandBasedRobot(){}

protected:             //! Protected access for all robot attributes.
    std::string name_; //! Name of the Robot.
    double speed_;     //! Driving speed of the Robot.
    double width_;     //! Width of the base of the Robot.
    double length_;    //! Lengh of the base of the Robot.
    double height_;    //! Height of the base of the Robot.
    double capacity_;  //! Payload of the arm.
	int x_;            //! X coordinate of the robot in the maze.
    int y_;            //! Y coordinate of the robot in the maze.
	char direction_;   //! Direction that the robot is facing; 'N'(north),'E'(east),'W'(west),'S'(south).
}; // End of the LandBasedRobot class
} // End of namespace fp