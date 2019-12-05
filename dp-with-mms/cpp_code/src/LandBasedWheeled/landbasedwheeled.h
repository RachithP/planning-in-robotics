//!Group 10 - fp
//! \file landbasedwheeled.h

#pragma once
#include <iostream>
//!Including basic LandBasedRobot header file.
#include "../LandBasedRobot/landbasedrobot.h" 

namespace fp /** @brief Defining common namespace fp. */
{
class LandBasedWheeled : public LandBasedRobot /** Creating LandBasedWheeled class by deriving from existing LandBasedRobot class. */
{	
	public:        
        /** @brief Constructor of wheeled land based robot with name, coordinates, number and type of wheels. */
		LandBasedWheeled(std::string, int, int, int wheel_number=0);
        
		/** Accessors or Getters */
		/** @brief Accessor for wheel number. */
        /** @return wheel_number_: Number of wheels on robot. */ 
		int get_wheel_number() const{
			return wheel_number_; //Returns number of wheels
		}
        
		/** Setters or Mutators */
		/** @brief Setter for wheel_number */
		void set_wheel_number(int wheel_number){
			wheel_number_ = wheel_number; //Assigns wheel number to Robot attribute value
		}
        
		/** @brief Function Prototyping */
		/** @details The robot can increase it's speed, which is translated by the number of 
         * cells in the maze that the robot can traverse in each step.
         * 
         *  SpeedUp(int): Increase speed==number of cells in the maze that the robot can traverse per step
         *  MoveForward(): Move the robot forward in the maze
         *  TurnLeft(): Turns robot 90 degrees counter-clockwise direction
         *  TurnRight(): Turns robot 90 degrees clockwise direction
         */
        void SpeedUp(int); 
		virtual void MoveForward() override;
		virtual void TurnLeft() override; 
		virtual void TurnRight() override;
        
		/** @brief LandBasedWheeled destructor */
		virtual ~LandBasedWheeled(){}
		
        /** @brief Land Based Wheeled robot attributes included in protected class section */
        /** @param wheel_number_: number of wheels mounted on robot */
	protected: 
		int wheel_number_;
		
}; //end of LandBasedWheeled class
} //end of namespace fp