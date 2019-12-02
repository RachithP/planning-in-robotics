//!Group 10 - fp
//! \file landbasedwheeled.h

#pragma once
#include <iostream>
//!Including basic LandBasedRobot header file.
#include "../LandBasedRobot/landbasedrobot.h" 

namespace fp //!Defining common namespace fp.
{
class LandBasedWheeled : public LandBasedRobot //!Creating LandBasedWheeled class by deriving from existing LandBasedRobot class.
{
	public:        
        //!Constructor of wheeled land based robot with name, coordinates, number and type of wheels.
		LandBasedWheeled(std::string, int, int, int wheel_number=0);
        
		//!Accessors or Getters.        
		//!Accessor for wheel number. Returns number of wheels.
		int get_wheel_number() const{
			return wheel_number_; //Returns number of wheels
		}
        
		//!Setters or Mutators.
		//!Setter for wheel_number.
		void set_wheel_number(int wheel_number){
			wheel_number_ = wheel_number; //Assigns wheel number to Robot attribute value
		}
        
		//!Function Prototyping
		//!The robot can increase it's speed, which is translated by the number of 
        //!cells in the maze that the robot can traverse in each step.
        void SpeedUp(int);								//! Increase speed==number of cells in the maze that the robot can traverse per step. 
		virtual void MoveForward() override;       		//! Move the robot forward in the maze.
		virtual void TurnLeft() override;   			//! Turn Robot 90 deg counter-clockwise direction.
		virtual void TurnRight() override;  			//! Turn Robot 90 deg clockwise direction.
        
		//!LandBasedWheeled destructor.
		virtual ~LandBasedWheeled(){}
		
	protected: //!Land Based Wheeled robot attributes included in protected class section.
		int wheel_number_; //!Number of wheels mounted on the robot.
		
}; //end of LandBasedWheeled class
} //end of namespace fp