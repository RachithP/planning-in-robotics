//! \file landbasedrobot.h

#pragma once
#include <iostream>
#include <string>

/** @brief fp namespace defined for all classes */
namespace fp{

/** @brief Creating basic Land Based Robot class */
class LandBasedRobot{
    
/** @brief Public access of class methods */
public:

    LandBasedRobot(std::string name = "none",
        int x = 0,
        int y = 0,
        double speed = 0.0,
        double width = 0.0,
        double length = 0.0,
        double height = 0.0,
        double capacity = 0.0,
		char direction = 'n');
		
    /** @brief Accessors or Getters for position and action */
    /** @brief Accessor to get x. @return Value for robot X position */
    int get_x() const{return x_;}
    
    /** @brief Accessor to get y. @return Value for robot Y position */
    int get_y() const{return y_;}
    
    /** @brief Accessor to get name. @return String for robot name */
    std::string get_name() const{return name_;}
    
	/** @brief Accessor to get speed. @return double for current robot speed */
    double get_speed() const{return speed_;}
    
	/** @brief Accessor to get width. @return double for robot chassis width */
    double get_width() const{return width_;}
    
	/** @brief Accessor to get length. @return double for robot chassis length */
    double get_length() const{return length_;}
    
	/** @brief Accessor to get height. @return double for robot chassis height */
    double get_height() const{return height_;}
    
	/** @brief Accessor to get capacity. @return double to get robot payload capacity */
    double get_capacity() const{return capacity_;}
    
	/** @brief Accessor to get direction. @return char for robot heading */
    char get_direction() const{return direction_;}

    /** @brief Mutators or Setters for position and action */
    /** @details Mutator to set x. Sets x value to robot attribute for x-maze position */
    void set_x(int x){x_ = x;}
    
    /** @details Mutator to set y. Sets Y value to robot attribute for y-maze position */
    void set_y(int y){y_ = y;}
    
    /** @details Mutator to set name string. Sets name string to robot attribute */
    void set_name(std::string name){name_ = name;}

    /** @brief Function Prototyping for movement */
    /** MoveForward. Move robot forward in maze
     *  TurnLeft. Turn robot 90 deg counter-clockwise
     *  TurnRight. Turn robot 90 deg clockwise
     */
    virtual void MoveForward() = 0;
    virtual void TurnLeft() = 0;
    virtual void TurnRight() = 0;

    /** @brief Land Based Robot class destructor */
    virtual ~LandBasedRobot(){}

protected:             
    std::string name_;
    double speed_;
    double width_;
    double length_;
    double height_;
    double capacity_;
	int x_;
    int y_;
	char direction_;
}; // End of the LandBasedRobot class
} // End of namespace fp